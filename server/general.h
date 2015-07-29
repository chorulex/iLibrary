/**genaral.h
 * description: 书库信息服务
 * author: chorulex
 * date: 07/23/2015
 */

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

	/* Only for unit test */
	class genaral_fake : public genaral
	{
	protected:
		option _option;

	public:
		bool initialize() override
		{
			_option.count = 0;
			_option.name = "Library of Chorulex";

			return true;
		}

		void destroy() override
		{

		}

		option acquire() override
		{
			return _option;
		}

		bool update(const option& _new) override
		{
			_option = _new;
			return true;
		}

		bool update_store_name(const std::string& name) override
		{
			_option.name = name;
			return true;
		}

		bool update_books_count(int count) override
		{
			_option.count = count;
			return true;
		}
	};

};
