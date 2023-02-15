#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif

using namespace std::literals;

namespace logger = SKSE::log;

namespace util
{
	using SKSE::stl::report_and_fail;
	using SKSE::stl::to_underlying;
	using SKSE::stl::utf8_to_utf16;

	inline std::wstring Translate(std::wstring a_text)
	{
		const auto scaleformManager = RE::BSScaleformManager::GetSingleton();
		const auto loader = scaleformManager ? scaleformManager->loader : nullptr;
		const auto translator = loader
			? loader->GetState<RE::GFxTranslator>(RE::GFxState::StateType::kTranslator)
			: nullptr;

		if (translator) {
			RE::GFxTranslator::TranslateInfo translateInfo;
			RE::GFxWStringBuffer buffer;
			translateInfo.key = a_text.c_str();
			translateInfo.result = &buffer;
			translator->Translate(&translateInfo);
			if (!buffer.empty()) {
				return buffer.c_str();
			}
		}

		return a_text;
	}
}

#define DLLEXPORT __declspec(dllexport)

#include "Plugin.h"
