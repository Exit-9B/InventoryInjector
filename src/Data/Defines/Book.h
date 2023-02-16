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
}
