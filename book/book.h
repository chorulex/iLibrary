/**book.h
 * description: 记录并操作书籍信息
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _BOOK_ITEM_H_
#define _BOOK_ITEM_H_

#include "detail.h"

#include <vector>

namespace iLibrary
{
  class book
  {
  public:
	book() {}

    /* 无阅读记录 */
    book(const cip& base, const purchase& buy) : _cip(base), _purchase(buy) {}

    /* 已阅读部分 */
    book(const cip& base, const purchase& buy, const state& stat) : _cip(base), _purchase(buy), _state(stat) {}

  protected:
    cip _cip;
    purchase _purchase;
    state _state;
    std::vector<comment> _comments;

  public:
    cip get_cip() { return _cip; }
    purchase get_purchase() { return _purchase; }
    state get_state() { return _state; }
    std::vector<comment> get_comment() { return _comments; }

    void set_cip(const cip& src) { _cip = src; }
    void set_purchase(const purchase& src) { _purchase = src; }
    void set_state(const state& src) { _state = src; }

    void add_comment(const comment& item) { _comments.push_back(item); }

    void print()
    {
      _cip.print();
      _purchase.print();
      _state.print();

	  for (auto iter = begin(_comments); iter != end(_comments); iter++ )
		iter->print();
    }
  };

};

#endif