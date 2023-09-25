#include <iostream>

#include <fmt/format.h>
#include <imgui.h>
#include <implot.h>

#include "render.hpp"

void WindowClass::Draw(std::string_view label) {
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

    // int open_action = -1;
    // if (ImGui::Button("Open all"))
    //     open_action = 1;
    // ImGui::SameLine();
    // if (ImGui::Button("Close all"))
    //     open_action = 0;
    // ImGui::SameLine();

    DrawMenu();
    ImGui::Separator(); // lines
    DrawContent();
    ImGui::Separator();
    DrawActions();
    ImGui::Separator();
    DrawFilter();

    ImGui::End();
}

void WindowClass::DrawMenu() {

    if (ImGui::Button("Go Up")) {
        if (currentPath.has_parent_path()) {
            currentPath = currentPath.parent_path();
        }
    }
    ImGui::SameLine();
    ImGui::Text("Current Directory: %s", currentPath.string().c_str());
}

void WindowClass::DrawContent() {

    for (const auto &entry : fs::directory_iterator(currentPath)) {
        // controls
        const auto is_selected = entry.path() == selectedEntry;
        const auto is_directory = entry.is_directory();
        const auto is_file = entry.is_regular_file();
        // get current entry
        auto entry_name = entry.path().filename().string();
        // check
        if (is_directory)
            entry_name = "[D]" + entry_name;
        else if (is_file)
            entry_name = "[F]" + entry_name;
        // display
        if (ImGui::Selectable(entry_name.c_str(), is_selected)) {
            if (is_directory)
                currentPath /= entry.path().filename();
            selectedEntry = entry.path();
        }
    }
}

void WindowClass::DrawActions() {
    ImGui::Text("DrawActions");
}

void WindowClass::DrawFilter() {
    ImGui::Text("DrawFilter");
}

void render(WindowClass &window_obj) {
    window_obj.Draw("Label");
}
