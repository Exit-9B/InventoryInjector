#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::enum_dict<Enum> EnumLookup;

	enum class AmmoType
	{
		Arrow = 0,
		Bolt = 1,
	};

	template <>
	inline const util::enum_dict<AmmoType> EnumLookup<AmmoType> = {
		{ "Arrow", AmmoType::Arrow },
		{ "Bolt", AmmoType::Bolt },
	};

	inline static const util::enum_dict<std::wstring> AmmoSubTypeDisplayMap = {
		{ "Arrow", L"$Arrow" },
		{ "Bolt", L"$Bolt" },
	};

	using AmmoFlag = RE::AMMO_DATA::Flag;

	template <>
	inline const util::enum_dict<AmmoFlag> EnumLookup<AmmoFlag> = {
		{ "IgnoresNormalWeaponResistance", AmmoFlag::kIgnoresNormalWeaponResistance },
		{ "NonPlayable", AmmoFlag::kNonPlayable },
		{ "NonBolt", AmmoFlag::kNonBolt },
	};
}
