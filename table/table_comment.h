/**table_comment.h
 * description: 书籍评论数据表操作
 * author: chorulex
 * date: 07/30/2015
 */

#ifndef _LIBRARY_TABLE_COMMENT_H_
#define _LIBRARY_TABLE_COMMENT_H_

#include <string>
#include <vector>

#include "../book/detail.h"
#include "../xml/tinyxml.h"

#include "table_base.h"
namespace iLibrary
{
	class table_comment : public table
	{
	public:
		table_comment()
		{
			_table_name = "database/comment.xml";
		}

		bool add(const isbn& book_id, const comment& comm)
		{
			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
			{
				TiXmlNode* node = new TiXmlElement("comments");
				_doc->LinkEndChild(node);
			}

			root = _doc->RootElement();

			TiXmlElement item("comment");
			item.SetAttribute("isbn", book_id.value.c_str());

			TiXmlElement name("name");
			name.InsertEndChild(TiXmlText(comm.name.c_str()));
			item.InsertEndChild(name);

			TiXmlElement context("context");
			context.InsertEndChild(TiXmlText(comm.context.c_str()));
			item.InsertEndChild(context);

			root->InsertEndChild(item);
			return true;
		}

		bool add(const isbn& book_id, const std::vector<comment>& comms)
		{
			for (auto iter = begin(comms); iter != end(comms); ++iter)
			{
				if (!add(book_id, *iter))
					return false;
			}

			return true;
		}

		std::vector<comment> query_isbn(const isbn& book_id)
		{
			std::vector<comment> result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;
			
			for(TiXmlElement* elem = root->FirstChildElement("comment"); elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if( opt == nullptr || opt->Value() != book_id.value )
					continue;

				comment comm;

				TiXmlElement* item = elem->FirstChildElement("name");
				if (item != nullptr && !item->NoChildren())
					comm.name = item->FirstChild()->Value();

				item = elem->FirstChildElement("context");
				if (item != nullptr && !item->NoChildren())
					comm.context = item->FirstChild()->Value();

				result.push_back(comm);
			}

			return result;
		}
	};
}

#endif
