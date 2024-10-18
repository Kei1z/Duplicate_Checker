#include "checker.h"

std::wstring openFileDialog() {
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[MAX_PATH]; // buffer for file name

    // Initialize the OPENFILENAME structure
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; // Wide string literals
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box 
    if (GetOpenFileName(&ofn)) {
        return std::wstring(ofn.lpstrFile);
    }
    return L"";
}

std::wstring saveFileDialog() {
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[MAX_PATH]; // buffer for file name

    // Initialize the OPENFILENAME structure
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"; // Wide string literals
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_OVERWRITEPROMPT;

    // Display the Save dialog box 
    if (GetSaveFileName(&ofn)) {
        return std::wstring(ofn.lpstrFile);
    }
    return L"";
}


void checkAndUpdateFile_CSV(const std::wstring& inputFilename, const std::wstring& outputFilename) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cout << "File does not exist or cannot be opened." << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cout << "File does not exist or cannot be opened." << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::unordered_map<std::string, int> wordCount;
    std::string line;
    bool isFirstRow = true;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    // Process the lines and append duplicates
    std::vector<std::string> updatedLines;

    for (auto& line : lines) {
        std::stringstream ss(line);
        std::string word;
        std::vector<std::string> columns;

        // Split line into columns
        while (std::getline(ss, word, '\t')) {
            columns.push_back(word);
        }

        if (!isFirstRow) {
            std::string& name = columns[0];
            wordCount[name]++;
            if (wordCount[name] != 1) {
                name += std::to_string(wordCount[name]);
            }
        }
        else {
            isFirstRow = false;
        }

        outputFile << columns[0]; // First column
        for (size_t i = 1; i < columns.size(); ++i) {
            outputFile << "," << columns[i]; // Subsequent columns with tab
        }
        outputFile << "\n"; // New line for the next line of text
    }

    outputFile.close();
}

void checkAndUpdateFile_TXT(const std::wstring& inputFilename, const std::wstring& outputFilename) {
    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cout << "File does not exist or cannot be opened." << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cout << "File does not exist or cannot be opened." << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::unordered_map<std::string, int> wordCount;
    std::string line;
    bool isFirstRow = true;

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    // Process the lines and append duplicates
    std::vector<std::string> updatedLines;

    for (auto& line : lines) {
        std::stringstream ss(line);
        std::string word;
        std::vector<std::string> columns;

        // Split line into columns
        while (std::getline(ss, word, '\t')) {
            columns.push_back(word);
        }

        if (!isFirstRow) {
            std::string& name = columns[0];
            wordCount[name]++;
            if (wordCount[name] != 1) {
                name += std::to_string(wordCount[name]);
            }
        }
        else {
            isFirstRow = false;
        }

        outputFile << columns[0]; // First column
        for (size_t i = 1; i < columns.size(); ++i) {
            outputFile << "\t" << columns[i]; // Subsequent columns with tab
        }
        outputFile << "\n"; // New line for the next line of text
    }

    outputFile.close();
}
