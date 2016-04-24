/*
 * common_Mapper.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: mastanca
 */

#include "common_Mapper.h"
#include <sstream>

#define SPACE " "

void Mapper::map(const std::string& city, const float& temperature,
		const uint& day, std::stringstream& outputStream) {
	// Return day, temperature, city
	outputStream << day << SPACE;
	outputStream << temperature << SPACE;
	outputStream << city;
}

Mapper::~Mapper() {
}

