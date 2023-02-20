#pragma once

#include "CustomDataParser.h"
#include "PropertyParser.h"
#include "Rule.h"

#include <json/json.h>

namespace Data
{
	class RuleParser final
	{
	public:
		RuleParser() = delete;

		[[nodiscard]] static Rule ParseRule(const Json::Value& a_rule);

	private:
		static std::shared_ptr<PropertyParser> GetPropertyParser(
			const std::string& a_name,
			RE::FormType a_formType);

		static std::shared_ptr<CustomDataParser> GetCustomDataParser(
			const std::string& a_name,
			RE::FormType a_formType);
	};
}
