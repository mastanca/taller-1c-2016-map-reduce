/*
 * common_Mapper.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: mastanca
 */

#include <sstream>
#include <string>
#include "client_Mapper.h"

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

