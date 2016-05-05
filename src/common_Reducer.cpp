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
#include <algorithm>

#define ABSOLUTE_ZERO -273.15
#define CITIES_SEPARATOR "/"

Reducer::~Reducer() {
}

std::pair<uint, std::string> Reducer::reduce(const uint& day,
		std::vector<Value>& valuesList) {
	float temperature = ABSOLUTE_ZERO;
	std::vector<std::string> citiesVector;

	for (std::vector<Value>::iterator it = valuesList.begin();
			it != valuesList.end(); ++it) {
		// If value's temperature is greater than temperature then save it
		if ((*it).getTemperature() > temperature) {
			temperature = (*it).getTemperature();
			// Erase old vector before adding
			citiesVector.erase(citiesVector.begin(), citiesVector.end());
			citiesVector.push_back((*it).getCity());
		} else if ((*it).getTemperature() == temperature) {
			// If its equal append the city
			citiesVector.push_back((*it).getCity());
		}
	}
	std::stringstream finalStream;
	finalStream << ": " << getSortedCitiesVector(&citiesVector) << " ("
			<< temperature << ")";
	return std::make_pair(day, finalStream.str());
}

std::string Reducer::getSortedCitiesVector(
		std::vector<std::string>* citiesVector) {
	std::stringstream stringToReturn;
	std::sort(citiesVector->begin(), citiesVector->end());
	for (std::vector<std::string>::iterator it = citiesVector->begin();
			it != citiesVector->end(); ++it) {
		stringToReturn << *it;
		if (it != citiesVector->end() - 1) {
			stringToReturn << CITIES_SEPARATOR;
		}
	}
	return stringToReturn.str();
}
