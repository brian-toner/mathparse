/* 
 * File:   stringfuncts.h
 * Author: brian
 *
 * Created on June 10, 2014, 7:25 PM
 */

#ifndef STRINGFUNCTS_H
#define	STRINGFUNCTS_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <limits>

typedef std::vector<std::string> StringList;
typedef std::vector<char> CharList;

 class BadConversion : public std::runtime_error {
 public:
   BadConversion(std::string const& s)
     : std::runtime_error(s)
     { }
 };

/**
 * Converts the string to the type of argInput
 * @param s -String we are converting from.
 * @return -Value of the converted string with type argInput
 */
template <class T>
inline T string_to_type(std::string const& s)
{
    std::istringstream i(s);
    T x;
    if (!(i >> x))
        throw BadConversion("convertString(\"" + s + "\")");
    return x;
}

/**
* Converts a wide range of data containers values into a string value (int, double, float etc)
* @param t Argument we are converting into a string.
* @return Returns a string value representing the input value.
*/
template <class T>
inline std::string to_string (const T& t){
    std::stringstream ss;
    ss << t;
    return ss.str();
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
int is_numb(const char *argInput, int argPos, int argMaxCount, bool &argNumber, bool &argNegative, bool &argDecimal);
int is_numb(const char *argInput, int argPos, int argMaxCount);
int is_bool(const char *argInput, int argPos, int argMaxCount, bool &argBool);

bool is_boolean(std::string aValue);
bool is_number(std::string aValue);

/**
 * Converts a string into a double.  If Value is not a number than NaN is returned.
 * @param aValue
 * @return 
 */
double string_to_double(std::string aValue);

/**
 * Removes spaces, tabs, and newline characters from strings.
 * @param aInput String we are removing white space from.
 * @return String similar to the original only with white space removed.
 */
std::string remove_white_space(std::string aInput);

void print_stringlist(StringList &aInput);


#endif	/* STRINGFUNCTS_H */

