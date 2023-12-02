#pragma once
#include "Common.h"

struct DrawResult
{
	int32_t red_cubes;
	int32_t green_cubes;
	int32_t blue_cubes;
};

int32_t get_game_id(std::string_view line)
{
	int32_t game_id = 0;
	size_t pos = line.find("Game");
	if (pos != std::string::npos)
	{
		pos += 5;
		game_id = std::stoi(std::string(line.substr(pos, line.find(':') - pos)));
	}
	return game_id;
}

std::vector<DrawResult> get_draw_result(std::string_view line)
{
	std::vector<DrawResult> draw_results{};
	std::vector<std::string_view> tokens;

	size_t draw_start_pos = line.find(": ");
	char delimiter = ';';
	size_t delimiter_pos = line.find(delimiter, draw_start_pos);
	
	while (delimiter_pos != std::string::npos)
	{
		tokens.push_back(line.substr(draw_start_pos + 2, delimiter_pos - draw_start_pos - 2));
		draw_start_pos = delimiter_pos;
		delimiter_pos = line.find(delimiter, draw_start_pos + 1);
	}

	tokens.push_back(line.substr(draw_start_pos + 2, line.size() - 1 - draw_start_pos - 2));

	draw_results.resize(tokens.size());

	for (int i = 0; i < tokens.size(); ++i)
	{
		for (int j = 0; j < tokens[i].size(); ++j)
		{
			if (std::isdigit(tokens[i][j]))
			{
				size_t color_pos = tokens[i].find_first_of("rgb", j);
				if (color_pos != std::string::npos)
				{
					switch (tokens[i][color_pos])
					{
						case 'r':
							draw_results[i].red_cubes = std::stoi(std::string(tokens[i].substr(j, color_pos - j - 1)));
							break;
						case 'g':
							draw_results[i].green_cubes = std::stoi(std::string(tokens[i].substr(j, color_pos - j - 1)));
							break;
						case 'b':
							draw_results[i].blue_cubes = std::stoi(std::string(tokens[i].substr(j, color_pos - j - 1)));
							break;
						default:
							break;
					}

					j = color_pos;
				}
			}
		}
	}

	return draw_results;
}

void D2()
{
	std::ifstream ifs("input2.txt");
	std::string line;

	constexpr int32_t max_red_cubes = 12;
	constexpr int32_t max_green_cubes = 13;
	constexpr int32_t max_blue_cubes = 14;

	int32_t valid_game_id_sum = 0;
	int64_t max_game_power_sum = 0;

	while (std::getline(ifs, line))
	{
		std::vector<DrawResult> draw_results = get_draw_result(line);

		for (int i = 0; i < draw_results.size(); ++i)
		{
			if (draw_results[i].red_cubes > max_red_cubes ||
				draw_results[i].green_cubes > max_green_cubes ||
				draw_results[i].blue_cubes > max_blue_cubes)
			{
				break;
			}
			else if (i == draw_results.size() - 1)
			{
				valid_game_id_sum += get_game_id(line);
			}
		}

		DrawResult max_draw_result = draw_results[0];

		for (int i = 1; i < draw_results.size(); ++i)
		{
			if (draw_results[i].red_cubes > max_draw_result.red_cubes)
			{
				max_draw_result.red_cubes = draw_results[i].red_cubes;
			}
			if (draw_results[i].green_cubes > max_draw_result.green_cubes)
			{
				max_draw_result.green_cubes = draw_results[i].green_cubes;
			}
			if (draw_results[i].blue_cubes > max_draw_result.blue_cubes)
			{
				max_draw_result.blue_cubes = draw_results[i].blue_cubes;
			}
		}

		max_game_power_sum += max_draw_result.red_cubes * max_draw_result.green_cubes * max_draw_result.blue_cubes;
	}

	std::cout << valid_game_id_sum << std::endl;
	std::cout << max_game_power_sum << std::endl;
}
