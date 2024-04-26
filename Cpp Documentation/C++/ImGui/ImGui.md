
## Configuration

```cpp
void WindowClass::Draw(std::string_view label)
{
    constexpr static auto window_flags =
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;

    // Window 1
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(1280.0F, 720.0F));
    ImGui::Begin(label.data(), nullptr, window_flags);
	...
}
```

## Basic Methods
```cpp
ImGui::SameLine(); // Puts the next element in the same line
ImGui::Separator(); // Draws a line across before the next element
ImGui::Text("Current Directory"); // Basic text printing
```

[[filesystem]]