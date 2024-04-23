#pragma once

#include "Property.h"
#include "Rule.h"

#include <json/json.h>

namespace Data
{
	template <typename Enum>
	extern const util::istring_map<Enum> EnumLookup;

	class PropertyParser
	{
	public:
		PropertyParser(const std::string& a_name) : _name{ a_name } {}

		void Parse(const Json::Value& a_spec, IPropertyContainer* a_properties) const;

		virtual void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const;

		virtual void ParseNumber(double a_value, IPropertyContainer* a_properties) const;

	protected:
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
	};

	class ColorParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const override;
	};

	class KeywordsParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const override;
	};

	class PartsParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseNumber(double a_value, IPropertyContainer* a_properties) const override;
	};

	class MainPartParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseNumber(double a_value, IPropertyContainer* a_properties) const override;
	};

	template <typename T>
	class EnumParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const override;
	};

	template <typename T>
	class BitfieldParser final : public PropertyParser
	{
	public:
		using PropertyParser::PropertyParser;

		void ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
			const override;
	};

	template <typename T>
	void EnumParser<T>::ParseString(const Json::String& a_value, IPropertyContainer* a_properties)
		const
	{
		std::underlying_type_t<T> underlying{};
		if (util::try_get(EnumLookup<T>, a_value, underlying)) {
			a_properties->AddProperty(_name, std::make_shared<MatchProperty>(underlying));
			return;
		}
		// Special case used by weightClass
		else if (util::iequals(a_value, "Other"sv))
		{
			a_properties->AddProperty(_name, std::make_shared<MatchProperty>(std::nullopt));
			return;
		}

		PropertyParser::ParseString(a_value, a_properties);
	}

	template <typename T>
	void BitfieldParser<T>::ParseString(
		const Json::String& a_value,
		IPropertyContainer* a_properties) const
	{
		std::uint32_t flag = 0;
		if (util::try_get(EnumLookup<T>, a_value, flag)) {
			a_properties->AddProperty(_name, std::make_shared<BitfieldProperty>(flag));
			return;
		}

		PropertyParser::ParseString(a_value, a_properties);
	}
}
