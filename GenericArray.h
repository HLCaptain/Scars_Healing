#ifndef GENERICARRAY_H
#define	GENERICARRAY_H

#include "memtrace.h"

/// This GenericArray can store any type of things dynamically. Maybe I will do a static version as well. Or just implement it with a bool. Time will tell...
template<class C>
class GenericArray {
	C* Array;
	size_t Size;
public:
	/// Default Constructor
	GenericArray<C>() : /*Array(new C[2]),*/ Size(0) { Array = new C[Size]; }

	/// Copy Constructor
	GenericArray<C>(const GenericArray<C>& GA) : Array(new C[GA.Size]), Size(GA.Size) {
		for (size_t i = 0; i < Size; i++) {
			Array[i] = GA.Array[i];
		}
	}

	/// Destructor
	virtual ~GenericArray() {
		delete[] Array;
	}

	/// Adding an Element to the Array
	void add(const C& Element) {
		C* NewArray = new C[++Size]; // size increased
		for (size_t i = 0; i < Size - 1; i++) { // copying data
			NewArray[i] = Array[i];
		}
		NewArray[Size-1] = Element; // new data added
		delete[] Array;
		Array = NewArray;
	}

	/// Removes an Element from the Array
	void remove(const size_t& Index) {
		if (Size < 2) {
			Size = 0;
			delete[] Array;
			Array = new C[1];
		}
		else {
			C* NewArray = new C[Size - 1];
			for (size_t i = 0; i < Index; i++) {
				NewArray[i] = Array[i];
			}
			for (size_t i = Index + 1; i < Size; i++) {
				NewArray[i - 1] = Array[i];
			}
			Size--;
			delete[] Array;
			Array = NewArray;
		}
	}

	/// Clears (deletes and then reallocate) the Array
	void clear() {
		delete[] Array;
		Array = new C[1];
		Size = 0;
	}

	/// Accessing Data as constant
	C& operator[](size_t Index) const { return Array[Index]; }

	/// Accessing Data
	C& operator[](size_t Index) { return Array[Index]; }

	/// Get Size of the Array
	const size_t& getSize() { return Size; }

	/// Get Number of specific Items in the Array
	template<class Pred>
	size_t getPredNum(Pred pred) {
		size_t Num = 0;
		for (size_t i = 0; i < getSize(); i++) {
			if (pred(Array[i]))
				Num++;
		}
		return Num;
	}
};

#endif // GENERICARRAY_H



