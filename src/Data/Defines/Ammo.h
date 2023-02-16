#pragma once

namespace Data
{
	enum class AmmoType
	{
		Arrow = 0,
		Bolt = 1,
	};

	inline static util::enum_dict<AmmoType> AmmoSubTypeMap = {
		{ "arrow", AmmoType::Arrow },
		{ "bolt", AmmoType::Bolt },
	};

	inline static util::enum_dict<std::wstring> AmmoSubTypeDisplayMap = {
		{ "arrow", L"$Arrow" },
		{ "bolt", L"$Bolt" },
	};

	using AmmoFlag = RE::AMMO_DATA::Flag;

	inline static util::enum_dict<AmmoFlag> AmmoFlagsMap = {
		{ "ignoresNormalWeaponResistance", AmmoFlag::kIgnoresNormalWeaponResistance },
		{ "nonPlayable", AmmoFlag::kNonPlayable },
		{ "nonBolt", AmmoFlag::kNonBolt },
	};
}
