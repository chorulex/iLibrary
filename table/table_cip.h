/**table_cip.h
 * description: 图书CIP数据表操作
 * author: chorulex
 * date: 07/30/2015
 */

#ifndef _LIBRARY_TABLE_CIP_H_
#define _LIBRARY_TABLE_CIP_H_

#include <string>


#include "../book/detail.h"
#include "../xml/tinyxml.h"

#include "table_base.h"
#include "table_publish.h"

namespace iLibrary
{
	class table_cip : public table
	{
	protected:
		table_publish& _publish_table;

	public:
		table_cip(table_publish& publish_table) : _publish_table(publish_table)
		{
			_table_name = "database/cip.xml";
		}

		bool add(const cip& base)
		{
			if (!_publish_table.add(base.id, base.press))
				return false;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
			{
				TiXmlNode* node = new TiXmlElement("cips");
				_doc->LinkEndChild(node);
			}

			root = _doc->RootElement();

			TiXmlElement item("cip");
			item.SetAttribute("isbn", base.id.value.c_str());

			TiXmlElement price("price");
			stringstream value;
			value << base.price;
			price.InsertEndChild(TiXmlText(value.str().c_str()));
			item.InsertEndChild(price);
			
			TiXmlElement title("title");
			title.InsertEndChild(TiXmlText(base.title.c_str()));
			item.InsertEndChild(title);

			TiXmlElement author("author");
			author.InsertEndChild(TiXmlText(base.author.c_str()));
			item.InsertEndChild(author);

			root->InsertEndChild(item);
			return true;
		}

		cip query_isbn(const isbn& book_id)
		{
			cip result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;

			TiXmlElement* elem = root->FirstChildElement("cip");
			for( ; elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if( opt == nullptr )
					continue;

				if( opt->Value() != book_id.value )
					continue;

				result.id = book_id;

				TiXmlElement* item = elem->FirstChildElement("price");
				if (item != nullptr && !item->NoChildren())
					result.price = atoi(item->FirstChild()->Value());

				item = elem->FirstChildElement("title");
				if (item != nullptr && !item->NoChildren())
					result.title = item->FirstChild()->Value();

				item = elem->FirstChildElement("author");
				if (item != nullptr && !item->NoChildren())
					result.author = item->FirstChild()->Value();

				result.press = _publish_table.query_isbn(book_id);
				return result;
			}

			return result;
		}

		std::vector<isbn> query_title(const std::string& title)
		{
			return query_section("cip", "title", title);
		}

		std::vector<isbn> query_author(const std::string& author)
		{
			return query_section("cip", "author", author);
		}

		std::vector<isbn> query_publisher(const std::string& publisher)
		{
			return _publish_table.query_publisher(publisher);
		}

		std::vector<isbn> query_translated(bool translated)
		{
			return translated ? _publish_table.query_translated() : _publish_table.query_not_translated();
		}

		bool remove(const isbn& book_id)
		{
			return remove_item(book_id, "cip") && _publish_table.remove(book_id);
		}
	};
}

#endif
