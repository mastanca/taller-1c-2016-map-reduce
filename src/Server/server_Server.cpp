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
#include <utility>
#include <sstream>

#include "../MapReduce/common_Reducer.h"
#include "../MapReduce/common_Value.h"
#include "../Others/common_InputParser.h"

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
	std::string inputLine;
	// Getting the first one for testing
	clients.back()->receive(inputLine);
	InputParser parser;
	std::vector<std::pair<uint, Value> > tuplesVector = parser.parse(inputLine);
	Reducer reducer;
	for (std::vector<std::pair<uint, Value> >::iterator it = tuplesVector.begin();
			it != tuplesVector.end(); ++it) {
		// TODO: Use vec cause in future we need all of the same day
		std::vector<Value*> vec;
		vec.push_back(&((*it).second));
		uint day = (*it).first;
		reducer.reduce(day, vec);
	}
}
