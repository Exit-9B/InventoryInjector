#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::istring_map<Enum> EnumLookup;

	enum class WeaponType
	{
		Melee = 0,
		Sword = 1,
		Dagger = 2,
		WarAxe = 3,
		Mace = 4,
		Greatsword = 5,
		Battleaxe = 6,
		Warhammer = 7,
		Bow = 8,
		Crossbow = 9,
		Staff = 10,
		Pickaxe = 11,
		WoodAxe = 12,
		Spear = 13,
		Javelin = 14,
		Pike = 15,
		Halberd = 16,
		Rapier = 17,
		Quarterstaff = 18,
		Claw = 19,
		Whip = 20,
		Katana = 21,
		Scythe = 22,
		Gun = 23,
	};

	template <>
	inline const util::istring_map<WeaponType> EnumLookup<WeaponType> = {
		{ "Melee", WeaponType::Melee },
		{ "Sword", WeaponType::Sword },
		{ "Dagger", WeaponType::Dagger },
		{ "WarAxe", WeaponType::WarAxe },
		{ "Mace", WeaponType::Mace },
		{ "Greatsword", WeaponType::Greatsword },
		{ "Battleaxe", WeaponType::Battleaxe },
		{ "Warhammer", WeaponType::Warhammer },
		{ "Bow", WeaponType::Bow },
		{ "Crossbow", WeaponType::Crossbow },
		{ "Staff", WeaponType::Staff },
		{ "Pickaxe", WeaponType::Pickaxe },
		{ "WoodAxe", WeaponType::WoodAxe },
	};

	template <>
	inline const util::istring_map<RE::WEAPON_TYPE> EnumLookup<RE::WEAPON_TYPE> = {
		{ "HandToHandMelee", RE::WEAPON_TYPE::kHandToHandMelee },
		{ "OneHandSword", RE::WEAPON_TYPE::kOneHandSword },
		{ "OneHandDagger", RE::WEAPON_TYPE::kOneHandDagger },
		{ "OneHandAxe", RE::WEAPON_TYPE::kOneHandAxe },
		{ "OneHandMace", RE::WEAPON_TYPE::kOneHandMace },
		{ "TwoHandSword", RE::WEAPON_TYPE::kTwoHandSword },
		{ "TwoHandAxe", RE::WEAPON_TYPE::kTwoHandAxe },
		{ "Bow", RE::WEAPON_TYPE::kBow },
		{ "Staff", RE::WEAPON_TYPE::kStaff },
		{ "Crossbow", RE::WEAPON_TYPE::kCrossbow },
	};

	inline static const util::istring_map<std::wstring> WeaponSubTypeDisplayMap = {
		{ "Melee", L"$Melee" },
		{ "Sword", L"$Sword" },
		{ "Dagger", L"$Dagger" },
		{ "WarAxe", L"$War Axe" },
		{ "Mace", L"$Mace" },
		{ "Greatsword", L"$Greatsword" },
		{ "Battleaxe", L"$Battleaxe" },
		{ "Bow", L"$Bow" },
		{ "Crossbow", L"$Crossbow" },
		{ "Staff", L"$Staff" },
		{ "Pickaxe", L"$Pickaxe" },
		{ "WoodAxe", L"$Wood Axe" },
	};
}
