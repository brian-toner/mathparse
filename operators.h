/* 
 * File:   operators.h
 * Author: brian
 *
 * Created on June 11, 2014, 7:49 AM
 */

#ifndef OPERATORS_H
#define	OPERATORS_H

#include "stringfuncts.h"
#include <math.h>

double op(std::string arg1, std::string arg2, bool (*op_func)(double, double));
bool comp(std::string arg1, std::string arg2, bool (*comp_func)(double, double));
bool comp_eq(double argT, double argU);
bool comp_geq(double argT, double argU);
bool comp_leq(double argT, double argU);
bool comp_gt(double argT, double argU);
bool comp_lt(double argT, double argU);

double op_add(double *argVars);
double op_subtract(double *argVars);
double op_divide(double *argVars);
double op_multiply(double *argVars);
double op_mod(double *argVars);
double op_power(double *argVars);
double op_factorial(double *argVars);
double fn_sin(double *argVars);
double fn_cos(double *argVars);
double fn_tan(double *argVars);
double fn_qtnt(double *argVars);
double fn_rmdr(double *argVars);

#endif	/* OPERATORS_H */

