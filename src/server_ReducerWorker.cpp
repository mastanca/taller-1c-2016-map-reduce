/*
 * server_ReducerWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_ReducerWorker.h"

#include <string>
#include <utility>

#include "common_Lock.h"

ReducerWorker::~ReducerWorker() {
}

void ReducerWorker::run() {
	// So finally reduce
	storeReducedData(reducer.reduce(day, *valuesVector));
}

void ReducerWorker::storeReducedData(std::pair<uint, std::string> data) {
	// Secure access to shared resource
	Lock lock(mutex);
	reducedData->push_back(data);
}
