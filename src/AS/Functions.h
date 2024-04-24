#pragma once

namespace AS
{
	class ProcessEntry final : public RE::GFxFunctionHandler
	{
	public:
		void Call(Params& a_params) override;
	};

	bool RegisterFuncs(RE::GFxMovieView* a_view, RE::GFxValue* a_root);
}
