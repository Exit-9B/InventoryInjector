#include "CustomDataManager.h"

#include "Data/Config/RuleParser.h"

#include <json/json.h>

namespace Data
{
	RE::BSResourceNiBinaryStream& operator>>(
		RE::BSResourceNiBinaryStream& a_sin,
		Json::Value& a_root)
	{
		Json::CharReaderBuilder fact;
		std::unique_ptr<Json::CharReader> const reader{ fact.newCharReader() };

		auto size = a_sin.stream->totalSize;
		auto buffer = std::make_unique<char[]>(size);
		a_sin.read(buffer.get(), size);

		auto begin = buffer.get();
		auto end = begin + size;

		std::string errs;
		bool ok = reader->parse(begin, end, &a_root, &errs);

		if (!ok) {
			throw std::runtime_error(errs);
		}

		return a_sin;
	}

	CustomDataManager* CustomDataManager::GetSingleton()
	{
		static CustomDataManager singleton{};
		return &singleton;
	}

	void CustomDataManager::LoadConfigs()
	{
		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		if (!dataHandler)
			return;

		for (auto& file : dataHandler->files) {
			if (!file || file->recordFlags.none(RE::TESFile::RecordFlag::kChecked))
				continue;

			auto fileName = std::filesystem::path(file->fileName);
			fileName.replace_extension("json"sv);
			auto directory = std::filesystem::path(fmt::format("SKSE/Plugins/{}"sv, Plugin::NAME));
			auto configFile = directory / fileName;

			LoadConfig(configFile);
		}
	}

	void CustomDataManager::LoadConfig(const std::filesystem::path& a_path)
	{
		RE::BSResourceNiBinaryStream fileStream{ a_path.string() };

		if (!fileStream.good())
			return;

		Json::Value root;
		try {
			fileStream >> root;
		}
		catch (...) {
			logger::error("Parse errors in file: {}", a_path.filename().string());
		}

		if (!root.isObject())
			return;

		Json::Value rules = root["rules"];
		std::uint32_t numRules = 0;
		if (rules.isArray()) {
			for (auto& rule : rules) {
				auto parsed = RuleParser::ParseRule(rule);

				if (parsed.Validate()) {
					_rules.push_back(std::move(parsed));
					numRules++;
				}
			}
		}

		logger::info("Read {} rules from {}", numRules, a_path.filename().string());
	}

	void CustomDataManager::ProcessEntry(
		RE::GFxValue* a_entryObject,
		std::function<void(RE::GFxValue*)> a_processIconCallback) const
	{
		bool needsIconUpdate = false;
		for (const auto& rule : _rules) {
			rule.SetInfo(a_entryObject, needsIconUpdate);
		}

		if (needsIconUpdate && a_processIconCallback) {
			a_entryObject->DeleteMember("iconLabel");
			a_entryObject->DeleteMember("iconColor");
			a_processIconCallback(a_entryObject);
		}

		for (const auto& rule : _rules) {
			rule.SetIcon(a_entryObject);
		}
	}
}
