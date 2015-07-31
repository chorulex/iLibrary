/**store.cpp
 * description: 书籍的详细信息，包括CIP数据、阅读状态以及书籍的社会评论
 * author: chorulex
 * date: 07/23/2015
 */

#include "store.h"

namespace iLibrary
{
	bool store::initialize()
	{
		return _book_table.initialize();
	}

	void store::destroy()
	{
		_book_table.destroy();
	}

	/* 添加一本书 */
	bool store::add(const book& item)
	{
		return _book_table.add(item);
	}

	/* 添加多本书 */
	bool store::add( package& set)
	{
		while( set.has_more() )
		{
			if (!add(set.next()))
				return false;
		}

		return true;
	}

	/* 根据书名移除书籍，可能删除多本同名的书籍 */
	bool store::remove(const std::string& title)
	{
		return true;
	}

	/* 根据isbn标识移除书籍 */
	bool store::remove(const isbn& id)
	{
		return true;
	}
	
	/* 根据isbn修改书籍评论 */
	bool store::add_comment(const isbn& id, const comment& comm)
	{
		return true;
	}

	/* 查询所有书籍 */
	package store::query_all()
	{
		return _book_table.query_all();
	}

	/* 根据isbn查询书籍 */
	book store::query_isbn(const isbn& id) noexcept(false)
	{
		return _book_table.query_isbn(id);
	}

	/* 根据书名查询书籍 */
	package store::query_title(const std::string& title)
	{
		return _book_table.query_title(title);
	}

	/* 根据作者查询书籍 */
	package store::query_author(const std::string& author)
	{
		return _book_table.query_author(author);
	}

	/* 根据出版社查询书籍 */
	package store::query_publisher(const std::string& publisher)
	{
		return _book_table.query_publisher(publisher);
	}

	/* 查询是否翻译书籍 */
	package store::query_translated(bool translated)
	{
		return _book_table.query_translated(translated);
	}

	/* 根据是否阅读完成状态查询书籍，有可能查询出多本书籍 */
	package store::query_over(bool over)
	{
		return _book_table.query_over(over);
	}

	/* 根据在库状态查询书籍，有可能查询出多本书籍 */
	package store::query_in_store(bool in_store)
	{
		return _book_table.query_in_store(in_store);
	}

	/* 修改已读状态 */
	bool store::update_over(const isbn& id, bool over)
	{
		return _book_table.update_over(id, over);
	}

	/* 修改在库状态 */
	bool store::update_in_store(const isbn& id, bool in_store)
	{
		return _book_table.update_in_store(id, in_store);
	}

	/* 修改已阅读页数 */
	bool store::updata_current_page_read(const isbn& id, int page)
	{
		return _book_table.updata_current_page_read(id, page);
	}

	/* 修改阅读状态 */
	bool store::update_state(const isbn& id, const state& stat)
	{
		return _book_table.update_state(id, stat);
	}
};
