
#include "library/library.h"

int main()
{
  iLibrary::library lib;
  if( !lib.initialize() )
  {
    std::cout<< "Faid to init library!" << std::endl;
    return 0;
  }

  iLibrary::option& opt = lib.get_srv_genaral().acquire();
  opt.print();

  iLibrary::store& srv_store = lib.get_srv_store();
  iLibrary::package& books = srv_store.query();
  books.print();

  books = srv_store.query_over(true);
  if (books.count() == 0)
	  std::cout<< "No over_readed books!" << std::endl;
  else
	books.print();

  lib.destroy();
  return 0;
}
