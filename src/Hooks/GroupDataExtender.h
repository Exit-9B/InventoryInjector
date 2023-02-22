#pragma once

namespace Hooks
{
	class GroupDataExtender
	{
	public:
		GroupDataExtender() = delete;

		static void Install(RE::GFxMovieView* a_view, const char* a_pathToObj);

	private:
		class ProcessIconDataFunc : public RE::GFxFunctionHandler
		{
		public:
			void Call(Params& a_params) override;
		};

		class OnLoadInitFunc : public RE::GFxFunctionHandler
		{
		public:
			void Call(Params& a_params) override;
		};
	};
}
