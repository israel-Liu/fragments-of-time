#include <iostream>

#include "function.h"
#include "login_form.h"

void StartLogin()
{
	std::string str("StartLogin");
	std::cout << str << std::endl;
}

void ShowLogin()
{
	using namespace nana;
	login_form fm_login;
	//API::modal_window(fm_login);
	fm_login.show();
	std::cout << "Block execution till modal form is closed" << std::endl;
	std::cout << "modal form is closed" << std::endl;
}