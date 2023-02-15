#pragma once

#include "Config/Rule.h"

namespace Data
{
	class Value
	{
	public:
		virtual void Set(RE::GFxValue& a_value) const = 0;

		virtual RE::GFxValue Retrieve(RE::GFxValue& a_entryObject) const = 0;
	};

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
