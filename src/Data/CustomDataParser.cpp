#include "CustomDataParser.h"

namespace Data
{
	void CustomDataParser::Parse(
		const Json::Value& a_value,
		std::function<AddCustomData_t> a_addCustomData) const
	{
		if (a_value.isBool()) {
			a_addCustomData(_name, a_value.asBool());
		}
		else if (a_value.isNumeric()) {
			a_addCustomData(_name, a_value.asDouble());
		}
		else if (a_value.isString()) {
			ParseString(a_value.asString(), a_addCustomData);
		}
	}

	void CustomDataParser::ParseString(
		const Json::String& a_value,
		std::function<AddCustomData_t> a_addCustomData) const
	{
		RE::GFxValue str;
		str.SetString(*_stringCache.insert(a_value).first);
		a_addCustomData(_name, str);
	}

	void IconColorParser::ParseString(
		const Json::String& a_value,
		std::function<AddCustomData_t> a_addCustomData) const
	{
		a_addCustomData("iconColor", ParseColor(a_value));
	}

	std::uint32_t IconColorParser::ParseColor(std::string_view a_hexCode)
	{
		if (a_hexCode.empty()) {
			return 0x000000;
		}

		std::size_t prefix = a_hexCode[0] == '#' ? 1 : 0;
		a_hexCode.remove_prefix(prefix);
		return static_cast<std::uint32_t>(std::stoll(std::string(a_hexCode), nullptr, 16));
	}

	void SubTypeParser::ParseString(
		const Json::String& a_value,
		std::function<AddCustomData_t> a_addCustomData) const
	{
		std::int32_t type = -1;
		std::wstring displayStr;

		switch (_formType) {
		case RE::FormType::Misc:
			type = util::to_underlying(MiscSubTypeMap[a_value]);
			displayStr = MiscSubTypeDisplayMap[a_value].c_str();
			break;
		case RE::FormType::Weapon:
			type = util::to_underlying(WeaponSubTypeMap[a_value]);
			displayStr = WeaponSubTypeDisplayMap[a_value].c_str();
			break;
		}

		if (type != -1) {
			a_addCustomData("subType", type);

			if (!displayStr.empty()) {
				displayStr = util::Translate(displayStr);

				RE::GFxValue str;
				str.SetStringW(*_wstringCache.insert(displayStr).first);
				a_addCustomData("subTypeDisplay", str);
			}

			return;
		}

		CustomDataParser::ParseString(a_value, a_addCustomData);
	}

	void SubTypeDisplayParser::ParseString(
		const Json::String& a_value,
		std::function<AddCustomData_t> a_addCustomData) const
	{
		std::wstring displayStr = util::utf8_to_utf16(a_value).value_or(L"");
		displayStr = util::Translate(displayStr);

		if (!displayStr.empty()) {
			RE::GFxValue str;
			str.SetStringW(*_wstringCache.insert(displayStr).first);
			a_addCustomData("subTypeDisplay", str);
		}
	}
}
