#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include "tasmenu.h"
#include "errorlog.h"
#include "../../features/parsecsstas.h"
#include "../../../include/ImGui/imgui.h"
#include "../../hooks/createmove.h"
#include "../../features/playbackcsstas.h"
#include "../../../include/CUserCmd.h"


char filename[256];
std::string contents;

static errorlog::ErrorLog errorLog;
PlaybackContainer playbackContainer;

void tasmenu::DrawMenu(bool open) {
	ImGui::Begin("TAS menu", &open);

	if(ImGui::CollapsingHeader("TAS Properties", ImGuiTreeNodeFlags_None))
	{
		ImGui::InputText("Filename", filename, 256);
		if (ImGui::Button("Load")) 
		{
            std::ifstream file(filename);
            std::stringstream buffer;
            buffer << file.rdbuf();
            contents = buffer.str();
            contents = "\n" + contents;
            errorLog.AddLog(contents.c_str());

			playbackContainer = PlaybackContainer(parsecsstas::ParseFile(contents));
		}
		ImGui::SameLine();
		if (ImGui::Button("Save")) 
        {
            std::ofstream file(filename, std::ios::out);
			file << contents;
		}
	}

	if (ImGui::Button("Playback TAS") || GetAsyncKeyState(VK_F8) != 0)
	{
		playbackContainer.StartPlayback();
	}

	ImGui::End();
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::Begin("CreateMove() Debug", &open, ImGuiWindowFlags_NoBackground + ImGuiWindowFlags_NoDecoration);
	ImGui::Text(createmove.c_str());
	ImGui::End();
	ImGui::Begin("Playback Debug");
	ImGui::Text(std::to_string(frame).c_str());
	ImGui::Text(std::to_string(playing).c_str());
	ImGui::End();
    errorlog::ShowLog(errorLog ,&open);
}

void tasmenu::AddLog(const char* log)
{
	errorLog.AddLog(log);
}

void tasmenu::CurrentFrame(CUserCmd* cmd) 
{
	playbackContainer.CurrentFrame(cmd);
}