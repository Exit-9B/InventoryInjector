#pragma once

#include "Property.h"
#include "Rule.h"

#include <json/json.h>

namespace Data
{
	class PropertyParser
	{
	public:
		PropertyParser(const std::string a_name) : _name{ a_name } {}

		void Parse(const Json::Value& a_spec, IPropertyContainer* a_properties) const;

		virtual void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const;

		virtual void ParseNumber(double a_value, IPropertyContainer* a_properties) const;

	private:
		std::string _name;
	};

	class FormTypeParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const override;
	};

	class FormIDParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const override;

	private:
		static RE::FormID ParseFormID(const std::string& a_identifier);
	};

	class MainPartParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseNumber(double a_value, IPropertyContainer* a_properties) const override;
	};
}
