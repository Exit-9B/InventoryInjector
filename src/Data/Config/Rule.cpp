#include "Rule.h"

namespace Data
{
	void Rule::AddProperty(const std::string& a_name, std::shared_ptr<Property> a_property)
	{
		_properties[a_name] = a_property;
	}

	void Rule::AddCustomData(const std::string& a_name, const RE::GFxValue& a_data)
	{
		_customData[a_name] = a_data;
	}

	bool Rule::IsValid() const
	{
		return !_properties.empty() && !_customData.empty();
	}

	void Rule::SetInfo(RE::GFxValue* a_entryObject, bool& a_needsIconUpdate) const
	{
		if (!Match(a_entryObject)) {
			return;
		}

		a_needsIconUpdate |= HasInfo();

		for (auto& [name, value] : _customData) {
			if (name.rfind("icon", 0) == 0) {
				continue;
			}

			a_entryObject->SetMember(name.c_str(), value);
		}
	}

	void Rule::SetIcon(RE::GFxValue* a_entryObject) const
	{
		if (!Match(a_entryObject)) {
			return;
		}

		for (auto& [name, value] : _customData) {
			if (name.rfind("icon", 0) != 0) {
				continue;
			}

			a_entryObject->SetMember(name.c_str(), value);
		}
	}

	bool Rule::Match(const RE::GFxValue* a_entryObject) const
	{
		return std::ranges::all_of(
			_properties,
			[a_entryObject](auto& p)
			{
				RE::GFxValue value;
				a_entryObject->GetMember(p.first.c_str(), &value);
				return p.second->Match(value);
			});
	}

	bool Rule::HasInfo() const
	{
		return std::ranges::any_of(
			_customData,
			[](auto& p)
			{
				return p.first.rfind("icon", 0) != 0;
			});
	}
}
