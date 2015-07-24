/**gui_test.h
* description: GUI模式下的测试用例，这一部分最终会作为真正的程序入口！
* author: chorulex
* date: 07/24/2015
*/

#ifndef _GUI_TEST_H_
#define _GUI_TEST_H_

#include "../view/manager.h"

namespace iLibrary
{
	namespace gui_test
	{
		int main()
		{
			iLibrary::manager_view _fream;
			_fream.show();

			nana::exec();

			return 0;
		}
	}
}

#endif
