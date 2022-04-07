#include "ImGui/ImGui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "menu.h"
#include "globals.h"

#include <iostream>
#include <windows.h>

bool doOnce = true;

ImVec4 firstChildBorder = ImColor(42, 42, 42, 255);
ImVec4 firstChildColor = ImColor(17, 17, 17, 255);

ImVec4 seconedChildBorder = ImColor(42, 42, 42, 255);
ImVec4 seconedChildColor = ImColor(21, 21, 21, 255);

static const char* cheat_subs[]{ "Counter Strike : Global Offensive", "Rust" };
static int selected_cheat = 0;


class initWindow {
public:
    const char* window_title = "injecter.club";
    ImVec2 window_size{ 220, 205 };
    
    DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
} iw;

void load_styles()
{
    ImVec4* colors = ImGui::GetStyle().Colors;
    {
        colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

        colors[ImGuiCol_Border] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);

        colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);

        colors[ImGuiCol_ButtonHovered] = ImColor(21, 21, 21, 255);
        colors[ImGuiCol_ButtonActive] = ImColor(21, 21, 21, 255);
        colors[ImGuiCol_Button] = ImColor(21, 21, 21, 255);

        colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.21f, 0.21f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);

        colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.31f);
    }

    ImGuiStyle* style = &ImGui::GetStyle();
    {
        style->WindowTitleAlign = ImVec2(.5, .5);

        style->FramePadding = ImVec2(3, 9);
        style->FrameBorderSize = 1;
    }
}

void menu::render()
{
    if (doOnce)
    {
        load_styles();
        doOnce = false;
    }

    if (globals.active)
    {
        ImGui::SetNextWindowSize(iw.window_size);
        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::Begin(iw.window_title, &globals.active, iw.window_flags);
        {

            ImGui::PushStyleColor(ImGuiCol_Border, firstChildBorder);
            ImGui::PushStyleColor(ImGuiCol_ChildBg, firstChildColor);
            ImGui::BeginChild("##firstChild", ImVec2(ImGui::GetWindowWidth() - 16, ImGui::GetWindowHeight() - 45), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            {
                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);
                ImGui::BeginChild("##CheatSelection", ImVec2(ImGui::GetWindowWidth() - 16, 55), true);
                {
                    ImGui::TextDisabled("                Your Subscriptions");

                    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 16);
                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
                    {
                        ImGui::Combo("##Subscriptions", &selected_cheat, cheat_subs, IM_ARRAYSIZE(cheat_subs));
                    }
                    ImGui::PopStyleVar();
                }
                ImGui::EndChild();
                ImGui::PopStyleColor(2);

                ImGui::PushStyleColor(ImGuiCol_Border, seconedChildBorder);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, seconedChildColor);
                ImGui::BeginChild("##InfoSection", ImVec2(ImGui::GetWindowWidth() - 16, 60), true);
                {
                    ImGui::TextDisabled("             Subscription Information");

                    if (selected_cheat == 0) // CS:GO
                    {
                        ImGui::Text("Status:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("Undetected");

                        ImGui::Text("Expiry:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("29.9 Days");
                    }
                    else if (selected_cheat == 1) // Rust
                    {
                        ImGui::Text("Status:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("Updating");

                        ImGui::Text("Expiry:");
                        ImGui::SameLine();
                        ImGui::TextDisabled("22.4 Days");

                    }
                }
                ImGui::EndChild();
                ImGui::PopStyleColor(2);

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 6));
                if (ImGui::Button("Inject", ImVec2(ImGui::GetWindowWidth() - 16, 23)))
                {

                }
                ImGui::PopStyleVar();

            }
            ImGui::EndChild();
            ImGui::PopStyleColor(2);

        }
        ImGui::End();
    }
    else
    {
        exit(0);
    }
}