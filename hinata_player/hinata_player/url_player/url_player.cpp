#include "repair.h"

#include <windows.h>
#include <Shlwapi.h>

namespace repair {

const int kBufSize = MAX_PATH + 1;

std::wstring get_dll_in_system_path(const std::wstring& dll_name)
{
    wchar_t file_name[kBufSize] {0};
    ::GetSystemDirectory(file_name, MAX_PATH);
    if (!::PathAppend(file_name, dll_name.c_str())) {
        return std::wstring();
    }

    if (GetFileAttributes(file_name) == INVALID_FILE_ATTRIBUTES) {
        return std::wstring();
    }

    return file_name;
}

bool move_backup(const std::wstring& file_name)
{
    wchar_t new_file_folder[kBufSize] {file_name[0], file_name[1], 0};

    if (!::PathAppend(new_file_folder, L"BililiveCleanToolBackup")) {
        return false;
    }

    if (!CreateDirectory(new_file_folder, nullptr)) {
        if (GetLastError() != ERROR_ALREADY_EXISTS) {
            return false;
        }
    }

    std::wstring dll_name(file_name.begin() + file_name.find_last_of(L"\\") + 1, file_name.end());
    if (!::PathAppend(new_file_folder, dll_name.c_str())) {
        return false;
    }

    if (!::MoveFileEx(file_name.c_str(), new_file_folder, MOVEFILE_REPLACE_EXISTING)) {
        return false;
    }

    return true;
}

} // namespace repair