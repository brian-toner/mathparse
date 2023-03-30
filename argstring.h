/* 
 * File:   argstring.h
 * Author: brian
 *
 * Created on June 10, 2014, 6:05 PM
 */

#ifndef ARGSTRING_H
#define	ARGSTRING_H

#include <iostream>
#include <vector>
#include <map>
#include "stringfuncts.h"
#include <limits>






class argstring {
public:
    
    std::string vData;
    
    argstring& replace_value(std::string aArgument, std::string aValue){
        
        
        size_t lPos = vData.find(aArgument);
        
        while(lPos != std::string::npos){
            vData.replace(lPos,aArgument.length(),aValue);
            lPos = vData.find(aArgument);
        }
        
        return *this;
    }
    
    argstring();
    argstring(const char* aCString){
        vData = aCString;
        //std::string(aCString);
        
    }
    
    //argstring(const argstring& orig);
    //virtual ~argstring();
private:

};

#endif	/* ARGSTRING_H */

