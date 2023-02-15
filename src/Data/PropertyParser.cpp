#include "PropertyParser.h"

#include "Data/Defines.h"

namespace Data
{
	void PropertyParser::Parse(
		const Json::Value& a_spec,
		std::function<AddProperty_t> a_addProperty) const
	{
		if (a_spec.isNumeric()) {
			ParseNumber(a_spec.asDouble(), a_addProperty);
		}
		if (a_spec.isString()) {
			ParseString(a_spec.asString(), a_addProperty);
		}
		else if (a_spec.isObject()) {
			const Json::Value& anyOf = a_spec["anyOf"];
			if (anyOf.isArray()) {
				auto prop = std::make_shared<AnyOfProperty>();
				for (auto& a_subSpec : anyOf) {
					Parse(
						a_subSpec,
						[prop](const std::string&, std::shared_ptr<Property> a_property)
						{
							prop->AddProperty(a_property);
						});
				}

				a_addProperty(_name, prop);
			}
		}
	}

	void PropertyParser::ParseString(
		const Json::String& a_value,
		std::function<AddProperty_t> a_addProperty) const
	{
		a_addProperty(_name, std::make_shared<MatchProperty>(a_value));
	}

	void PropertyParser::ParseNumber(double a_value, std::function<AddProperty_t> a_addProperty)
		const
	{
		a_addProperty(_name, std::make_shared<MatchProperty>(a_value));
	}

	void FormTypeParser::ParseString(
		const Json::String& a_value,
		std::function<AddProperty_t> a_addProperty) const
	{
		if (auto it = FormTypeMap.find(a_value); it != FormTypeMap.end()) {
			auto value = it->second;
			a_addProperty("formType", std::make_shared<MatchProperty>(util::to_underlying(value)));
			return;
		}

		PropertyParser::ParseString(a_value, a_addProperty);
	}

	void FormIDParser::ParseString(
		const Json::String& a_value,
		std::function<AddProperty_t> a_addProperty) const
	{
		auto formID = ParseFormID(a_value);
		if (formID) {
			a_addProperty(
				"formId",
				std::make_shared<MatchProperty>(static_cast<std::uint32_t>(formID)));
			return;
		}

		PropertyParser::ParseString(a_value, a_addProperty);
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

	void MainPartParser::ParseNumber(double a_value, std::function<AddProperty_t> a_addProperty)
		const
	{
		auto part = static_cast<std::uint32_t>(a_value);
		if (part < 30 || part > 61) {
			logger::warn("Part number {} is out of range", part);
			return;
		}

		auto value = 1 << (part - 30);
		a_addProperty("partMask", std::make_shared<MainPartProperty>(value));
	}
}
