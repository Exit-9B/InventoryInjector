#pragma once

namespace Data
{
	inline static util::enum_dict<RE::FormType> FormTypeMap = {
		{ "", RE::FormType::None },
		{ "Ammo", RE::FormType::Ammo },
		{ "Armor", RE::FormType::Armor },
		{ "Book", RE::FormType::Book },
		{ "Enchantment", RE::FormType::Enchantment },
		{ "Ingredient", RE::FormType::Ingredient },
		{ "Key", RE::FormType::KeyMaster },
		{ "Light", RE::FormType::Light },
		{ "MiscItem", RE::FormType::Misc },
		{ "Potion", RE::FormType::AlchemyItem },
		{ "Scroll", RE::FormType::Scroll },
		{ "Spell", RE::FormType::Spell },
		{ "SoulGem", RE::FormType::SoulGem },
		{ "Weapon", RE::FormType::Weapon },
	};
}
