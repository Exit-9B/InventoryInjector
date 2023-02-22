#include "GroupDataExtender.h"

#include "FavoritesListEntry.h"

namespace Hooks
{
	void GroupDataExtender::Install(RE::GFxMovieView* a_view, const char* a_pathToObj)
	{
		assert(a_view);

		RE::GFxValue obj;
		a_view->GetVariable(&obj, a_pathToObj);
		if (!obj.IsObject()) {
			return;
		}

		logger::trace("Hooking {}.processIconData", a_pathToObj);
		{
			RE::GFxValue processIconData;
			auto processIconDataImpl = RE::make_gptr<ProcessIconDataFunc>();

			a_view->CreateFunction(&processIconData, processIconDataImpl.get());
			obj.SetMember("processIconData", processIconData);
		}

		logger::trace("Hooking {}.onLoadInit", a_pathToObj);
		{
			RE::GFxValue onLoadInit;
			auto onLoadInitImpl = RE::make_gptr<OnLoadInitFunc>();

			a_view->CreateFunction(&onLoadInit, onLoadInitImpl.get());
			obj.SetMember("onLoadInit", onLoadInit);
		}
	}

	void GroupDataExtender::ProcessIconDataFunc::Call(Params& a_params)
	{
		RE::GFxValue iconData;
		a_params.thisPtr->GetMember("iconData", &iconData);

		if (!iconData.IsArray()) {
			return;
		}

		RE::GFxValue groupButtons;
		a_params.thisPtr->GetMember("_groupButtons", &groupButtons);

		if (!groupButtons.IsArray()) {
			return;
		}

		for (std::uint32_t i = 0, size = iconData.GetArraySize(); i < size; i++) {
			RE::GFxValue iconSource;
			RE::GFxValue itemId;
			iconData.GetElement(i, &itemId);
			if (itemId.IsNumber()) {
				RE::GFxValue itemIdMap;
				a_params.thisPtr->GetMember("_itemIdMap", &itemIdMap);
				RE::GFxValue t;
				std::string itemIdStr = fmt::format("{}", itemId.GetNumber());
				if (itemIdMap.IsObject()) {
					itemIdMap.GetMember(itemIdStr.c_str(), &t);
				}

				if (t.IsObject()) {
					t.GetMember("iconSource", &iconSource);
				}
				else {
					a_params.thisPtr->Invoke("reportInvalidItem", nullptr, &itemId, 1);
				}
			}

			if (iconSource.IsUndefined()) {
				iconSource = "skyui/icons_item_psychosteve.swf";
			}

			RE::GFxValue groupButton;
			groupButtons.GetElement(i, &groupButton);

			RE::GFxValue itemIcon;
			if (groupButton.IsObject()) {
				groupButton.GetMember("itemIcon", &itemIcon);
			}

			if (itemIcon.IsDisplayObject()) {
				RE::GFxValue iconLoader;
				a_params.movie->CreateObject(&iconLoader, "MovieClipLoader");
				if (!iconLoader.IsObject()) {
					logger::debug("Failed to create MovieClipLoader object");
					return;
				}

				iconLoader.Invoke("addListener", nullptr, a_params.thisPtr, 1);

				std::array<RE::GFxValue, 2> loadClipArgs{ iconSource, itemIcon };
				iconLoader.Invoke("loadClip", loadClipArgs);

				itemIcon.SetMember("_visible", false);
			}
		}
	}

	void GroupDataExtender::OnLoadInitFunc::Call(Params& a_params)
	{
		if (a_params.argCount < 1) {
			logger::debug("Expected 1 argument, received {}", a_params.argCount);
			return;
		}

		auto& a_icon = a_params.args[0];

		RE::GFxValue iconData;
		a_params.thisPtr->GetMember("iconData", &iconData);

		if (!iconData.IsArray()) {
			return;
		}

		RE::GFxValue groupButtons;
		a_params.thisPtr->GetMember("_groupButtons", &groupButtons);

		if (!groupButtons.IsArray()) {
			return;
		}

		std::uint32_t i = 0, size = groupButtons.GetArraySize();
		for (; i < size; i++) {
			RE::GFxValue groupButton;
			groupButtons.GetElement(i, &groupButton);
			if (!groupButton.IsObject()) {
				continue;
			}

			RE::GFxValue itemIcon;
			groupButton.GetMember("itemIcon", &itemIcon);
			if (itemIcon == a_icon) {
				break;
			}
		}

		if (i == size) {
			return;
		}

		RE::GFxValue iconLabel;
		RE::GFxValue iconColor;
		RE::GFxValue itemId;
		iconData.GetElement(i, &itemId);
		if (itemId.IsNumber()) {
			RE::GFxValue itemIdMap;
			a_params.thisPtr->GetMember("_itemIdMap", &itemIdMap);
			RE::GFxValue t;
			std::string itemIdStr = fmt::format("{}", itemId.GetNumber());
			if (itemIdMap.IsObject()) {
				itemIdMap.GetMember(itemIdStr.c_str(), &t);
			}

			if (t.IsObject()) {
				t.GetMember("iconLabel", &iconLabel);
				t.GetMember("iconColor", &iconColor);
			}
		}

		if (iconLabel.IsUndefined()) {
			iconLabel = 1;
		}

		a_icon.Invoke("gotoAndStop", nullptr, &iconLabel, 1);

		FavoritesListEntry::ChangeIconColor(a_icon, iconColor);

		a_icon.VisitMembers(
			[]([[maybe_unused]] const char* a_name, const RE::GFxValue& a_val)
			{
				if (!a_val.IsDisplayObject()) {
					return;
				}

				RE::GFxValue transform;
				a_val.GetMember("transform", &transform);

				if (!transform.IsObject()) {
					return;
				}

				RE::GFxValue matrix;
				transform.GetMember("matrix", &matrix);

				if (!matrix.IsObject()) {
					return;
				}

				std::array<RE::GFxValue, 2> args{ -64.0, -64.0 };
				matrix.Invoke("translate", args);

				transform.SetMember("matrix", matrix);
			});
	}
}
