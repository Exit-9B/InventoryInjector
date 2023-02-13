#pragma once

namespace Data
{
	class CustomDataManager final
	{
	public:
		static CustomDataManager* GetSingleton();

		CustomDataManager(const CustomDataManager&) = delete;
		CustomDataManager(CustomDataManager&&) = delete;
		CustomDataManager& operator=(const CustomDataManager&) = delete;
		CustomDataManager& operator=(CustomDataManager&&) = delete;

		void LoadConfigs();

		void ProcessEntry(
			RE::GFxValue* a_entryObject,
			std::function<void(RE::GFxValue*)> a_processIconCallback);

	private:
		CustomDataManager() = default;
	};
}
