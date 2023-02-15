#pragma once

namespace Data
{
	enum class SoulGemType
	{
		None = 0,
		Petty = 1,
		Lesser = 2,
		Common = 3,
		Greater = 4,
		Grand = 5,
		Azura = 6,
	};

	inline static std::map<std::string, SoulGemType> SoulGemSubTypeMap = {
		{ "none", SoulGemType::None },
		{ "petty", SoulGemType::Petty },
		{ "lesser", SoulGemType::Lesser },
		{ "common", SoulGemType::Common },
		{ "greater", SoulGemType::Greater },
		{ "grand", SoulGemType::Grand },
		{ "azura", SoulGemType::Azura },
	};

	inline static std::map<std::string, std::wstring> SoulGemSubTypeDisplayMap = {
		{ "none", L"$Empty" },
		{ "petty", L"$Petty" },
		{ "lesser", L"$Lesser" },
		{ "common", L"$Common" },
		{ "greater", L"$Greater" },
		{ "grand", L"$Grand" },
		{ "azura", L"$Azura" },
	};
}
