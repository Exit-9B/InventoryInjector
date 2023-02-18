#include "Property.h"

#include "Data/Defines/Armor.h"

namespace Data
{
	bool AnyOfProperty::Match(const RE::GFxValue& a_value) const
	{
		for (const auto& subProperty : _subProperties) {
			if (subProperty->Match(a_value)) {
				return true;
			}
		}
		return false;
	}

	void AnyOfProperty::AddProperty(
		[[maybe_unused]] const std::string& a_name,
		std::shared_ptr<Property> a_property)
	{
		_subProperties.push_back(a_property);
	}

	bool MatchProperty::Match(const RE::GFxValue& a_value) const
	{
		if (a_value.IsArray()) {
			for (std::uint32_t i = 0, size = a_value.GetArraySize(); i < size; i++) {
				RE::GFxValue elem;
				a_value.GetElement(i, &elem);
				if (a_value == _value) {
					return true;
				}
			}
		}

		return a_value == _value;
	}

	bool RangeProperty::Match(const RE::GFxValue& a_value) const
	{
		if (!a_value.IsNumber()) {
			return false;
		}

		auto value = a_value.GetNumber();

		if (_min.has_value() && value < _min.value()) {
			return false;
		}

		if (_max.has_value() && value > _max.value()) {
			return false;
		}

		return true;
	}

	bool BitfieldProperty::Match(const RE::GFxValue& a_value) const
	{
		if (!a_value.IsNumber()) {
			return false;
		}

		auto value = static_cast<std::uint32_t>(a_value.GetNumber());
		return value & _flags;
	}

	bool KeywordsProperty::Match(const RE::GFxValue& a_value) const
	{
		RE::GFxValue hasKeyword;
		a_value.GetMember(_keyword.c_str(), &hasKeyword);

		return hasKeyword.IsBool() && hasKeyword.GetBool();
	}

	bool MainPartProperty::Match(const RE::GFxValue& a_value) const
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
}
