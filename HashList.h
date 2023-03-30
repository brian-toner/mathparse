/* 
 * File:   HashList.h
 * Author: brian
 *
 * Created on June 10, 2014, 10:35 PM
 */

#ifndef HASHLIST_H
#define	HASHLIST_H

#include <iostream>
#include <vector>
#include <map>
#include "stringfuncts.h"
#include <limits>


template <class T>
class HashList {
public:
    
    
    
    typename std::map<std::string,T> vData;

    
    
    void insert(const char* aObjName, T aObj){
        std::string lObjName = aObjName;
        vData.insert(std::make_pair(lObjName, aObj ) );
        
    }
    
    void insert(std::string aObjName, T aObj){
        
        vData.insert(std::make_pair(aObjName, aObj ) );
        
    }
    
    T& operator[](std::string aObjName){
        //return vData[aObjName];
        vData.at(aObjName);
        //return vData[aObjName];
    };
    
    bool exists(std::string aObjName){
        bool lReturn = false;

        typename std::map<std::string,T>::iterator it = vData.find(aObjName);
        
        if(it != vData.end()){
            lReturn = true;
        }
        
        return lReturn;
    };
    

    typename std::map<std::string,T>::iterator find(std::string aObjName){
        size_t lIndex = std::string::npos;

        typename std::map<std::string,T>::iterator it = vData.find(aObjName);
        return it;

    };

    size_t max_length(){
        size_t lReturn = 0;


        for(typename std::map<std::string,T>::iterator it = vData.begin(); it != vData.end(); it++){
            
            
            if(lReturn < (*it).first.length() ){
                lReturn = (*it).first.length();
            }
            
        }

        return lReturn;
    };

    /**
     * Returns a reference to the variable if it is found.
     * @param aVarName
     * @return 
     */
    //T& at(std::string aObjName){
    //
    //    return vData[aObjName];
    //    
    //};

    size_t is_type(const char *argInput, int argPos, int argMaxCount){

        size_t locMaxSize = 0;
        size_t locOperatorSize = 0;
        

        locMaxSize = max_length();
        
        //std::cout << locMaxSize << std::endl;
        
        if(argMaxCount < locMaxSize){
            locMaxSize = argMaxCount;
        }

        std::string tempCompare = "";

        for(int i = 0; i < locMaxSize; i++){
            tempCompare += argInput[argPos+i];
            //std::cout << tempCompare << std::endl;
            
            if(exists(tempCompare)){
                locOperatorSize = i+1;
                break;
            }
        }

        return locOperatorSize;

    }    
    
    HashList(){};
    HashList(const HashList& orig) : vData(orig.vData){};
    virtual ~HashList(){};
private:

};

#endif	/* HASHLIST_H */

