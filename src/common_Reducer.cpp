/*
 * common_Reducer.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "common_Reducer.h"

#include <sys/types.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include <utility>
#include <string>
#include <vector>


#define ABSOLUTE_ZERO -273.15

Reducer::~Reducer() {
}

std::pair<uint, std::string> Reducer::reduce(const uint& day,
		std::vector<Value>& valuesList) {
	float temperature = ABSOLUTE_ZERO;
	std::stringstream city; // Use stringstream here to support multiple cities

	for (std::vector<Value>::iterator it = valuesList.begin();
			it != valuesList.end(); ++it) {
		// If value's temperature is greater than temperature then save it
		if ((*it).getTemperature() > temperature) {
			temperature = (*it).getTemperature();
			// Build city stringstream from scratch
			city.str(std::string());
			city.clear();
			city << (*it).getCity();
		} else if ((*it).getTemperature() == temperature) {
			// If its equal append the city
			// TODO: Should be ordered alphabetically?
			city << "/" + (*it).getCity();
		}
	}
	std::stringstream finalStream;
	finalStream << ": " << city.str() << " (" << temperature << ")";
	return std::make_pair(day, finalStream.str());
}
