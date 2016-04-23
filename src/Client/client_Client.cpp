/*
 * client_Client.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: mastanca
 */

#include "client_Client.h"

#include <iostream>
#include <sstream>
#include <string>

#include "../MapReduce/common_Mapper.h"

Client::~Client() {
}

void Client::run() {
	std::string inputLine, city, temperature, day;
	std::stringstream inputStream;
	while (std::getline(std::cin, inputLine)) {
		// Get line from stdin and separate to variables
		inputStream.str(inputLine);
		inputStream >> city;
		inputStream >> temperature;
		inputStream >> day;

		// Send to mapper

		std::stringstream mappedStream;
		Mapper mapper;
		mapper.map(city, temperature, day, mappedStream);

		std::cout << mappedStream.str() << std::endl;
	}
}
