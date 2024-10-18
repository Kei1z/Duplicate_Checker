#include "WindowUI.h"
#include "checker.h" 

std::wstring fileToRead;
std::wstring fileToWrite;

void OnStartButtonClick(const std::wstring& text) {
    fileToRead = openFileDialog();
}

void OnOption_TXT_Click(const std::wstring& text) {
    fileToWrite = saveFileDialog();
    checkAndUpdateFile_TXT(fileToRead, fileToWrite);
}

void OnOption_CSV_Click(const std::wstring& text) {
    fileToWrite = saveFileDialog(); 
    checkAndUpdateFile_CSV(fileToRead, fileToWrite);

}

int main() {
    InitializeGUI();

    // Register callbacks for buttons
    RegisterButtonCallback(1, OnStartButtonClick);  // First screen button
    RegisterButtonCallback(2, OnOption_TXT_Click);      // Option 1 button
    RegisterButtonCallback(3, OnOption_CSV_Click);      // Option 2 button

    RunGUI();
    return 0;
}
