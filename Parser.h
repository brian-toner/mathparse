/* 
 * File:   Parser.h
 * Author: brian
 *
 * Created on June 10, 2014, 5:51 PM
 */

#ifndef PARSER_H
#define	PARSER_H

#include "FunctionList.h"
#include "OperatorList.h"
#include "VariableList.h"
#include "stringfuncts.h"
#include "operators.h"
#include "parsefunctions.h"

class Parser {
public:
    
    FunctionList vFunctions;
    OperatorList vOperators;
    //VariableList vVariables;
    std::map<std::string,std::string> vVariables;
    std::vector<char> vNumbers;
    std::vector<char> vLetters;
    std::vector<char> vDelims;
    TokList vRPN;
    StringList vTokens;
    
    TokList vTokenList;
    TokList vVarTokenList;
    
    Parser();
    Parser(const Parser& orig);
    virtual ~Parser();
    
    void insert_variable(std::string aVarName, double aValue){
        insert_variable(aVarName, to_string(aValue));
    }
    
    void insert_variable(std::string aVarName, std::string aValue){
        
        if(vVariables.find(aVarName) == vVariables.end() ){
            vVariables.insert(std::make_pair(aVarName, aValue) );
        } else {
            vVariables[aVarName] = aValue;
        }
    }
    
    
    
    void assign_var_value(){
        vVarTokenList = vTokenList;
        
        for(TokList::iterator itv = vVarTokenList.begin(); itv != vVarTokenList.end(); itv++){

            if( (*itv).vType == LETTER ){

                if(vVariables.find((*itv).vToken) != vVariables.end() ){
                
                    (*itv).vToken = vVariables[(*itv).vToken];
                    (*itv).vType = NUMBER;
                    
                }
            }
        }

    }
    
    void insert_function(std::string aFunction){
        vFunctions.insert_function(aFunction);
    }
    
    void construct_numbers(){
        
        for(char i = 48; i < 58; i++){
            vNumbers.push_back(i);
        }

        vNumbers.push_back('.');
    }
    
    void construct_delim(){
        
        vDelims.push_back('(');
        vDelims.push_back(')');
        vDelims.push_back(',');
    }
    
    void construct_characters(){
        
        for(char i = 65; i < 91; i++){
            vLetters.push_back(i);
        }

        for(char i = 97; i < 123; i++){
            vLetters.push_back(i);
        }

        for(char i = 48; i < 58; i++){
            vLetters.push_back(i);
        }    

        vLetters.push_back('_');
        
    }
    
    /**
     * Designed for if we deviate away from the standard 8 bit character.
     * @param argInput
     * @return 
     */
    bool is_letter_char(char argInput){
        for(int i = 0; i < vLetters.size(); i++){
            if(argInput == vLetters.at(i)){
                return true;
            }
        }
    }

    bool is_number_char(char argInput){

        for(int i = 0; i < vNumbers.size(); i++){
            if(argInput == vNumbers.at(i)){
                return true;
            }
        }

        return false;

    }    
    
    bool is_delim_char(char argInput){
        
        for(int i = 0; i < vDelims.size(); i++){
            if(argInput == vDelims.at(i)){
                return true;
            }
        }

        return false;
    }
    
    void print_tokens(bool aPrintTypes = false){
        
        //for(StringList::iterator it = vTokens.begin(); it != vTokens.end(); it++){
        //    std::cout << (*it) << std::endl;
        //}
        for(TokList::iterator it = vTokenList.begin(); it != vTokenList.end(); it++){
            std::cout << (*it).vToken << " ";
        }
        std::cout << std::endl;
        
        if(aPrintTypes)
            for(TokList::iterator it = vTokenList.begin(); it != vTokenList.end(); it++){
                std::cout << (*it).vToken << " : " << (*it).vType << std::endl;
            }
        
        
    }
    
    void print_rpn(){
        
        for(TokList::iterator it = vRPN.begin(); it!= vRPN.end(); it++){
            std::cout << (*it).vToken << " ";
        }
        std::cout << std::endl;
    }
    
    void assign_variable(const std::string &argInput){
        
        
        std::string lInputClean = remove_white_space(argInput);
        size_t lAssignOp = lInputClean.find('=',0);
        std::string lVarName = lInputClean.substr(0,lAssignOp);
        std::string lVarValue = lInputClean.substr(lAssignOp+1,lInputClean.length()-lAssignOp);
        
        //vVariables.vData.insert(std::make_pair(lVarName, Variable(lVarName,lVarValue) ) );
        
    }
    
    void print_variables(){
        
        //vVariables.print_vars();
        
    }
    
