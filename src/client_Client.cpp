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

#include "common_Mapper.h"

#define STOP_SENDING_SIGNAL "End\n"

Client::~Client() {
}

void Client::processInput(std::string& city, float& temperature, uint& day,
		std::stringstream& inputStream) {
	inputStream >> city;
	inputStream >> temperature;
	inputStream >> day;
}

void Client::run() {
	std::string inputLine, city;
	float temperature;
	uint day;
	std::stringstream inputStream;
	while (std::getline(std::cin, inputLine)) {
		// Get line from stdin and separate to variables
		inputStream.clear();
		inputStream.str(inputLine);
		processInput(city, temperature, day, inputStream);

		// Send to mapper
		std::stringstream mappedStream;
		Mapper mapper;
		mapper.map(city, temperature, day, mappedStream);

		serverProxy.send(mappedStream.str() + "\n");
		std::cout << "Sent " << mappedStream.str() << std::endl;
	}
	serverProxy.send(STOP_SENDING_SIGNAL);
}
