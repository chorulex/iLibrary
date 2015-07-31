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

		void test_store_query_all()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_all();

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

		void test_store_query_not_over()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_over(false);
			if (books.count() == 0)
				std::cout << "No being read books!" << std::endl;
			else
				books.print();
		}

		void test_store_query_in_store()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_in_store(true);
			if (books.count() == 0)
				std::cout << "No in_store books!" << std::endl;
			else
				books.print();
		}
		
		void test_store_query_not_in_store()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_in_store(false);
			if (books.count() == 0)
				std::cout << "No not_in_store books!" << std::endl;
			else
				books.print();
		}

		void test_store_query_title()
		{
			const std::string title("C++ primer");

			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_title(title);
			if (books.count() == 0)
				std::cout << "No books named " << title << std::endl;
			else
				books.print();
		}

		void test_store_query_author()
		{
			const std::string author("Chorulex");

			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_author(author);
			if (books.count() == 0)
				std::cout << "No books by " << author << std::endl;
			else
				books.print();
		}

		void test_store_query_publisher()
		{
			const std::string publisher("Alesxhiagic");

			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_publisher(publisher);
			if (books.count() == 0)
				std::cout << "No books pressed by " << publisher << std::endl;
			else
				books.print();
		}

		void test_store_query_translated()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_translated(true);
			if (books.count() == 0)
				std::cout << "No books translated!" << std::endl;
			else
				books.print();
		}

		void test_store_query_not_translated()
		{
			iLibrary::store& srv_store = _lib.get_srv_store();
			iLibrary::package& books = srv_store.query_translated(false);
			if (books.count() == 0)
				std::cout << "No books not-translated!" << std::endl;
			else
				books.print();
		}

		void test_store_update_over()
		{
			const isbn book_id("45f_dfg_3qasdfs4");
			bool over = true;

			iLibrary::store& srv_store = _lib.get_srv_store();
			if ( !srv_store.update_over(book_id, over))
				std::cout << "Fail to updata over!" << std::endl;
		}

		void test_store_update_in_store()
		{
			const isbn book_id("45f_dfg_3qasdfs4");
			bool in_store = true;

			iLibrary::store& srv_store = _lib.get_srv_store();
			if (!srv_store.update_in_store(book_id, in_store))
				std::cout << "Fail to updata in_store!" << std::endl;
		}

	public:
		int main()
		{
			test_initialize();

			
			//test_genaral_acquire();

			//test_genaral_update();
			//test_genaral_acquire();
			
			/*
			//test_store_add();
			//test_store_query_all();

			//test_store_update_over();
			//test_store_query_over();
			
			//test_store_query_not_over();

			//test_store_query_in_store();
			//test_store_query_not_in_store();

			//test_store_query_title();
			//test_store_query_author();

			//test_store_query_publisher();
			
			test_store_query_translated();
			test_store_query_not_translated();
			*/

			test_store_update_in_store();

			test_destroy();
			return 0;
		}
	};
};

#endif
