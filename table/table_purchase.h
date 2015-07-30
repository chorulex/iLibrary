/**table_purchase.h
 * description: 书籍的购买信息数据表操作
 * author: chorulex
 * date: 07/30/2015
 */

#ifndef _LIBRARY_TABLE_PURCHASE_H_
#define _LIBRARY_TABLE_PURCHASE_H_

#include <string>

#include "../book/detail.h"
#include "../xml/tinyxml.h"

#include "table_base.h"
namespace iLibrary
{
	class table_purchase : public table
	{
	public:
		table_purchase()
		{
			_table_name = "database/purchase.xml";
		}

		bool add(const isbn& book_id, const purchase& _purchase)
		{
			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
			{
				TiXmlNode* node = new TiXmlElement("purchases");
				_doc->LinkEndChild(node);
			}

			root = _doc->RootElement();

			TiXmlElement item("purchase");
			item.SetAttribute("isbn", book_id.value.c_str());

			TiXmlElement seller("seller");
			seller.InsertEndChild(TiXmlText(_purchase.seller.c_str()));
			item.InsertEndChild(seller);


			TiXmlElement charge("charge");
			stringstream value;
			value << _purchase.charge;
			charge.InsertEndChild(TiXmlText(value.str().c_str()));
			item.InsertEndChild(charge);

			TiXmlElement date("date");
			value << _purchase.date;
			date.InsertEndChild(TiXmlText(value.str().c_str()));
			item.InsertEndChild(date);

			root->InsertEndChild(item);
			return true;
		}

		purchase query(const isbn& book_id)
		{
			purchase result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;
			
			for(TiXmlElement* elem = root->FirstChildElement("purchase"); elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if( opt == nullptr )
					continue;
				if( opt->Value() != book_id.value )
					continue;
				
				TiXmlElement* item = elem->FirstChildElement("charge");
				if (item != nullptr && !item->NoChildren())
					result.charge = atoi(item->FirstChild()->Value());

				item = elem->FirstChildElement("date");
				if (item != nullptr && !item->NoChildren())
					result.date = atoi(item->FirstChild()->Value());

				item = elem->FirstChildElement("seller");
				if (item != nullptr && !item->NoChildren())
					result.seller = item->FirstChild()->Value();

				return result;
			}

			return result;
		}
	};
}

#endif
