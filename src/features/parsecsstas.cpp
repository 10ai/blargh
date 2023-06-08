#include <iostream>
#include "parsecsstas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <bitset>

const std::string WHITESPACE = " \n\r\t\f\v";

auto trim = [&](const std::string& s) {
	auto ltrim = [](const std::string& s)
	{
		size_t start = s.find_first_not_of(WHITESPACE);
		return (start == std::string::npos) ? "" : s.substr(start);
	};
	auto rtrim = [](const std::string& s)
	{
		size_t end = s.find_last_not_of(WHITESPACE);
		return (end == std::string::npos) ? "" : s.substr(0, end + 1);
	};

	return rtrim(ltrim(s));
};

std::vector<std::string> split(const std::string& text, char sep)
{
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}

std::vector<std::string> SplitStringByNewline(const std::string& str)
{
	auto result = std::vector<std::string>{};
	auto ss = std::stringstream{ str };

	for (std::string line; std::getline(ss, line, '\n');)
		result.push_back(trim(line));

	return result;
}

parsecsstas::Run parsecsstas::ParseFile(std::string contents) {
	Run result;
	result.initialCommand = ParseKey("init", contents);
	contents = contents.substr(contents.find("frames") + 7);
	std::vector<std::string> lines = SplitStringByNewline(contents);
	for (std::string line : lines)
	{
		if (line != "\n")
		{

			Framebulk fb;

			// moveFlags parsing
			fb.moveFlags |= (line[11] == 'f') ? forward : 0;
			fb.moveFlags |= (line[12] == 'l') ? moveleft : 0;
			fb.moveFlags |= (line[13] == 'r') ? moveright : 0;
			fb.moveFlags |= (line[14] == 'b') ? backward : 0;
			fb.moveFlags |= (line[15] == 'u') ? up : 0;
			fb.moveFlags |= (line[16] == 'd') ? down : 0;

			// actionFlags parsing
			fb.actionFlags |= (line[18] == 'j') ? jump : 0;
			fb.actionFlags |= (line[19] == 'd') ? duck : 0;
			fb.actionFlags |= (line[20] == 'u') ? use : 0;
			fb.actionFlags |= (line[21] == '1') ? attack : 0;
			fb.actionFlags |= (line[22] == '2') ? attack2 : 0;
			fb.actionFlags |= (line[23] == 'r') ? reload : 0;
			fb.actionFlags |= (line[24] == 'w') ? walk : 0;
			fb.actionFlags |= (line[24] == 's') ? sprint : 0;

			std::vector<std::string> tokens = split(line, '|');

			if (tokens.at(3) != "-")
				fb.yaw = std::stof(tokens.at(3));
			else
				fb.yaw = -256;
			if (tokens.at(4) != "-")
				fb.pitch = std::stof(split(line, '|').at(4));
			else
				fb.pitch = -256;
			fb.ticks = std::stoi(split(line, '|').at(5));
			fb.commands = split(line, '|').at(6);

			result.framebulks.push_back(fb);
		}
	}
	return result;
}

std::string parsecsstas::ParseKey(std::string key, std::string contents)
{
	key += ":";
	int index = contents.find(key) + key.size();
	return trim(contents.substr(index, contents.substr(index).find("\n")));
}