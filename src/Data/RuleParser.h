#pragma once

#include "Data/CustomDataParser.h"
#include "Data/PropertyParser.h"
#include "Data/Rule.h"

#include <json/json.h>

namespace Data
{
	class RuleParser final
	{
	public:
		RuleParser() = delete;

		static Rule ParseRule(const Json::Value& a_rule);

	private:
		static std::shared_ptr<PropertyParser> GetPropertyParser(const std::string& a_name);

		static std::shared_ptr<CustomDataParser> GetCustomDataParser(
			const std::string& a_name,
			RE::FormType a_formType);
	};
}
