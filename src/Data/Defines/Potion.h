#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::istring_map<Enum> EnumLookup;

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

	template <>
	inline const util::istring_map<PotionType> EnumLookup<PotionType> = {
		{ "Health", PotionType::Health },
		{ "HealRate", PotionType::HealRate },
		{ "HealRateMult", PotionType::HealRateMult },
		{ "Magicka", PotionType::Magicka },
		{ "MagickaRate", PotionType::MagickaRate },
		{ "MagickaRateMult", PotionType::MagickaRateMult },
		{ "Stamina", PotionType::Stamina },
		{ "StaminaRate", PotionType::StaminaRate },
		{ "StaminaRateMult", PotionType::StaminaRateMult },
		{ "FireResist", PotionType::FireResist },
		{ "ElectricResist", PotionType::ElectricResist },
		{ "FrostResist", PotionType::FrostResist },
		{ "Potion", PotionType::Potion },
		{ "Drink", PotionType::Drink },
		{ "Food", PotionType::Food },
		{ "Poison", PotionType::Poison },
	};

	inline static const util::istring_map<std::wstring> PotionSubTypeDisplayMap = {
		{ "Health", L"$Health" },
		{ "HealRate", L"$Health" },
		{ "HealRateMult", L"$Health" },
		{ "Magicka", L"$Magicka" },
		{ "MagickaRate", L"$Magicka" },
		{ "MagickaRateMult", L"$Magicka" },
		{ "Stamina", L"$Stamina" },
		{ "StaminaRate", L"$Stamina" },
		{ "StaminaRateMult", L"$Stamina" },
		//{ "FireResist", L"" },
		//{ "ElectricResist", L"" },
		//{ "FrostResist", L"" },
		{ "Potion", L"$Potion" },
		{ "Drink", L"$Drink" },
		{ "Food", L"$Food" },
		{ "Poison", L"$Poison" },
	};

	using PotionFlag = RE::AlchemyItem::AlchemyFlag;

	template <>
	inline const util::istring_map<PotionFlag> EnumLookup<PotionFlag> = {
		{ "ManualCalc", PotionFlag::kCostOverride },
		{ "Food", PotionFlag::kFoodItem },
		{ "Medicine", PotionFlag::kMedicine },
		{ "Poison", PotionFlag::kPoison },
	};
}
