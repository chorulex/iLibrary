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
	class console_test
	{
	private:
		iLibrary::library _lib;

	private:
		void test_initialize()
		{
			if (!_lib.initialize())
			{
				std::cout << "Faid to init library!" << std::endl;
			}
		}

		void test_destroy()
		{
			_lib.destroy();
		}

		void test_genaral_acquire()
		{
			iLibrary::option& opt = _lib.get_srv_genaral().acquire();
			opt.print();
		}

		void test_genaral_update()
		{
			option opt;
			opt.count = 1;
			opt.name = "Library of Chorulex";
			if (!_lib.get_srv_genaral().update(opt))
			{
				std::cout << "Faid to update library option!" << std::endl;
			}

		}

		void test_store_add()
		{
			package books;
			books.add(book(cip(92, "C++ primer", "Chorulex", isbn("adf_123_3q341234"), publish(4, true, "Alesxhiagic Press")), purchase(78, 5412, "Amazon.cn")));
			books.add(book(cip(65, "C++ Inside", "Chorulex.C.sexet", isbn("45f_dfg_3qasdfs4"), publish(1, true, "Alesxhiagic Press")), purchase(45, 2542, "Taobao.com")));

			if (!_lib.get_srv_store().add(books))
			{
				std::cout << "Faid to add book!" << std::endl;
			}
		}

		void test_store_query()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query();

			if (books.count() == 0)
			{
				std::cout << "None book!" << std::endl;
			}
			else
			{
				books.print();
			}
		}

		void test_store_query_over()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_over(true);
			if (books.count() == 0)
				std::cout << "No over_readed books!" << std::endl;
			else
				books.print();
		}

	public:
		int main()
		{
			test_initialize();

			/*
			test_genaral_acquire();

			test_genaral_update();
			test_genaral_acquire();
			*/

			//test_store_add();
			//test_store_query();
			test_store_query_over();

			test_destroy();
			return 0;
		}
	};
};

#endif
