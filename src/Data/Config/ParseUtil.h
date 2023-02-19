#pragma once

namespace Data
{
	class ParseUtil
	{
	public:
		ParseUtil() = delete;

		[[nodiscard]] static RE::FormID ParseFormID(const std::string& a_identifier);

		[[nodiscard]] static std::uint32_t ParseColor(std::string_view a_hexCode);
	};
}
