#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::istring_map<Enum> EnumLookup;

	enum class BookType
	{
		SpellTome = 0,
		Note = 1,
		Recipe = 2,
	};

	template <>
	inline const util::istring_map<BookType> EnumLookup<BookType> = {
		{ "SpellTome", BookType::SpellTome },
		{ "Note", BookType::Note },
		{ "Recipe", BookType::Recipe },
	};

	inline static const util::istring_map<std::wstring> BookSubTypeDisplayMap = {
		{ "SpellTome", L"$Spell Tome" },
		{ "Note", L"$Note" },
		{ "Recipe", L"$Recipe" },
	};

	template <>
	inline const util::istring_map<RE::OBJ_BOOK::Type> EnumLookup<RE::OBJ_BOOK::Type> = {
		{ "Book", RE::OBJ_BOOK::Type::kBookTome },
		{ "Note", RE::OBJ_BOOK::Type::kNoteScroll },
	};

	using BookFlag = RE::OBJ_BOOK::Flag;

	template <>
	inline const util::istring_map<BookFlag> EnumLookup<BookFlag> = {
		{ "TeachesSpell", BookFlag::kTeachesSpell },
		{ "TeachesSkill", BookFlag::kAdvancesActorValue },
		{ "Read", BookFlag::kHasBeenRead },
	};
}
