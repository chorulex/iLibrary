/**package.h
 * description: 图书集合，这里称之为"package"
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _BOOK_PAKAGE_H_
#define _BOOK_PAKAGE_H_

#include "../enumerator.h"
#include "../printor.h"
#include "book.h"

namespace iLibrary
{
	class package : public enumerator<book>, public printor
	{
	public:
		package() {}
		package(const package& src) : _books(src._books) {}

	private:
		std::vector<book> _books;

	protected:

	public:
		void print() override
		{
			for (auto iter = begin(_books); iter != end(_books); ++iter)
			{
				std::cout << std::endl;
				iter->print();
			}
		}

		void remove(const std::string& title)
		{
			for (auto iter = begin(_books); iter != end(_books); ++iter)
			{
				book& item = *iter;
				if (item.get_cip().title == title)
					_books.erase(iter);
			}
		}

		void remove(const isbn& id)
		{
			for (auto iter = begin(_books); iter != end(_books); ++iter)
			{
				book& item = *iter;
				if (item.get_cip().id.value == id.value)
					_books.erase(iter);
			}
		}

		void add(const book& item)
		{
			_books.push_back(item);
		}

		int count() const
		{
			return static_cast<int>(_books.size());
		}


		/* 枚举器继承 */
		bool has_more() const  override
		{
			return _current < static_cast<int>(_books.size());
		}

		book& next()  override
		{
			return _books[_current++];
		}
	};
};

#endif