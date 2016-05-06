/*
 * server_MappedData.cpp
 *
 *  Created on: May 6, 2016
 *      Author: mastanca
 */

#include "server_MappedData.h"

#include "common_Lock.h"
#include <string>
#include <vector>

MappedData::~MappedData() {
	if (self != NULL)
		delete self;
}

std::vector<std::string>* MappedData::getData() {
	return self;
}

void MappedData::saveData(const std::string& string) {
	// Shared resource, needs locking
	Lock lock(mutex);
	self->push_back(string);
}

MappedData::MappedData() {
	self = new std::vector<std::string>;
}
