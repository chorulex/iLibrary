/**table_general.h
 * description: general数据库操作
 * author: chorulex
 * date: 07/29/2015
 */

#ifndef _LIBRARY_TABLE_GENERAL_H_
#define _LIBRARY_TABLE_GENERAL_H_

#include <cstdlib>
#include <string>
#include <sstream>

#include "../book/detail.h"
#include "../xml/tinyxml.h"

#include "table_base.h"

namespace iLibrary
{
	class table_general : public table
	{
	public:
		table_general()
		{
			_table_name = "database/general.xml";
		}

		option acquire()
		{
			option opt;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
			{
				opt.count = 0;
				opt.name = "Library of Chorulex";

				TiXmlNode* node = new TiXmlElement("general");

				TiXmlNode* count = new TiXmlElement("count");
				count->InsertEndChild(TiXmlText("0"));
				node->LinkEndChild(count);

				TiXmlNode* name = new TiXmlElement("name");
				name->InsertEndChild(TiXmlText(opt.name.c_str()));
				node->LinkEndChild(name);

				_doc->LinkEndChild(node);
				return opt;
			}
			else
			{
				TiXmlElement* node = root->FirstChildElement("count");
				if (node != nullptr && !node->NoChildren())
					opt.count = atoi(node->FirstChild()->Value());

				node = root->FirstChildElement("name");
				if (node != nullptr && !node->NoChildren())
					opt.name = node->FirstChild()->Value();
			}

			return opt;
		}

		bool update(const option& _new)
		{
			return update_count(_new.count) && update_name(_new.name);
		}

		bool update_name(const std::string& name)
		{
			return update_section("general", "name", name);
		}

		bool update_count(int count)
		{
			std::stringstream value;
			value << count;

			return update_section("general", "count", value.str());
		}
	};
}

#endif
