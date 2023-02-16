#pragma once

namespace Data
{
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

	inline static util::enum_dict<WeaponType> WeaponSubTypeMap = {
		{ "melee", WeaponType::Melee },
		{ "sword", WeaponType::Sword },
		{ "dagger", WeaponType::Dagger },
		{ "waraxe", WeaponType::WarAxe },
		{ "mace", WeaponType::Mace },
		{ "greatsword", WeaponType::Greatsword },
		{ "battleaxe", WeaponType::Battleaxe },
		{ "bow", WeaponType::Bow },
		{ "crossbow", WeaponType::Crossbow },
		{ "staff", WeaponType::Staff },
		{ "pickaxe", WeaponType::Pickaxe },
		{ "woodaxe", WeaponType::WoodAxe },
	};

	inline static util::enum_dict<std::wstring> WeaponSubTypeDisplayMap = {
		{ "melee", L"$Melee" },
		{ "sword", L"$Sword" },
		{ "dagger", L"$Dagger" },
		{ "waraxe", L"$War Axe" },
		{ "mace", L"$Mace" },
		{ "greatsword", L"$Greatsword" },
		{ "battleaxe", L"$Battleaxe" },
		{ "bow", L"$Bow" },
		{ "crossbow", L"$Crossbow" },
		{ "staff", L"$Staff" },
		{ "pickaxe", L"$Pickaxe" },
		{ "woodaxe", L"$Wood Axe" },
	};
}
