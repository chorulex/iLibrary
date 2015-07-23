/**printor.h
 * description: 打印器
 * author: chorulex
 * date: 07/23/2015
 */

#ifndef _BASE_PRINTOR_H_
#define _BASE_PRINTOR_H_

#include <cstdio>
#include <iostream>
using namespace std;

class printor
{
public:
  virtual ~printor() {}

public:
  virtual void print() = 0;
};

#endif