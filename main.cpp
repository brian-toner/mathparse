/* 
 * File:   main.cpp
 * Author: brian
 *
 * Created on June 10, 2014, 5:50 PM
 */

#include <cstdlib>
#include "argstring.h"
#include "stringfuncts.h"
#include "VariableList.h"
#include "Parser.h"
#include "FunctionList.h"
#include "OperatorList.h"
#include "parsefunctions.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    //cout << is_number("-") << endl;
    
    OperatorList lList;
    
    StringList lVals;
    
    //is_number_char('1');
    //is_letter_char('a');
    //is_delim_char('(');
    
    Function lFunc("f(x,y)=x^3+y+sin(x)", &lList);
    
    lVals.push_back("sin(x)");
    lVals.push_back("4");
    
    
    //if(isnan(lFunc.exec_fn(lVals,false))){
    //    std::cout << "NaN" << std::endl;
    //} else {
      //cout << lFunc.exec_fn(lVals,false) << endl;
    //}
    //print_toklist(lFunc.vVarTokenList);
    
    Parser lTest;
    lTest.insert_function("fun(x,y)=5*x+y");
    lTest.insert_function("blaw(x)=5*x");
    lTest.insert_variable("y","5");
    lTest.insert_variable("x","7");
    
    std::cout << "Limit: " << lTest.limit("100/(x^2+5)","x",1e100) << std::endl;
    std::cout << "Limit: " << lTest.limit("2.71^(x)","x",5) << std::endl;
    
    for(int i = 0; i < 10; i++){
        lTest.insert_variable("x",i);
        cout << "Answer: " << lTest.evaluate("blaw(x/100)*2") << std::endl;
        print_toklist(lTest.vVarTokenList);
        std::cout << std::endl;
    }
    
    //lTest.split_equation("x+5+x^2+y");
    //lTest.insert_variable("x","5");
    //lTest.assign_var_value();
    //print_toklist(lTest.vVarTokenList);
    
    //lTest.split_equation("fun(5,3)+5");
    
    //lTest.to_rpn();
    //print_toklist(lTest.vRPN, " ");
    
    //lTest.split_equation("((44.3+5e1)*3)*(7^2)!+sin(4)");
    //lTest.split_equation("4 + sin(4)");
    //lTest.split_equation("5e3+1");
    //lTest.split_equation("5 + ((1 + 2) * 4) − 3");
    //lTest.split_equation("5/4+3/2");
    
    //lTest.assign_variable("x = 4 + 3");
    //lTest.print_variables();
    
    //lTest.split_equation("x=4+3");
    //lTest.split_equation("cos(4)+sin(4)");
    //lTest.print_tokens();
    //lTest.to_rpn();
    //lTest.print_rpn();
    
    //cout << "Answer: " << lTest.evaluate();
    
    return 0;
}

