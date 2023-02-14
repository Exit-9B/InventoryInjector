#pragma once

namespace Hooks
{
	class MovieManager final
	{
	public:
		static MovieManager* GetSingleton();

		~MovieManager() = default;
		MovieManager(const MovieManager&) = delete;
		MovieManager(MovieManager&&) = delete;
		MovieManager& operator=(const MovieManager&) = delete;
		MovieManager& operator=(MovieManager&&) = delete;

		void Install();

	private:
		class ProcessListFunc : public RE::GFxFunctionHandler
		{
		public:
			ProcessListFunc(RE::GFxValue a_oldFunc) : _oldFunc(a_oldFunc) {}

			void Call(Params& a_params) override;

		private:
			RE::GFxValue _oldFunc;
		};

		class InventoryListEntry_InitializeFunc : public RE::GFxFunctionHandler
		{
		public:
			void Call(Params& a_params) override;
		};

		class FormatItemIconFunc : public RE::GFxFunctionHandler
		{
		public:
			void Call(Params& a_params) override;
		};

		MovieManager() = default;

		static void AddScaleformHooks(
			RE::GFxMovieView* a_view,
			RE::GFxMovieView::ScaleModeType a_scaleMode);

		static bool HookProcessListFunc(RE::GFxMovieView* a_view, const char* a_pathToObj);

		static bool HookInventoryListEntry(RE::GFxMovieView* a_view, const char* a_pathToObj);

		static void ProcessEntry(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject);

		static void ProcessIconInternal(RE::GFxValue* a_thisPtr, RE::GFxValue* a_entryObject);

		inline static REL::Relocation<decltype(&AddScaleformHooks)> _SetViewScaleMode;
	};
}
