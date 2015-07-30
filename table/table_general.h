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
			return update(_new.count) && update(_new.name);
		}

		bool update(const std::string& name)
		{
			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return false;

			TiXmlElement* name_node = root->FirstChildElement("name");
			if (name_node == nullptr)
				return false;

			if (name_node->NoChildren())
				name_node->InsertEndChild(TiXmlText(name.c_str()));
			else
				name_node->FirstChild()->SetValue(name.c_str());
			return true;
		}

		bool update(int count)
		{
			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return false;

			TiXmlElement* count_node = root->FirstChildElement("count");
			if (count_node == nullptr)
				return false;

			std::stringstream count_str;
			count_str << count;

			if (count_node->NoChildren())
				count_node->InsertEndChild(TiXmlText(count_str.str().c_str()));
			else
				count_node->FirstChild()->SetValue(count_str.str().c_str());
			return true;
		}
	};
}

#endif
