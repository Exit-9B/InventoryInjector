#include "CustomData.h"

namespace Data
{
	CustomData::operator RE::GFxValue() const
	{
		if (std::holds_alternative<bool>(*this)) {
			return RE::GFxValue(std::get<bool>(*this));
		}
		else if (std::holds_alternative<double>(*this)) {
			return RE::GFxValue(std::get<double>(*this));
		}
		else if (std::holds_alternative<std::string>(*this)) {
			const auto& value = std::get<std::string>(*this);
			if (value.empty() || value[0] != '$') {
				return RE::GFxValue(std::get<std::string>(*this));
			}
			else {
				const auto utf16 = util::utf8_to_utf16(value).value_or(L"");
				const auto& translation =
					*_translationCache.insert(util::Translate(utf16)).first;

				return RE::GFxValue(translation);
			}
		}
		else if (std::holds_alternative<std::wstring>(*this)) {
			const auto& value = std::get<std::wstring>(*this);
			if (value.empty() || value[0] != L'$') {
				return RE::GFxValue(std::get<std::wstring>(*this));
			}
			else {
				const auto& translation =
					*_translationCache.insert(util::Translate(value)).first;

				return RE::GFxValue(translation);
			}
		}

		return RE::GFxValue();
	}
}
