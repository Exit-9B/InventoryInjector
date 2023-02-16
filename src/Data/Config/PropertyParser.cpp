#include "PropertyParser.h"

#include "Data/Defines/Form.h"

namespace Data
{
	void PropertyParser::Parse(const Json::Value& a_spec, IPropertyContainer* a_properties) const
	{
		if (a_spec.isNumeric()) {
			ParseNumber(a_spec.asDouble(), a_properties);
		}
		if (a_spec.isString()) {
			ParseString(a_spec.asString(), a_properties);
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
			auto value = it->second;
			a_properties->AddProperty(
				"formType",
				std::make_shared<MatchProperty>(util::to_underlying(value)));
			return;
		}

		PropertyParser::ParseString(a_value, a_properties);
	}

	void FormIDParser::ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
		const
	{
		auto formID = ParseFormID(a_value);
		if (formID) {
			a_properties->AddProperty(
				"formId",
				std::make_shared<MatchProperty>(static_cast<std::uint32_t>(formID)));
			return;
		}

		PropertyParser::ParseString(a_value, a_properties);
	}

	RE::FormID FormIDParser::ParseFormID(const std::string& a_identifier)
	{
		std::istringstream ss{ a_identifier };
		std::string plugin, id;

		std::getline(ss, plugin, '|');
		std::getline(ss, id);
		RE::FormID rawFormID;
		std::istringstream(id) >> std::hex >> rawFormID;

		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		const auto file = dataHandler->LookupModByName(plugin);
		if (!file || file->compileIndex == 0xFF) {
			return 0x00000000;
		}

		RE::FormID formID = file->compileIndex << 24;
		formID += file->smallFileCompileIndex << 12;
		formID += rawFormID;

		return formID;
	}

	void MainPartParser::ParseNumber(double a_value, IPropertyContainer* a_properties) const
	{
		auto part = static_cast<std::uint32_t>(a_value);
		if (part < 30 || part > 61) {
			logger::warn("Part number {} is out of range", part);
			return;
		}

		auto value = 1 << (part - 30);
		a_properties->AddProperty("partMask", std::make_shared<MainPartProperty>(value));
	}
}
