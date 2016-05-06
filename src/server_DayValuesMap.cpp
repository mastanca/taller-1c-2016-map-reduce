/*
 * server_DayValuesMap.cpp
 *
 *  Created on: May 6, 2016
 *      Author: mastanca
 */

#include "server_DayValuesMap.h"

#include "common_Lock.h"
#include <map>
#include <vector>

DayValuesMap::~DayValuesMap() {
}

void DayValuesMap::storeData(uint day, Value value) {
	// Shared resource
	Lock lock(mutex);
	self[day].push_back(value);
}

std::map<uint, std::vector<Value> >* DayValuesMap::getMap() {
	return &self;
}
