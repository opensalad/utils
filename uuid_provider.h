#pragma once

#include <string>
#include <random>

namespace opensalad
{
	namespace utils
	{
		class uuid_provider
		{
		public:
			static std::string create_random_uuid(int length)
			{
				std::string result = "";
				while (length--)
				{
					result += uuid_valid_characters[rand() % uuid_valid_characters_count];
				}

				return result;
			}

		private:
			static const char uuid_valid_characters[];
			static const int uuid_valid_characters_count;
		};

		const char uuid_provider::uuid_valid_characters[] = "1234567890qwertyuiopasdfghjklzxcvbnm#$_*%";
		const int uuid_provider::uuid_valid_characters_count = sizeof(uuid_provider::uuid_valid_characters);
	}
}