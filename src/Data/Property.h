#pragma once

#include "Data/Defines.h"

namespace Data
{
	class Property
	{
	public:
		[[nodiscard]] virtual bool Match(const RE::GFxValue& a_value) const = 0;
	};

	class AnyOfProperty final : public Property
	{
	public:
		bool Match(const RE::GFxValue& a_value) const override
		{
			for (const auto& subProperty : _subProperties) {
				if (subProperty->Match(a_value)) {
					return true;
				}
			}
			return false;
		}

		void AddProperty(std::shared_ptr<Property> a_subProperty)
		{
			_subProperties.push_back(a_subProperty);
		}

	private:
		std::vector<std::shared_ptr<Property>> _subProperties;
	};

	class MatchProperty final : public Property
	{
	public:
		MatchProperty(bool a_boolean) : _value{ a_boolean } {}
		MatchProperty(double a_number) : _value{ a_number } {}
		MatchProperty(std::int32_t a_number) : _value{ a_number } {}
		MatchProperty(std::uint32_t a_number) : _value{ a_number } {}

		MatchProperty(std::string_view a_string)
			: _cachedString{ a_string },
			  _value{ _cachedString }
		{
		}

		bool Match(const RE::GFxValue& a_value) const override { return a_value == _value; }

	private:
		std::string _cachedString;
		RE::GFxValue _value;
	};

	class MainPartProperty final : public Property
	{
	public:
		MainPartProperty(std::uint32_t a_slot) : _slot{ a_slot } {}

		bool Match(const RE::GFxValue& a_value) const override
		{
			if (!a_value.IsNumber()) {
				return false;
			}

			auto value = static_cast<std::uint32_t>(a_value.GetNumber());

			std::uint32_t mainPart = 0;
			for (std::uint32_t i = 0; i < PartMaskPrecedence.size(); i++) {
				auto slot = static_cast<std::uint32_t>(PartMaskPrecedence[i]);
				if (value & slot) {
					mainPart = slot;
					break;
				}
			}

			return mainPart && _slot == mainPart;
		}

	private:
		std::uint32_t _slot;
	};
}
