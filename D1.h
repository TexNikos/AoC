#pragma once

#include "Common.h"

constexpr std::array<const char*, 10> numbers = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

std::pair<size_t, int32_t> find_first_number_word(std::string_view line)
{
	size_t pos = std::string::npos;
	size_t min_pos = std::string::npos;
	int32_t out_number = 0;

	for (int i = 0; i < numbers.size(); ++i)
	{
		pos = line.find(numbers[i]);

		if (pos < min_pos)
		{
			min_pos = pos;
			out_number = i;
		}
	}

	return {min_pos, out_number};
}

std::pair<size_t, int32_t> find_last_number_word(std::string_view line)
{
	size_t pos = std::string::npos;
	size_t max_pos = 0;
	int32_t out_number = 0;
	bool found = false;

	for (int i = 0; i < numbers.size(); ++i)
	{
		pos = line.rfind(numbers[i]);

		if (pos != std::string::npos)
		{
			found = true;
			if (pos > max_pos)
			{
				max_pos = pos;
				out_number = i;
			}
		}
	}

	if (!found)
	{
		return {std::string::npos, 0};
	}

	return {max_pos, out_number};
}

void D1()
{
	std::ifstream ifs("input.txt");
	std::string line;
	bool found_word = false;

	size_t sum = 0;

	while (std::getline(ifs, line))
	{
		auto [pos, number] = find_first_number_word(line);
		int i = 0;

		for (; i < line.size(); i++)
		{
			if (std::isdigit(line[i]))
			{
				break;
			}
		}


		if (pos != std::string::npos)
		{
			if (pos < i)
			{
				sum += number * 10;
				found_word = true;
			}
		}

		if (!found_word)
		{
			if (i == line.size())
				continue;

			sum += (line[i] - '0') * 10;
		}

		found_word = false;

		auto [pos2, number2] = find_last_number_word(line);

		i = line.size() - 1;

		for (; i > -1; i--)
		{
			if (std::isdigit(line[i]))
			{
				break;
			}
		}

		if (pos2 != std::string::npos)
		{
			if (pos2 > i)
			{
				sum += number2;
				found_word = true;
			}
		}

		if (!found_word)
		{
			sum += (line[i] - '0');
		}

		found_word = false;
	}

	std::cout << sum << std::endl;
}

