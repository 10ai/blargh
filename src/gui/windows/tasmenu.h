#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include "../../../include/CUserCmd.h"
	
namespace tasmenu 
{
	void DrawMenu(bool open);
	void AddLog(const char* log);
	void CurrentFrame(CUserCmd* cmd);

	static std::string createmove;
	static int frame;
	static bool playing;
	static CUserCmd* cmd;
}

