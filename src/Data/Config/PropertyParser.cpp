#include "PropertyParser.h"

#include "ParseUtil.h"

#include "Data/Defines/Form.h"

namespace Data
{
	void PropertyParser::Parse(const Json::Value& a_spec, IPropertyContainer* a_properties) const
	{
		if (a_spec.isString()) {
			ParseString(a_spec.asString(), a_properties);
		}
		else if (a_spec.isNumeric()) {
			ParseNumber(a_spec.asDouble(), a_properties);
		}
		else if (a_spec.isBool()) {
			a_properties->AddProperty(_name, std::make_shared<MatchProperty>(a_spec.asBool()));
		}
		else if (a_spec.isArray()) {
			for (auto& a_subSpec : a_spec) {
				Parse(a_subSpec, a_properties);
			}
		}
		else if (a_spec.isObject()) {
			const Json::Value& anyOf = a_spec["anyOf"];
			if (anyOf.isArray()) {
				auto prop = std::make_shared<AnyOfProperty>();
				for (auto& a_subSpec : anyOf) {
					Parse(a_subSpec, prop.get());
				}

				a_properties->AddProperty(_name, prop);
			}

			std::optional<double> min;
			std::optional<double> max;

			if (a_spec["min"].isNumeric()) {
				min = a_spec["min"].asDouble();
			}

			if (a_spec["max"].isNumeric()) {
				max = a_spec["max"].asDouble();
			}

			if (min.has_value() || max.has_value()) {
				a_properties->AddProperty(_name, std::make_shared<RangeProperty>(min, max));
			}
		}
	}

	void PropertyParser::ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
		const
	{
		a_properties->AddProperty(_name, std::make_shared<MatchProperty>(a_value));
	}

	void PropertyParser::ParseNumber(double a_value, IPropertyContainer* a_properties) const
	{
		a_properties->AddProperty(_name, std::make_shared<MatchProperty>(a_value));
	}

	void FormTypeParser::ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
		const
	{
		if (auto it = FormTypeMap.find(a_value); it != FormTypeMap.end()) {
			const auto value = util::to_underlying(it->second);
			const auto prop = std::make_shared<MatchProperty>(value);
			a_properties->AddProperty(_name, prop);
			return;
		}

		PropertyParser::ParseString(a_value, a_properties);
	}

	void FormIDParser::ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
		const
	{
		const auto formID = ParseUtil::ParseFormID(a_value);
		if (formID) {
			const auto value = static_cast<std::uint32_t>(formID);
			const auto prop = std::make_shared<MatchProperty>(value);
			a_properties->AddProperty(_name, prop);
			return;
		}

		PropertyParser::ParseString(a_value, a_properties);
	}

	void ColorParser::ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
		const
	{
		const auto prop = std::make_shared<MatchProperty>(ParseUtil::ParseColor(a_value));
		a_properties->AddProperty(_name, prop);
	}

	void KeywordsParser::ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
		const
	{
		a_properties->AddProperty(_name, std::make_shared<KeywordsProperty>(a_value));
	}

	void PartsParser::ParseNumber(double a_value, IPropertyContainer* a_properties) const
	{
		const std::uint32_t value = 1 << (static_cast<std::uint32_t>(a_value) - 30);
		a_properties->AddProperty("partMask", std::make_shared<BitfieldProperty>(value));
	}

	void MainPartParser::ParseNumber(double a_value, IPropertyContainer* a_properties) const
	{
		const auto part = static_cast<std::uint32_t>(a_value);
		if (part < 30 || part > 61) {
			logger::warn("Part number {} is out of range", part);
			return;
		}

		const auto value = 1 << (part - 30);
		a_properties->AddProperty("partMask", std::make_shared<MainPartProperty>(value));
	}
}
