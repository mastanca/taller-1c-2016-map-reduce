/*
 * common_Mapper.h
 *
 *  Created on: Apr 22, 2016
 *      Author: mastanca
 */

#ifndef SRC_MAPREDUCE_COMMON_MAPPER_H_
#define SRC_MAPREDUCE_COMMON_MAPPER_H_

#include <iostream>
#include <string>

class Mapper {
public:
	// Constructor
	Mapper() {}
	// Maps (city, temperature, day) to (day, temperature, city)
	void map(const std::string& city, const std::string& temperature, const std::string& day, std::stringstream& outputStream);
	// Destroyer
	virtual ~Mapper();
};

#endif /* SRC_MAPREDUCE_COMMON_MAPPER_H_ */
