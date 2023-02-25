#include "Rule.h"

namespace Data
{
	void Rule::AddProperty(const std::string& a_name, std::shared_ptr<Property> a_property)
	{
		_properties[a_name] = a_property;
	}

	void Rule::AddCustomData(const std::string& a_name, const CustomData& a_data)
	{
		_customData[a_name] = a_data;
	}

	bool Rule::Validate()
	{
		if (auto i = _customData.find("iconSource"s); i != _customData.end()) {
			auto& data = i->second;

			bool isSourceValid =
				std::holds_alternative<std::string>(data) &&
				ValidateIconSource(std::get<std::string>(data));

			if (!isSourceValid) {
				_customData.erase(i);
				_customData.erase("iconLabel"s);
			}
		}
		else if (_customData.contains("iconLabel"s)) {
			_customData.insert({ "iconSource"s, nullptr });
		}

		return !_properties.empty() && !_customData.empty();
	}

	bool Rule::ValidateIconSource(std::string a_iconSource)
	{
		if (auto i = _validatedSources.find(a_iconSource); i != _validatedSources.end()) {
			return i->second;
		}

		RE::BSResourceNiBinaryStream stream{
			fmt::format("Interface/{}", a_iconSource)
		};

		bool valid = stream.good();
		_validatedSources.insert({ a_iconSource, valid });
		return valid;
	}

	void Rule::SetInfo(RE::GFxValue* a_entryObject, bool& a_needsIconUpdate) const
	{
		assert(a_entryObject);

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
		assert(a_entryObject);

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
		assert(a_entryObject);

		for (const auto& [name, prop] : _properties) {
			RE::GFxValue value;
			a_entryObject->GetMember(name.c_str(), &value);

			if (!prop->Match(value)) {
				return false;
			}
		}

		return true;
	}

	bool Rule::HasInfo() const
	{
		for (const auto& [name, data] : _customData) {
			if (name.rfind("icon", 0) != 0) {
				return true;
			}
		}

		return false;
	}
}
