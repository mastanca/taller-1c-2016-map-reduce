/*
 * common_Reducer.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_MAPREDUCE_COMMON_REDUCER_H_
#define SRC_MAPREDUCE_COMMON_REDUCER_H_

#include <sys/types.h>
#include <vector>

#include "common_Value.h"

class Reducer {
public:
	// Constructor
	Reducer() {}
	// Destroyer
	virtual ~Reducer();
	// Reduces day, [(temperature1, city2), (temperature2, city2), ...] to
	// the day/s with the highest temperature
	void reduce(const uint& day, std::vector<Value*>& valuesList);
};

#endif /* SRC_MAPREDUCE_COMMON_REDUCER_H_ */
