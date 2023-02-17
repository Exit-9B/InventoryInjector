#pragma once

namespace Data
{
	struct CustomData : std::variant<bool, double, std::string, std::wstring>
	{
	public:
		using Base = std::variant<bool, double, std::string, std::wstring>;
		using Base::Base;

		template <typename Num> requires std::is_arithmetic_v<Num>
		CustomData(Num a_value) : Base(static_cast<double>(a_value)) {}

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
