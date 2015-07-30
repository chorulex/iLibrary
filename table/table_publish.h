/**table_publish.h
 * description: 书籍出版信息数据表操作
 * author: chorulex
 * date: 07/30/2015
 */

#ifndef _LIBRARY_TABLE_PUBLISH_H_
#define _LIBRARY_TABLE_PUBLISH_H_

#include <string>
#include <vector>

#include "../book/detail.h"
#include "../xml/tinyxml.h"

#include "table_base.h"

namespace iLibrary
{
	class table_publish : public table
	{
	public:
		table_publish()
		{
			_table_name = "database/publish.xml";
		}

		bool add(const isbn& book_id, const publish& press)
		{
			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
			{
				TiXmlNode* node = new TiXmlElement("publishs");
				_doc->LinkEndChild(node);
			}

			root = _doc->RootElement();

			TiXmlElement item("publish");
			item.SetAttribute("isbn", book_id.value.c_str());

			TiXmlElement version("version");
			stringstream value;
			value << press.version;
			version.InsertEndChild(TiXmlText(value.str().c_str()));
			item.InsertEndChild(version);

			TiXmlElement translated("translated");
			translated.InsertEndChild(TiXmlText(press.translated?"true":"false"));
			item.InsertEndChild(translated);

			TiXmlElement datetime("datetime");
			value << press.datetime;
			datetime.InsertEndChild(TiXmlText(value.str().c_str()));
			item.InsertEndChild(datetime);

			TiXmlElement company("company");
			company.InsertEndChild(TiXmlText(press.company.c_str()));
			item.InsertEndChild(company);

			root->InsertEndChild(item);
			return true;
		}

		publish query(const isbn& book_id)
		{
			publish result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;

			for(TiXmlElement* elem = root->FirstChildElement("publish"); elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if( opt == nullptr )
					continue;
				if( opt->Value() != book_id.value )
					continue;

				TiXmlElement* item = elem->FirstChildElement("version");
				if (item != nullptr && !item->NoChildren())
					result.version = atoi(item->FirstChild()->Value());

				item = elem->FirstChildElement("translated");
				if (item != nullptr && !item->NoChildren())
					result.translated = item->FirstChild()->Value() == "true";

				item = elem->FirstChildElement("datetime");
				if (item != nullptr && !item->NoChildren())
					result.datetime = atoi(item->FirstChild()->Value());

				item = elem->FirstChildElement("company");
				if (item != nullptr && !item->NoChildren())
					result.company = item->FirstChild()->Value();

				return result;
			}

			return result;
		}
	};
}

#endif
