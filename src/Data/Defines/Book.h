#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::enum_dict<Enum> EnumLookup;

	enum class BookType
	{
		SpellTome = 0,
		Note = 1,
		Recipe = 2,
	};

	template <>
	inline const util::enum_dict<BookType> EnumLookup<BookType> = {
		{ "SpellTome", BookType::SpellTome },
		{ "Note", BookType::Note },
		{ "Recipe", BookType::Recipe },
	};

	inline static const util::enum_dict<std::wstring> BookSubTypeDisplayMap = {
		{ "SpellTome", L"$Spell Tome" },
		{ "Note", L"$Note" },
		{ "Recipe", L"$Recipe" },
	};

	template <>
	inline const util::enum_dict<RE::OBJ_BOOK::Type> EnumLookup<RE::OBJ_BOOK::Type> = {
		{ "Book", RE::OBJ_BOOK::Type::kBookTome },
		{ "Note", RE::OBJ_BOOK::Type::kNoteScroll },
	};

	using BookFlag = RE::OBJ_BOOK::Flag;

	template <>
	inline const util::enum_dict<BookFlag> EnumLookup<BookFlag> = {
		{ "Spell", BookFlag::kTeachesSpell },
		{ "Skill", BookFlag::kAdvancesActorValue },
		{ "Read", BookFlag::kHasBeenRead },
	};
}
