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

#include "../Threading/common_Thread.h"
#include "server_ClientProxy.h"

class ReceiverWorker: public Thread {
private:
	// The client that will receive data (has the socket inside)
	ClientProxy* client;
	// The mappeddata to be received
	std::vector<std::string>* mappedData;
public:
	// Constructor
	ReceiverWorker(ClientProxy* client, std::vector<std::string>* mappedData) :
			client(client), mappedData(mappedData) {
	}
	// Destroyer
	virtual ~ReceiverWorker();
	// Run the worker
	void run();
};

#endif /* SRC_SERVER_SERVER_RECEIVERWORKER_H_ */
