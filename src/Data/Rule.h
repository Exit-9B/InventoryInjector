#pragma once

#include "Data/Property.h"

namespace Data
{
	class Rule final
	{
	public:
		void AddProperty(const std::string& a_name, std::shared_ptr<Property> a_property);

		void AddCustomData(const std::string& a_name, const RE::GFxValue& a_data);

		[[nodiscard]] bool IsValid() const;

		void SetInfo(RE::GFxValue* a_entryObject, bool& a_needsIconUpdate) const;

		void SetIcon(RE::GFxValue* a_entryObject) const;

	private:
		bool Match(const RE::GFxValue* a_entryObject) const;

		bool HasInfo() const;

		std::map<std::string, std::shared_ptr<Property>> _properties;
		std::map<std::string, RE::GFxValue> _customData;
	};
}
