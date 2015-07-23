/**option.h
 * description: 书库的属性
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _STORE_OPTION_H_
#define _STORE_OPTION_H_

#include "../printor.h"
#include <string>

 namespace iLibrary
 {
   class option : public printor
   {
   public:
     int count;         // 书籍数目
     std::string name;  // 书库名称

	 void print() override
	 {
		 std::cout << "count:" << count << " name:" << name << std::endl;
	 }
   };

 };

#endif