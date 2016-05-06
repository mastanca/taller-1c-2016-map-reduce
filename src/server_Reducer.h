/*
 * server_Reducer.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_MAPREDUCE_COMMON_REDUCER_H_
#define SRC_MAPREDUCE_COMMON_REDUCER_H_

#include <sys/types.h>
#include <string>
#include <utility>
#include <vector>

#include "common_Value.h"

class Reducer {
private:
	// Sorts internal cities vector
	std::string getSortedCitiesVector(std::vector<std::string>* citiesVector);
public:
	// Constructor
	Reducer() {
	}
	// Destroyer
	virtual ~Reducer();
	// Reduces day, [(temperature1, city2), (temperature2, city2), ...] to
	// the day/s with the highest temperature
	std::pair<uint, std::string> reduce(const uint& day,
			std::vector<Value>& valuesList);
};

#endif /* SRC_MAPREDUCE_COMMON_REDUCER_H_ */
