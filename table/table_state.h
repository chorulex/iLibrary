/**table_state.h
 * description: 图书阅读状态数据表操作
 * author: chorulex
 * date: 07/30/2015
 */

#ifndef _LIBRARY_TABLE_STATE_H_
#define _LIBRARY_TABLE_STATE_H_

#include <string>
#include <sstream>

#include "../book/detail.h"
#include "../xml/tinyxml.h"

#include "table_base.h"
namespace iLibrary
{
	class table_state: public table
	{
	public:
		table_state()
		{
			_table_name = "database/state.xml";
		}

		bool add(const isbn& book_id, const state& read_stat)
		{
			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
			{
				TiXmlNode* node = new TiXmlElement("states");
				_doc->LinkEndChild(node);
			}

			root = _doc->RootElement();

			TiXmlElement item("state");
			item.SetAttribute("isbn", book_id.value.c_str());

			TiXmlElement over("over");
			over.InsertEndChild(TiXmlText(read_stat.over ? "true" : "false"));
			item.InsertEndChild(over);

			TiXmlElement in_store("in_store");
			in_store.InsertEndChild(TiXmlText(read_stat.in_store ? "true" : "false"));
			item.InsertEndChild(in_store);

			TiXmlElement page("page");
			stringstream value;
			value << read_stat.page;
			page.InsertEndChild(TiXmlText(value.str().c_str()));
			item.InsertEndChild(page);

			TiXmlElement current("current");
			value << read_stat.page;
			current.InsertEndChild(TiXmlText(value.str().c_str()));
			item.InsertEndChild(current);

			root->InsertEndChild(item);
			return true;
		}

		state query_isbn(const isbn& book_id)
		{
			state result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;

			for(TiXmlElement* elem = root->FirstChildElement("state"); elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if( opt == nullptr )
					continue;
				if( opt->Value() != book_id.value )
					continue;

				TiXmlElement* item = elem->FirstChildElement("over");
				if (item != nullptr && !item->NoChildren())
					result.over = std::string("true").compare(item->FirstChild()->Value()) == 0;

				item = elem->FirstChildElement("in_store");
				if (item != nullptr && !item->NoChildren())
					result.in_store = std::string("true").compare(item->FirstChild()->Value()) == 0;

				item = elem->FirstChildElement("page");
				if (item != nullptr && !item->NoChildren())
					result.page = atoi(item->FirstChild()->Value());

				item = elem->FirstChildElement("current");
				if (item != nullptr && !item->NoChildren())
					result.current = atoi(item->FirstChild()->Value());

				return result;
			}

			return result;
		}

		std::vector<isbn> query_over(bool over)
		{
			return query_section("state", "over", over ? "true" : "false");
		}

		std::vector<isbn> query_in_store(bool in_store)
		{
			return query_section("state", "in_store", in_store ? "true" : "false");
		}

		bool updata_over(const isbn& book_id, bool over)
		{
			return update_section(book_id, "state", "over", over ? "true" : "false");
		}

		bool updata_in_store(const isbn& book_id, bool in_store)
		{
			return update_section(book_id, "state", "in_store", in_store ? "true" : "false");
		}

		bool updata_current_page_read(const isbn& book_id, int page)
		{
			std::stringstream value;
			value << page;

			return update_section(book_id, "state", "current", value.str());
		}

		bool update(const isbn& book_id, const state& stat)
		{
			return updata_over(book_id, stat.over) && updata_in_store(book_id, stat.in_store) && updata_current_page_read(book_id, stat.current);
		}
	};
}

#endif
