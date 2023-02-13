#include "CustomDataManager.h"

namespace Data
{
	CustomDataManager* CustomDataManager::GetSingleton()
	{
		static CustomDataManager singleton{};
		return &singleton;
	}

	void CustomDataManager::LoadConfigs()
	{
		// TODO Load configs
	}

	void CustomDataManager::ProcessEntry(
		RE::GFxValue* a_entryObject,
		std::function<void(RE::GFxValue*)> a_processIconCallback)
	{
		// TODO Set data from configs

		// hardcoded stuff for testing
		bool dataChanged = false;
		RE::GFxValue formId;
		a_entryObject->GetMember("formId", &formId);

		switch (static_cast<RE::FormID>(formId.GetNumber())) {
		case 0x040179C9:
		case 0x040206F2:
		case 0x040398E6:
			a_entryObject->SetMember("subType", 11);
			a_entryObject->SetMember("subTypeDisplay", "$Pickaxe");
			dataChanged = true;
			break;
		}

		if (dataChanged) {
			a_processIconCallback(a_entryObject);
		}
	}
}
