/**general.cpp
 * description: 书库信息服务
 * author: chorulex
 * date: 07/23/2015
 */

 #include "general.h"

 namespace iLibrary
 {
   bool genaral::initialize()
   {
	   return _general_table.initialize();
   }

   void genaral::destroy() 
   {
	   _general_table.destroy();
   }

   option genaral::acquire()
   {
	   return _general_table.acquire();
   }

   bool genaral::update(const option& _new)
   {
	   return _general_table.update(_new);
   }

   bool genaral::update_store_name(const std::string& name)
   {
	   return _general_table.update(name);
   }

   bool genaral::update_books_count(int count)
   {
	   return _general_table.update(count);
   }
 };
