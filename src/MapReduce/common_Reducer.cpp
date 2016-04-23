/*
 * common_Reducer.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "common_Reducer.h"

#include <iostream>
#include <iterator>
#include <sstream>

#define ABSOLUTE_ZERO -273.15

Reducer::~Reducer() {
}

void Reducer::reduce(const std::string& day, std::vector<Value*>& valuesList) {
	// firstElement of valuesList is the temperature, second one is the city

	float temperature = ABSOLUTE_ZERO;
	float auxTemperature;
	std::stringstream city, inputTemperature; // Use stringstream here to support multiple cities

	for (std::vector<Value*>::iterator it = valuesList.begin();
			it != valuesList.end(); ++it) {
		// Convert incoming string to float to compare
		inputTemperature.str((*it)->getFirstElement());
		std::string testing = inputTemperature.str();
		inputTemperature >> auxTemperature; // Bug here when 14

		if (auxTemperature > temperature){
			temperature = auxTemperature;
			city << (*it)->getSecondElement();
		} else if (auxTemperature == temperature){
			city << "/" + (*it)->getSecondElement();
		}
	}

	std::cout << day << ": " << city.str() << " (" << temperature << ")" << std::endl;
}