    void split_equation(const std::string &argInput){
        vTokens.clear();
        vTokenList.clear();
        
        int i = 0;
        int locLastI = 0;
        int locCount = 0;


        while(i < argInput.size()){

            if(argInput[i] == ' '){
                i++;
                continue;
            }
            
            if(locLastI != i){
                locLastI = i;
            } else {
                locCount ++;
            }

            if(locCount > 2){
                locCount = 0;
                i++;
            }


            bool tempIsNegative = false;
            int tempOpSize = vOperators.is_type(argInput.c_str(),i, argInput.size()-i);
            
            
            if(tempOpSize > 0){
                std::string tempString = argInput.substr(i, tempOpSize);
                //std::cout << "Operator: " << tempString << std::endl;


                if(tempString.compare("-") == 0){
                    if(vTokens.size() == 0){
                        tempIsNegative = true;
                    }

                    if(vTokens.size() >= 1){

                        if( vOperators.exists( vTokens.at(i-1) ) ){
                            tempIsNegative = true;
                        }

                    }

                }

                if(!tempIsNegative){
  
                    this->vTokens.push_back(tempString);
                    vTokenList.push_back(TokenType(tempString,OPERATOR));
                    i += tempOpSize;
                } else {

                    //int tempChainSize = is_negative_chain(argInput->c_str(),i, argInput->size()-i);

                    //if(tempChainSize > 1){
                    //    for(int j = 0; j < tempChainSize; j++){
                    //        this->vTokens.push_back("-1");
                    //        this->vTokens.push_back("*");
                    //    }

                    //    i += tempChainSize + 1;
                    //}

                }

                continue;
            }

            int tempFnSize = vFunctions.is_type(argInput.c_str(),i, argInput.size()-i);
            if(tempFnSize > 0){
                std::string tempString = argInput.substr(i, tempFnSize);

                if(tempString.compare("-") == 0){
                    if(vTokens.size() == 0){
                        tempIsNegative = true;
                    }

                    if(vTokens.size() >= 1){

                        if( vFunctions.exists( vTokens.at(i-1) ) ){
                            tempIsNegative = true;
                        }

                    }

                }

                if(!tempIsNegative){
  
                    this->vTokens.push_back(tempString);
                    vTokenList.push_back(TokenType(tempString,FUNCTION));
                    i += tempFnSize;
                } else {

                    //int tempChainSize = is_negative_chain(argInput->c_str(),i, argInput->size()-i);

                    //if(tempChainSize > 1){
                    //    for(int j = 0; j < tempChainSize; j++){
                    //        this->vTokens.push_back("-1");
                    //        this->vTokens.push_back("*");
                    //    }

                    //    i += tempChainSize + 1;
                    //}

                }

                continue;
            }
            
            //int tempFuncSize = vFunctions.is_type(argInput.c_str(),i, argInput.size()-i);
            //int tempFuncSize = is_delim_char(i);
            

            if(is_delim_char(argInput.c_str()[i])){
                vTokenList.push_back(TokenType(argInput.substr(i,1),DELIM));
                vTokens.push_back(argInput.substr(i,1));
                i++;
                continue;
            }
            
            
            //if(tempFuncSize > 0){
            //    std::string tempString = argInput.substr(i,tempFuncSize);
            //    vTokens.push_back(tempString);
            //    i += tempFuncSize;
            //
            //}        

            int tempNumbSize = is_numb(argInput.c_str(),i, argInput.size()-i);
            if(tempNumbSize > 0){
                std::string tempString = argInput.substr(i,tempNumbSize);
                vTokenList.push_back(TokenType(tempString,NUMBER));
                vTokens.push_back(tempString);
                i += tempNumbSize;
                continue;
            }    

            if(is_letter_char(argInput.c_str()[i])){
                int tempCount = 1;
                while (is_letter_char(argInput.c_str()[tempCount+i])){
                    tempCount ++;
                }

                
                std::string tempString = argInput.substr(i,tempCount);
                vTokenList.push_back(TokenType(tempString,LETTER));
                vTokens.push_back(tempString);
                i += tempCount;
                continue;
            }

            if(argInput.c_str()[i] == ' ' || argInput.c_str()[i] == ','){
                i++;
            }

        }



    }   
    
    bool to_rpn(){
        TokList locOutput;
        TokList locStack;

        int locStackSize = 0;

        for(TokList::iterator it = vVarTokenList.begin(); it != vVarTokenList.end(); it++){
            
            if((*it).vType == NUMBER || (*it).vType == LETTER){
                locOutput.push_back((*it));
            }
            
            if( (*it).vToken[0] == '(' ){
                locStack.push_back((*it));
            }
            
            if( (*it).vToken[0] == ')' ){

                while(locStack.back().vToken[0] != '('){
                    locOutput.push_back(locStack.back());
                    locStack.pop_back();
                }

                locStack.pop_back();
                
                if(locStack.size() > 0){
                    if(locStack.back().vType == FUNCTION){
                        locOutput.push_back(locStack.back());
                        locStack.pop_back();
                    }
                }
                
            }
            
            if((*it).vType == OPERATOR){
                
                Operator tempOp = vOperators[(*it).vToken];
                
                if(locStack.size() > 0){
                    
                    if(locStack.back().vToken[0] != '('){
                        Operator compOp = vOperators[locStack.back().vToken]; 

                        if(compOp.varPrecident <= tempOp.varPrecident){
                             locOutput.push_back(locStack.back());
                             locStack.pop_back();
                             locStack.push_back((*it));
                        } else {
                             locStack.push_back((*it));
                        }
                    } else {
                        locStack.push_back((*it));
                    }
                    
                } else {
                    locStack.push_back((*it));
                }
                
            }
            
            if((*it).vType == FUNCTION){
                
                locStack.push_back((*it));
                
                
            }
            
            
        }

        locStackSize = locStack.size();

        for(int i = 0; i < locStackSize; i++){
            locOutput.push_back(locStack.back());
            locStack.pop_back();

        }


        //for(int i = 0; i < locOutput.size(); i++){
        //    std::cout << locOutput.at(i).vToken << " ";
        //}
       // std::cout << std::endl;


        
        
        //vRPN.clear();
        vRPN = locOutput;

        //for(TokList::iterator it = locOutput.begin(); it != locOutput.end(); it++){
        //    vRPN.push_back((*it).vToken );
        //}

    }
    
