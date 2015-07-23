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
		return true;
	}

	void store::destroy()
	{

	}

	/* 添加一本书 */
	bool store::add(const book& item)
	{
		return true;
	}

	/* 添加多本书 */
	bool store::add(const package& set)
	{
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

	/* 根据isbn查询书籍 */
	book store::query(const isbn& id) noexcept(false)
	{
		return book();
	}

	/* 根据书名查询书籍 */
	package store::query(const std::string& title)
	{
		return package();
	}

	/* 根据是否阅读完成状态查询书籍，有可能查询出多本书籍 */
	package store::query_over(bool over)
	{
		return package();
	}

	/* 根据在库状态查询书籍，有可能查询出多本书籍 */
	package store::query_in_store(bool in_store)
	{
		return package();
	}

	/* 查询所有书籍 */
	package store::query()
	{
		return package();
	}
};