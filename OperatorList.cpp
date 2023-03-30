/* 
 * File:   OperatorList.cpp
 * Author: brian
 * 
 * Created on June 10, 2014, 10:25 PM
 */

#include "OperatorList.h"

OperatorList::OperatorList() {
    construct_default_operators();
}

OperatorList::OperatorList(const OperatorList& orig) : HashList(orig)  {
}

OperatorList::~OperatorList() {
}

