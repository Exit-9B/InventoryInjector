#include "IconUtil.h"

#include "Data/Defines/Ammo.h"
#include "Data/Defines/Armor.h"
#include "Data/Defines/Book.h"
#include "Data/Defines/Misc.h"
#include "Data/Defines/Potion.h"
#include "Data/Defines/SoulGem.h"
#include "Data/Defines/Weapon.h"

namespace Data
{
	void IconUtil::ProcessDefaultIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		RE::GFxValue formType;
		a_entryObject->GetMember("formType", &formType);
		if (!formType.IsNumber()) {
			return;
		}

		switch (static_cast<RE::FormType>(formType.GetNumber())) {
		case RE::FormType::Spell:
			ProcessSpellIcon(a_entryObject);
			break;

		case RE::FormType::Scroll:
			a_entryObject->SetMember("iconLabel", "default_scroll");
			ProcessScrollResist(a_entryObject);
			break;

		case RE::FormType::Armor:
			ProcessArmorIcon(a_entryObject);
			break;

		case RE::FormType::Book:
			ProcessBookIcon(a_entryObject);
			break;

		case RE::FormType::Ingredient:
			a_entryObject->SetMember("iconLabel", "default_ingredient");
			break;

		case RE::FormType::Light:
			a_entryObject->SetMember("iconLabel", "misc_torch");
			break;

		case RE::FormType::Misc:
			ProcessMiscIcon(a_entryObject);
			break;

		case RE::FormType::Weapon:
			ProcessWeaponIcon(a_entryObject);
			break;

		case RE::FormType::Ammo:
			ProcessAmmoIcon(a_entryObject);
			break;

		case RE::FormType::KeyMaster:
			a_entryObject->SetMember("iconLabel", "default_key");
			break;

		case RE::FormType::AlchemyItem:
			ProcessPotionIcon(a_entryObject);
			break;

		case RE::FormType::SoulGem:
			ProcessSoulGemIcon(a_entryObject);
			break;
		}
	}

	void IconUtil::ProcessSpellIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "default_power");

		RE::GFxValue school;
		a_entryObject->GetMember("school", &school);

		if (!school.IsNumber())
			return;

		switch (static_cast<RE::ActorValue>(school.GetNumber())) {
		case RE::ActorValue::kAlteration:
			a_entryObject->SetMember("iconLabel", "default_alteration");
			break;

		case RE::ActorValue::kConjuration:
			a_entryObject->SetMember("iconLabel", "default_conjuration");
			break;

		case RE::ActorValue::kDestruction:
			a_entryObject->SetMember("iconLabel", "default_destruction");
			ProcessSpellResist(a_entryObject);
			break;

		case RE::ActorValue::kIllusion:
			a_entryObject->SetMember("iconLabel", "default_illusion");
			break;

		case RE::ActorValue::kRestoration:
			a_entryObject->SetMember("iconLabel", "default_restoration");
			break;
		}
	}

	void IconUtil::ProcessSpellResist(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		RE::GFxValue resistance;
		a_entryObject->GetMember("resistance", &resistance);

		if (!resistance.IsNumber())
			return;

		switch (static_cast<RE::ActorValue>(resistance.GetNumber())) {
		case RE::ActorValue::kResistFire:
			a_entryObject->SetMember("iconLabel", "magic_fire");
			a_entryObject->SetMember("iconColor", 0xC73636);
			break;

		case RE::ActorValue::kResistShock:
			a_entryObject->SetMember("iconLabel", "magic_shock");
			a_entryObject->SetMember("iconColor", 0xEAAB00);
			break;

		case RE::ActorValue::kResistFrost:
			a_entryObject->SetMember("iconLabel", "magic_frost");
			a_entryObject->SetMember("iconColor", 0x1FFBFF);
			break;
		}
	}

	void IconUtil::ProcessScrollResist(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		RE::GFxValue resistance;
		a_entryObject->GetMember("resistance", &resistance);

		if (!resistance.IsNumber())
			return;

		switch (static_cast<RE::ActorValue>(resistance.GetNumber())) {
		case RE::ActorValue::kResistFire:
			a_entryObject->SetMember("iconLabel", "magic_fire");
			a_entryObject->SetMember("iconColor", 0xC73636);
			break;

		case RE::ActorValue::kResistShock:
			a_entryObject->SetMember("iconLabel", "magic_shock");
			a_entryObject->SetMember("iconColor", 0xFFFF00);
			break;

		case RE::ActorValue::kResistFrost:
			a_entryObject->SetMember("iconLabel", "magic_frost");
			a_entryObject->SetMember("iconColor", 0x1FFBFF);
			break;
		}
	}

	void IconUtil::ProcessArmorIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "default_armor");
		a_entryObject->SetMember("iconColor", 0xEDDA87);

		RE::GFxValue weightClass;
		a_entryObject->GetMember("weightClass", &weightClass);

		if (!weightClass.IsNumber())
			return;

		switch (static_cast<Data::WeightClass>(weightClass.GetNumber())) {
		case Data::WeightClass::Light:
			ProcessLightArmorIcon(a_entryObject);
			break;

		case Data::WeightClass::Heavy:
			ProcessHeavyArmorIcon(a_entryObject);
			break;

		case Data::WeightClass::Jewelry:
			ProcessJewelryArmorIcon(a_entryObject);
			break;

		case Data::WeightClass::Clothing:
		default:
			ProcessClothingArmorIcon(a_entryObject);
			break;
		}
	}

	void IconUtil::ProcessLightArmorIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		assert(a_entryObject);

		a_entryObject->SetMember("iconColor", 0x756000);

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::EquipType>(subType.GetNumber())) {
		case Data::EquipType::Head:
		case Data::EquipType::Hair:
		case Data::EquipType::LongHair:
			a_entryObject->SetMember("iconLabel", "lightarmor_head");
			break;

		case Data::EquipType::Body:
		case Data::EquipType::Tail:
			a_entryObject->SetMember("iconLabel", "lightarmor_body");
			break;

		case Data::EquipType::Hands:
			a_entryObject->SetMember("iconLabel", "lightarmor_hands");
			break;

		case Data::EquipType::Forearms:
			a_entryObject->SetMember("iconLabel", "lightarmor_forearms");
			break;

		case Data::EquipType::Feet:
			a_entryObject->SetMember("iconLabel", "lightarmor_feet");
			break;

		case Data::EquipType::Calves:
			a_entryObject->SetMember("iconLabel", "lightarmor_calves");
			break;

		case Data::EquipType::Shield:
			a_entryObject->SetMember("iconLabel", "lightarmor_shield");
			break;

		case Data::EquipType::Amulet:
		case Data::EquipType::Ring:
		case Data::EquipType::Circlet:
		case Data::EquipType::Ears:
			ProcessJewelryArmorIcon(a_entryObject);
			break;
		}
	}

	void IconUtil::ProcessHeavyArmorIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconColor", 0x6B7585);

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::EquipType>(subType.GetNumber())) {
		case Data::EquipType::Head:
		case Data::EquipType::Hair:
		case Data::EquipType::LongHair:
			a_entryObject->SetMember("iconLabel", "armor_head");
			break;

		case Data::EquipType::Body:
		case Data::EquipType::Tail:
			a_entryObject->SetMember("iconLabel", "armor_body");
			break;

		case Data::EquipType::Hands:
			a_entryObject->SetMember("iconLabel", "armor_hands");
			break;

		case Data::EquipType::Forearms:
			a_entryObject->SetMember("iconLabel", "armor_forearms");
			break;

		case Data::EquipType::Feet:
			a_entryObject->SetMember("iconLabel", "armor_feet");
			break;

		case Data::EquipType::Calves:
			a_entryObject->SetMember("iconLabel", "armor_calves");
			break;

		case Data::EquipType::Shield:
			a_entryObject->SetMember("iconLabel", "armor_shield");
			break;

		case Data::EquipType::Amulet:
		case Data::EquipType::Ring:
		case Data::EquipType::Circlet:
		case Data::EquipType::Ears:
			ProcessJewelryArmorIcon(a_entryObject);
			break;
		}
	}

	void IconUtil::ProcessJewelryArmorIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::EquipType>(subType.GetNumber())) {
		case Data::EquipType::Amulet:
			a_entryObject->SetMember("iconLabel", "armor_amulet");
			break;

		case Data::EquipType::Ring:
			a_entryObject->SetMember("iconLabel", "armor_ring");
			break;

		case Data::EquipType::Circlet:
			a_entryObject->SetMember("iconLabel", "armor_circlet");
			break;

		case Data::EquipType::Ears:
			break;
		}
	}

	void IconUtil::ProcessClothingArmorIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::EquipType>(subType.GetNumber())) {
		case Data::EquipType::Head:
		case Data::EquipType::Hair:
		case Data::EquipType::LongHair:
			a_entryObject->SetMember("iconLabel", "clothing_head");
			break;

		case Data::EquipType::Body:
		case Data::EquipType::Tail:
			a_entryObject->SetMember("iconLabel", "clothing_body");
			break;

		case Data::EquipType::Hands:
			a_entryObject->SetMember("iconLabel", "clothing_hands");
			break;

		case Data::EquipType::Forearms:
			a_entryObject->SetMember("iconLabel", "clothing_forearms");
			break;

		case Data::EquipType::Feet:
			a_entryObject->SetMember("iconLabel", "clothing_feet");
			break;

		case Data::EquipType::Calves:
			a_entryObject->SetMember("iconLabel", "clothing_calves");
			break;

		case Data::EquipType::Shield:
			a_entryObject->SetMember("iconLabel", "clothing_shield");
			break;

		case Data::EquipType::Ears:
			break;
		}
	}

	void IconUtil::ProcessBookIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "default_book");

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::BookType>(subType.GetNumber())) {
		case Data::BookType::Recipe:
		case Data::BookType::Note:
			a_entryObject->SetMember("iconLabel", "book_note");
			break;

		case Data::BookType::SpellTome:
			a_entryObject->SetMember("iconLabel", "book_tome");
			break;
		}
	}

	void IconUtil::ProcessWeaponIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "default_weapon");
		a_entryObject->SetMember("iconColor", 0xA4A5BF);

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::WeaponType>(subType.GetNumber())) {
		case Data::WeaponType::Melee:
			break;

		case Data::WeaponType::Sword:
			a_entryObject->SetMember("iconLabel", "weapon_sword");
			break;

		case Data::WeaponType::Dagger:
			a_entryObject->SetMember("iconLabel", "weapon_dagger");
			break;

		case Data::WeaponType::WarAxe:
			a_entryObject->SetMember("iconLabel", "weapon_waraxe");
			break;

		case Data::WeaponType::Mace:
			a_entryObject->SetMember("iconLabel", "weapon_mace");
			break;

		case Data::WeaponType::Greatsword:
			a_entryObject->SetMember("iconLabel", "weapon_greatsword");
			break;

		case Data::WeaponType::Battleaxe:
			a_entryObject->SetMember("iconLabel", "weapon_battleaxe");
			break;

		case Data::WeaponType::Warhammer:
			a_entryObject->SetMember("iconLabel", "weapon_hammer");
			break;

		case Data::WeaponType::Bow:
			a_entryObject->SetMember("iconLabel", "weapon_bow");
			break;

		case Data::WeaponType::Staff:
			a_entryObject->SetMember("iconLabel", "weapon_staff");
			break;

		case Data::WeaponType::Crossbow:
			a_entryObject->SetMember("iconLabel", "weapon_crossbow");
			break;

		case Data::WeaponType::Pickaxe:
			a_entryObject->SetMember("iconLabel", "weapon_pickaxe");
			break;

		case Data::WeaponType::WoodAxe:
			a_entryObject->SetMember("iconLabel", "weapon_woodaxe");
			break;
		}
	}

	void IconUtil::ProcessAmmoIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "weapon_arrow");
		a_entryObject->SetMember("iconColor", 0xA89E8C);

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::AmmoType>(subType.GetNumber())) {
		case Data::AmmoType::Arrow:
			a_entryObject->SetMember("iconLabel", "weapon_arrow");
			break;
		case Data::AmmoType::Bolt:
			a_entryObject->SetMember("iconLabel", "weapon_bolt");
			break;
		}
	}

	void IconUtil::ProcessPotionIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "default_potion");

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::PotionType>(subType.GetNumber())) {
		case Data::PotionType::Drink:
			a_entryObject->SetMember("iconLabel", "food_wine");
			break;

		case Data::PotionType::Food:
			a_entryObject->SetMember("iconLabel", "default_food");
			break;

		case Data::PotionType::Poison:
			a_entryObject->SetMember("iconLabel", "potion_poison");
			a_entryObject->SetMember("iconColor", 0xAD00B3);
			break;

		case Data::PotionType::Health:
		case Data::PotionType::HealRate:
		case Data::PotionType::HealRateMult:
			a_entryObject->SetMember("iconLabel", "potion_health");
			a_entryObject->SetMember("iconColor", 0xDB2E73);
			break;

		case Data::PotionType::Magicka:
		case Data::PotionType::MagickaRate:
		case Data::PotionType::MagickaRateMult:
			a_entryObject->SetMember("iconLabel", "potion_magic");
			a_entryObject->SetMember("iconColor", 0x2E9FDB);
			break;

		case Data::PotionType::Stamina:
		case Data::PotionType::StaminaRate:
		case Data::PotionType::StaminaRateMult:
			a_entryObject->SetMember("iconLabel", "potion_stam");
			a_entryObject->SetMember("iconColor", 0x51DB2E);
			break;

		case Data::PotionType::FireResist:
			a_entryObject->SetMember("iconLabel", "potion_fire");
			a_entryObject->SetMember("iconColor", 0xC73636);
			break;

		case Data::PotionType::ElectricResist:
			a_entryObject->SetMember("iconLabel", "potion_shock");
			a_entryObject->SetMember("iconColor", 0xEAAB00);
			break;

		case Data::PotionType::FrostResist:
			a_entryObject->SetMember("iconLabel", "potion_frost");
			a_entryObject->SetMember("iconColor", 0x1FFBFF);
			break;
		}
	}

	void IconUtil::ProcessSoulGemIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "default_soulgem");
		a_entryObject->SetMember("iconColor", 0xE3E0FF);

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::SoulGemType>(subType.GetNumber())) {
		case Data::SoulGemType::Petty:
			a_entryObject->SetMember("iconColor", 0xD7D4FF);
			ProcessSoulGemStatusIcon(a_entryObject);
			break;

		case Data::SoulGemType::Lesser:
			a_entryObject->SetMember("iconColor", 0xC0BAFF);
			ProcessSoulGemStatusIcon(a_entryObject);
			break;

		case Data::SoulGemType::Common:
			a_entryObject->SetMember("iconColor", 0xABA3FF);
			ProcessSoulGemStatusIcon(a_entryObject);
			break;

		case Data::SoulGemType::Greater:
			a_entryObject->SetMember("iconColor", 0x948BFC);
			ProcessGrandSoulGemIcon(a_entryObject);
			break;

		case Data::SoulGemType::Grand:
			a_entryObject->SetMember("iconColor", 0x7569FF);
			ProcessGrandSoulGemIcon(a_entryObject);
			break;

		case Data::SoulGemType::Azura:
			a_entryObject->SetMember("iconColor", 0x7569FF);
			a_entryObject->SetMember("iconLabel", "soulgem_azura");
			break;
		}
	}

	void IconUtil::ProcessGrandSoulGemIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		RE::GFxValue status;
		a_entryObject->GetMember("status", &status);

		switch (static_cast<Data::SoulGemStatus>(status.GetNumber())) {
		case Data::SoulGemStatus::Empty:
			a_entryObject->SetMember("iconLabel", "soulgem_grandempty");
			break;

		case Data::SoulGemStatus::Full:
			a_entryObject->SetMember("iconLabel", "soulgem_grandfull");
			break;

		case Data::SoulGemStatus::Partial:
			a_entryObject->SetMember("iconLabel", "soulgem_grandpartial");
			break;
		}
	}

	void IconUtil::ProcessSoulGemStatusIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		RE::GFxValue status;
		a_entryObject->GetMember("status", &status);

		switch (static_cast<Data::SoulGemStatus>(status.GetNumber())) {
		case Data::SoulGemStatus::Empty:
			a_entryObject->SetMember("iconLabel", "soulgem_empty");
			break;

		case Data::SoulGemStatus::Full:
			a_entryObject->SetMember("iconLabel", "soulgem_full");
			break;

		case Data::SoulGemStatus::Partial:
			a_entryObject->SetMember("iconLabel", "soulgem_partial");
			break;
		}
	}

	void IconUtil::ProcessMiscIcon(RE::GFxValue* a_entryObject)
	{
		assert(a_entryObject);

		a_entryObject->SetMember("iconLabel", "default_misc");

		RE::GFxValue subType;
		a_entryObject->GetMember("subType", &subType);

		if (!subType.IsNumber())
			return;

		switch (static_cast<Data::MiscType>(subType.GetNumber())) {
		case Data::MiscType::Artifact:
			a_entryObject->SetMember("iconLabel", "misc_artifact");
			break;

		case Data::MiscType::Gem:
			a_entryObject->SetMember("iconLabel", "misc_gem");
			a_entryObject->SetMember("iconColor", 0xFFB0D1);
			break;

		case Data::MiscType::Hide:
			a_entryObject->SetMember("iconLabel", "misc_hide");
			a_entryObject->SetMember("iconColor", 0xDBB36E);
			break;

		case Data::MiscType::Remains:
			a_entryObject->SetMember("iconLabel", "misc_remains");
			break;

		case Data::MiscType::Ingot:
			a_entryObject->SetMember("iconLabel", "misc_ingot");
			a_entryObject->SetMember("iconColor", 0x828282);
			break;

		case Data::MiscType::Clutter:
			a_entryObject->SetMember("iconLabel", "misc_clutter");
			break;

		case Data::MiscType::Firewood:
			a_entryObject->SetMember("iconLabel", "misc_wood");
			a_entryObject->SetMember("iconColor", 0xA89E8C);
			break;

		case Data::MiscType::DragonClaw:
			a_entryObject->SetMember("iconLabel", "misc_dragonclaw");
			break;

		case Data::MiscType::Lockpick:
			a_entryObject->SetMember("iconLabel", "misc_lockpick");
			break;

		case Data::MiscType::Gold:
			a_entryObject->SetMember("iconLabel", "misc_gold");
			a_entryObject->SetMember("iconColor", 0xCCCC33);
			break;

		case Data::MiscType::Leather:
			a_entryObject->SetMember("iconLabel", "misc_leather");
			a_entryObject->SetMember("iconColor", 0xBA8D23);
			break;

		case Data::MiscType::LeatherStrips:
			a_entryObject->SetMember("iconLabel", "misc_strips");
			a_entryObject->SetMember("iconColor", 0xBA8D23);
			break;

		case Data::MiscType::ChildrensClothes:
			a_entryObject->SetMember("iconColor", 0xEDDA87);
			a_entryObject->SetMember("iconLabel", "clothing_body");
			break;
		}
	}
}
