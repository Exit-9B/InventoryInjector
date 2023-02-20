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

		if (_oldFunc.IsObject()) {
			_oldFunc.Invoke(
				"call",
				a_params.retVal,
				a_params.argsWithThisRef,
				static_cast<std::size_t>(a_params.argCount) + 1);
		}

		if (a_params.argCount != 2) {
			logger::debug("Expected 2 arguments, received {}", a_params.argCount);
			return;
		}

		auto& a_entryObject = a_params.args[0];
		[[maybe_unused]] auto& a_state = a_params.args[1];

		RE::GFxValue iconSetter;
		a_params.movie->GetVariable(&iconSetter, "_global.FavoritesIconSetter");
		if (!iconSetter.IsObject()) {
			logger::debug("Failed to get FavoritesIconSetter");
			return;
		}

		IconSetter::ProcessEntry(&iconSetter, &a_entryObject);

		// The favorites menu has icons embedded but we will override those
		std::string source{ "skyui/icons_item_psychosteve.swf" };

		{
			RE::GFxValue iconSource;
			a_entryObject.GetMember("iconSource", &iconSource);

			if (iconSource.IsString()) {
				source = iconSource.GetString();
			}
		}

		RE::GFxValue iconSource;
		a_params.thisPtr->GetMember("_iconSource", &iconSource);
		bool sourceChanged = !iconSource.IsString() || iconSource.GetString() != source;

		iconSource = source;
		a_params.thisPtr->SetMember("_iconSource", iconSource);

		if (sourceChanged) {
			RE::GFxValue iconLabel;
			a_entryObject.GetMember("iconLabel", &iconLabel);
			if (iconLabel.IsUndefined()) {
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
		if (!iconLabel.IsString()) {
			logger::debug("Failed to get icon label for custom source");
			iconLabel = "default_misc";
		}

		a_icon.Invoke("gotoAndStop", nullptr, &iconLabel, 1);
		a_icon.SetMember("_x", 0);
		a_icon.SetMember("_y", 0);

		RE::GFxValue iconColor;
		a_params.thisPtr->GetMember("_iconColor", &iconColor);
		ChangeIconColor(a_params.movie, a_icon, iconColor);
	}

	void FavoritesListEntry::ChangeIconColor(
		RE::GFxMovie* a_movie,
		const RE::GFxValue& a_icon,
		const RE::GFxValue& a_rgb)
	{
		if (!a_icon.IsDisplayObject()) {
			logger::debug("ChangeIconColor received bad arguments");
			return;
		}

		struct ObjectVisitor : RE::GFxValue::ObjectVisitor
		{
			ObjectVisitor(RE::GFxMovie* a_movie, const RE::GFxValue& a_rgb)
				: movie_{ a_movie },
				  rgb_{ a_rgb }
			{
			}

			void Visit([[maybe_unused]] const char* a_name, const RE::GFxValue& a_val) override
			{
				if (!a_val.IsDisplayObject()) {
					return;
				}

				RE::GFxValue ct;
				movie_->CreateObject(&ct, "flash.geom.ColorTransform");
				if (!ct.IsObject()) {
					logger::debug("Failed to create ColorTransform object");
					return;
				}

				RE::GFxValue tf;
				movie_->CreateObject(&tf, "flash.geom.Transform", &a_val, 1);
				if (!ct.IsObject()) {
					logger::debug("Failed to create Transform object");
					return;
				}

				ct.SetMember("rgb", rgb_.IsNumber() ? rgb_.GetNumber() : 0xFFFFFF);
				tf.SetMember("colorTransform", ct);
			}

			RE::GFxMovie* movie_;
			const RE::GFxValue& rgb_;
		};

		ObjectVisitor visitor{ a_movie, a_rgb };
		a_icon.VisitMembers(&visitor);
	}
}
