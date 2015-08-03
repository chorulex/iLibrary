/**detail.h
 * description: 书籍的详细信息，包括CIP数据、阅读状态以及书籍的社会评论
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _BOOK_DETIALS_H_
#define _BOOK_DETIALS_H_

#include "../printor.h"

#include <ctime>
#include <string>

namespace iLibrary
{
	class isbn : public printor
	{
	public:
		isbn() {}
		isbn(const std::string& _new) : value(_new) {}

		std::string value;

		void print() override
		{
			std::cout << "ISBN:" << value << std::endl;
		}
	};

	class publish : public printor
	{
	public:
		publish() {}
		publish(int _version, bool _translated, const std::string& _company) : version(_version), translated(_translated), company(_company) {}

		int version = 1;
		bool translated = false;
		time_t datetime = 0;
		std::string company;

		void print() override
		{
			std::cout << "Publish: " << "version:" << version
			<< " translated:" << (translated ? "true" : "false")
			<< " datetime:" << datetime
			<< " company:" << company
			<< std::endl;
		}
	};

	class cip : public printor
	{
	public:
		cip() {}
		cip(int _price, const std::string& _title, const std::string& _author, const isbn& _id, const publish& _press) \
		: price(_price), title(_title), author(_author), id(_id), press(_press) {}

		int price;
		std::string title;
		std::string author;

		isbn id;
		publish press;

		void print() override
		{
			std::cout << "title:" << title << std::endl;
			std::cout << "CIP: " << "price:" << price << " author:" << author << std::endl;

			id.print();
			press.print();
		}
	};

	class purchase : public printor
	{
	public:
		purchase() {}
		purchase(int _charge, time_t _date, const std::string& _seller) : charge(_charge), date(_date), seller(_seller) {}

		int charge = 0;
		time_t date = 0;
		std::string seller = "unknown";

		void print() override
		{
			std::cout << "Purchase: " << "seller:" << seller << " charge:" << charge << " date:" << date << std::endl;
		}
	};

	class comment : public printor
	{
	public:
		std::string context;
		std::string name;

		comment() {}
		comment(const std::string& new_name, const std::string& new_context) : name(new_name), context(new_context) {}

		void print() override
		{
			std::cout <<"Comment: " << "context:" << context << " name:" << name << std::endl;
		}
	};

	class state : public printor
	{
	public:
		state() {}
		state(bool _over, bool _in_store, int _page, int _current) \
		: over(_over), in_store(_in_store), page(_page), current(_current) {}

		bool over = false;
		bool in_store = true;
		int page = 0;
		int current = 0;

		void print() override
		{
			std::cout << "State: "<< "over:" << (over ? "true" : "false")
				<< " in_store:" << (in_store ? "true" : "false")
				<< " page:" << page
				<< " current:" << current
				<< std::endl;
		}
	};
};

#endif
