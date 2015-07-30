/**table_book.h
 * description: book数据库操作
 * author: chorulex
 * date: 07/29/2015
 */

#ifndef _LIBRARY_TABLE_BOOK_H_
#define _LIBRARY_TABLE_BOOK_H_

#include <cstdlib>
#include <string>
#include <sstream>

#include "../book/detail.h"
#include "../xml/tinyxml.h"

#include "table_base.h"
#include "table_comment.h"
#include "table_state.h"
#include "table_publish.h"
#include "table_purchase.h"
#include "table_cip.h"

namespace iLibrary
{
	class table_book : public table
	{
	public:
		table_book() : _cip_table( _publish_table)
		{
				_table_name = "database/book.xml";
		}

	protected:
		table_publish _publish_table;

		table_cip _cip_table;
		table_comment _comment_table;
		table_purchase _purchase_table;
		table_state _state_table;

	public:
		bool initialize()
		{
			if( !table::initialize() )
				return false;

			return _cip_table.initialize() &&
					_comment_table.initialize() &&
					_publish_table.initialize() &&
					_purchase_table.initialize() &&
					_state_table.initialize();
		}

		void destroy()
		{
			_state_table.destroy();
			_purchase_table.destroy();
			_publish_table.destroy();
			_comment_table.destroy();
			_cip_table.destroy();

			table::destroy();
		}

		bool add(const book& item)
		{
			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
			{
				TiXmlNode* node = new TiXmlElement("books");
				_doc->LinkEndChild(node);
			}

			root = _doc->RootElement();
			TiXmlElement* isbn = new TiXmlElement("book");
			isbn->SetAttribute("isbn", item.get_cip().id.value.c_str());
			isbn->InsertEndChild(TiXmlText(item.get_cip().title.c_str()));
			root->LinkEndChild(isbn);

			_state_table.add(item.get_cip().id, item.get_state());
			_purchase_table.add(item.get_cip().id, item.get_purchase());
			_cip_table.add(item.get_cip());

			return true;
		}

		bool remove(const std::string& title)
		{
			return true;
		}

		bool remove(const isbn& id)
		{
			return true;
		}

		bool modify(const isbn& id, const state& stat)
		{
			return true;
		}

		bool modify(const isbn& id, const comment& comm)
		{
			return true;
		}

		book query(const isbn& id) noexcept(false)
		{
			book result;

			result.set_cip(_cip_table.query(id));
			result.set_purchase(_purchase_table.query(id));
			result.set_state(_state_table.query(id));
			result.set_comments(_comment_table.query(id));

			return result;
		}

		package query(const std::string& title)
		{
			return package();
		}

		package query_over(bool over)
		{
			return package();
		}

		package query_in_store(bool in_store)
		{
			return package();
		}

		package query()
		{
			package result;

			TiXmlElement* elem = _doc->FirstChildElement("book");
			for( ; elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if( opt == nullptr )
					continue;

				book single;
				single.set

				state result;

				TiXmlElement* item = elem->FirstChildElement("over");
				if (item != nullptr && !item->NoChildren())
					result.over = item->FirstChild()->Value() == "true";

				item = elem->FirstChildElement("in_store");
				if (item != nullptr && !item->NoChildren())
					result.in_store = item->FirstChild()->Value() == "true";

				item = elem->FirstChildElement("page");
				if (item != nullptr && !item->NoChildren())
					result.page = atoi(item->FirstChild()->Value());

				item = elem->FirstChildElement("current");
				if (item != nullptr && !item->NoChildren())
					result.current = atoi(item->FirstChild()->Value());

				return result;
			return package();
		}
	};
}

#endif
