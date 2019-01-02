#pragma once

#include <string>

namespace repair {

std::wstring get_dll_in_system_path(const std::wstring& dll_name);
bool move_backup(const std::wstring& file_name);

}
