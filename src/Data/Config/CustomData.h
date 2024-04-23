#pragma once

namespace Data
{
	struct CustomData : std::variant<std::nullptr_t, bool, double, std::string, std::wstring>
	{
	public:
		using Base = std::variant<std::nullptr_t, bool, double, std::string, std::wstring>;
		using Base::Base;

		CustomData(std::integral auto a_value) : Base(static_cast<double>(a_value)) {}
		CustomData(float a_value) : Base(static_cast<double>(a_value)) {}
		CustomData(bool a_value) : Base(a_value) {}

		operator RE::GFxValue() const;

	private:
		inline static std::set<std::wstring> _translationCache;
	};

	class ICustomDataContainer
	{
	public:
		virtual void AddCustomData(const std::string& a_name, const CustomData& a_data) = 0;
	};
}
