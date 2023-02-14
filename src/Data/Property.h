#pragma once

namespace Data
{
	class Property
	{
	public:
		virtual bool Match(const RE::GFxValue& a_value) const = 0;
	};

	// TODO Make implementations
}
