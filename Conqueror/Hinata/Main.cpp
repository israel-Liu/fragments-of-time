#include <Windows.h>
#include <nana/gui/wvl.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>

#include "function.h"
#include "conqueror_form.h"

#ifdef _DEBUG
int main()
#else
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow)
#endif // _DEBUG
{
	using namespace nana;

	conqueror_form cqrFm;
	cqrFm.show();

	exec();
}