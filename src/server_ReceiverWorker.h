/*
 * server_ReceiverWorker.h
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_RECEIVERWORKER_H_
#define SRC_SERVER_SERVER_RECEIVERWORKER_H_

#include <string>
#include <vector>

#include "common_Thread.h"
#include "server_ClientProxy.h"
#include "server_MappedData.h"
#include "server_ParsedData.h"
#include "server_DayValuesMap.h"

class ReceiverWorker: public Thread {
private:
	// The client that will receive data (has the socket inside)
	ClientProxy* client;
	// The mappeddata to be received
	MappedData mappedData;
	// The received data, now parsed
	ParsedData parsedData;
	// The mapped received data
	DayValuesMap* dayValuesMap;
public:
	// Constructor
	ReceiverWorker(ClientProxy* client, DayValuesMap* dayValuesMap) :
			client(client), dayValuesMap(dayValuesMap) {
	}
	// Destroyer
	virtual ~ReceiverWorker();
	// Run the worker
	void run();
private:
	// Wrapper for mapped data structure accessing
	void storeMappedData(const std::string& data);
	// Parses the received data
	void parseMappedData();
	// Distributes the corresponding values to their keys
	void distributeParsedData();
};

#endif /* SRC_SERVER_SERVER_RECEIVERWORKER_H_ */
