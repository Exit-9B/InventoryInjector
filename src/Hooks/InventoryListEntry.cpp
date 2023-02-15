#include "InventoryListEntry.h"

namespace Hooks
{
	void InventoryListEntry::Install(RE::GFxMovieView* a_view, const char* a_pathToObj)
	{
		assert(a_view);

		RE::GFxValue obj;
		a_view->GetVariable(&obj, a_pathToObj);
		if (!obj.IsObject()) {
			return;
		}

		logger::trace("Hooking {}.initialize", a_pathToObj);
		{
			RE::GFxValue initialize;
			auto initializeImpl = RE::make_gptr<InitializeFunc>();

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
	}

	void InventoryListEntry::InitializeFunc::Call(Params& a_params)
	{
		logger::trace("Running InventoryListEntry.initialize hook");

		assert(a_params.thisPtr);

		RE::GFxValue super;
		a_params.thisPtr->GetMember("__proto__", &super);
		if (super.IsObject()) {
			super.Invoke("initialize");
		}

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

	void InventoryListEntry::FormatItemIconFunc::Call(Params& a_params)
	{
		logger::trace("Running InventoryListEntry.formatItemIcon hook");

		assert(a_params.thisPtr);

		if (a_params.argCount != 3) {
			logger::debug("Expected 3 arguments, received {}", a_params.argCount);
			return;
		}

		auto& a_entryField = a_params.args[0];
		auto& a_entryObject = a_params.args[1];
		auto& a_state = a_params.args[2];

		if (!a_entryObject.IsObject()) {
			logger::debug("a_entryObject was not an object");
			return;
		}

		constexpr std::string_view DEFAULT_SOURCE = "skyui/icons_items_psychosteve.swf";
		std::string source{ DEFAULT_SOURCE };

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

		RE::GFxValue itemIcon;
		a_params.thisPtr->GetMember("itemIcon", &itemIcon);
		if (!itemIcon.IsObject()) {
			logger::debug("Failed to get item icon movie clip");
			return;
		}

		RE::GFxValue iconSource;
		a_params.thisPtr->GetMember("_iconSource", &iconSource);
		bool sourceChanged = !iconSource.IsString() || iconSource.GetString() != source;

		iconSource = source;
		a_params.thisPtr->SetMember("_iconSource", iconSource);

		if (sourceChanged) {
			RE::GFxValue iconLoader;
			a_params.movie->CreateObject(&iconLoader, "MovieClipLoader");

			iconLoader.Invoke("addListener", nullptr, a_params.thisPtr, 1);

			std::array<RE::GFxValue, 2> loadClipArgs{ iconSource, itemIcon };
			iconLoader.Invoke("loadClip", loadClipArgs);

			itemIcon.SetMember("_visible", false);
		}
		else {
			a_entryField.Invoke("gotoAndStop", nullptr, &iconLabel, 1);
			std::array<RE::GFxValue, 2> changeIconColorArgs{ a_entryField, iconColor };
			a_params.thisPtr->Invoke("changeIconColor", changeIconColorArgs);
		}
	}
}
