#pragma once

namespace Data
{
	enum class BookType
	{
		SpellTome = 0,
		Note = 1,
		Recipe = 2,
	};

	inline static const util::enum_dict<BookType> BookSubTypeMap = {
		{ "SpellTome", BookType::SpellTome },
		{ "Note", BookType::Note },
		{ "Recipe", BookType::Recipe },
	};

	inline static const util::enum_dict<std::wstring> BookSubTypeDisplayMap = {
		{ "SpellTome", L"$Spell Tome" },
		{ "Note", L"$Note" },
		{ "Recipe", L"$Recipe" },
	};

	using BookFlag = RE::OBJ_BOOK::Flag;

	inline static const util::enum_dict<BookFlag> BookFlagsMap = {
		{ "Spell", BookFlag::kTeachesSpell },
		{ "Skill", BookFlag::kAdvancesActorValue },
		{ "Read", BookFlag::kHasBeenRead },
	};
}
