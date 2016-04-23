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

void Client::processInput(std::string& city, std::string& temperature,
		std::string& day, std::stringstream& inputStream) {
	inputStream >> city;
	inputStream >> temperature;
	inputStream >> day;
}

void Client::run() {
	std::string inputLine, city, temperature, day;
	std::stringstream inputStream;
	while (std::getline(std::cin, inputLine)) {
		// Get line from stdin and separate to variables
		inputStream.str(inputLine);
		processInput(city, temperature, day, inputStream);

		// Send to mapper
		std::stringstream mappedStream;
		Mapper mapper;
		mapper.map(city, temperature, day, mappedStream);

		std::cout << mappedStream.str() << std::endl;
	}
	std::cout << "End" << std::endl;
}