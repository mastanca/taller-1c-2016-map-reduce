/*
 * server_ParsedData.cpp
 *
 *  Created on: May 6, 2016
 *      Author: mastanca
 */

#include "server_ParsedData.h"

#include "common_Lock.h"

ParsedData::~ParsedData() {
}

void ParsedData::saveData(
		const std::vector<std::pair<uint, Value> >& tuplesVector) {
	// Shared resource, needs locking
	Lock lock(mutex);
	vectorOfTuplesVectors.push_back(tuplesVector);
}

std::vector<std::vector<std::pair<uint, Value> > >* ParsedData::getData() {
	return &vectorOfTuplesVectors;
}
