/*
 * server_ReceiverWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_ReceiverWorker.h"

ReceiverWorker::~ReceiverWorker() {
}

void ReceiverWorker::run() {
	std::string inboundData;
	client->receive(inboundData);
	mappedData->push_back(inboundData);
}
