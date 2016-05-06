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
	distributeParsedData();
}

void ReceiverWorker::storeMappedData(const std::string& data) {
	mappedData.saveData(data);
}

void ReceiverWorker::parseMappedData() {
	InputParser parser;
	for (std::vector<std::string>::iterator it = mappedData.getData()->begin();
			it != mappedData.getData()->end(); ++it) {
		std::vector<std::pair<uint, Value> > tuplesVector = parser.parse(*it);
		parsedData.saveData(tuplesVector);
	}
}

void ReceiverWorker::distributeParsedData() {
	for (std::vector<std::vector<std::pair<uint, Value> > >::iterator bigIt =
			parsedData.getData()->begin(); bigIt != parsedData.getData()->end();
			++bigIt) {
		for (std::vector<std::pair<uint, Value> >::iterator it =
				(*bigIt).begin(); it != (*bigIt).end(); ++it) {
			Value value = (*it).second;
			uint day = (*it).first;
			dayValuesMap->storeData(day, value);
		}
	}
}
