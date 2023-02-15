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

	void AnyOfProperty::AddProperty(std::shared_ptr<Property> a_subProperty)
	{
		_subProperties.push_back(a_subProperty);
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
