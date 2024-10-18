#pragma once
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>

std::wstring openFileDialog();
std::wstring saveFileDialog();
void checkAndUpdateFile_TXT(const std::wstring& inputFilename, const std::wstring& outputFilename);
void checkAndUpdateFile_CSV(const std::wstring& inputFilename, const std::wstring& outputFilename);