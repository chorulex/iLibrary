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
     return true;
   }

   void genaral::destroy() 
   {

   }

   option genaral::acquire()
   {
     return option();
   }

   bool genaral::update(const option& _new)
   {
     return true;
   }

   bool genaral::update_store_name(const std::string& name)
   {
     return true;
   }

   bool genaral::update_books_count(int count)
   {
     return true;
   }
 };
