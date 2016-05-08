/*
 * server_DayValuesMap.h
 *
 *  Created on: May 6, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_DAYVALUESMAP_H_
#define SRC_SERVER_DAYVALUESMAP_H_

#include <sys/types.h>
#include <map>
#include <vector>

#include "common_Mutex.h"
#include "common_Value.h"

class DayValuesMap {
private:
	// Mutex for locking shared resource
	Mutex mutex;
	// The actual structure holding the map
	std::map<uint, std::vector<Value> > self;
public:
	// Destroyer
	virtual ~DayValuesMap();
	// Store (key, value) --> (day, value)
	void storeData(uint day, Value value);
	// Get the actual data
	std::map<uint, std::vector<Value> >* getMap();
};

#endif /* SRC_SERVER_DAYVALUESMAP_H_ */
