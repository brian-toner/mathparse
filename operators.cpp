
#include "operators.h"

double op(std::string arg1, std::string arg2, bool (*op_func)(double, double)){
        
    double locN1 = string_to_double(arg1);
    double locN2 = string_to_double(arg2);
    
    return (*op_func)(locN1,locN2);
}

bool comp(std::string arg1, std::string arg2, bool (*comp_func)(double, double)){
    double locN1 = string_to_double(arg1);
    double locN2 = string_to_double(arg2);     

    return comp_func(locN1, locN2);
    
}

bool comp_eq(double argT, double argU){
    return argT == argU;
}

bool comp_geq(double argT, double argU){
    return argT >= argU;
}

bool comp_leq(double argT, double argU){
    return argT <= argU;
}    

bool comp_gt(double argT, double argU){
    return argT > argU;
}   

bool comp_lt(double argT, double argU){
    return argT < argU;
}   

double op_add(double *argVars){
    return argVars[0] + argVars[1];
}

double op_subtract(double *argVars){
    return argVars[0] - argVars[1];
}

double op_divide(double *argVars){
    return argVars[0] / argVars[1];
}

double op_multiply(double *argVars){
    return argVars[0] * argVars[1];
}

double op_mod(double *argVars){
    return (long)argVars[0] % (long)argVars[1];
}

double op_power(double *argVars){
    return pow(argVars[0],argVars[1]);
}

double op_factorial(double *argVars){
    double locReturn = 1;
    
    for(long i = 0; i < (long)argVars[0]; i++){
        locReturn *= (i+1);
    }
    
    return locReturn;
}

double fn_sin(double *argVars){
    return sin(argVars[0]);
}

double fn_cos(double *argVars){
    return cos(argVars[0]);
}

double fn_tan(double *argVars){
    return tan(argVars[0]);
}

double fn_qtnt(double *argVars){
    return (long)argVars[0]/(long)argVars[1];
}

double fn_rmdr(double *argVars){
    double locQuotient = fn_qtnt(argVars);
    return argVars[0] - (locQuotient*argVars[1]);
}