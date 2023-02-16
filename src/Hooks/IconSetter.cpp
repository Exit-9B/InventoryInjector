#include "IconSetter.h"

#include "Data/CustomDataManager.h"
#include "Data/Defines/Book.h"

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

		if (a_params.argCount < 1) {
			logger::debug("Expected 1 argument, received {}", a_params.argCount);
			return;
		}

		auto& a_list = a_params.args[0];
		RE::GFxValue entryList;
		if (a_list.IsObject()) {
			a_list.GetMember("_entryList", &entryList);
		}

		if (entryList.IsArray()) {
			for (std::uint32_t i = 0, size = entryList.GetArraySize(); i < size; i++) {
				RE::GFxValue entryObject;
				entryList.GetElement(i, &entryObject);
				if (entryObject.IsObject()) {
					if (entryObject.HasMember("bookType")) {
						FixNote(entryObject);
					}
				}
			}
		}

		if (_oldFunc.IsObject()) {
			_oldFunc.Invoke(
				"call",
				a_params.retVal,
				a_params.argsWithThisRef,
				static_cast<std::size_t>(a_params.argCount) + 1);
		}

		if (entryList.IsArray()) {
			for (std::uint32_t i = 0, size = entryList.GetArraySize(); i < size; i++) {
				RE::GFxValue entryObject;
				entryList.GetElement(i, &entryObject);
				if (entryObject.IsObject()) {
					ProcessEntry(a_params.thisPtr, &entryObject);
				}
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

	void IconSetter::FixNote(RE::GFxValue& a_entryObject)
	{
		RE::GFxValue formId;
		a_entryObject.GetMember("formId", &formId);

		RE::TESObjectBOOK* book = nullptr;
		if (formId.IsNumber()) {
			book = RE::TESForm::LookupByID<RE::TESObjectBOOK>(
				static_cast<RE::FormID>(formId.GetNumber()));
		}

		if (!book) {
			return;
		}

		auto stem = std::filesystem::path(book->model.c_str()).stem().string();

		auto range = std::ranges::search(
			stem,
			"Note"sv,
			[](char ch1, char ch2)
			{
				return std::toupper(ch1) == std::toupper(ch2);
			});

		bool isNote = !range.empty();

		if (isNote) {
			a_entryObject.SetMember("bookType", 0xFF);

			RE::GFxValue subType;
			a_entryObject.GetMember("subType", &subType);

			if (subType.IsUndefined()) {
				a_entryObject.SetMember("subType", util::to_underlying(Data::BookType::Note));
			}
		}
	}
}
