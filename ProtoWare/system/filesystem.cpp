#include "pch.h"
#include "filesystem.h"
#include "unmanaged_list.hpp"

bool filesystem::is_file_exists(const char* path)
{
    DWORD fileAttr = GetFileAttributesA(path);
    if (fileAttr == INVALID_FILE_ATTRIBUTES)
        return false;
    if (fileAttr & FILE_ATTRIBUTE_DIRECTORY)
        return false;
    return true;
}
bool filesystem::is_directory_exists(const char* path)
{
    DWORD fileAttr = GetFileAttributesA(path);
    return (fileAttr != INVALID_FILE_ATTRIBUTES) && (fileAttr & FILE_ATTRIBUTE_DIRECTORY);
}

bool filesystem::read_file(const char* path, uintptr_t& outPointer, int64_t& outSize, int sizeEven, bool nullTerminator) {
    HANDLE fileHandle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("Failed to open file!\n");
        return 0;
    }

    if (!GetFileSizeEx(fileHandle, (PLARGE_INTEGER)&outSize)) {
        printf("Failed to get file size!\n");
        return 0;
    }

    outPointer = (uintptr_t)malloc((sizeEven == -1 ? outSize : (outSize + (outSize % sizeEven) + 1)) + (nullTerminator ? 1 : 0));
    if (nullTerminator)
        *(byte*)(outPointer + (sizeEven == -1 ? outSize : (outSize + (outSize % sizeEven) + 1))) = 0;
    if (!ReadFile(fileHandle, (LPVOID)outPointer, outSize, nullptr, nullptr)) {
        printf("Failed to read and load file!\n");
        free((void*)outPointer);
        return 0;
    }

    CloseHandle(fileHandle);

    return 1;
}

bool filesystem::write_file(const char* path, uintptr_t buffer, int size) {
    HANDLE fileHandle = CreateFileA(path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (fileHandle == INVALID_HANDLE_VALUE) {
        printf("Failed to open file!\n");
        return 0;
    }

    if (!WriteFile(fileHandle, (LPCVOID)buffer, size, 0, 0)) {
        printf("Failed to write file!\n");
        return 0;
    }

    CloseHandle(fileHandle);

    return 1;
}

bool filesystem::delete_file(const char* path) {
    return DeleteFileA(path);
}

bool filesystem::create_directory(const char* path)
{
    if (is_directory_exists(path))
        return true;

    return CreateDirectoryA(path, NULL) != 0;
}

void filesystem::get_all_files(const char* path, unmanaged_list<char*>& pathes) {
    int cycled = 0;
    WIN32_FIND_DATAA findData;
    HANDLE hFind;

    std::string directory = std::string(path);
    std::string searchPath = directory + "\\*";

    hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) 
        return;

    do {
        findData.cFileName[258] = 0;
        if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
            continue;

        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            char* confname = (char*)malloc(260);
            memcpy(confname, findData.cFileName, 260);
            pathes.push(confname);
        }

        cycled++;
        if (cycled > 64) break;

    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);
}