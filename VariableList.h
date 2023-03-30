/* 
 * File:   VariableList.h
 * Author: brian
 *
 * Created on June 10, 2014, 10:28 PM
 */

#ifndef VARIABLELIST_H
#define	VARIABLELIST_H

#include <iostream>
#include <vector>
#include <map>
#include "stringfuncts.h"
#include <limits>
#include "HashList.h"

class Variable {
    
public:
    std::string vVarName;
    std::string vValue;
    
    
    Variable& operator =(std::string aValue){
        vValue = aValue;
        return *this;
    }
    
    Variable& operator =(double aValue){
        vValue = to_string(aValue);
        return *this;
    }
    
    operator double(){
        
        if(is_number(vValue))
            return string_to_type<double>(vValue);
        
        return std::numeric_limits<double>::quiet_NaN();
    }
    
    Variable(){}
    Variable(std::string aVarName){
        vVarName = aVarName;
    }
    
    Variable(std::string aVarName, std::string aValue){
        vVarName = aVarName;
        vValue = aValue;
    }
    
    Variable(const Variable& orig) : vValue(orig.vValue), vVarName(orig.vVarName) {
        
    }
    
};

typedef std::map<std::string,Variable> VarMap;

class VariableList : public HashList<Variable>{
public:
    
    
    void print_vars(){
        
        for(VarMap::iterator it = vData.begin(); it != vData.end(); it++){
            
            std::cout << (*it).second.vVarName << " : " << (*it).second.vValue << std::endl;
            
        }
        
    }
    
    VariableList();
    VariableList(const VariableList& orig);
    virtual ~VariableList();
    
};


#endif	/* VARIABLELIST_H */

