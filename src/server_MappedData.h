/*
 * server_MappedData.h
 *
 *  Created on: May 6, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_MAPPEDDATA_H_
#define SRC_SERVER_MAPPEDDATA_H_

#include <string>
#include <vector>


class MappedData {
private:
	// The actual data
	std::vector<std::string>* self;
public:
	// Constructor
	MappedData();
	// Destroyer
	virtual ~MappedData();
	// Store data in structure
	void saveData(const std::string& string);
	// Returns the actual data
	std::vector<std::string>* getData();
};

#endif /* SRC_SERVER_MAPPEDDATA_H_ */
