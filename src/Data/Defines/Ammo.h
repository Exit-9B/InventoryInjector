#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::istring_map<Enum> EnumLookup;

	enum class AmmoType
	{
		Arrow = 0,
		Bolt = 1,
	};

	template <>
	inline const util::istring_map<AmmoType> EnumLookup<AmmoType> = {
		{ "Arrow", AmmoType::Arrow },
		{ "Bolt", AmmoType::Bolt },
	};

	inline static const util::istring_map<std::wstring> AmmoSubTypeDisplayMap = {
		{ "Arrow", L"$Arrow" },
		{ "Bolt", L"$Bolt" },
	};

	using AmmoFlag = RE::AMMO_DATA::Flag;

	template <>
	inline const util::istring_map<AmmoFlag> EnumLookup<AmmoFlag> = {
		{ "IgnoresNormalWeaponResistance", AmmoFlag::kIgnoresNormalWeaponResistance },
		{ "NonPlayable", AmmoFlag::kNonPlayable },
		{ "NonBolt", AmmoFlag::kNonBolt },
	};
}
