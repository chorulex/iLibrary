/**manager.cpp
* description: 主视图，显示当前书库的基本信息以及各个其他操作入口
* author: chorulex
* date: 08/04/2015
*
* 依赖gtkmm
*/

#include "manager.h"

namespace iLibrary
{
	manager_view::manager_view(library& lib) : _library(lib), _srv_stroe(_library.get_srv_store()), _srv_general(_library.get_srv_genaral())
	{
	}

	bool manager_view::init_window()
	{
		//
		add(_lb_general);

		std::string title("iLibrary");
		
		set_title(title);
		set_default_size(400,300);

		return true;
	}

	bool manager_view::load_general()
	{
		option opt = _srv_general.acquire();


		return true;
	}

	bool manager_view::load_books()
	{
		return true;
	}
 }
