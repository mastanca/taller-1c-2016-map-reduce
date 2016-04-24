/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "server_Server.h"

#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>

#include "common_InputParser.h"
#include "server_AcceptorWorker.h"
#include "server_ReducerWorker.h"

#define STOP_LISTENING "q"

Server::~Server() {
	// Free client proxys
	for (std::vector<ClientProxy*>::iterator it = clients.begin();
			it != clients.end(); ++it) {
		delete (*it);
	}
	clients.clear();

	// Free reducers
	for (std::vector<Thread*>::iterator it = reducers.begin();
			it != reducers.end(); ++it) {
		delete (*it);
	}
	reducers.clear();
}

Server::Server(const std::string& port) {
	dispatcherSocket = Socket(NULL, port.c_str());
	dispatcherSocket.bind();
}

void Server::run() {
	// Threading area 1
	callAcceptorWorker();

	/////////////////////////////////////////////////////////////////////////
	// We will receive all the data in inputline and then parse it all
	InputParser parser;
	// Big structure here, we need a vector to hold the vectors of tuples
	std::vector<std::vector<std::pair<uint, Value> > > vectorOfTuplesVectors;
	for (std::vector<std::string>::iterator it = mappedData.begin();
			it != mappedData.end(); ++it) {
		std::vector<std::pair<uint, Value> > tuplesVector = parser.parse(*it);
		vectorOfTuplesVectors.push_back(tuplesVector);
	}

	// We need to create a map of (day, [Values])
	std::map<uint, std::vector<Value> > map;
	for (std::vector<std::vector<std::pair<uint, Value> > >::iterator bigIt =
			vectorOfTuplesVectors.begin(); bigIt != vectorOfTuplesVectors.end();
			++bigIt) {
		for (std::vector<std::pair<uint, Value> >::iterator it =
				(*bigIt).begin(); it != (*bigIt).end(); ++it) {
			Value value = (*it).second;
			uint day = (*it).first;
			map[day].push_back(value);
		}
	}
	//////////////////////////////////////////////////////////////////////////

	// Threading area 2
	// Now that we have our map we iterate over it and reduce each key
	for (std::map<uint, std::vector<Value> >::iterator it = map.begin();
			it != map.end(); ++it) {
		// Each worker accesses only his vector, should be no race condition
		ReducerWorker* reducerWorker = new ReducerWorker((*it).first,
				&(*it).second, &reducedData);
		reducers.push_back(reducerWorker);
		reducerWorker->start();
	}

	//Print results here by calling another method
	printFinalResults();
}

void Server::printFinalResults() {
	// First join workers
	for (std::vector<Thread*>::iterator it = reducers.begin();
			it != reducers.end(); ++it) {
		(*it)->join();
	}

	// Sort by day
	// According to docs, pair overrides "<" to compare first by key then by
	// value
	std::sort(reducedData.begin(), reducedData.end());

	// Finally print
	for (std::vector<std::pair<uint, std::string> >::iterator it =
			reducedData.begin(); it != reducedData.end(); ++it) {
		std::cout << (*it).first << (*it).second << std::endl;
	}

}

void Server::callAcceptorWorker() {
	bool keepOnListening = true;
	std::string userInput;

	// Initiate AcceptorWorker and get him to work
	AcceptorWorker acceptorWorker(&dispatcherSocket, &keepOnListening,
			&mappedData);
	acceptorWorker.start();

	while (keepOnListening && std::getline(std::cin, userInput)) {
		if (userInput == STOP_LISTENING) {
			keepOnListening = false;
		}
	}

	// We are done listening so join the worker
	acceptorWorker.join();
}
