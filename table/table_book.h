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

#include "table.h"

namespace iLibrary
{
	class table_book : public table
	{
	public:
		table_book()
		{
			_table_name = "database/book.xml";
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
			TiXmlNode* isbn = new TiXmlElement("ISBN");
			isbn->InsertEndChild(TiXmlText(item.get_cip().id.value.c_str()));
			root->LinkEndChild(isbn);

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
			return book();
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
			return package();
		}
	};
}

#endif
