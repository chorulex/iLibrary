/**library.h
 * description: 书库处理；这里作为用户的直接视图，通过本视图操作书库。
 * author: chorulex
 * date: 07/23/2015
 */

#include "../server/general.h"
#include "../server/store.h"
#include "../book/package.h"
#include "option.h"

namespace iLibrary
{
  class library
  {
  private:
    genaral_fake _srv_genaral;
    store_fake _srv_store;

  protected:

  public:
    genaral& get_srv_genaral() { return _srv_genaral; }
    store& get_srv_store() { return _srv_store; }

    bool initialize()
    {
      return _srv_genaral.initialize() && _srv_store.initialize();
    }

    void destroy()
    {
      _srv_genaral.destroy();
      _srv_store.destroy();
    }
  };

};
