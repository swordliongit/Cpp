- fs::is_directory(path)
- fs::is_regular_file(path)

```cpp
namespace fs = std::filesystem;
```

## current_path(), path()
```cpp
fs::path genericPath{ fs::path() };
fs::path currentPath{ fs::current_path() };
```

## has_parent_path(), parent_path()
```cpp

if (currentPath.has_parent_path())
{
	currentPath = currentPath.parent_path();
}
```

## Printing Current Directory
```cpp
ImGui::Text("Current Directory: %s", currentPath.string().c_str());
// ImGui::Text("Current Directory: %s", fs::current_path().string().c_str());
```

## Fetching the content of a directory
- is_directory()
- is_regular_file()
- path().filename()
```cpp
for (const auto& entry : fs::directory_iterator(currentPath)) {
	const auto is_directory = entry.is_directory();
	const auto is_file = entry.is_regular_file();

	ImGui::Text("%s", entry.path().filename().string().c_str());
}
```