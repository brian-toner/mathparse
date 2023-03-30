/* 
 * File:   parsefunctions.h
 * Author: brian
 *
 * Created on June 13, 2014, 9:37 AM
 */

#ifndef PARSEFUNCTIONS_H
#define	PARSEFUNCTIONS_H

#include "OperatorList.h"
#include "VariableList.h"
#include "stringfuncts.h"
#include "operators.h"

enum TOKTYPE{
    UNDEF = 0,
    OPERATOR = 1,
    LETTER = 2,
    NUMBER = 3,
    DELIM = 4,
    FUNCTION = 5,
};

struct TokenType{
    std::string vToken;
    TOKTYPE vType;
    int vPrecidence;
    
    TokenType(std::string aToken, TOKTYPE aType, int aPrecidence = 10){
        vToken = aToken;
        vType = aType;
        vPrecidence = aPrecidence;
    }
    
    TokenType(const TokenType& orig) : 
            vToken(orig.vToken), vType(orig.vType), vPrecidence(orig.vPrecidence){};
            
    TokenType(){

    }
    
};


typedef std::vector<TokenType> TokList;

void split_equation(const std::string &argInput, TokList &vTokenList, OperatorList *vOperators);
bool to_rpn(TokList &vRPN, TokList &vTokenList, OperatorList *vOperators);
std::string evaluate(TokList &vRPN, OperatorList *vOperators);

bool is_letter_char(char argInput);
bool is_delim_char(char argInput);
bool is_number_char(char argInput);


void print_toklist(TokList &aInput, std::string aDelim = "");
std::string toklist_to_string(TokList &aInput);
#endif	/* PARSEFUNCTIONS_H */

