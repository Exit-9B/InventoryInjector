#include "RuleParser.h"

#include "Data/Defines/Ammo.h"
#include "Data/Defines/Book.h"
#include "Data/Defines/Form.h"
#include "Data/Defines/Potion.h"

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

			if (const auto parser = GetPropertyParser(name, formType)) {
				parser->Parse(prop, &parsed);
			}
		}

		for (auto& name : customData.getMemberNames()) {
			const Json::Value& val = customData[name];

			if (const auto parser = GetCustomDataParser(name, formType)) {
				parser->Parse(val, &parsed);
			}
		}

		return parsed;
	}

	std::shared_ptr<PropertyParser> RuleParser::GetPropertyParser(
		const std::string& a_name,
		RE::FormType a_formType)
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
		else if (a_name == "parts") {
			return std::make_shared<PartsParser>(a_name);
		}
		else if (a_name == "flags") {
			switch (a_formType) {
			case RE::FormType::Book:
				return std::make_shared<BitfieldParser<BookFlag>>(a_name, BookFlagsMap);
			case RE::FormType::Ammo:
				return std::make_shared<BitfieldParser<AmmoFlag>>(a_name, AmmoFlagsMap);
			case RE::FormType::AlchemyItem:
				return std::make_shared<BitfieldParser<PotionFlag>>(a_name, PotionFlagsMap);
			}
		}

		return std::make_shared<PropertyParser>(a_name);
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
		else {
			return std::make_shared<CustomDataParser>(a_name);
		}
	}
}
