/* 
 * File:   OperatorList.h
 * Author: brian
 *
 * Created on June 10, 2014, 10:25 PM
 */

#ifndef OPERATORLIST_H
#define	OPERATORLIST_H

#include <iostream>
#include <vector>
#include <map>
#include "stringfuncts.h"
#include <limits>
#include "HashList.h"
#include "operators.h"

typedef double(*ptFunction)(double*);

struct Operator{
    std::string varOp;
    int varArguments;
    int varPrecident;
    bool varLeftAssoc;
    bool varIsFunction;
    ptFunction varPtFunction;
    
    Operator(){};
    
    Operator(std::string argOp, int argArgNumb, int argPrecident, bool argLeftAssoc, bool argIsFunction, ptFunction argPtFunction){

        varOp = argOp;
        varArguments = argArgNumb;
        varPrecident = argPrecident;
        varLeftAssoc = argLeftAssoc;
        varIsFunction = argIsFunction;
        varPtFunction = argPtFunction;

    }
    
    Operator(const Operator& orig) : varOp(orig.varOp), 
                                    varArguments(orig.varArguments),
                                    varPrecident(orig.varPrecident), 
                                    varLeftAssoc(orig.varLeftAssoc),
                                    varIsFunction(orig.varIsFunction),
                                    varPtFunction(orig.varPtFunction){
        
    }
};

typedef std::vector<Operator> OpList;
typedef std::map<std::string,Operator> OpMap;

class OperatorList : public HashList<Operator>{
public:
    
    void print_operators(){
        std::cout << "Printing Operators" << std::endl;
        
        for(OpMap::iterator it = vData.begin(); it != vData.end(); it++){
            std::cout << (*it).first << std::endl;
        }
        
        
    }
    
    void construct_default_operators(){
        
        //std::cout << "test1" << std::endl;
        //vOperators["*"];// = Operator("*",2,4,1,0,&op_multiply);
        vData.insert(std::make_pair("*",     Operator("*",    2,2 ,1,0,&op_multiply) ) );
        vData.insert(std::make_pair("/",     Operator("/",    2,2 ,1,0,&op_divide) ) );
        vData.insert(std::make_pair("%",     Operator("%",    2,3 ,1,0,&op_mod) ) );
        vData.insert(std::make_pair("+",     Operator("+",    2,3 ,1,0,&op_add) ) );
        vData.insert(std::make_pair("-",     Operator("-",    2,3 ,1,0,&op_subtract) ) );
        vData.insert(std::make_pair("−",     Operator("−",    2,3 ,1,0,&op_subtract) ) );
        vData.insert(std::make_pair("^",     Operator("^",    2,1 ,0,0,&op_power) ) );
        vData.insert(std::make_pair("sin",   Operator("sin",  1,0,0,1,&fn_sin) ) );
        vData.insert(std::make_pair("cos",   Operator("cos",  1,0,0,1,&fn_cos) ) );
        vData.insert(std::make_pair("tan",   Operator("tan",  1,0,0,1,&fn_tan) ) );
        vData.insert(std::make_pair("sum",   Operator("sum",  2,0,0,1,&op_add) ) );
        vData.insert(std::make_pair("qtnt",  Operator("qtnt", 2,0,0,1,&fn_qtnt) ) );
        vData.insert(std::make_pair("rmdr",  Operator("rmdr", 2,0,0,1,&fn_rmdr) ) );
        
        
        vData.insert(std::make_pair("!",     Operator("!",    1,1 ,1,0,&op_factorial) ) );
        
        //print_operators();
        //vData.insert(std::make_pair("=",     Operator("=",    1,0 ,1,0,&op_factorial) ) );
        //vOperators.vData.insert(std::make_pair("(",     Operator("(",    1,99 ,1,0,&op_factorial) ) );
    }
    
    
    
    double exec_op(std::string aOperator, StringList aValues){
        
        Operator lOperator = vData[aOperator];
        double* lDouble = new double(lOperator.varArguments);
        
        for(StringList::reverse_iterator it = aValues.rbegin(); it != aValues.rend(); it++){
            size_t i = (it - aValues.rbegin());
            lDouble[i] = string_to_double((*it));
        }
        
        double lResult = lOperator.varPtFunction(lDouble);
        
        delete[] lDouble;
        
        return lResult;
    }
    
    OperatorList();
    OperatorList(const OperatorList& orig);
    virtual ~OperatorList();
private:

};


#endif	/* OPERATORLIST_H */

