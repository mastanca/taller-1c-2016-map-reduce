/*
 * common_Value.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "common_Value.h"

const std::string& Value::getCity() const {
	return city;
}

Value::Value() {
}

float Value::getTemperature() const {
	return temperature;
}

Value::~Value() {
}

