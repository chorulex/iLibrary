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

		std::vector<comment> query_isbn(const isbn& book_id)
		{
			std::vector<comment> result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;

			TiXmlElement* elem = _doc->FirstChildElement("books");
			for( ; elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if( opt == nullptr )
					continue;
				if( opt->Value() != book_id.value )
					continue;

				for(TiXmlElement* item = elem->FirstChildElement("comment"); item != nullptr; item->NextSiblingElement())
				{
					comment comm;

					TiXmlAttribute* name = elem->FirstAttribute();
					comm.name = name == nullptr? "unknown": name->Value();

					if (!item->NoChildren())
						comm.context = item->FirstChild()->Value();

					result.push_back(comm);
				}

				return result;
			}

			return result;
		}
	};
}

#endif
