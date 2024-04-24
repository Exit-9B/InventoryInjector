#pragma once

namespace Data
{
	class IconUtil final
	{
	public:
		static void ProcessDefaultIcon(RE::GFxValue* a_entryObject);

	private:
		static void ProcessSpellIcon(RE::GFxValue* a_entryObject);
		static void ProcessSpellResist(RE::GFxValue* a_entryObject);
		static void ProcessScrollResist(RE::GFxValue* a_entryObject);
		static void ProcessArmorIcon(RE::GFxValue* a_entryObject);
		static void ProcessLightArmorIcon(RE::GFxValue* a_entryObject);
		static void ProcessHeavyArmorIcon(RE::GFxValue* a_entryObject);
		static void ProcessJewelryArmorIcon(RE::GFxValue* a_entryObject);
		static void ProcessClothingArmorIcon(RE::GFxValue* a_entryObject);
		static void ProcessBookIcon(RE::GFxValue* a_entryObject);
		static void ProcessWeaponIcon(RE::GFxValue* a_entryObject);
		static void ProcessAmmoIcon(RE::GFxValue* a_entryObject);
		static void ProcessPotionIcon(RE::GFxValue* a_entryObject);
		static void ProcessSoulGemIcon(RE::GFxValue* a_entryObject);
		static void ProcessGrandSoulGemIcon(RE::GFxValue* a_entryObject);
		static void ProcessSoulGemStatusIcon(RE::GFxValue* a_entryObject);
		static void ProcessMiscIcon(RE::GFxValue* a_entryObject);
	};
}
