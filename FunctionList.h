/* 
 * File:   FunctionList.h
 * Author: brian
 *
 * Created on June 10, 2014, 10:27 PM
 */

#ifndef FUNCTIONLIST_H
#define	FUNCTIONLIST_H

#include <iostream>
#include <vector>
#include <map>
#include "stringfuncts.h"
#include <limits>
#include "OperatorList.h"
#include "parsefunctions.h"


struct Function{
    std::string vName;
    std::string varFunc;
    int varArguments;
    TokList vRPN;
    TokList vTokenList;
    TokList vVarTokenList;
    StringList vVariables;
    
    OperatorList* vOperators;
    
    
    void insert_function(std::string aFunc){

        TokList lFuncDecl;
        std::string lFunc;
        
        lFunc = remove_white_space(aFunc);
        varFunc = lFunc;

        size_t lAssignOp = lFunc.find('=',0);
        std::string lLeftHandSide = lFunc.substr(0,lAssignOp);
        std::string lRightHandSide = lFunc.substr(lAssignOp+1,lFunc.length()-lAssignOp);
        //std::cout << lLeftHandSide << " : " << lRightHandSide << std::endl;

        split_equation(lLeftHandSide, lFuncDecl, vOperators);
        split_equation(lRightHandSide, vTokenList, vOperators);

        varArguments = lFuncDecl.size() - 3;
        vName = lFuncDecl.at(0).vToken;

        for(int i = 0; i < varArguments; i++){
            vVariables.push_back(lFuncDecl.at(2+i).vToken);
        }

        //print_toklist(lFuncDecl);
        //print_toklist(vTokenList);
        //print_stringlist(vVariables);
        
    }
    
    void insert_variable(std::string aVarName){
        vVariables.push_back(aVarName);
    }
    
    void assign_var_value_fwd(StringList aValues){
        
        vVarTokenList = vTokenList;

        for(StringList::iterator it = vVariables.begin(); it != vVariables.end(); it++){
            size_t i = (it - vVariables.begin());

            for(TokList::iterator itv = vVarTokenList.begin(); itv != vVarTokenList.end(); itv++){
 
                if( (*itv).vType == LETTER ){
                    
                    if( (*itv).vToken.compare((*it)) == 0){
                        (*itv).vToken = aValues.at(i);
                    } 
                }
            }
        }
    }
    
    void assign_var_value_rev(StringList aValues){
        
        vVarTokenList = vTokenList;

        for(StringList::reverse_iterator it = vVariables.rbegin(); it != vVariables.rend(); it++){
            size_t i = (it - vVariables.rbegin());

            for(TokList::iterator itv = vVarTokenList.begin(); itv != vVarTokenList.end(); itv++){
 
                if( (*itv).vType == LETTER ){
                    
                    if( (*itv).vToken.compare((*it)) == 0){
                        (*itv).vToken = aValues.at(i);
                    } 
                }
            }
        }
    }
    
    
    
    std::string exec_fn(StringList aValues, bool aReverse = true){
        
        if(aReverse){
            assign_var_value_rev(aValues);
        } else {
            assign_var_value_fwd(aValues);
        }

        std::string lFilledEqn = toklist_to_string(vVarTokenList);

        lFilledEqn = remove_white_space(lFilledEqn);

        TokList lFilledTok;

        split_equation(lFilledEqn, lFilledTok, vOperators);

        vVarTokenList = lFilledTok;

        to_rpn(vRPN,lFilledTok,vOperators);

        std::string lOutput = evaluate(vRPN,vOperators);
        double lReturn = string_to_double(lOutput);

        if(isnan(lReturn) ){
            return toklist_to_string(vVarTokenList);
        } else {
            return lOutput;
        }
        
    }
    
    Function(){};
    
    Function(std::string aFunc){
        insert_function(aFunc);
    };
    
    Function(std::string argFunc, OperatorList* aOperators){
        vOperators = aOperators;
        insert_function(argFunc);
    }
    
    Function(std::string argFunc, int argArgNumb){

        varFunc = argFunc;
        varArguments = argArgNumb;
        
    }
    
    Function(const Function& orig) : vName(orig.vName),
                                        varFunc(orig.varFunc),
                                        varArguments(orig.varArguments),
                                        vRPN(orig.vRPN),
                                        vTokenList(orig.vTokenList),
                                        vVarTokenList(orig.vVarTokenList),
                                        vVariables(orig.vVariables),
                                        vOperators(orig.vOperators){}
    
    
    
    
};

class FunctionList : public HashList<Function>{
public:

    OperatorList* vOperators;
    TokList vRPN;
    TokList vTokenList;
    
    double exec_fn(std::string aFunction, StringList aValues){
        
        Function lFunction = vData[aFunction];

        std::string lResult = lFunction.exec_fn(aValues);
        
        return string_to_double(lResult);
    }
    
    void insert_function(std::string aFunction){
        
        Function lFunction(aFunction,vOperators);
        vData.insert(std::make_pair(lFunction.vName, lFunction) );
        
    }
    
    
    FunctionList();
    FunctionList(const FunctionList& orig);
    virtual ~FunctionList();
private:

};

#endif	/* FUNCTIONLIST_H */

