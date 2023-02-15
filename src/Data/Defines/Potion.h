#pragma once

namespace Data
{
	enum class PotionType
	{
		Health = 0,
		HealRate = 1,
		HealRateMult = 2,
		Magicka = 3,
		MagickaRate = 4,
		MagickaRateMult = 5,
		Stamina = 6,
		StaminaRate = 7,
		StaminaRateMult = 8,
		FireResist = 9,
		ElectricResist = 10,
		FrostResist = 11,
		Potion = 12,
		Drink = 13,
		Food = 14,
		Poison = 15,
	};

	inline static std::map<std::string, PotionType> PotionSubTypeMap = {
		{ "health", PotionType::Health },
		{ "healrate", PotionType::HealRate },
		{ "healratemult", PotionType::HealRateMult },
		{ "magicka", PotionType::Magicka },
		{ "magickarate", PotionType::MagickaRate },
		{ "magickaratemult", PotionType::MagickaRateMult },
		{ "stamina", PotionType::Stamina },
		{ "staminarate", PotionType::StaminaRate },
		{ "staminaratemult", PotionType::StaminaRateMult },
		{ "fireresist", PotionType::FireResist },
		{ "electricresist", PotionType::ElectricResist },
		{ "frostresist", PotionType::FrostResist },
		{ "potion", PotionType::Potion },
		{ "drink", PotionType::Drink },
		{ "food", PotionType::Food },
		{ "poison", PotionType::Poison },
	};

	inline static std::map<std::string, std::wstring> PotionSubTypeDisplayMap = {
		{ "health", L"$Health" },
		{ "healrate", L"$Health" },
		{ "healratemult", L"$Health" },
		{ "magicka", L"$Magicka" },
		{ "magickarate", L"$Magicka" },
		{ "magickaratemult", L"$Magicka" },
		{ "stamina", L"$Stamina" },
		{ "staminarate", L"$Stamina" },
		{ "staminaratemult", L"$Stamina" },
		//{ "fireresist", L"" },
		//{ "electricresist", L"" },
		//{ "frostresist", L"" },
		{ "potion", L"$Potion" },
		{ "drink", L"$Drink" },
		{ "food", L"$Food" },
		{ "poison", L"$Poison" },
	};
}
