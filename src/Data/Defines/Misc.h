#pragma once

namespace Data
{
	template <typename Enum>
	extern const util::istring_map<Enum> EnumLookup;

	enum class MiscType
	{
		Gem = 0,
		DragonClaw = 1,
		Artifact = 2,
		Leather = 3,
		LeatherStrips = 4,
		Hide = 5,
		Remains = 6,
		Ingot = 7,
		Tool = 8,
		ChildrensClothes = 9,
		Toy = 10,
		Firewood = 11,

		Fastener = 12,
		WeaponRack = 13,
		Shelf = 14,
		Furniture = 15,
		Exterior = 16,
		Container = 17,

		HousePart = 18,
		Clutter = 19,
		Lockpick = 20,
		Gold = 21,
	};

	template <>
	inline const util::istring_map<MiscType> EnumLookup<MiscType> = {
		{ "Gem", MiscType::Gem },
		{ "DragonClaw", MiscType::DragonClaw },
		{ "Artifact", MiscType::Artifact },
		{ "Leather", MiscType::Leather },
		{ "LeatherStrips", MiscType::LeatherStrips },
		{ "Hide", MiscType::Hide },
		{ "Remains", MiscType::Remains },
		{ "Ingot", MiscType::Ingot },
		{ "Tool", MiscType::Tool },
		{ "ChildrensClothes", MiscType::ChildrensClothes },
		{ "Toy", MiscType::Toy },
		{ "Firewood", MiscType::Firewood },
		{ "Fastener", MiscType::Fastener },
		{ "WeaponRack", MiscType::WeaponRack },
		{ "Shelf", MiscType::Shelf },
		{ "Furniture", MiscType::Furniture },
		{ "Exterior", MiscType::Exterior },
		{ "Container", MiscType::Container },
		{ "HousePart", MiscType::HousePart },
		{ "Clutter", MiscType::Clutter },
		{ "Lockpick", MiscType::Lockpick },
		{ "Gold", MiscType::Gold },
	};

	inline static const util::istring_map<std::wstring> MiscSubTypeDisplayMap = {
		{ "Gem", L"$Gem" },
		{ "DragonClaw", L"$Claw" },
		{ "Artifact", L"$Artifact" },
		{ "Leather", L"$Leather" },
		{ "LeatherStrips", L"$Strips" },
		{ "Hide", L"$Hide" },
		{ "Remains", L"$Remains" },
		{ "Ingot", L"$Ingot" },
		{ "Tool", L"$Tool" },
		{ "ChildrensClothes", L"$Clothing" },
		{ "Toy", L"$Toy" },
		{ "Firewood", L"$Firewood" },
		//{ "Fastener", L"" },
		//{ "WeaponRack", L"" },
		//{ "Shelf", L"" },
		//{ "Furniture", L"" },
		//{ "Exterior", L"" },
		//{ "Container", L"" },
		{ "HousePart", L"$House Part" },
		{ "Clutter", L"$Clutter" },
		{ "Lockpick", L"$Lockpick" },
		{ "Gold", L"$Gold" },
	};
}
