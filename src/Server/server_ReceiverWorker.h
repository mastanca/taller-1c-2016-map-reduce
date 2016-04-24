/*
 * server_ReceiverWorker.h
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_RECEIVERWORKER_H_
#define SRC_SERVER_SERVER_RECEIVERWORKER_H_

#include "../Threading/common_Thread.h"

class ReceiverWorker: public Thread {
public:
	// Constructor
	ReceiverWorker();
	// Destroyer
	virtual ~ReceiverWorker();
	// Run the worker
	void run();
};

#endif /* SRC_SERVER_SERVER_RECEIVERWORKER_H_ */
