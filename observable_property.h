#pragma once

#include <type_traits>
#include <vector>
#include <functional>

#include <i_observable.h>

namespace opensalad
{
	namespace utils
	{
		template <typename T>
		class observable_property : public i_observable<std::function<void()>>
		{
		public:
			observable_property()
				: m_value()
			{}

			observable_property(T && initial_value)
				: m_value(initial_value)
			{}

			void changed()
			{
				for (auto observer : m_observers)
				{
					observer();
				}
			}

			observable_property<T>& operator = (T const& value)
			{
				return set_value(value);
			}

			operator T()
			{
				return m_value;
			}

			operator const T&() const
			{
				return m_value;
			}

			T const& value() const
			{
				return m_value;
			}

			observable_property<T>& set_value(T const& value)
			{
				m_value = value;
				changed();
				return *this;
			}
			
			void observe(std::function<void()> const& observer) override
			{
				m_observers.push_back(observer);
			}

		private:
			T m_value;
			std::vector<std::function<void()>> m_observers;
		};
	}
}
