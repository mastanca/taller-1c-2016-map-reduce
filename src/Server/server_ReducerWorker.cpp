/*
 * server_ReducerWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_ReducerWorker.h"

ReducerWorker::~ReducerWorker() {
}

void ReducerWorker::run() {
	// So finally reduce
	reducedData->push_back(reducer.reduce(day, *valuesVector));
}
