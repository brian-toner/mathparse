
#include "stringfuncts.h"



bool is_number(std::string aValue){
    bool lNumber;
    bool lNegative;
    bool lDecimal;

    is_numb(aValue.c_str(),0,aValue.length(),lNumber,lNegative,lDecimal);
    
    return lNumber;

}

bool is_boolean(std::string aValue){
    bool lBool;
    is_bool(aValue.c_str(),0,aValue.length(),lBool);
    
    return lBool;
}

/**
 * Runs through a string of const char and determines if from the starting position
 *  we have a string encoded number or not.
 * @param argInput -Input data
 * @param argPos -Start position in the input
 * @param argMaxCount -Maximum length we want to search, usually the length
 *              of the input, but should not exceed the size of the input.
 * @return -Length of the string encoded number, 0 if not a number.
 */
int is_numb(const char *argInput, int argPos, int argMaxCount, bool &argNumber, bool &argNegative, bool &argDecimal){

    argNumber = false;
    argDecimal = false;
    argNegative = false;
    
    int locNumberSize = 0; //Starts by assuming that the number size is 0.
    bool locIsNegative = false; //Flag to determine if we have a negative number.
    bool locIsDecimal = false;  
    
    char locCompare; //Holds current char we are comparing against.
    int i = 0; //Our counting integer, our position in the input.
    bool locIsNumb = true; //Flag to determine if input is a number, starts
                           // by assuming that we are working with a number.
       

    //Essentially runs through the elements of input and proves if we have
    // a number or not.
    while(i < argMaxCount && locIsNumb){
        locIsNumb = false;
        locCompare = argInput[argPos+i];
        
        //Are we a negative number? Can only be negative at index 0.
        if(i == 0 && locCompare == '-'){
            locIsNegative = true;
            locNumberSize ++;
            locIsNumb = true;
        
        //Are we are in scientific notation.
        } else if(i != 0 && locCompare == 'e'){
            locNumberSize ++;
            locIsNumb = true;
            locIsDecimal = true;
            
        }else {
            
            if(locCompare >= 48 && locCompare <= 58){
                locNumberSize ++;
                locIsNumb = true;
            }
            
            if(locCompare == '.'){
                locNumberSize ++;
                locIsNumb = true;
                locIsDecimal = true;
            }

        }
        
        i++;
    }
    
    //Negative number can't just be a negative sign.
    if(locIsNegative && locNumberSize == 1){
        locNumberSize = 0;
    }
    
    if(locNumberSize > 0){
        argNumber = true;
        argNegative = locIsNegative;
        argDecimal = locIsDecimal;
    } else {
        argNumber = false;
        argDecimal = false;
        argNegative = false;
    }
    
    return locNumberSize;
    
}

int is_numb(const char *argInput, int argPos, int argMaxCount){
    
    bool argNumber, argNegative, argDecimal;
    return is_numb(argInput,argPos,argMaxCount,argNumber,argNegative,argDecimal);
    
}

int is_bool(const char *argInput, int argPos, int argMaxCount, bool &argBool){
    
    std::string locBool;
    argBool = false;
    
    for(int i = 0; i < 4; i++)
        locBool += argInput[argPos+i];
    
    if( locBool.compare("true") == 0  ){
        argBool = true;
        return 4;
    } 
    
    locBool.clear();
    
    for(int i = 0; i < 5; i++)
        locBool += argInput[argPos+i];
    
    if ( locBool.compare("false") == 0 ) {
        argBool = true;
        return 5;
    }
    
    return 0;
}

double string_to_double(std::string aValue){
    
    if(is_number(aValue))
        return string_to_type<double>(aValue);
        
    return std::numeric_limits<double>::quiet_NaN();
    
}

std::string remove_white_space(std::string aInput){
    std::string lReturn;
    
    for(std::string::iterator it = aInput.begin(); it != aInput.end(); it++){
        if((*it) != ' ' && (*it) != '\t' && (*it) != '\n'){
            lReturn.push_back((*it));
        }
    }
    
    return lReturn;
}

void print_stringlist(StringList &aInput){

    for(StringList::iterator it = aInput.begin(); it != aInput.end(); it++){
        std::cout << (*it) << " ";
    }
    std::cout << std::endl;
}