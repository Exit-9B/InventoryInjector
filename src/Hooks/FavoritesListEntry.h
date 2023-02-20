#pragma once

namespace Hooks
{
	class FavoritesListEntry final
	{
	public:
		FavoritesListEntry() = delete;

		static void Install(RE::GFxMovieView* a_view, const char* a_pathToObj);

	private:
		class SetEntryFunc : public RE::GFxFunctionHandler
		{
		public:
			SetEntryFunc(const RE::GFxValue& a_oldFunc) : _oldFunc{ a_oldFunc } {}

			void Call(Params& a_params) override;

		private:
			RE::GFxValue _oldFunc;
		};

		class OnLoadInitFunc : public RE::GFxFunctionHandler
		{
		public:
			void Call(Params& a_params) override;
		};

		static void ChangeIconColor(
			RE::GFxMovie* a_movie,
			const RE::GFxValue& a_icon,
			const RE::GFxValue& a_rgb);
	};
}
