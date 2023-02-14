#include "MovieManager.h"

#include "Data/CustomDataManager.h"

namespace Hooks
{
	MovieManager* MovieManager::GetSingleton()
	{
		static MovieManager singleton{};
		return &singleton;
	}

	void MovieManager::Install()
	{
		auto hook = REL::Relocation<std::uintptr_t>(
			RE::Offset::BSScaleformManager::LoadMovie,
			0x1DD);

		if (!REL::make_pattern<"FF 15">().match(hook.address())) {
			util::report_and_fail("Failed to install MovieManager");
		}

		auto& trampoline = SKSE::GetTrampoline();
		auto ptr = trampoline.write_call<6>(hook.address(), &AddScaleformHooks);
		_SetViewScaleMode = *reinterpret_cast<std::uintptr_t*>(ptr);
	}

	void MovieManager::AddScaleformHooks(
		RE::GFxMovieView* a_view,
		RE::GFxMovieView::ScaleModeType a_scaleMode)
	{
		_SetViewScaleMode(a_view, a_scaleMode);

		bool loadIcons = false;

		loadIcons |= HookProcessListFunc(a_view, "_global.CraftingIconSetter.prototype");
		loadIcons |= HookProcessListFunc(a_view, "_global.FavoritesIconSetter.prototype");
		loadIcons |= HookProcessListFunc(a_view, "_global.InventoryIconSetter.prototype");
		loadIcons |= HookProcessListFunc(a_view, "_global.MagicIconSetter.prototype");

		if (loadIcons) {
			HookInventoryListEntry(a_view, "_global.InventoryListEntry.prototype");
		}
	}

	bool MovieManager::HookProcessListFunc(RE::GFxMovieView* a_view, const char* a_pathToObj)
	{
		RE::GFxValue obj;
		a_view->GetVariable(&obj, a_pathToObj);
		if (!obj.IsObject()) {
			return false;
		}

		logger::trace("Hooking {}.processList", a_pathToObj);
		{
			RE::GFxValue processList_old;
			obj.GetMember("processList", &processList_old);

			RE::GFxValue processList;
			auto processListImpl = RE::make_gptr<ProcessListFunc>(processList_old);

			a_view->CreateFunction(&processList, processListImpl.get());
			obj.SetMember("processList", processList);
		}

		return true;
	}

	bool MovieManager::HookInventoryListEntry(RE::GFxMovieView* a_view, const char* a_pathToObj)
	{
		RE::GFxValue obj;
		a_view->GetVariable(&obj, a_pathToObj);
		if (!obj.IsObject()) {
			return false;
		}

		logger::trace("Hooking {}.initialize", a_pathToObj);
		{
			RE::GFxValue initialize;
			auto initializeImpl = RE::make_gptr<InventoryListEntry_InitializeFunc>();

			a_view->CreateFunction(&initialize, initializeImpl.get());
			obj.SetMember("initialize", initialize);
		}

		logger::trace("Hooking {}.formatItemIcon", a_pathToObj);
		{
			RE::GFxValue formatItemIcon;
			auto formatItemIconImpl = RE::make_gptr<FormatItemIconFunc>();

			a_view->CreateFunction(&formatItemIcon, formatItemIconImpl.get());
			obj.SetMember("formatItemIcon", formatItemIcon);
		}

		return true;
	}

	void MovieManager::ProcessListFunc::Call(Params& a_params)
	{
		logger::trace("Running IconSetter.processList hook");

		if (_oldFunc.IsObject()) {
			_oldFunc.Invoke(
				"call",
				a_params.retVal,
				a_params.argsWithThisRef,
				static_cast<std::size_t>(a_params.argCount) + 1);
		}

		if (a_params.argCount != 1) {
			logger::debug("Received wrong number of arguments");
			return;
		}

		auto& a_list = a_params.args[0];
		if (!a_list.IsObject()) {
			logger::debug("a_list was not an object");
			return;
		}

		RE::GFxValue entryList;
		a_list.GetMember("_entryList", &entryList);
		if (!entryList.IsArray()) {
			logger::debug("Could not get entry list");
			return;
		}

		for (std::uint32_t i = 0, size = entryList.GetArraySize(); i < size; i++) {
			RE::GFxValue entryObject;
			entryList.GetElement(i, &entryObject);
			if (entryObject.IsObject()) {
				ProcessEntry(a_params.thisPtr, &entryObject);
			}
		}
	}

