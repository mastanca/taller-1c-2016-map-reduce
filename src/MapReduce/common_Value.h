/*
 * common_Value.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_MAPREDUCE_COMMON_VALUE_H_
#define SRC_MAPREDUCE_COMMON_VALUE_H_

#include <string>

class Value {
private:
	// We will have only 2 values in this case
	std::string firstElement, secondElement;
public:
	// Constructor
	Value(std::string firstElement, std::string secondElement) : firstElement(firstElement), secondElement(secondElement) {}
	// Destroyer
	virtual ~Value();
	// Return first element
	const std::string& getFirstElement() const;
	// Return second element
	const std::string& getSecondElement() const;
};

#endif /* SRC_MAPREDUCE_COMMON_VALUE_H_ */
