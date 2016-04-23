/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "server_Server.h"

#include <sys/types.h>
#include <iostream>
#include <iterator>
#include <sstream>

#include "../MapReduce/common_Reducer.h"
#include "../MapReduce/common_Value.h"

Server::~Server() {
	// Free client proxys
	for (std::vector<ClientProxy*>::iterator it = clients.begin();
			it != clients.end(); ++it) {
		delete (*it);
	}
}

Server::Server(const std::string& port) {
	dispatcherSocket = Socket(NULL, port.c_str());
	dispatcherSocket.bind();
	// Move this to a tread eventually
	dispatcherSocket.listen(MAX_QUEUE_SIZE);
	clients.push_back(new ClientProxy());
	clients.back()->acceptNewConnection(dispatcherSocket);
}

void Server::run() {
	std::string inputLine, city;
	float temperature;
	uint day;
	// Getting the first one for testing
	clients.back()->receive(inputLine);
	std::stringstream ss(inputLine);
	ss >> day;
	ss >> temperature;
	ss >> city;
	Value value = Value(temperature, city);
	Reducer reducer;
//	Value value1 = Value(22, "BuenosAires");
//	Value value2 = Value(3, "Chaco");
//	Value value3 = Value(22, "Rawson");
//	Value value4 = Value(8, "Mendoza");
//	Value value5 = Value(22, "Pinamar");
//	uint testDay = 5;
	std::vector<Value*> vec;
	vec.push_back(&value);
//	vec.push_back(&value1);
//	vec.push_back(&value2);
//	vec.push_back(&value3);
//	vec.push_back(&value4);
//	vec.push_back(&value5);


//	reducer.reduce(testDay, vec);
	reducer.reduce(day, vec);
}
