#include <iostream>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

void WindowClass::Draw(std::string_view label)
{
    // flag setup
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
    // initial values
    constexpr static auto window_pos = ImVec2(0.0F, 0.0F);
    constexpr static auto window_size = ImVec2(1280.0F, 720.0F);
    // Start
    ImGui::SetNextWindowPos(window_pos);
    ImGui::SetNextWindowSize(window_size);
    ImGui::Begin(label.data(), nullptr, window_flags);

    ImGui::Text("Hello World!");

    int open_action = -1;
    if (ImGui::Button("Open all"))
        open_action = 1;
    ImGui::SameLine();
    if (ImGui::Button("Close all"))
        open_action = 0;
    ImGui::SameLine();

    ImGui::End();
}

void render(WindowClass &window_obj)
{
    window_obj.Draw("Label");
}
