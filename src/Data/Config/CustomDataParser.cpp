#include "CustomDataParser.h"

#include "ParseUtil.h"

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
		a_customData->AddCustomData(_name, a_value);
	}

	void IconColorParser::ParseString(
		const Json::String& a_value,
		ICustomDataContainer* a_customData) const
	{
		a_customData->AddCustomData("iconColor", ParseUtil::ParseColor(a_value));
	}

	void SubTypeParser::ParseString(
		const Json::String& a_value,
		ICustomDataContainer* a_customData) const
	{
		std::int32_t type = -1;
		std::wstring displayStr;

		switch (_formType) {
		case RE::FormType::Armor:
			util::try_get(EnumLookup<EquipType>, a_value, type) &&
				util::try_get(ArmorSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Book:
			util::try_get(EnumLookup<BookType>, a_value, type) &&
				util::try_get(BookSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Misc:
			util::try_get(EnumLookup<MiscType>, a_value, type) &&
				util::try_get(MiscSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Weapon:
			util::try_get(EnumLookup<WeaponType>, a_value, type) &&
				util::try_get(WeaponSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::Ammo:
			util::try_get(EnumLookup<AmmoType>, a_value, type) &&
				util::try_get(AmmoSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::AlchemyItem:
			util::try_get(EnumLookup<PotionType>, a_value, type) &&
				util::try_get(PotionSubTypeDisplayMap, a_value, displayStr);
			break;
		case RE::FormType::SoulGem:
			util::try_get(EnumLookup<SoulGemType>, a_value, type) &&
				util::try_get(SoulGemSubTypeDisplayMap, a_value, displayStr);
			break;
		}

		if (type != -1) {
			a_customData->AddCustomData("subType", type);

			if (!displayStr.empty()) {
				a_customData->AddCustomData("subTypeDisplay", displayStr);
			}

			return;
		}

		CustomDataParser::ParseString(a_value, a_customData);
	}

	void WeightClassParser::ParseString(
		const Json::String& a_value,
		ICustomDataContainer* a_customData) const
	{
		std::int32_t type = -1;
		std::wstring displayStr;

		util::try_get(EnumLookup<EquipType>, a_value, type) &&
			util::try_get(ArmorSubTypeDisplayMap, a_value, displayStr);

		if (type != -1) {
			a_customData->AddCustomData("weightClass", type);

			if (!displayStr.empty()) {
				a_customData->AddCustomData("weightClassDisplay", displayStr);
			}

			return;
		}

		CustomDataParser::ParseString(a_value, a_customData);
	}
}
