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
			
			_cip_table.add(item.get_cip());
			_purchase_table.add(item.get_isbn(), item.get_purchase());
			_state_table.add(item.get_isbn(), item.get_state());
			_comment_table.add(item.get_isbn(), item.get_comments());

			return true;
		}
		
		bool add_comment(const isbn& book_id, const comment& comm)
		{
			return _comment_table.add(book_id, comm);
		}

		package query_all()
		{
			package result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;

			for (TiXmlElement* elem = root->FirstChildElement("book"); elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if (opt == nullptr || opt->Value() == nullptr)
					continue;

				book single;
				single.set_isbn(opt->Value());

				result.add(single);
			}

			while (result.has_more())
			{
				book& item = result.next();
				item = query_isbn(item.get_isbn());
			}
			return result;
		}

		book query_isbn(const isbn& id)
		{
			book result;

			result.set_cip(_cip_table.query_isbn(id));
			result.set_purchase(_purchase_table.query_isbn(id));
			result.set_state(_state_table.query_isbn(id));
			result.set_comments(_comment_table.query_isbn(id));

			return result;
		}

		package query_title(const std::string& title)
		{
			package result;
			std::vector<isbn>& book_ids = _cip_table.query_title(title);

			for (auto iter = begin(book_ids); iter != end(book_ids); ++iter)
			{
				book item = query_isbn(*iter);
				if (!item.get_isbn().value.empty())
					result.add(item);
			}

			return result;
		}

		package query_author(const std::string& author)
		{
			package result;
			std::vector<isbn>& book_ids = _cip_table.query_author(author);

			for (auto iter = begin(book_ids); iter != end(book_ids); ++iter)
			{
				book item = query_isbn(*iter);
				if (!item.get_isbn().value.empty())
					result.add(item);
			}

			return result;
		}

		package query_publisher(const std::string& publisher)
		{
			package result;
			std::vector<isbn>& book_ids = _cip_table.query_publisher(publisher);

			for (auto iter = begin(book_ids); iter != end(book_ids); ++iter)
			{
				book item = query_isbn(*iter);
				if (!item.get_isbn().value.empty())
					result.add(item);
			}

			return result;
		}		

		package query_translated(bool translated)
		{
			package result;
			std::vector<isbn>& book_ids = _cip_table.query_translated(translated);

			for (auto iter = begin(book_ids); iter != end(book_ids); ++iter)
			{
				book item = query_isbn(*iter);
				if (!item.get_isbn().value.empty())
					result.add(item);
			}

			return result;
		}

		package query_over(bool over)
		{
			package result;
			std::vector<isbn>& book_ids =  _state_table.query_over(over) ;
			
			for (auto iter = begin(book_ids); iter != end(book_ids); ++iter)
			{
				book item = query_isbn(*iter);
				if (!item.get_isbn().value.empty())
					result.add(item);
			}

			return result;
		}

		package query_in_store(bool in_store)
		{
			package result;
			std::vector<isbn>& book_ids = _state_table.query_in_store(in_store);

			for (auto iter = begin(book_ids); iter != end(book_ids); ++iter)
			{
				book item = query_isbn(*iter);
				if (!item.get_isbn().value.empty())
					result.add(item);
			}

			return result;
		}

		bool update_state(const isbn& id, const state& stat)
		{
			return _state_table.update(id, stat);
		}

		bool updata_current_page_read(const isbn& book_id, int page)
		{
			return _state_table.updata_current_page_read(book_id, page);
		}

		bool update_in_store(const isbn& id, bool in_store)
		{
			return _state_table.updata_in_store(id, in_store);
		}

		bool update_over(const isbn& id, bool over)
		{
			return _state_table.updata_over(id, over);
		}

		bool update(const isbn& id, const comment& comm)
		{
			return true;
		}
		
		bool remove(const isbn& id)
		{
			return remove_item(id, "book") && _cip_table.remove(id) && _purchase_table.remove(id) && _state_table.remove(id);					
		}
	};
}

#endif
