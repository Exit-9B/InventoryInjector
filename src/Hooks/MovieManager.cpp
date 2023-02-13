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

		// SKSE should write these bytes
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
			// TODO Load icons
		}
	}

	bool MovieManager::HookProcessListFunc(RE::GFxMovieView* a_view, const char* a_pathToObj)
	{
		logger::trace("Hooking {}.processList", a_pathToObj);

		RE::GFxValue obj;
		a_view->GetVariable(&obj, a_pathToObj);
		if (!obj.IsObject()) {
			return false;
		}

		RE::GFxValue oldFunc;
		obj.GetMember("processList", &oldFunc);

		RE::GFxValue newFunc;
		auto funcImpl = RE::make_gptr<ProcessListFunc>(oldFunc);

		a_view->CreateFunction(&newFunc, funcImpl.get());
		obj.SetMember("processList", newFunc);

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
		if (!a_thisPtr || !a_thisPtr->IsObject()) {
			return;
		}

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
}
