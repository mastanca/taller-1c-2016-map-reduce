/*
 * common_InputParser.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "common_InputParser.h"

#include <sstream>

InputParser::~InputParser() {
}

std::vector<std::pair<uint, Value> > InputParser::parse(
		const std::string& input) {
	std::vector<std::pair<uint, Value> > tuplesVector;
	std::stringstream ss(input);
	std::string city;
	float temperature;
	uint day;
	while (!ss.eof()){
		std::pair<uint, Value> aPair;
		ss >> day;
		ss >> temperature;
		ss >> city;
		Value value = Value(temperature, city);
		// Create a pair with day as key, value as value
		aPair = std::make_pair(day, value);
		tuplesVector.push_back(aPair);
	}
	return tuplesVector;
}
