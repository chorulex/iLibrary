/**server.h
 * description: 服务类结构的顶层类，所有的服务类都必须继承并实现
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _BOOK_SERVER_H_
#define _BOOK_SERVER_H_

 namespace iLibrary
 {
   class server
   {
   public:
     ~server() {}

   public:
     virtual bool initialize() = 0;
     virtual void destroy() = 0;
   };
 };

#endif