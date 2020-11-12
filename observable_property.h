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
		class observable_property : public i_observable<std::function<void(T const&, T const&)>>
		{
		public:
			observable_property()
				: m_value()
			{}

			observable_property(T const& initial_value)
				: m_value()
			{}

			observable_property(T&& initial_value)
				: m_value(initial_value)
			{}

			void changed(T const& oldValue, T const& newValue)
			{
				for (auto observer : m_observers)
				{
					observer(oldValue, newValue);
				}
			}

			observable_property<T>& operator = (T const& value)
			{
				return set_value(value);
			}

			observable_property<T>& operator = (T&& value)
			{
				return set_value(value);
			}

			operator T()
			{
				return m_value;
			}

			operator const T& () const
			{
				return m_value;
			}

			T const& value() const
			{
				return m_value;
			}

			observable_property<T>& set_value(T const& value)
			{
				T oldValue = m_value;
				m_value = value;
				changed(oldValue, m_value);
				return *this;
			}

			observable_property<T>& set_value(T&& value)
			{
				T oldValue = m_value;
				m_value = value;
				changed(oldValue, m_value);
				return *this;
			}

			void observe(std::function<void(T const&, T const&)> const& observer) override
			{
				m_observers.push_back(observer);
			}

		private:
			T m_value;
			std::vector<std::function<void(T const&, T const&)>> m_observers;
		};
	}
}
