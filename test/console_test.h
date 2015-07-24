/**console_test.h
* description: 控制台模式下的测试用例，用于测试书库的各个操作
* author: chorulex
* date: 07/24/2015
*/

#ifndef _TEST_FOR_CONSOLE_H_
#define _TEST_FOR_CONSOLE_H_

#include "library/library.h"

namespace iLibrary
{
	namespace console_test
	{
		int main()
		{
			iLibrary::library lib;
			if (!lib.initialize())
			{
				std::cout << "Faid to init library!" << std::endl;
				return 0;
			}

			iLibrary::option& opt = lib.get_srv_genaral().acquire();
			opt.print();

			iLibrary::store& srv_store = lib.get_srv_store();
			iLibrary::package& books = srv_store.query();
			books.print();

			books = srv_store.query_over(true);
			if (books.count() == 0)
				std::cout << "No over_readed books!" << std::endl;
			else
				books.print();

			lib.destroy();

			return 0;
		}
	};
};

#endif