    double evaluate_d(std::string aEquation){

        return string_to_double(evaluate(aEquation));

    }
    
    std::string evaluate(std::string aEquation){

        split_equation(aEquation);
        assign_var_value();
        to_rpn();
        return evaluate();

    }
    
    double sum_eqnation(std::string aEquation, std::string aVariable, int aStart, int aEnd){
        
        double aEval;
        
        for(int i = aStart; i < aEnd+1; i++){
            insert_variable(aVariable, i);
            split_equation(aEquation);
            assign_var_value();
            to_rpn();
            aEval += evaluate_d();
        }
        
        return aEval;
    }
    
    double prod_eqnation(std::string aEquation, std::string aVariable, int aStart, int aEnd){
        
        double aEval;
        
        for(int i = aStart; i < aEnd+1; i++){
            insert_variable(aVariable, i);
            evaluate(aEquation);
            aEval *= evaluate_d();
        }
        
        return aEval;
    }
    
    double limit_lhs(std::string aEquation, std::string aVariable, double aValue, double aDelta = 1e-300){
        
        double lTestVal = aValue - aDelta;
        insert_variable(aVariable, lTestVal);
        return evaluate_d(aEquation);
        
        
    }
    
    double limit_rhs(std::string aEquation, std::string aVariable, double aValue, double aDelta = 1e-300){
        
        double lTestVal = aValue + aDelta;
        insert_variable(aVariable, lTestVal);
        return evaluate_d(aEquation);
        
        
    }
    
    std::string limit(std::string aEquation, std::string aVariable, double aValue){
        
        insert_variable(aVariable, aVariable);
        double lReturn = evaluate_d(aEquation);
        if(isnan(lReturn)){
            
            double lLimitLHS = limit_lhs(aEquation,aVariable,aValue,1e-300);
            double lLimitRHS1 = limit_rhs(aEquation,aVariable,aValue,1e-150);
            double lLimitRHS2 = limit_rhs(aEquation,aVariable,aValue,1e-300);
            
            //std::cout << fabs(lLimitLHS - lLimitRHS1) << " : " << fabs(lLimitLHS - lLimitRHS2) << std::endl;
            //std::cout << lLimitLHS << " : " << lLimitRHS1 << " : " << lLimitRHS2 << std::endl;
            
            if(fabs(lLimitLHS - lLimitRHS1) >= fabs(lLimitLHS - lLimitRHS2) ){
                return to_string((lLimitLHS + lLimitRHS2)/2);
            } else {
                return "DNE";
            }
            
            
        }
         
        return to_string(lReturn);
        
        
    }
    
    double evaluate_d(){
        return string_to_double(evaluate());
    }
    
    std::string evaluate(){
    
        std::vector<std::string> locOutput;
        std::vector<std::string> locStack;    
        //varVariables.clear();

        
        for(TokList::iterator it = vRPN.begin(); it != vRPN.end(); it++){

            if ((*it).vType == FUNCTION) {

                Function tempFn = vFunctions[(*it).vToken];

                for(int i = 0; i < tempFn.varArguments; i++){
                    locStack.push_back(locOutput.back());
                    locOutput.pop_back();
                }

                double lValue = vFunctions.exec_fn((*it).vToken,locStack);

                locOutput.push_back(to_string(lValue));
                locStack.clear();
                
            } else if ((*it).vType == OPERATOR) {
                
                
                if((*it).vToken[0] == '='){
                    
                } else {
                
                    Operator tempOp = vOperators[(*it).vToken];
                    
                    for(int i = 0; i < tempOp.varArguments; i++){
                        locStack.push_back(locOutput.back());
                        locOutput.pop_back();
                    }

                    double lValue = vOperators.exec_op((*it).vToken,locStack);
                    locOutput.push_back(to_string(lValue));
                    locStack.clear();
                
                }
            } else {
                locOutput.push_back((*it).vToken);

            }

        }

        //for(int i = 0; i < locOutput.size(); i ++){
        //    std::cout << locOutput.at(i) << " ";
        //}
        //std::cout << std::endl;

        return locOutput.front();
    }
    
private:

};

#endif	/* PARSER_H */

