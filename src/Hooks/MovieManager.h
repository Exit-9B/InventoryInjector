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
		MovieManager() = default;

		static void AddScaleformHooks(
			RE::GFxMovieView* a_view,
			RE::GFxMovieView::ScaleModeType a_scaleMode);

		inline static REL::Relocation<decltype(&AddScaleformHooks)> _SetViewScaleMode;
	};
}
