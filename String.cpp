#include <iostream>
#include <cstring>

#include "memtrace.h" //Needs to be after the Standard Headers
#include "String.h"

#define _CRT_SECURE_NO_WARNINGS

/// Copy Constructor
String::String(String const& str) {
	//std::cout << "String ctor" << std::endl; //test
	len = str.len; //copying length
	pData = new char[len + 1]; // +1 for the '\0'
	strcpy(pData, str.pData); //copying data
}

/// Default Constructor from const char*
String::String(const char* str) {
	//std::cout << "String ctor" << std::endl; //test
	len = strlen(str); //copying length
	pData = new char[len + 1]; // +1 for the '\0'
	strcpy(pData, str); //copying data
}

/// Constructor from char
String::String(const char c) {
	//std::cout << "String ctor" << std::endl; //test
	len = 1; //giving length
	pData = new char[2]; // +1 for the '\0'
	pData[0] = c; //setting in character
	pData[1] = '\0'; //set '\0' in the end
}

/// Writes out String to outputstream
std::ostream& operator<<(std::ostream& os, String& str) {
	os << str.getStr();
	return os;
}

/// Assign the String's data to the String
String& String::operator=(const String& rhs_s) {
	if (this != &rhs_s) {
		delete[] pData;
		len = rhs_s.len;
		//copying length
		pData = new char[len + 1];
		//copying data
		strcpy(pData, rhs_s.pData);
	}
	return *this;
}

/// Adding 2 Strings together (returns constant)
String String::operator+(const String& rhs_s) const {
	String temp;
	temp.len = len + rhs_s.len;
	delete[] temp.pData;
	temp.pData = new char[temp.len + 1];
	strcpy(temp.pData, pData);
	strcat(temp.pData, rhs_s.pData);

	return temp;
}

/// Assign const char*'s data to the String
String& String::operator=(const char* rhs_s) {
	delete[] pData;
	len = strlen(rhs_s);
	//copying length
	pData = new char[len + 1];
	//copying data
	strcpy(pData, rhs_s);
	return *this;
}
 /// Input String from an inputstream
std::istream& operator>>(std::istream& is, String& s0) {
	unsigned char ch;
	s0 = String("");            
	std::ios_base::fmtflags fl = is.flags();
	is.setf(std::ios_base::skipws);			
	while (is >> ch) {
		is.unsetf(std::ios_base::skipws);
		/*if (isspace(ch)) {
			is.putback(ch);             
			break;
		}*/
		if (ch=='\n') {
			is.putback(ch);
			break;
		}
		else {
			s0 = s0 + ch;              
		}
	}
	is.setf(fl);						
	return is;
}
