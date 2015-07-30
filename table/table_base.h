/**table_base.h
 * description: 数据表操作类基类及相应的辅助工具
 * author: chorulex
 * date: 07/30/2015
 */

#ifndef _LIBRARY_TABLE_BASE_H_
#define _LIBRARY_TABLE_BASE_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "../xml/tinyxml.h"

namespace iLibrary
{
	class file
	{
		friend class table;

	private:
		file(const std::string& path) : _path(path) {}

	private:
		std::string _path;

		bool exist()
		{
			locale loc = locale::global(locale(""));
			std::ifstream file(_path.c_str(), ios::in);
			locale::global(loc);

			bool exist = file.is_open();

			file.close();
			return exist;
		}

		bool create()
		{
			locale loc = locale::global(locale(""));
			std::ofstream file;
			file.open(_path.c_str(), ios::app);
			locale::global(loc);

			return file.is_open();
		}
	};

	class table
	{
	protected:
		table() : _doc(nullptr) {}
		virtual ~table() {}

	protected:
		std::string _table_name;
		TiXmlDocument* _doc;

	protected:
		std::vector<isbn> query_section(const std::string& table, const std::string& section, const std::string& value)
		{
			std::vector<isbn> result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return result;

			for (TiXmlElement* elem = root->FirstChildElement(table.c_str()); elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if (opt == nullptr || opt->Value() == nullptr)
					continue;

				TiXmlElement* item = elem->FirstChildElement(section.c_str());
				if (item != nullptr && !item->NoChildren())
				{
					if (value == item->FirstChild()->Value())
					{
						result.push_back(isbn(opt->Value()));
					}
				}
			}

			return result;
		}

	public:
		bool initialize()
		{
			file _file(_table_name);

			bool exist = true;
			if (!_file.exist())
			{
				exist = false;

				std::cout << "Not Exist table file " << _table_name << std::endl;

				if (!_file.create())
				{
					std::cout << "Fail to create table file " << _table_name << std::endl;
					return false;
				}
			}

			_doc = new TiXmlDocument(_table_name.c_str());
			if (exist == false)
			{
				TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "yes");
				_doc->LinkEndChild(decl);
			}
			else
			{
				if (!_doc->LoadFile())
				{
					std::cout << _doc->ErrorDesc() << std::endl;
					return false;
				}
			}

			return true;
		}

		void destroy()
		{
			_doc->SaveFile();
		}
	};
}

#endif
