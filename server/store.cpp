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

	/* bool modify(isbn id, const book& item); // cip数据事后似乎不能修改 */

	/* 根据isbn修改阅读状态 */
	bool store::modify(const isbn& id, const state& stat)
	{
		return true;
	}

	/* 根据isbn修改书籍评论 */
	bool store::modify(const isbn& id, const comment& comm)
	{
		return true;
	}

	/* 查询所有书籍 */
	package store::query()
	{
		return _book_table.query();
	}

	/* 根据isbn查询书籍 */
	book store::query(const isbn& id) noexcept(false)
	{
		return _book_table.query(id);
	}

	/* 根据书名查询书籍 */
	package store::query(const std::string& title)
	{
		return package();
	}

	/* 根据是否阅读完成状态查询书籍，有可能查询出多本书籍 */
	package store::query_over(bool over)
	{
		return _book_table.query_over(over);
	}

	/* 根据在库状态查询书籍，有可能查询出多本书籍 */
	package store::query_in_store(bool in_store)
	{
		return package();
	}

};
