#pragma once

#include <nana/gui.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/gui/filebox.hpp>

using namespace nana;

class url_player_form : public form
{
public:
    url_player_form()
    {
        caption(L"url_player !");
    }

    ~url_player_form()
    { }

private:
    place   place_ {*this};
    label   label_ {*this};
};