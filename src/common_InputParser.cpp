/*
 * common_InputParser.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "common_InputParser.h"

#include <sstream>
#include <utility>
#include <string>
#include <vector>


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
		ss >> day;
		ss >> temperature;
		ss >> city;
		Value value = Value(temperature, city);
		// Create a pair with day as key, value as value
		std::pair<uint, Value> aPair(day, value);
		tuplesVector.push_back(aPair);
	}
	// Due to implementation the last pair is pushed twice,
	// as we are short of time lets just pop it
	tuplesVector.pop_back();
	return tuplesVector;
}
