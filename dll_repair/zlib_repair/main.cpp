#include <windows.h>
#include <string>

#include "repair.h"

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/filebox.hpp>

using namespace nana;

class repair_form : public form
{
public:
    repair_form()
    {
        caption(L"哔哩哔哩直播修复工具!");
        btn_.caption(L"修复");
        textbox_.editable(false);
        place_.div("<margin=[10, 10, 150, 10] btn> <weight = 80% textbox>");
        place_.field("btn") << btn_;
        place_.field("textbox") << textbox_;
        place_.collocate();

        btn_.events().click([this] (const arg_click& arg)
        {
            msgbox mb(arg.window_handle, "确认修复 !", msgbox::yes_no);
            mb.icon(mb.icon_question);
            mb << L"修复可能导致个别软件运行异常 !! \n是否继续 ??";

            if (mb.show() == msgbox::pick_yes) {
                std::wstring info(L"正在检查系统目录是否被污染!!!\n");
                textbox_.caption(info);
                // 用于将来输入别的dll
                std::wstring dll_name(L"zlib.dll");
                std::wstring file_name(repair::get_dll_in_system_path(dll_name));

                if (file_name.empty()) {
                    info.append(L"检查系统目录过时的zlib.dll失败!!!\n系统目录未被污染!!!\n");
                    textbox_.caption(info);
                    return;
                }

                info.append(L"检查到过时的zlib.dll!!!\n正在修复zlib.dll文件!!!\n");
                textbox_.caption(info);

                if (!repair::move_backup(file_name)) {
                    info.append(L"修复zlib.dll文件失败!!!\n请重启系统再试!!!\n");
                    textbox_.caption(info);
                    return;
                }

                info.append(L"修复zlib.dll文件成功!!!\n可继续使用直播姬了!!!");
                textbox_.caption(info);
            }
        });
    }

    ~repair_form()
    {}

private:
    place   place_      {*this};
    button  btn_        {*this};
    textbox textbox_    {*this};
    label   label_      {*this};
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, char*, int)
{
    repair_form rpform;
    HWND hwnd = reinterpret_cast<HWND>(API::root(rpform.handle()));
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    if (style & WS_MAXIMIZEBOX) {
        SetWindowLong(hwnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX);
    }
    rpform.show();
    exec();
}