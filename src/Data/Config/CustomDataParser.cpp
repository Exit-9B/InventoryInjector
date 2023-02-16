#include "CustomDataParser.h"

#include "Data/Defines/Ammo.h"
#include "Data/Defines/Armor.h"
#include "Data/Defines/Book.h"
#include "Data/Defines/Misc.h"
#include "Data/Defines/Potion.h"
#include "Data/Defines/SoulGem.h"
#include "Data/Defines/Weapon.h"

namespace Data
{
	void CustomDataParser::Parse(const Json::Value& a_value, ICustomDataContainer* a_customData)
		const
	{
		if (a_value.isBool()) {
			a_customData->AddCustomData(_name, a_value.asBool());
		}
		else if (a_value.isNumeric()) {
			a_customData->AddCustomData(_name, a_value.asDouble());
		}
		else if (a_value.isString()) {
			ParseString(a_value.asString(), a_customData);
		}
	}

	void CustomDataParser::ParseString(
		const Json::String& a_value,
		ICustomDataContainer* a_customData) const
	{
		RE::GFxValue str;
		str.SetString(*_stringCache.insert(a_value).first);
		a_customData->AddCustomData(_name, str);
	}

	void IconColorParser::ParseString(
		const Json::String& a_value,
		ICustomDataContainer* a_customData) const
	{
		a_customData->AddCustomData("iconColor", ParseColor(a_value));
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
		ICustomDataContainer* a_customData) const
	{
		std::int32_t type = -1;
		std::wstring displayStr;

		switch (_formType) {
		case RE::FormType::Armor:
			util::try_get(ArmorSubTypeMap, a_value, type) &&
				util::try_get(ArmorSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Book:
			util::try_get(BookSubTypeMap, a_value, type) &&
				util::try_get(BookSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Misc:
			util::try_get(MiscSubTypeMap, a_value, type) &&
				util::try_get(MiscSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Weapon:
			util::try_get(WeaponSubTypeMap, a_value, type) &&
				util::try_get(WeaponSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Ammo:
			util::try_get(AmmoSubTypeMap, a_value, type) &&
				util::try_get(AmmoSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::AlchemyItem:
			util::try_get(PotionSubTypeMap, a_value, type) &&
				util::try_get(PotionSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::SoulGem:
			util::try_get(SoulGemSubTypeMap, a_value, type) &&
				util::try_get(SoulGemSubTypeDisplayMap, a_value, displayStr);
			break;
		}

		if (type != -1) {
			a_customData->AddCustomData("subType", type);

			if (!displayStr.empty()) {
				displayStr = util::Translate(displayStr);

				RE::GFxValue str;
				str.SetStringW(*_wstringCache.insert(displayStr).first);
				a_customData->AddCustomData("subTypeDisplay", str);
			}

			return;
		}

		CustomDataParser::ParseString(a_value, a_customData);
	}

	void SubTypeDisplayParser::ParseString(
		const Json::String& a_value,
		ICustomDataContainer* a_customData) const
	{
		std::wstring displayStr = util::utf8_to_utf16(a_value).value_or(L"");
		displayStr = util::Translate(displayStr);

		if (!displayStr.empty()) {
			RE::GFxValue str;
			str.SetStringW(*_wstringCache.insert(displayStr).first);
			a_customData->AddCustomData("subTypeDisplay", str);
		}
	}
}
