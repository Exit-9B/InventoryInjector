#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::enum_dict<Enum> EnumLookup;

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
	inline const util::enum_dict<WeaponType> EnumLookup<WeaponType> = {
		{ "Melee", WeaponType::Melee },
		{ "Sword", WeaponType::Sword },
		{ "Dagger", WeaponType::Dagger },
		{ "WarAxe", WeaponType::WarAxe },
		{ "Mace", WeaponType::Mace },
		{ "Greatsword", WeaponType::Greatsword },
		{ "Battleaxe", WeaponType::Battleaxe },
		{ "Bow", WeaponType::Bow },
		{ "Crossbow", WeaponType::Crossbow },
		{ "Staff", WeaponType::Staff },
		{ "Pickaxe", WeaponType::Pickaxe },
		{ "WoodAxe", WeaponType::WoodAxe },
	};

	inline static const util::enum_dict<std::wstring> WeaponSubTypeDisplayMap = {
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
