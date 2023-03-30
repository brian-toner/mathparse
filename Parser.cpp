/* 
 * File:   Parser.cpp
 * Author: brian
 * 
 * Created on June 10, 2014, 5:51 PM
 */

#include "Parser.h"

Parser::Parser() {
    
    //construct_default_operators();
    construct_numbers();
    construct_characters();
    construct_delim();
    
    vFunctions.vOperators = &vOperators;
    
}

Parser::Parser(const Parser& orig) {
}

Parser::~Parser() {
}