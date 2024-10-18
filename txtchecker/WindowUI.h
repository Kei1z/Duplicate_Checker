#pragma once
#include <windows.h>
#include <string>

// Function declarations for GUI
void InitializeGUI();
void RunGUI();
void RegisterButtonCallback(int buttonId, void (*callback)(const std::wstring&));
std::wstring GetInputString();