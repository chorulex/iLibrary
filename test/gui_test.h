/**gui_test.h
* description: GUI模式下的测试用例，这一部分最终会作为真正的程序入口！
* author: chorulex
* date: 07/24/2015
*/

#ifndef _GUI_TEST_H_
#define _GUI_TEST_H_

#include "../library/library.h"
#include "../view/manager.h"

namespace iLibrary
{
	class gui_test
	{
	public:
		int main(int argc, char** argv)
		{
			library lib;
			if (!lib.initialize())
			{
				std::cout << "Fail to init library!" << std::endl;
				return 0;
			}

			Gtk::Main kit(argc, argv);
			manager_view window(lib);
			window.init_window();

			kit.run(window);

			lib.destroy();
			return 0;
		}
	};
}

#endif
