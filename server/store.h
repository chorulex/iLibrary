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
		bool initialize() override;
		void destroy() override;

		/* 添加一本书 */
		bool add(const book& item);

		/* 添加多本书 */
		bool add( package& set);
		
		/* 增加书籍评论 */
		bool add_comment(const isbn& book_id, const comment& comm);

		/* 根据isbn查询书籍 */
		book query_isbn(const isbn& id) noexcept(false);

		/* 根据书名查询书籍 */
		package query_title(const std::string& title);

		/* 根据作者查询书籍 */
		package query_author(const std::string& author);

		/* 根据出版社查询书籍 */
		package query_publisher(const std::string& publisher);

		/* 查询是否翻译书籍 */
		package query_translated(bool translated);

		/* 根据阅读状态查询书籍，有可能查询出多本书籍 */
		package query_over(bool over);

		/* 查看是否在库书籍 */
		package query_in_store(bool in_store);

		/* 查询所有书籍 */
		package query_all();
				
		/* 修改阅读状态 */
		bool update_state(const isbn& id, const state& stat);

		/* 修改已读状态 */
		bool update_over(const isbn& id, bool over);

		/* 修改在库状态 */
		bool update_in_store(const isbn& id, bool in_store);

		/* 修改已阅读页数 */
		bool updata_current_page_read(const isbn& id, int page);

		/* 根据isbn标识移除书籍 */
		bool remove(const isbn& id);

	};
};

#endif
