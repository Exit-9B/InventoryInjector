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
}
