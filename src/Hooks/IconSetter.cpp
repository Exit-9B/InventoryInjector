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

		if (!a_params.thisPtr->HasMember("_noIconColors")) {
			a_params.thisPtr->SetMember("_noIconColors", GetNoIconColors());
		}

		auto& a_list = a_params.args[0];
		RE::GFxValue entryList;
		if (a_list.IsObject()) {
			a_list.GetMember("_entryList", &entryList);
		}

		if (!entryList.IsArray()) {
			return;
		}

		for (std::uint32_t i = 0, size = entryList.GetArraySize(); i < size; i++) {
			RE::GFxValue entryObject;
			entryList.GetElement(i, &entryObject);
			ModifyObject(a_params.movie, entryObject);
		}

		if (_oldFunc.IsObject()) {
			_oldFunc.Invoke(
				"call",
				a_params.retVal,
				a_params.argsWithThisRef,
				static_cast<std::size_t>(a_params.argCount) + 1);
		}

		RE::GFxValue _noIconColors;
		a_params.thisPtr->GetMember("_noIconColors", &_noIconColors);
		bool noIconColors = _noIconColors.IsBool() && _noIconColors.GetBool();
		RE::GFxValue defaultColor;

		if (noIconColors) {
			RE::GFxValue dummy;
			a_params.movie->CreateObject(&dummy);

			auto dataManager = Data::CustomDataManager::GetSingleton();
			dataManager->ProcessEntry(&dummy, {});

			dummy.GetMember("iconColor", &defaultColor);
		}

		for (std::uint32_t i = 0, size = entryList.GetArraySize(); i < size; i++) {
			RE::GFxValue entryObject;
			entryList.GetElement(i, &entryObject);
			if (!entryObject.IsObject()) {
				continue;
			}

			ProcessEntry(a_params.thisPtr, &entryObject);

			if (noIconColors && entryObject.HasMember("iconColor")) {
				if (defaultColor.IsUndefined()) {
					entryObject.DeleteMember("iconColor");
				}
				else {
					entryObject.SetMember("iconColor", defaultColor);
				}
			}
		}
	}

	void IconSetter::ProcessEntry(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject)
	{
		const auto dataManager = Data::CustomDataManager::GetSingleton();

		auto processIconCallback = std::bind_front(&ProcessIconInternal, a_thisPtr);
		dataManager->ProcessEntry(a_entryObject, processIconCallback);
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
		case RE::FormType::Scroll:
			a_entryObject->SetMember("iconLabel", "default_scroll");
			a_thisPtr->Invoke("processResist", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Armor:
			a_thisPtr->Invoke("processArmorIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Book:
			a_thisPtr->Invoke("processBookIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::Ingredient:
			a_entryObject->SetMember("iconLabel", "default_ingredient");
			break;
		case RE::FormType::Light:
			a_entryObject->SetMember("iconLabel", "misc_torch");
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
		case RE::FormType::KeyMaster:
			a_entryObject->SetMember("iconLabel", "default_key");
			break;
		case RE::FormType::AlchemyItem:
			a_thisPtr->Invoke("processPotionIcon", nullptr, a_entryObject, 1);
			break;
		case RE::FormType::SoulGem:
			a_thisPtr->Invoke("processSoulGemIcon", nullptr, a_entryObject, 1);
			break;
		}
	}

	void IconSetter::ModifyObject(RE::GFxMovie* a_movie, RE::GFxValue& a_entryObject)
	{
		if (!a_entryObject.IsObject()) {
			return;
		}

		RE::GFxValue formType;
		a_entryObject.GetMember("formType", &formType);
		if (!formType.IsNumber()) {
			return;
		}

		switch (static_cast<RE::FormType>(formType.GetNumber())) {
		case RE::FormType::Spell:
		case RE::FormType::Scroll:
		case RE::FormType::Ingredient:
		case RE::FormType::AlchemyItem:
		case RE::FormType::MagicEffect:
		{
			// SkyUI normally does this, except for the Favorites menu
			RE::GFxValue magicType;
			a_entryObject.GetMember("magicType", &magicType);
			if (!magicType.IsUndefined()) {
				a_entryObject.SetMember("resistance", magicType);
				a_entryObject.DeleteMember("magicType");
			}

			ExtendMagicItemData(a_movie, a_entryObject);
		} break;

		case RE::FormType::Book:
		{
			FixNote(a_entryObject);
		} break;
		}
	}

	void IconSetter::ExtendMagicItemData(RE::GFxMovie* a_movie, RE::GFxValue& a_entryObject)
	{
		RE::GFxValue formId;
		a_entryObject.GetMember("formId", &formId);

		const RE::MagicItem* magicItem = nullptr;
		if (formId.IsNumber()) {
			auto form = RE::TESForm::LookupByID(static_cast<RE::FormID>(formId.GetNumber()));
			magicItem = skyrim_cast<RE::MagicItem*>(form);
		}

		if (!magicItem) {
			return;
		}

		RE::GFxValue keywordRoot;
		a_movie->CreateObject(&keywordRoot);

		for (const auto effect : magicItem->effects) {
			const auto baseEffect = effect ? effect->baseEffect : nullptr;
			if (!baseEffect) {
				continue;
			}

			for (const auto keyword : std::span(baseEffect->keywords, baseEffect->numKeywords)) {
				if (keyword) {
					keywordRoot.SetMember(keyword->formEditorID.c_str(), true);
				}
			}
		}

		a_entryObject.SetMember("effectKeywords", keywordRoot);
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
				a_entryObject.SetMember("subTypeDisplay", L"$Note");
			}
		}
	}

	bool IconSetter::GetNoIconColors()
	{
		bool noIconColors = false;
		bool hasOverride = false;

		RE::BSTSmartPointer<RE::BSScript::Object> scriptObject;

		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		const auto settingsManager = dataHandler
			? dataHandler->LookupForm(0x80A, "SkyUI_SE.esp"sv)
			: nullptr;

		if (settingsManager) {
			const auto skyrimVM = RE::SkyrimVM::GetSingleton();
			const auto vm = skyrimVM ? skyrimVM->impl : nullptr;
			const auto typeID = static_cast<RE::VMTypeID>(settingsManager->GetFormType());
			const auto policy = vm ? vm->GetObjectHandlePolicy() : nullptr;
			const auto handle = policy ? policy->GetHandleForObject(typeID, settingsManager) : 0;

			if (handle) {
				vm->FindBoundObject(handle, "SKI_SettingsManager", scriptObject);
			}
		}

		if (scriptObject) {
			const auto overrideKeys = scriptObject->GetVariable("_overrideKeys"sv);
			const auto overrideValues = scriptObject->GetVariable("_overrideValues"sv);
			const auto keys = overrideKeys->IsArray() ? overrideKeys->GetArray() : nullptr;
			const auto values = overrideValues->IsArray() ? overrideValues->GetArray() : nullptr;

			constexpr auto INVALID = static_cast<std::uint32_t>(-1);
			auto idx = INVALID;
			if (keys && values) {
				for (std::uint32_t i = 0, size = keys->size(); i < size; i++) {
					auto& key = (*keys)[i];
					if (key.IsString() && key.GetString() == "Appearance$icons$item$noColor"sv) {
						idx = i;
						break;
					}
				}

				if (idx != INVALID) {
					auto& value = (*values)[idx];
					if (value.IsString()) {
						noIconColors = util::iequals(value.GetString(), "true"sv);
						hasOverride = true;
					}
				}
			}
		}

		if (hasOverride) {
			return noIconColors;
		}

		RE::BSResourceNiBinaryStream fileStream{ R"(Data\Interface\skyui\config.txt)" };
		if (fileStream.good()) {
			auto size = fileStream.stream->totalSize;
			std::string text(size, '\0');
			fileStream.read(text.data(), size);

			auto section = text.find("[Appearance]");
			auto pos = section != std::string::npos
				? text.find("icons.item.noColor", section)
				: std::string::npos;

			auto eq = pos != std::string::npos ? text.find('=', pos) : std::string::npos;

			if (eq != std::string::npos) {
				auto end = text.find('\n', eq);
				if (end == std::string::npos) {
					end = text.size();
				}

				auto value = std::string_view(&text[eq], end - eq);
				value.remove_prefix(value.find_first_not_of(" ="));
				value.remove_suffix(value.size() - value.find_last_not_of(" \r\n") - 1);

				noIconColors = util::iequals(value, "true"sv);
			}
		}

		return noIconColors;
	}
}
