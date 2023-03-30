
#include "parsefunctions.h"

void split_equation(const std::string &argInput, TokList &vTokenList, OperatorList *vOperators){
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
            int tempOpSize = vOperators->is_type(argInput.c_str(),i, argInput.size()-i);
            

            if(tempOpSize > 0){
                std::string tempString = argInput.substr(i, tempOpSize);
                //std::cout << "Operator: " << tempString << std::endl;


                if(tempString.compare("-") == 0){
                    if(vTokenList.size() == 0){
                        tempIsNegative = true;
                    }

                    if(vTokenList.size() >= 1){

                        if( vOperators->exists( vTokenList.at(i-1).vToken ) ){
                            tempIsNegative = true;
                        }

                    }

                }

                if(!tempIsNegative){

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

            //int tempFuncSize = vFunctions.is_type(argInput.c_str(),i, argInput.size()-i);
            //int tempFuncSize = is_delim_char(i);
            

            if(is_delim_char(argInput.c_str()[i])){

                vTokenList.push_back(TokenType(argInput.substr(i,1),DELIM));
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
                i += tempCount;
                continue;
            }

            if(argInput.c_str()[i] == ' ' || argInput.c_str()[i] == ','){
                i++;
            }

        }
    }   


    bool to_rpn(TokList &vRPN, TokList &vTokenList, OperatorList *vOperators){
        TokList locOutput;
        TokList locStack;

        int locStackSize = 0;

        for(TokList::iterator it = vTokenList.begin(); it != vTokenList.end(); it++){
            
            
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
                
            }
            
            if((*it).vType == OPERATOR){
                
                Operator tempOp = (*vOperators)[(*it).vToken];
                
                
                
                if(locStack.size() > 0){
                    
                    if(locStack.back().vToken[0] != '('){
                        Operator compOp = (*vOperators)[locStack.back().vToken]; 

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
            

        }

        locStackSize = locStack.size();

        for(int i = 0; i < locStackSize; i++){
            locOutput.push_back(locStack.back());
            locStack.pop_back();

        }

        vRPN = locOutput;
        
    }

    std::string evaluate(TokList &vRPN, OperatorList *vOperators){
    
        std::vector<std::string> locOutput;
        std::vector<std::string> locStack;    

        for(TokList::iterator it = vRPN.begin(); it != vRPN.end(); it++){

            if((*it).vType != OPERATOR){
                locOutput.push_back((*it).vToken);

            } else {
                
                
                if((*it).vToken[0] == '='){
                    
                } else {
                
                    Operator tempOp = (*vOperators)[(*it).vToken];
                    
                    for(int i = 0; i < tempOp.varArguments; i++){
                        locStack.push_back(locOutput.back());
                        locOutput.pop_back();
                    }

                    double lValue = (*vOperators).exec_op((*it).vToken,locStack);
                    locOutput.push_back(to_string(lValue));
                    locStack.clear();
                
                }
            }
        }

        return locOutput.front();
    }    
    
    bool is_letter_char(char argInput, CharList vLetters){
        for(int i = 0; i < vLetters.size(); i++){
            if(argInput == vLetters.at(i)){
                return true;
            }
        }
    }

    bool is_number_char(char argInput, CharList vNumbers){

        for(int i = 0; i < vNumbers.size(); i++){
            if(argInput == vNumbers.at(i)){
                return true;
            }
        }

        return false;

    }    
    
    bool is_delim_char(char argInput, CharList vDelims){
        
        for(int i = 0; i < vDelims.size(); i++){
            if(argInput == vDelims.at(i)){
                return true;
            }
        }

        return false;
    }
    
    bool is_number_char(char argInput){

        if( (argInput >= 48 & argInput < 58) | argInput == '.'){
            return true;
        }
        
        return false;
    }
    
    bool is_delim_char(char argInput){
        
        if(argInput == '(' | argInput == ')'){
            return true;
        }
        
        return false;
    }
    
    bool is_letter_char(char argInput){
        
        if( (argInput >= 65 & argInput < 91) ){
            return true;
        }
        
        if( (argInput >= 97 & argInput < 123) ){
            return true;
        }
        
        if( (argInput >= 48 & argInput < 58) ){
            return true;
        }
        
        if( (argInput == '_') ){
            return true;
        }
    }
    
    
    void print_toklist(TokList &aInput, std::string aDelim){
        
        for(TokList::iterator it = aInput.begin(); it != aInput.end(); it++){
            std::cout << (*it).vToken << aDelim;
        }
        std::cout << std::endl;
    }
    
    std::string toklist_to_string(TokList &aInput){
        std::string lReturn = "";
        
        for(TokList::iterator it = aInput.begin(); it != aInput.end(); it++){
            lReturn = lReturn + (*it).vToken;
        }
        
        return lReturn;
    }