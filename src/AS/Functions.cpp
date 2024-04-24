#include "Functions.h"

#include "Data/CustomDataManager.h"
#include "Data/IconUtil.h"

#define REGISTER_FN(fn)                                \
	static auto handler_##fn = new fn();               \
	RE::GFxValue value_##fn;                           \
	a_view->CreateFunction(&value_##fn, handler_##fn); \
	a_root->SetMember(#fn, value_##fn)

namespace AS
{
	void ProcessEntry::Call(Params& a_params)
	{
		if (a_params.argCount < 1) {
			logger::debug("Expected 1 argument, received {}", a_params.argCount);
			return;
		}

		auto& a_entryObject = a_params.args[0];

		const auto dataManager = Data::CustomDataManager::GetSingleton();
		dataManager->ProcessEntry(&a_entryObject, &Data::IconUtil::ProcessDefaultIcon);
	}

	bool RegisterFuncs(RE::GFxMovieView* a_view, RE::GFxValue* a_root)
	{
		REGISTER_FN(ProcessEntry);

		return true;
	}
}
