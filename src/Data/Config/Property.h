#pragma once

namespace Data
{
	class Property
	{
	public:
		[[nodiscard]] virtual bool Match(const RE::GFxValue& a_value) const = 0;
	};

	class IPropertyContainer
	{
	public:
		virtual void AddProperty(
			const std::string& a_name,
			std::shared_ptr<Property> a_property) = 0;
	};

	class AnyOfProperty final : public Property, public IPropertyContainer
	{
	public:
		bool Match(const RE::GFxValue& a_value) const override;

		void AddProperty(const std::string& a_name, std::shared_ptr<Property> a_property) override;

	private:
		std::vector<std::shared_ptr<Property>> _subProperties;
	};

	class MatchProperty final : public Property
	{
	public:
		MatchProperty(bool a_boolean) : _value{ a_boolean } {}
		MatchProperty(double a_number) : _value{ a_number } {}
		MatchProperty(std::int32_t a_number) : _value{ a_number } {}
		MatchProperty(std::uint32_t a_number) : _value{ a_number } {}

		MatchProperty(std::string_view a_string)
			: _cachedString{ a_string },
			  _value{ _cachedString }
		{
		}

		bool Match(const RE::GFxValue& a_value) const override;

	private:
		std::string _cachedString;
		RE::GFxValue _value;
	};

	class RangeProperty final : public Property
	{
	public:
		RangeProperty(std::optional<double> a_min, std::optional<double> a_max)
			: _min{ a_min },
			  _max{ a_max }
		{
		}

		bool Match(const RE::GFxValue& a_value) const override;

	private:
		std::optional<double> _min;
		std::optional<double> _max;
	};

	class BitfieldProperty final : public Property
	{
	public:
		BitfieldProperty(std::uint32_t a_flags) : _flags{ a_flags } {}

		bool Match(const RE::GFxValue& a_value) const override;

	private:
		std::uint32_t _flags;
	};

	class KeywordsProperty final : public Property
	{
	public:
		KeywordsProperty(std::string_view a_string) : _keyword{ a_string } {}

		bool Match(const RE::GFxValue& a_value) const override;

	private:
		std::string _keyword;
	};

	class MainPartProperty final : public Property
	{
	public:
		MainPartProperty(std::uint32_t a_slot) : _slot{ a_slot } {}

		bool Match(const RE::GFxValue& a_value) const override;

	private:
		std::uint32_t _slot;
	};
}
