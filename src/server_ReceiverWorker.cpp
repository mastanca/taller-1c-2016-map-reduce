/*
 * server_ReceiverWorker.cpp
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#include "server_ReceiverWorker.h"

#include "common_InputParser.h"
#include <string>

ReceiverWorker::~ReceiverWorker() {
}

void ReceiverWorker::run() {
	std::string inboundData;
	client->receive(inboundData);
	storeMappedData(inboundData);
	parseMappedData();
}

void ReceiverWorker::storeMappedData(const std::string& data) {
	mappedData.saveData(data);
}

void ReceiverWorker::parseMappedData() {
	InputParser parser;
	for (std::vector<std::string>::iterator it = mappedData.getData()->begin();
			it != mappedData.getData()->end(); ++it) {
		std::vector<std::pair<uint, Value> > tuplesVector = parser.parse(*it);
		parsedData->saveData(tuplesVector);
	}
}
