// GUI.cpp
#include "WindowUI.h"
#include <map>

// Global variables
HWND hMainWindow;
HWND hButton1, hButton2;
HWND hStaticText;
HWND hInput;  // Input field
bool isFirstScreen = true;
std::map<int, void(*)(const std::wstring&)> buttonCallbacks;

// Window procedure function declaration
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void RegisterButtonCallback(int buttonId, void (*callback)(const std::wstring&)) {
    buttonCallbacks[buttonId] = callback;
}

std::wstring GetInputString() {
    int length = GetWindowTextLengthW(hInput) + 1;
    std::wstring text(length, 0);
    GetWindowTextW(hInput, &text[0], length);
    return text;
}

// Register window class
void RegisterWindowClass(HINSTANCE hInst, LPCWSTR className) {
    WNDCLASSW wc = { 0 };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = className;
    wc.lpfnWndProc = WindowProcedure;

    RegisterClassW(&wc);
}

// Create main window
HWND CreateMainWindow(HINSTANCE hInst, LPCWSTR className, LPCWSTR title) {
    hMainWindow = CreateWindowW(className, title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 500, 400,  // Made window slightly larger
        NULL, NULL, hInst, NULL);
    return hMainWindow;
}

// Show first screen
void ShowFirstScreen(HWND hwnd) {
    // Create static text
    hStaticText = CreateWindowW(L"static", L"Welcome to the .txt file checker\nPlease press the below button to start",
        WS_VISIBLE | WS_CHILD | SS_CENTER,
        100, 50, 300, 120,
        hwnd, NULL, NULL, NULL);

    hButton1 = CreateWindowW(L"button", L"Start",
        WS_VISIBLE | WS_CHILD,
        200, 120, 100, 30,
        hwnd, (HMENU)1, NULL, NULL);

    if (hButton2) ShowWindow(hButton2, SW_HIDE);
}

// Show second screen
void ShowSecondScreen(HWND hwnd) {
    SetWindowTextW(hStaticText, L"Please choose which format of file you want to convert");

    ShowWindow(hButton1, SW_HIDE);

    hButton1 = CreateWindowW(L"button", L".txt",
        WS_VISIBLE | WS_CHILD,
        100, 120, 120, 30,
        hwnd, (HMENU)2, NULL, NULL);

    hButton2 = CreateWindowW(L"button", L".csv",
        WS_VISIBLE | WS_CHILD,
        280, 120, 120, 30,
        hwnd, (HMENU)3, NULL, NULL);
}

// Window procedure
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND:
    {
        int buttonId = LOWORD(wParam);
        auto it = buttonCallbacks.find(buttonId);
        if (it != buttonCallbacks.end() && it->second != nullptr) {
            std::wstring inputText = GetInputString();
            it->second(inputText); // Call the callback with the input string

            if (buttonId == 2 || buttonId == 3) {
                DestroyWindow(hMainWindow);
            }
        }

        // Handle GUI changes
        if (buttonId == 1) {
            isFirstScreen = false;
            ShowSecondScreen(hwnd);
        }
    }
    break;
    case WM_CREATE:
        ShowFirstScreen(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void InitializeGUI() {
    buttonCallbacks.clear();
}

void RunGUI() {
    HINSTANCE hInst = GetModuleHandle(NULL);
    const wchar_t className[] = L"MyWindowClass";

    RegisterWindowClass(hInst, className);
    HWND hwnd = CreateMainWindow(hInst, className, L"Duplicate Title Checker");

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}