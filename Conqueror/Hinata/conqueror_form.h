#pragma once

#include <memory>
#include <vector>

#include <nana/gui/wvl.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/progress.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/treebox.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/date_chooser.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/categorize.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui/tooltip.hpp>
#include <nana/filesystem/filesystem_selector.hpp>
#include <nana/filesystem/filesystem_ext.hpp>

#include "function.h"

using namespace nana;

class conqueror_form : public form
{
public:
	conqueror_form()
	{
		caption("Conqueror");
		move(API::make_center(960, 600));
		m_place.bind(*this);
		m_place.div("< <vert <m_btHead weight = 80> <m_tabbar> > <m_tabpage> >"
				   );
		init_buttons();
		init_tabbar();
		m_place.collocate();
	}

	void init_buttons()
	{
		auto p = std::make_shared<button>(*this);
		m_buttons.push_back(p);
		m_place.field("m_btHead") << *p;
		p->events().click(ShowLogin);
		
		auto ptr = m_buttons[0];
		//Nana does not support ICON under Linux now
#if defined(NANA_WINDOWS)
		ptr->icon(nana::paint::image("../Images/image.ico"));
#else
		ptr->icon(nana::paint::image("../Images/image.bmp"));
#endif
		ptr->caption(("Button with An Image"));
	}

	void init_tabbar()
	{
		m_tabbar.create(*this);
		m_place.field("m_tabbar") << m_tabbar;
		m_tabbar.push_back("Downloading");
		m_tabbar.push_back("Completed");
		m_tabbar.push_back("Dustbin");
	}

private:
	//A layout management
	place									m_place;
	tabbar<std::string>						m_tabbar;
	std::vector<std::shared_ptr<button>>	m_buttons;
};