/*
 * common_Value.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "common_Value.h"
#include <string>

const std::string& Value::getCity() const {
	return city;
}

float Value::getTemperature() const {
	return temperature;
}

Value::~Value() {
}

