#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::enum_dict<Enum> EnumLookup;

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

	template <>
	inline const util::enum_dict<SoulGemType> EnumLookup<SoulGemType> = {
		{ "None", SoulGemType::None },
		{ "Petty", SoulGemType::Petty },
		{ "Lesser", SoulGemType::Lesser },
		{ "Common", SoulGemType::Common },
		{ "Greater", SoulGemType::Greater },
		{ "Grand", SoulGemType::Grand },
		{ "Azura", SoulGemType::Azura },
	};

	inline static const util::enum_dict<std::wstring> SoulGemSubTypeDisplayMap = {
		{ "None", L"$Empty" },
		{ "Petty", L"$Petty" },
		{ "Lesser", L"$Lesser" },
		{ "Common", L"$Common" },
		{ "Greater", L"$Greater" },
		{ "Grand", L"$Grand" },
		{ "Azura", L"$Azura" },
	};

	enum class SoulGemStatus
	{
		Empty = 0,
		Partial = 1,
		Full = 2,
	};

	template <>
	inline const util::enum_dict<SoulGemStatus> EnumLookup<SoulGemStatus> = {
		{ "Empty", SoulGemStatus::Empty },
		{ "Partial", SoulGemStatus::Partial },
		{ "Full", SoulGemStatus::Full },
	};
}
