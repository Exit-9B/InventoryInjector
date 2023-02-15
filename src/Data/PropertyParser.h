#pragma once

#include "Data/Property.h"
#include "Data/Rule.h"

#include <json/json.h>

namespace Data
{
	using AddProperty_t = void(const std::string&, std::shared_ptr<Property>);

	class PropertyParser
	{
	public:
		PropertyParser(const std::string a_name) : _name{ a_name } {}

		void Parse(const Json::Value& a_spec, std::function<AddProperty_t> a_addProperty) const;

		virtual void ParseString(
			const Json::String& a_value,
			std::function<AddProperty_t> a_addProperty) const;

		virtual void ParseNumber(
			double a_value,
			std::function<AddProperty_t> a_addProperty) const;

	private:
		std::string _name;
	};

	class FormTypeParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(
			const Json::String& a_value,
			std::function<AddProperty_t> a_addProperty) const override;
	};

	class FormIDParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(
			const Json::String& a_value,
			std::function<AddProperty_t> a_addProperty) const override;

	private:
		static RE::FormID ParseFormID(const std::string& a_identifier);
	};

	class MainPartParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseNumber(
			double a_value,
			std::function<AddProperty_t> a_addProperty) const override;
	};
}
