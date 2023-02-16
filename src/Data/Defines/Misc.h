#pragma once

namespace Data
{
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

	inline static util::enum_dict<MiscType> MiscSubTypeMap = {
		{ "gem", MiscType::Gem },
		{ "dragonclaw", MiscType::DragonClaw },
		{ "artifact", MiscType::Artifact },
		{ "leather", MiscType::Leather },
		{ "leatherstrips", MiscType::LeatherStrips },
		{ "hide", MiscType::Hide },
		{ "remains", MiscType::Remains },
		{ "ingot", MiscType::Ingot },
		{ "tool", MiscType::Tool },
		{ "childrensclothes", MiscType::ChildrensClothes },
		{ "toy", MiscType::Toy },
		{ "firewood", MiscType::Firewood },
		{ "fastener", MiscType::Fastener },
		{ "weaponrack", MiscType::WeaponRack },
		{ "shelf", MiscType::Shelf },
		{ "furniture", MiscType::Furniture },
		{ "exterior", MiscType::Exterior },
		{ "container", MiscType::Container },
		{ "housepart", MiscType::HousePart },
		{ "clutter", MiscType::Clutter },
		{ "lockpick", MiscType::Lockpick },
		{ "gold", MiscType::Gold },
	};

	inline static util::enum_dict<std::wstring> MiscSubTypeDisplayMap = {
		{ "gem", L"$Gem" },
		{ "dragonclaw", L"$Claw" },
		{ "artifact", L"$Artifact" },
		{ "leather", L"$Leather" },
		{ "leatherstrips", L"$Strips" },
		{ "hide", L"$Hide" },
		{ "remains", L"$Remains" },
		{ "ingot", L"$Ingot" },
		{ "tool", L"$Tool" },
		{ "childrensclothes", L"$Clothing" },
		{ "toy", L"$Toy" },
		{ "firewood", L"$Firewood" },
		//{ "fastener", L"" },
		//{ "weaponrack", L"" },
		//{ "shelf", L"" },
		//{ "furniture", L"" },
		//{ "exterior", L"" },
		//{ "container", L"" },
		{ "housepart", L"$House Part" },
		{ "clutter", L"$Clutter" },
		{ "lockpick", L"$Lockpick" },
		{ "gold", L"$Gold" },
	};
}
