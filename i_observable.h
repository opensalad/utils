#pragma once

namespace opensalad
{
	namespace utils
	{
		template <typename F>
		class i_observable
		{
		public:
			virtual void observe(F const&) = 0;
		};
	}
}