/**store.h
 * description: 系统书库数据保存的服务接口
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _BOOK_STORE_H_
#define _BOOK_STORE_H_

#include "../book/package.h"
#include "../table/table_book.h"

#include "server.h"


namespace iLibrary
{
	class store : public server
	{
	public:

	private:
		table_book _book_table;

	protected:

	public:
		virtual bool initialize() override;
		virtual void destroy() override;

		/* 添加一本书 */
		virtual bool add(const book& item);

		/* 添加多本书 */
		virtual bool add( package& set);

		/* 根据书名移除书籍，可能删除多本同名的书籍 */
		virtual bool remove(const std::string& title);

		/* 根据isbn标识移除书籍 */
		virtual bool remove(const isbn& id);

		/* bool modify(isbn id, const book& item); // cip数据事后似乎不能修改 */

		/* 根据isbn修改阅读状态 */
		virtual bool modify(const isbn& id, const state& stat);

		/* 根据isbn修改书籍评论 */
		virtual bool modify(const isbn& id, const comment& comm);

		/* 根据isbn查询书籍 */
		virtual book query(const isbn& id) noexcept(false);

		/* 根据书名查询书籍 */
		virtual package query(const std::string& title);

		/* 根据阅读状态查询书籍，有可能查询出多本书籍 */
		virtual package query_over(bool over);
		virtual package query_in_store(bool in_store);

		/* 查询所有书籍 */
		virtual package query();
	};

	class store_fake : public store
	{
	protected:
		package _books;

	public:
		bool initialize() override
		{
			_books.add(book(cip(92, "C++ primer", "Chorulex", isbn("adf_123_3q341234"), publish(4, true, "人民邮电出版社")), purchase(78, 5412, "亚马逊")));
			_books.add(book(cip(65, "C++ 沉思录", "Chorulex.C.sexet", isbn("45f_dfg_3qasdfs4"), publish(1, true, "人民邮电出版社")), purchase(45, 2542, "淘宝网")));

			return true;
		}

		void destroy() override
		{

		}

		bool add(const book& item) override
		{
			_books.add(item);
			return true;
		}

		bool add( package& pkg) override
		{
			while (pkg.has_more())
			{
				add(pkg.next());
			}

			return true;
		}

		bool remove(const std::string& title) override
		{
			try
			{
				package pkg = query(title);
				_books.remove(title);
			}
			catch (out_of_range& e)
			{
				std::cout << e.what();
				return false;
			}

			return true;
		}

		bool remove(const isbn& id) override
		{
			try
			{
				book item = query(id);
			}
			catch (out_of_range& e)
			{
				std::cout << e.what();
				return false;
			}

			_books.remove(id);
			return true;
		}

		/* 根据isbn修改阅读状态 */
		bool modify(const isbn& id, const state& stat)  override
		{
			return false;
		}

		bool modify(const isbn& id, const comment& comm)  override
		{
			return false;
		}

		package query() override
		{
			return _books;
		}

		book query(const isbn& id) noexcept(false) override
		{
			while (_books.has_more())
			{
				book& item = _books.next();
				if (item.get_cip().id.value == id.value)
					return item;
			}

			throw out_of_range("no exist this book!");
		}

		package query(const std::string& title) override
		{
			package pkg;
			while (_books.has_more())
			{
				book& item = _books.next();
				if (item.get_cip().title == title)
					pkg.add(item);
			}

			return pkg;
		}

		package query_over(bool over) override
		{
			package pkg;
			while (_books.has_more())
			{
				book& item = _books.next();
				if (item.get_state().over == over)
					pkg.add(item);
			}

			return pkg;
		}

		package query_in_store(bool in_store) override
		{
			package pkg;
			while (_books.has_more())
			{
				book& item = _books.next();
				if (item.get_state().in_store == in_store)
					pkg.add(item);
			}

			return pkg;
		}
	};
};

#endif
