/**table.h
 * description: 数据操作类
 * author: chorulex
 * date: 07/29/2015
 */

#ifndef _LIBRARY_TABLE_H_
#define _LIBRARY_TABLE_H_

#include <string>
#include <iostream>
#include <fstream>

#include "../book/detail.h"
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

	class table_cip : public table
	{
	public:
		table_cip()
		{
			_table_name = "database/cip.xml";
		}
	};

	class table_comment : public table
	{
	public:
		table_comment()
		{
			_table_name = "database/comment.xml";
		}
	};

	class table_publish : public table
	{
	public:
		table_publish()
		{
			_table_name = "database/publish.xml";
		}
	};

	class table_purchase : public table
	{
	public:
		table_purchase()
		{
			_table_name = "database/purchase.xml";
		}
	};

	class table_state: public table
	{
	public:
		table_state()
		{
			_table_name = "database/state.xml";
		}
	};
}

#endif
