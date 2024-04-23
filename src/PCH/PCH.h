#pragma once

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

#ifdef NDEBUG
#include <spdlog/sinks/basic_file_sink.h>
#else
#include <spdlog/sinks/msvc_sink.h>
#endif

using namespace std::literals;

namespace logger = SKSE::log;

namespace util
{
	using SKSE::stl::report_and_fail;
	using SKSE::stl::to_underlying;
	using SKSE::stl::utf8_to_utf16;

	[[nodiscard]] constexpr int ascii_tolower(int ch) noexcept
	{
		if (ch >= 'A' && ch <= 'Z')
			ch += 'a' - 'A';
		return ch;
	}

	struct iequal_to
	{
		template <std::ranges::contiguous_range S1, std::ranges::contiguous_range S2>
			requires(
				std::is_same_v<std::ranges::range_value_t<S1>, char> &&
				std::is_same_v<std::ranges::range_value_t<S2>, char>)
		constexpr bool operator()(S1&& a_str1, S2&& a_str2) const
		{
			std::size_t count = std::ranges::size(a_str1);
			if (count != std::ranges::size(a_str2))
				return false;

			if (count) {
				const char* p1 = std::ranges::data(a_str1);
				const char* p2 = std::ranges::data(a_str2);

				do {
					const int ch1 = ascii_tolower(*p1++);
					const int ch2 = ascii_tolower(*p2++);
					if (ch1 != ch2)
						return false;
				} while (--count);
			}

			return true;
		}
	};

	[[nodiscard]] bool iequals(auto&& a_str1, auto&& a_str2)
	{
		return iequal_to{}(a_str1, a_str2);
	}

	struct iless
	{
		using is_transparent = int;

		template <std::ranges::contiguous_range S1, std::ranges::contiguous_range S2>
			requires(
				std::is_same_v<std::ranges::range_value_t<S1>, char> &&
				std::is_same_v<std::ranges::range_value_t<S2>, char>)
		constexpr bool operator()(S1&& a_str1, S2&& a_str2) const
		{
			std::size_t count = std::ranges::size(a_str2);
			const std::size_t len1 = std::ranges::size(a_str1);
			const bool shorter = len1 < count;
			if (shorter)
				count = len1;

			if (count) {
				const char* p1 = std::ranges::data(a_str1);
				const char* p2 = std::ranges::data(a_str2);

				do {
					const int ch1 = ascii_tolower(*p1++);
					const int ch2 = ascii_tolower(*p2++);
					if (ch1 != ch2)
						return ch1 < ch2;
				} while (--count);
			}

			return shorter;
		}
	};

	template <class T>
	using istring_map = std::map<std::string, T, iless>;

	template <typename Map, typename Key, typename Result>
	inline bool try_get(Map const& a_map, Key&& a_key, Result& a_result)
	{
		if (const auto it = a_map.find(a_key); it != a_map.end()) {
			a_result = static_cast<Result>(it->second);
			return true;
		}

		return false;
	}

	[[nodiscard]] inline std::wstring Translate(std::wstring a_text)
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
