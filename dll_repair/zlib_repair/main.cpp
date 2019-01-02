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
        caption(L"��������ֱ���޸�����!");
        btn_.caption(L"�޸�");
        textbox_.editable(false);
        place_.div("<margin=[10, 10, 150, 10] btn> <weight = 80% textbox>");
        place_.field("btn") << btn_;
        place_.field("textbox") << textbox_;
        place_.collocate();

        btn_.events().click([this] (const arg_click& arg)
        {
            msgbox mb(arg.window_handle, "ȷ���޸� !", msgbox::yes_no);
            mb.icon(mb.icon_question);
            mb << L"�޸����ܵ��¸�����������쳣 !! \n�Ƿ���� ??";

            if (mb.show() == msgbox::pick_yes) {
                std::wstring info(L"���ڼ��ϵͳĿ¼�Ƿ���Ⱦ!!!\n");
                textbox_.caption(info);
                // ���ڽ���������dll
                std::wstring dll_name(L"zlib.dll");
                std::wstring file_name(repair::get_dll_in_system_path(dll_name));

                if (file_name.empty()) {
                    info.append(L"���ϵͳĿ¼��ʱ��zlib.dllʧ��!!!\nϵͳĿ¼δ����Ⱦ!!!\n");
                    textbox_.caption(info);
                    return;
                }

                info.append(L"��鵽��ʱ��zlib.dll!!!\n�����޸�zlib.dll�ļ�!!!\n");
                textbox_.caption(info);

                if (!repair::move_backup(file_name)) {
                    info.append(L"�޸�zlib.dll�ļ�ʧ��!!!\n������ϵͳ����!!!\n");
                    textbox_.caption(info);
                    return;
                }

                info.append(L"�޸�zlib.dll�ļ��ɹ�!!!\n�ɼ���ʹ��ֱ������!!!");
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