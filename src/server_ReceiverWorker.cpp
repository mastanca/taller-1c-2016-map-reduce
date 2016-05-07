/*
 * server_ReceiverWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_ReceiverWorker.h"

#include <string>

ReceiverWorker::~ReceiverWorker() {
}

void ReceiverWorker::run() {
	std::string inboundData;
	client->receive(inboundData);
	storeMappedData(inboundData);
}

void ReceiverWorker::storeMappedData(const std::string& data) {
	mappedData->saveData(data);
}
