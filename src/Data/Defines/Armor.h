#pragma once

namespace Data
{
	enum class EquipType
	{
		Head = 0,
		Hair = 1,
		LongHair = 2,
		Body = 3,
		Forearms = 4,
		Hands = 5,
		Shield = 6,
		Calves = 7,
		Feet = 8,
		Circlet = 9,
		Amulet = 10,
		Ears = 11,
		Ring = 12,
		Tail = 13,
	};

	inline static const util::enum_dict<EquipType> ArmorSubTypeMap = {
		{ "Head", EquipType::Head },
		{ "Hair", EquipType::Hair },
		{ "LongHair", EquipType::LongHair },
		{ "Body", EquipType::Body },
		{ "Forearms", EquipType::Forearms },
		{ "Hands", EquipType::Hands },
		{ "Shield", EquipType::Shield },
		{ "Calves", EquipType::Calves },
		{ "Feet", EquipType::Feet },
		{ "Circlet", EquipType::Circlet },
		{ "Amulet", EquipType::Amulet },
		{ "Ears", EquipType::Ears },
		{ "Ring", EquipType::Ring },
		{ "Tail", EquipType::Tail },
	};

	inline static const util::enum_dict<std::wstring> ArmorSubTypeDisplayMap = {
		{ "Head", L"$Head" },
		{ "Hair", L"$Head" },
		{ "LongHair", L"$Head" },
		{ "Body", L"$Body" },
		{ "Forearms", L"$Forearms" },
		{ "Hands", L"$Hands" },
		{ "Shield", L"$Shield" },
		{ "Calves", L"$Calves" },
		{ "Feet", L"$Feet" },
		{ "Circlet", L"$Circlet" },
		{ "Amulet", L"$Amulet" },
		{ "Ears", L"$Ears" },
		{ "Ring", L"$Ring" },
		{ "Tail", L"$Tail" },
	};

	inline static std::vector<RE::BIPED_MODEL::BipedObjectSlot> PartMaskPrecedence = {
		RE::BIPED_MODEL::BipedObjectSlot::kBody,
		RE::BIPED_MODEL::BipedObjectSlot::kHair,
		RE::BIPED_MODEL::BipedObjectSlot::kHands,
		RE::BIPED_MODEL::BipedObjectSlot::kForearms,
		RE::BIPED_MODEL::BipedObjectSlot::kFeet,
		RE::BIPED_MODEL::BipedObjectSlot::kCalves,
		RE::BIPED_MODEL::BipedObjectSlot::kShield,
		RE::BIPED_MODEL::BipedObjectSlot::kAmulet,
		RE::BIPED_MODEL::BipedObjectSlot::kRing,
		RE::BIPED_MODEL::BipedObjectSlot::kLongHair,
		RE::BIPED_MODEL::BipedObjectSlot::kEars,
		RE::BIPED_MODEL::BipedObjectSlot::kHead,
		RE::BIPED_MODEL::BipedObjectSlot::kCirclet,
		RE::BIPED_MODEL::BipedObjectSlot::kTail,
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 14),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 15),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 16),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 17),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 18),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 19),
		RE::BIPED_MODEL::BipedObjectSlot::kDecapitateHead,
		RE::BIPED_MODEL::BipedObjectSlot::kDecapitate,
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 22),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 23),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 24),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 25),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 26),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 27),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 28),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 29),
		static_cast<RE::BIPED_MODEL::BipedObjectSlot>(1 << 30),
		RE::BIPED_MODEL::BipedObjectSlot::kFX01,
	};

	enum class WeightClass
	{
		Light = 0,
		Heavy = 1,
		None = 2,
		Clothing = 3,
		Jewelry = 4,
	};

	inline static const util::enum_dict<WeightClass> ArmorWeightClassMap = {
		{ "Light", WeightClass::Light },
		{ "Heavy", WeightClass::Heavy },
		{ "None", WeightClass::None },
		{ "Clothing", WeightClass::Clothing },
		{ "Jewelry", WeightClass::Jewelry },
	};
}
