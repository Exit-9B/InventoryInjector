#include "ParseUtil.h"

namespace Data
{
	RE::FormID ParseUtil::ParseFormID(const std::string& a_identifier)
	{
		std::istringstream ss{ a_identifier };
		std::string plugin, id;

		std::getline(ss, plugin, '|');
		std::getline(ss, id);
		RE::FormID rawFormID;
		std::istringstream(id) >> std::hex >> rawFormID;

		const auto dataHandler = RE::TESDataHandler::GetSingleton();
		const auto file = dataHandler->LookupModByName(plugin);
		if (!file || file->compileIndex == 0xFF) {
			return 0x00000000;
		}

		RE::FormID formID = file->compileIndex << 24;
		formID += file->smallFileCompileIndex << 12;
		formID += rawFormID;

		return formID;
	}

	std::uint32_t ParseUtil::ParseColor(std::string_view a_hexCode)
	{
		if (a_hexCode.empty()) {
			return 0x000000;
		}

		std::size_t prefix = a_hexCode[0] == '#' ? 1 : 0;
		a_hexCode.remove_prefix(prefix);
		return static_cast<std::uint32_t>(std::stoll(std::string(a_hexCode), nullptr, 16));
	}
}
