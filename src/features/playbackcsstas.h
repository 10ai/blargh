#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <cstdint>
#include <vector>
#include "../gui/windows/tasmenu.h"
#include "parsecsstas.h"
#include "../../include/CUserCmd.h"
#include <windows.h>
#include "autostrafer.h"

class PlaybackContainer
{
private:
	uint32_t m_Frame;
	std::vector<parsecsstas::Framebulk> m_Frames;
	bool m_Playing;
public:
	PlaybackContainer()
	{
		m_Frame = 0;
		m_Playing = false;
	}
	PlaybackContainer(parsecsstas::Run run)
	{
		m_Frame = 0;
		m_Playing = false;
		m_Frames = run.framebulks;
	}
	void CurrentFrame(CUserCmd* cmd) 
	{
		uint16_t index = 0;
		int total = 0;
		for (int i = 0; i < m_Frames.size(); i++)
		{
			total += m_Frames.at(i).ticks;
			if (total < m_Frame)
			{
				index++;
			}
		}
		if (m_Playing)
		{
			parsecsstas::Framebulk currentFrame = m_Frames.at(index);
			if (currentFrame.yaw != -256)
			{
				cmd->viewangles.x = m_Frames.at(index).yaw;
			}
			if (currentFrame.pitch != -256)
			{
				cmd->viewangles.y = m_Frames.at(index).pitch;
			}
			if (currentFrame.moveFlags & parsecsstas::forward) { cmd->forwardmove += 400; cmd->buttons |= IN_FORWARD; }
			if (currentFrame.moveFlags & parsecsstas::backward) { cmd->forwardmove -= 400; cmd->buttons |= IN_BACK;  }
			if (currentFrame.moveFlags & parsecsstas::moveright) { cmd->sidemove += 400; cmd->buttons |= IN_MOVERIGHT; }
			if (currentFrame.moveFlags & parsecsstas::moveleft) { cmd->sidemove -= 400; cmd->buttons |= IN_MOVELEFT; }

			if (currentFrame.actionFlags & parsecsstas::jump) { cmd->buttons |= IN_JUMP; }

			if (m_Playing)
				m_Frame++;
			if (m_Frame > total)
			{
				EndPlayback();
			}
			//uintptr_t moduleBase = (uintptr_t)GetModuleHandle("client.dll");
			//uintptr_t* velx = (uintptr_t*)(moduleBase + 0x4A4070);
			//uintptr_t* vely = (uintptr_t*)(moduleBase + 0x4A4074);
			/*if (cmd->buttons & IN_JUMP)
				autostrafer::Strafe(cmd, *(float*)velx, *(float*)vely);
			tasmenu::AddLog("\n");
			tasmenu::AddLog(std::to_string(autostrafer::Velocity(*(float*)velx, *(float*)vely)).c_str());
			tasmenu::AddLog("\n");
			tasmenu::AddLog(std::to_string(*(float*)vely).c_str());
			tasmenu::AddLog("\n");
			tasmenu::AddLog(std::to_string(*(float*)velx).c_str());
			tasmenu::AddLog("\n---------------\n");*/
		}
		tasmenu::frame = m_Frame;
		tasmenu::playing = m_Playing;
	}
	void StartPlayback()
	{
		this->m_Frame = 0;
		this->m_Playing = true;
	}
	void EndPlayback()
	{
		m_Playing = false;
	}
};