	void MovieManager::ProcessEntry(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject)
	{
		const auto inventoryManager = Data::CustomDataManager::GetSingleton();

		auto processIconCallback = std::bind_front(&ProcessIconInternal, a_thisPtr);
		inventoryManager->ProcessEntry(a_entryObject, processIconCallback);
	}

	void MovieManager::ProcessIconInternal(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject)
	{
		RE::GFxValue formType;
		a_entryObject->GetMember("formType", &formType);
		if (!formType.IsNumber()) {
			return;
		}

		switch (static_cast<RE::FormType>(formType.GetNumber())) {
		case RE::FormType::Spell:
			a_thisPtr->Invoke("processSpellIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Armor:
			a_thisPtr->Invoke("processArmorIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Book:
			a_thisPtr->Invoke("processBookIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Misc:
			a_thisPtr->Invoke("processMiscIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Weapon:
			a_thisPtr->Invoke("processWeaponIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Ammo:
			a_thisPtr->Invoke("processAmmoIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::AlchemyItem:
			a_thisPtr->Invoke("processPotionIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::SoulGem:
			a_thisPtr->Invoke("processSoulGemIcon", nullptr, a_entryObject, 1);
			break;
		}
	}

	void MovieManager::InventoryListEntry_InitializeFunc::Call(Params& a_params)
	{
		logger::trace("Running InventoryListEntry.initialize hook");

		a_params.thisPtr->Invoke("super.initialize", nullptr, nullptr, 0);

		RE::GFxValue itemIcon;
		a_params.thisPtr->GetMember("itemIcon", &itemIcon);
		if (itemIcon.IsObject()) {
			itemIcon.SetMember("_visible", false);
		}

		RE::GFxValue equipIcon;
		a_params.thisPtr->GetMember("equipIcon", &equipIcon);
		if (equipIcon.IsObject()) {
			equipIcon.SetMember("_visible", false);
		}

		for (int i = 0;; i++) {
			RE::GFxValue textField;
			a_params.thisPtr->GetMember(fmt::format("textField{}", i).c_str(), &textField);

			if (!textField.IsObject()) {
				break;
			}

			textField.SetMember("_visible", false);
		}
	}

	void MovieManager::FormatItemIconFunc::Call(Params& a_params)
	{
		logger::trace("Running InventoryListEntry.formatItemIcon hook");

		if (a_params.argCount != 3) {
			logger::debug("Expected 3 arguments, received {}", a_params.argCount);
			return;
		}

		[[maybe_unused]] auto& a_entryField = a_params.args[0];
		auto& a_entryObject = a_params.args[1];
		auto& a_state = a_params.args[2];

		if (!a_entryObject.IsObject()) {
			logger::debug("a_entryObject was not an object");
			return;
		}

		std::string source = "skyui/icons_item_psychosteve.swf";

		if (a_state.IsObject()) {
			RE::GFxValue iconSource;
			a_state.GetMember("iconSource", &iconSource);

			if (iconSource.IsString()) {
				source = iconSource.GetString();
			}

			a_entryObject.GetMember("iconSource", &iconSource);

			if (iconSource.IsString()) {
				source = iconSource.GetString();
			}
		}

		RE::GFxValue iconLabel;
		a_entryObject.GetMember("iconLabel", &iconLabel);
		if (iconLabel.IsNull()) {
			iconLabel = "default_misc";
		}
		a_params.thisPtr->SetMember("_iconLabel", iconLabel);

		RE::GFxValue iconColor;
		a_entryObject.GetMember("iconColor", &iconColor);
		a_params.thisPtr->SetMember("_iconColor", iconColor);

		RE::GFxValue iconLoader;
		a_params.movie->CreateObject(&iconLoader, "MovieClipLoader");

		iconLoader.Invoke("addListener", nullptr, a_params.thisPtr, 1);

		std::array<RE::GFxValue, 2> loadClipArgs;
		loadClipArgs[0] = source;
		a_params.thisPtr->GetMember("itemIcon", &loadClipArgs[1]);
		iconLoader.Invoke("loadClip", loadClipArgs);

		RE::GFxValue itemIcon;
		a_params.thisPtr->GetMember("itemIcon", &itemIcon);
		if (itemIcon.IsObject()) {
			itemIcon.SetMember("_visible", false);
		}

		RE::GFxValue equipIcon;
		a_params.thisPtr->GetMember("equipIcon", &equipIcon);
		if (equipIcon.IsObject()) {
			equipIcon.SetMember("_visible", false);
		}
	}
}
