#pragma once

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>

#include "function.h"

using namespace nana;

class login_form : public form
{
public:
	login_form()
	{
		// Define widgets
		caption("Fany");
		
		m_tbUserName.tip_string("SetUserName:").multi_lines(false);
		m_tbUserPassword.tip_string("SetUserPassword:").multi_lines(false).mask('*');

		// Divide the form into fields
		m_plc.div("<><weight = 80% vertical<><weight = 70% vertical <vertical gap = 10 textboxs arrange = [25, 25]>  <weight = 25 gap = 10 buttons> ><>><>");

		//Insert widgets
		//The field textboxs is vertical, it automatically adjusts the widgets' top and height. 
		m_plc.field("textboxs") << m_tbUserName << m_tbUserPassword;
		m_plc["buttons"] << m_btLogin << m_btCancel;

		//Finially, the widgets should be collocated.
		//Do not miss this line, otherwise the widgets are not collocated
		//until the form is resized.
		m_plc.collocate();

		// 设置用户文件加密密钥
		m_tbUserName.events().click(StartLogin);
		m_btCancel.events().click(API::exit);
	}
	~login_form()
	{

	}

private:
	// Define a place for the form.
	place	m_plc;
	textbox m_tbUserName, m_tbUserPassword;
	button  m_btLogin, m_btCancel;
};

