/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "server_Server.h"

#include <vector>

#include "../MapReduce/common_Reducer.h"
#include "../MapReduce/common_Value.h"

Server::~Server() {
}

void Server::run() {
	Reducer reducer;
	Value value1 = Value("22", "BuenosAires");
	Value value2 = Value("14", "Chaco");
	Value value3 = Value("22", "Rawson");
	std::string testDay = "5";
	std::vector<Value*> vec;
	vec.push_back(&value1);
	vec.push_back(&value2);
	vec.push_back(&value3);


	reducer.reduce(testDay, vec);
}
