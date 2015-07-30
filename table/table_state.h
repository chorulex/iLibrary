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

		state query(const isbn& book_id)
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
			}

			return result;
		}

		std::vector<isbn> query_over()
		{
			return query_section("state", "over", "true");
		}

		std::vector<isbn> query_not_over()
		{
			return query_section("state", "over", "false");
		}
	};
}

#endif
