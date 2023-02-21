#include "FavoritesListEntry.h"

#include "Hooks/IconSetter.h"

namespace Hooks
{
	void FavoritesListEntry::Install(RE::GFxMovieView* a_view, const char* a_pathToObj)
	{
		assert(a_view);

		RE::GFxValue obj;
		a_view->GetVariable(&obj, a_pathToObj);
		if (!obj.IsObject()) {
			return;
		}

		logger::trace("Hooking {}.setEntry", a_pathToObj);
		{
			RE::GFxValue setEntry_old;
			obj.GetMember("setEntry", &setEntry_old);

			RE::GFxValue setEntry;
			auto setEntryImpl = RE::make_gptr<SetEntryFunc>(setEntry_old);

			a_view->CreateFunction(&setEntry, setEntryImpl.get());
			obj.SetMember("setEntry", setEntry);
		}

		logger::trace("Hooking {}.onLoadInit", a_pathToObj);
		{
			RE::GFxValue onLoadInit;
			auto onLoadInitImpl = RE::make_gptr<OnLoadInitFunc>();

			a_view->CreateFunction(&onLoadInit, onLoadInitImpl.get());
			obj.SetMember("onLoadInit", onLoadInit);
		}
	}

	void FavoritesListEntry::SetEntryFunc::Call(Params& a_params)
	{
		logger::trace("Running FavoritesListEntry.setEntry hook");

		assert(a_params.movie);
		assert(a_params.thisPtr);

		if (a_params.argCount < 2) {
			logger::debug("Expected 2 arguments, received {}", a_params.argCount);
			return;
		}

		if (_oldFunc.IsObject()) {
			_oldFunc.Invoke(
				"call",
				a_params.retVal,
				a_params.argsWithThisRef,
				static_cast<std::size_t>(a_params.argCount) + 1);
		}

		auto& a_entryObject = a_params.args[0];
		[[maybe_unused]] auto& a_state = a_params.args[1];

		RE::GFxValue itemIcon;
		a_params.thisPtr->GetMember("itemIcon", &itemIcon);
		if (!itemIcon.IsObject()) {
			logger::debug("Failed to get item icon movie clip");
			return;
		}

		// Favorites menu icons are offset by (64, 64) compared to icon swf
		// Icon sprite also has a transform, which might vary depending on mods
		if (!a_params.thisPtr->HasMember("_iconPosFixed")) {
			RE::GFxValue transform;
			itemIcon.GetMember("transform", &transform);

			if (transform.IsObject()) {
				RE::GFxValue matrix;
				transform.GetMember("matrix", &matrix);

				if (matrix.IsObject()) {
					RE::GFxValue sx, sy;
					matrix.GetMember("a", &sx);
					matrix.GetMember("d", &sy);

					if (sx.IsNumber() && sy.IsNumber()) {
						std::array<RE::GFxValue, 2>
							args{ -64.0 * sx.GetNumber(), -64.0 * sy.GetNumber() };
						matrix.Invoke("translate", args);

						transform.SetMember("matrix", matrix);
						a_params.thisPtr->SetMember("_iconPosFixed", true);
					}
				}
			}
		}

		// We are overriding the embedded icons in the movie
		const char* source = "skyui/icons_item_psychosteve.swf";

		{
			RE::GFxValue iconSource;
			a_entryObject.GetMember("iconSource", &iconSource);

			if (iconSource.IsString()) {
				source = iconSource.GetString();
			}
		}

		RE::GFxValue iconLabel;
		a_entryObject.GetMember("iconLabel", &iconLabel);
		if (iconLabel.IsUndefined()) {
			iconLabel = "default_misc";
		}
		a_params.thisPtr->SetMember("_iconLabel", iconLabel);

		RE::GFxValue iconColor;
		a_entryObject.GetMember("iconColor", &iconColor);
		a_params.thisPtr->SetMember("_iconColor", iconColor);

		RE::GFxValue iconSource;
		a_params.thisPtr->GetMember("_iconSource", &iconSource);
		bool sourceChanged = !iconSource.IsString() ||
			::strcmp(iconSource.GetString(), source) != 0;

		iconSource = source;
		a_params.thisPtr->SetMember("_iconSource", iconSource);

		if (sourceChanged) {
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
		else {
			ChangeIconColor(itemIcon, iconColor);
		}
	}

	void FavoritesListEntry::OnLoadInitFunc::Call(Params& a_params)
	{
		logger::trace("Running FavoritesListEntry.onLoadInit hook");

		assert(a_params.thisPtr);

		if (a_params.argCount != 1) {
			logger::debug("Expected 1 argument, received {}", a_params.argCount);
			return;
		}

		auto& a_icon = a_params.args[0];

		RE::GFxValue iconLabel;
		a_params.thisPtr->GetMember("_iconLabel", &iconLabel);
		if (iconLabel.IsUndefined()) {
			logger::debug("Failed to get icon label for custom source");
			iconLabel = "default_misc";
		}

		a_icon.Invoke("gotoAndStop", nullptr, &iconLabel, 1);

		RE::GFxValue iconColor;
		a_params.thisPtr->GetMember("_iconColor", &iconColor);
		ChangeIconColor(a_icon, iconColor);
	}

	void FavoritesListEntry::ChangeIconColor(const RE::GFxValue& a_icon, const RE::GFxValue& a_rgb)
	{
		if (!a_icon.IsDisplayObject()) {
			logger::debug("ChangeIconColor received bad arguments");
			return;
		}

		a_icon.VisitMembers(
			[&a_rgb]([[maybe_unused]] const char* a_name, const RE::GFxValue& a_val)
			{
				if (!a_val.IsDisplayObject()) {
					return;
				}

				std::uint32_t rgb = a_rgb.IsNumber()
					? static_cast<std::uint32_t>(a_rgb.GetNumber())
					: 0xFFFFFF;

				auto cx = GetColorTransform(rgb);
				const_cast<RE::GFxValue&>(a_val).SetCxform(cx);
			});
	}

	RE::GRenderer::Cxform FavoritesListEntry::GetColorTransform(std::uint32_t a_rgb)
	{
		RE::GRenderer::Cxform cx;
		cx.matrix[0][0] = 0.0f;
		cx.matrix[1][0] = 0.0f;
		cx.matrix[2][0] = 0.0f;
		cx.matrix[0][1] = static_cast<float>((a_rgb >> 16) & 0xFF);
		cx.matrix[1][1] = static_cast<float>((a_rgb >> 8) & 0xFF);
		cx.matrix[2][1] = static_cast<float>((a_rgb >> 0) & 0xFF);

		return cx;
	}
}
