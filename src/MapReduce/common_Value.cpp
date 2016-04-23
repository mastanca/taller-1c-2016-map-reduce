/*
 * common_Value.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "common_Value.h"

const std::string& Value::getFirstElement() const {
	return firstElement;
}

const std::string& Value::getSecondElement() const {
	return secondElement;
}

Value::~Value() {
}

