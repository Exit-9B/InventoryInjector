#pragma once

#include "Data/Rule.h"

namespace Data
{
	class CustomDataManager final
	{
	public:
		static CustomDataManager* GetSingleton();

		~CustomDataManager() = default;
		CustomDataManager(const CustomDataManager&) = delete;
		CustomDataManager(CustomDataManager&&) = delete;
		CustomDataManager& operator=(const CustomDataManager&) = delete;
		CustomDataManager& operator=(CustomDataManager&&) = delete;

		void LoadConfigs();

		void ProcessEntry(
			RE::GFxValue* a_entryObject,
			std::function<void(RE::GFxValue*)> a_processIconCallback) const;

	private:
		CustomDataManager() = default;

		void LoadConfig(const std::filesystem::path& a_path);

		std::vector<Rule> _rules;
	};
}
