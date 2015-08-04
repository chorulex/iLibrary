/**genaral.h
 * description: 书库信息服务
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _LIBRARY_GENERAL_H_
#define _LIBRARY_GENERAL_H_

#include "../library/option.h"
#include "../table/table_general.h"
#include "server.h"

namespace iLibrary
{
	class genaral : public server
	{
	public:
		virtual ~genaral() {}

	private:

	protected:
		table_general _general_table;

	public:
		virtual bool initialize() override;
		virtual void destroy() override;

		virtual option acquire();
		virtual bool update(const option& _new);
		virtual bool update_store_name(const std::string& name);
		virtual bool update_books_count(int count);
	};
};

#endif