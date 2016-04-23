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
	float temperature;
	std::string city;
public:
	// Constructor
	Value(float temperature, std::string city) : temperature(temperature), city(city) {}
	// Destroyer
	virtual ~Value();
	const std::string& getCity() const;
	float getTemperature() const;
};

#endif /* SRC_MAPREDUCE_COMMON_VALUE_H_ */
