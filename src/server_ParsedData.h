/*
 * server_ParsedData.h
 *
 *  Created on: May 6, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_PARSEDDATA_H_
#define SRC_SERVER_PARSEDDATA_H_

#include <sys/types.h>
#include <utility>
#include <vector>

#include "common_Value.h"

class ParsedData {
private:
	// The actual data
	std::vector<std::vector<std::pair<uint, Value> > > vectorOfTuplesVectors;
public:
	virtual ~ParsedData();
	// Store data in structure
	void saveData(const std::vector<std::pair<uint, Value> >& tuplesVector);
	// Returns the actual data
	std::vector<std::vector<std::pair<uint, Value> > >* getData();
};

#endif /* SRC_SERVER_PARSEDDATA_H_ */
