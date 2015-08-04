/**manager.h
* description: 主视图，显示当前书库的基本信息以及各个其他操作入口
* author: chorulex
* date: 07/24/2015
*/

#ifndef _VIEW_MANAGER_H_
#define _VIEW_MANAGER_H_

#include "../library/library.h"

#include <gtkmm.h>
#include <gtk/gtk.h>

namespace iLibrary
{
	class manager_view : public Gtk::Window
	{
	public:
		manager_view(library& lib);

	private:
		library& _library;
		store& _srv_stroe;
		genaral& _srv_general;

		//
		Gtk::Label _lb_general;

	public:
		bool init_window();
		bool load_general();
		bool load_books();
	};
}

#endif
