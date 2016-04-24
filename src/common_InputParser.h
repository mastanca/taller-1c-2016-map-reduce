/*
 * common_InputParser.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_OTHERS_COMMON_INPUTPARSER_H_
#define SRC_OTHERS_COMMON_INPUTPARSER_H_

#include <sys/types.h>
#include <string>
#include <utility>
#include <vector>

#include "common_Value.h"

class InputParser {
public:
	// Destroyer
	virtual ~InputParser();
	// Returns a vector of pairs (uint as key, value)
	std::vector<std::pair<uint, Value> > parse(const std::string& input);
};

#endif /* SRC_OTHERS_COMMON_INPUTPARSER_H_ */
