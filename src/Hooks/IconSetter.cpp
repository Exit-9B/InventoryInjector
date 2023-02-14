#include "IconSetter.h"

#include "Data/CustomDataManager.h"

namespace Hooks
{
	void IconSetter::Install(RE::GFxMovieView* a_view, const char* a_pathToObj)
	{
		assert(a_view);

		RE::GFxValue obj;
		a_view->GetVariable(&obj, a_pathToObj);
		if (!obj.IsObject()) {
			return;
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
	}

	void IconSetter::ProcessListFunc::Call(Params& a_params)
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
			logger::debug("Expected 1 argument, received {}", a_params.argCount);
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

	void IconSetter::ProcessEntry(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject)
	{
		const auto inventoryManager = Data::CustomDataManager::GetSingleton();

		auto processIconCallback = std::bind_front(&ProcessIconInternal, a_thisPtr);
		inventoryManager->ProcessEntry(a_entryObject, processIconCallback);
	}

	void IconSetter::ProcessIconInternal(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject)
	{
		assert(a_thisPtr);
		assert(a_entryObject);

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
