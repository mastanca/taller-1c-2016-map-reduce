/*
 * server_ReducerWorker.h
 *
 *  Created on: Apr 24, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_REDUCERWORKER_H_
#define SRC_SERVER_SERVER_REDUCERWORKER_H_

#include <sys/types.h>
#include <vector>

#include "../MapReduce/common_Reducer.h"
#include "../MapReduce/common_Value.h"
#include "../Threading/common_Thread.h"
#include "../Threading/common_Mutex.h"

class ReducerWorker: public Thread {
private:
	// The actual reducer to execute
	Reducer reducer;
	// The day assigned to this worker
	uint day;
	// The values vector
	std::vector<Value>* valuesVector;
	// Shared structure to store results
	std::vector<std::pair<uint, std::string> >* reducedData;
public:
	// Constructor
	ReducerWorker(uint day, std::vector<Value>* valuesVector,
			std::vector<std::pair<uint, std::string> >* reducedData) :
			day(day), valuesVector(valuesVector), reducedData(reducedData) {
	}
	// Destroyer
	virtual ~ReducerWorker();
	// Run the worker
	void run();
private:
	// Mutex for threading
	Mutex mutex;
	// Reduced data structure accessor wrapper
	void storeReducedData(std::pair<uint, std::string> data);
};

#endif /* SRC_SERVER_SERVER_REDUCERWORKER_H_ */
