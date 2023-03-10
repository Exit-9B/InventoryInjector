#pragma once

#include "Rule.h"

#include <json/json.h>

namespace Data
{
	class CustomDataParser
	{
	public:
		CustomDataParser(const std::string& a_name) : _name{ a_name } {}

		void Parse(const Json::Value& a_value, ICustomDataContainer* a_customData) const;

		virtual void ParseString(const Json::String& a_value, ICustomDataContainer* a_customData)
			const;

	protected:
		std::string _name;
	};

	class IconColorParser final : public CustomDataParser
	{
	public:
		using CustomDataParser::CustomDataParser;

		void ParseString(const Json::String& a_value, ICustomDataContainer* a_customData)
			const override;
	};

	class SubTypeParser final : public CustomDataParser
	{
	public:
		SubTypeParser(const std::string& a_name, RE::FormType a_formType)
			: CustomDataParser(a_name),
			  _formType{ a_formType }
		{
		}

		void ParseString(const Json::String& a_value, ICustomDataContainer* a_customData)
			const override;

	private:
		RE::FormType _formType;
	};

	class WeightClassParser final : public CustomDataParser
	{
	public:
		using CustomDataParser::CustomDataParser;

		void ParseString(const Json::String& a_value, ICustomDataContainer* a_customData)
			const override;
	};
}
