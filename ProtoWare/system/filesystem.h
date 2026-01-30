#pragma once
template <typename T>
class unmanaged_list;

namespace filesystem {
    bool is_file_exists(const char* path);
    bool is_directory_exists(const char* path);
    bool read_file(const char* path, uintptr_t& outPointer, int64_t& outSize, int sizeEven = -1, bool nullTerminator = false);
    bool write_file(const char* path, uintptr_t buffer, int size);
    bool delete_file(const char* path);
    bool create_directory(const char* path);
    void get_all_files(const char* path, unmanaged_list<char*>& pathes);
};

