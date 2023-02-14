#pragma once

namespace Hooks
{
	class InventoryListEntry final
	{
	public:
		InventoryListEntry() = delete;

		static void Install(RE::GFxMovieView* a_view, const char* a_pathToObj);

	private:
		class InitializeFunc : public RE::GFxFunctionHandler
		{
		public:
			void Call(Params& a_params) override;
		};

		class FormatItemIconFunc : public RE::GFxFunctionHandler
		{
		public:
			void Call(Params& a_params) override;
		};
	};
}
