#pragma once

namespace Data
{
	enum class AmmoType
	{
		Arrow = 0,
		Bolt = 1,
	};

	inline static const util::enum_dict<AmmoType> AmmoSubTypeMap = {
		{ "Arrow", AmmoType::Arrow },
		{ "Bolt", AmmoType::Bolt },
	};

	inline static const util::enum_dict<std::wstring> AmmoSubTypeDisplayMap = {
		{ "Arrow", L"$Arrow" },
		{ "Bolt", L"$Bolt" },
	};

	using AmmoFlag = RE::AMMO_DATA::Flag;

	inline static const util::enum_dict<AmmoFlag> AmmoFlagsMap = {
		{ "IgnoresNormalWeaponResistance", AmmoFlag::kIgnoresNormalWeaponResistance },
		{ "NonPlayable", AmmoFlag::kNonPlayable },
		{ "NonBolt", AmmoFlag::kNonBolt },
	};
}
