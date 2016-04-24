/*
 * server_AcceptorWorker.h
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_ACCEPTORWORKER_H_
#define SRC_SERVER_SERVER_ACCEPTORWORKER_H_

#include "../Threading/common_Thread.h"

class AcceptorWorker: public Thread {
public:
	// Constructor
	AcceptorWorker();
	// Destroyer
	virtual ~AcceptorWorker();
	// Run the worker
	void run();
};

#endif /* SRC_SERVER_SERVER_ACCEPTORWORKER_H_ */
