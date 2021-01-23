#ifndef STRING_H
#define STRING_H

#include <iostream>
#include "memtrace.h"

/// Seperate String class, because STL are not allowed...
class String {
	/// Data Pointer
	char* pData;

	/// Length of the string
	size_t len;
public:
	/// Copy Constructor
	String(String const& str);

	/// Default Constructor from const char*
	String(const char* str = "");

	/// Constructor from char
	String(const char c);
	
	/// Destructor
	virtual ~String() { delete[] pData; }

	/// Return the content of the String
	const char* getStr() { return pData; }

	/// Return the length of the String
	const size_t getSize() { return len; }

	/// Assign the String's data to the String
	String& operator=(const String& rhs_s);

	/// Assign const char*'s data to the String
	String& operator=(const char* rhs_s);

	/// Adding String to the original
	String& operator+=(const String& rhs_s) {
		*this = *this + rhs_s;
		return *this;
	}

	/// Adding 2 Strings together (returns constant)
	String operator+(const String& rhs_s) const;

	/// Adding a char to the String (returns constant)
	String operator+(char rhs_c) const { return *this + String(rhs_c); }

};

///Writes out String to outputstream
std::ostream& operator<<(std::ostream& os, String& str);

///Reads in String from inputstream
std::istream& operator>>(std::istream& is, String& s0);

#endif //STRING_H