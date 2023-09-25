#pragma once

#include <cstdint>
#include <filesystem>
#include <string_view>

namespace fs = std::filesystem;

class WindowClass
{
public:
    WindowClass()
        : currentPath(fs::current_path()), selectedEntry(fs::path()){};
    void Draw(std::string_view label);

private:
    void DrawMenu();
    void DrawContent();
    void DrawActions();
    void DrawFilter();

private:
    fs::path currentPath;
    fs::path selectedEntry;
};

void render(WindowClass &window_obj);
