/*
 * main.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: mastanca
 */

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>


int main(){
	std::cout<< "Hello Client!" << std::endl;
	std::string inputLine, city, temperature, day;
	std::stringstream inputStream;
	while (std::getline(std::cin, inputLine)) {
		inputStream.str(inputLine);
		inputStream >> city;
		inputStream >> temperature;
		inputStream >> day;
	}

	return EXIT_SUCCESS;

}


