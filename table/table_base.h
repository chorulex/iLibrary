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

		bool update_section(TiXmlElement* table_node, TiXmlElement* section_node, const std::string& section, const std::string& value)
		{
			if (table_node == nullptr)
				return false;

			if (section_node == nullptr)
			{
				TiXmlElement new_section(section.c_str());
				new_section.InsertEndChild(TiXmlText(value.c_str()));
				table_node->InsertEndChild(new_section);
			}
			else
			{
				if (section_node->NoChildren())
				{
					section_node->InsertEndChild(TiXmlText(value.c_str()));
				}
				else
				{
					section_node->FirstChild()->SetValue(value.c_str());
				}
			}

			return true;
		}

		bool update_section(const std::string& table, const std::string& section, const std::string& value)
		{
			std::vector<isbn> result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return false;

			TiXmlElement* elem = nullptr;
			if( table.compare(root->Value()) == 0)
				elem = _doc->FirstChildElement(table.c_str());
			else
				elem = root->FirstChildElement(table.c_str());

			for (; elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlElement* item = elem->FirstChildElement(section.c_str());

				if (!update_section(elem, item, section, value))
					return false;
			}

			return true;
		}

		bool update_section(const isbn& book_id, const std::string& table, const std::string& section, const std::string& value)
		{
			std::vector<isbn> result;

			TiXmlElement* root = _doc->RootElement();
			if (root == nullptr)
				return false;

			for (TiXmlElement* elem = root->FirstChildElement(table.c_str()); elem != nullptr; elem = elem->NextSiblingElement())
			{
				TiXmlAttribute* opt = elem->FirstAttribute();
				if (opt == nullptr || opt->Value() == nullptr)
					continue;

				const std::string id(opt->Value());
				if (id.compare(book_id.value) == 0)
				{
					TiXmlElement* item = elem->FirstChildElement(section.c_str());
					return update_section(elem, item, section, value);
				}
			}

			return false;
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
