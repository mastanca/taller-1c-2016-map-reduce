/*
 * Worker.h
 *
 *  Created on: Apr 12, 2016
 *      Author: mastanca
 */

#ifndef SRC_WORKER_H_
#define SRC_WORKER_H_

#include "Worker.h"
#include "Thread.h"

class Worker : public Thread {
private:
	//Expression* expressionToRun;
	// What to run goes here
public:
//	// Constructor
//	explicit Worker(Expression* expression) :
//		expressionToRun(expression) {}
	// Destroyer
	virtual ~Worker();
	// Run the runner
	void run();
};

#endif /* SRC_WORKER_H_ */
