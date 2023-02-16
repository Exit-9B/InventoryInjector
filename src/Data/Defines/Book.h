#pragma once

namespace Data
{
	enum class BookType
	{
		SpellTome = 0,
		Note = 1,
		Recipe = 2,
	};

	inline static util::enum_dict<BookType> BookSubTypeMap = {
		{ "spelltome", BookType::SpellTome },
		{ "note", BookType::Note },
		{ "recipe", BookType::Recipe },
	};

	inline static util::enum_dict<std::wstring> BookSubTypeDisplayMap = {
		{ "spelltome", L"$Spell Tome" },
		{ "note", L"$Note" },
		{ "recipe", L"$Recipe" },
	};

	using BookFlag = RE::OBJ_BOOK::Flag;

	inline static util::enum_dict<BookFlag> BookFlagsMap = {
		{ "spell", BookFlag::kTeachesSpell },
		{ "skill", BookFlag::kAdvancesActorValue },
		{ "read", BookFlag::kHasBeenRead },
	};
}
