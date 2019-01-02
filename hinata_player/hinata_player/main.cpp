#include <windows.h>
#include <string>

#include "url_player/url_player_form.h"

using namespace nana;

int WINAPI WinMain(HINSTANCE, HINSTANCE, char*, int)
{
    url_player_form upform;
    upform.show();
    exec();
}