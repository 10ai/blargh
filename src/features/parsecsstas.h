#pragma once
#include <vector>
#include <string>

namespace parsecsstas
{
	enum moveFlags
	{
		forward = (1 << 0),
		moveleft = (1 << 1),
		moveright = (1 << 2),
		backward = (1 << 3),
		up = (1 << 4),
		down = (1 << 5)
	};
	enum actionFlags
	{
		jump = (1 << 0),
		duck = (1 << 1),
		use = (1 << 2),
		attack = (1 << 3),
		attack2 = (1 << 4),
		reload = (1 << 5),
		walk = (1 << 6),
		sprint = (1 << 7)
	};

	struct Framebulk
	{
		uint32_t moveFlags = 0;
		uint32_t actionFlags = 0;
		float yaw = -256;
		float pitch = -256;
		uint32_t ticks = 0;
		std::string commands;
	};
	struct Run
	{
		std::string initialCommand;
		std::vector<Framebulk> framebulks;
	};

	Run ParseFile(std::string contents);
	std::string ParseKey(std::string key, std::string contents);
}