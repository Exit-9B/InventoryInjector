#include "RuleParser.h"

#include "Data/Defines/Form.h"

namespace Data
{
	Rule RuleParser::ParseRule(const Json::Value& a_rule)
	{
		Rule parsed{};

		const Json::Value& properties = a_rule["properties"];
		const Json::Value& customData = a_rule["customData"];

		if (!properties.isObject() || !customData.isObject()) {
			return parsed;
		}

		[[maybe_unused]] RE::FormType formType = FormTypeMap[properties["formType"].asString()];

		for (auto& name : properties.getMemberNames()) {
			const Json::Value& prop = properties[name];

			if (const auto parser = GetPropertyParser(name)) {
				auto addProperty =
					[&parsed](const std::string& a_name, std::shared_ptr<Property> a_property)
				{
					parsed.AddProperty(a_name, a_property);
				};

				parser->Parse(prop, addProperty);
			}
		}

		for (auto& name : customData.getMemberNames()) {
			const Json::Value& val = customData[name];

			if (const auto parser = GetCustomDataParser(name, formType)) {
				auto addCustomData =
					[&parsed](const std::string& a_name, const RE::GFxValue& a_data)
				{
					parsed.AddCustomData(a_name, a_data);
				};

				parser->Parse(val, addCustomData);
			}
		}

		return parsed;
	}

	std::shared_ptr<PropertyParser> RuleParser::GetPropertyParser(const std::string& a_name)
	{
		if (a_name == "formType") {
			return std::make_shared<FormTypeParser>(a_name);
		}
		else if (a_name == "formId") {
			return std::make_shared<FormIDParser>(a_name);
		}
		else if (a_name == "mainPart") {
			return std::make_shared<MainPartParser>(a_name);
		}
		else {
			return std::make_shared<PropertyParser>(a_name);
		}
	}

	std::shared_ptr<CustomDataParser> RuleParser::GetCustomDataParser(
		const std::string& a_name,
		RE::FormType a_formType)
	{
		if (a_name == "iconColor") {
			return std::make_shared<IconColorParser>(a_name);
		}
		else if (a_name == "subType") {
			return std::make_shared<SubTypeParser>(a_name, a_formType);
		}
		else if (a_name == "subTypeDisplay") {
			return std::make_shared<SubTypeDisplayParser>(a_name);
		}
		else {
			return std::make_shared<CustomDataParser>(a_name);
		}
	}
}
