#pragma once

namespace Data
{
	enum class AmmoType
	{
		Arrow = 0,
		Bolt = 1,
	};

	inline static std::map<std::string, AmmoType> AmmoSubTypeMap = {
		{ "arrow", AmmoType::Arrow },
		{ "bolt", AmmoType::Bolt },
	};

	inline static std::map<std::string, std::wstring> AmmoSubTypeDisplayMap = {
		{ "arrow", L"$Arrow" },
		{ "bolt", L"$Bolt" },
	};
}
