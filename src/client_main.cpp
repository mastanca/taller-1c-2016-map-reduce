/*
 * main.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: mastanca
 */

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

#include "MapReduce/common_Mapper.h"


int main(){
	std::cout<< "Hello Client!" << std::endl;
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

	return EXIT_SUCCESS;

}


