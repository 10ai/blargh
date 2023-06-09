#include "errorlog.h"

void errorlog::ShowLog(ErrorLog errorLog, bool* p_open)
{
    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Error Log", p_open);

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    errorLog.Draw("Error Log", p_open);
}