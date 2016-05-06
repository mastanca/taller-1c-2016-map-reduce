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
#include <utility>
#include <string>
#include <vector>

#include "common_InputParser.h"
#include "server_AcceptorWorker.h"
#include "server_ReducerWorker.h"

#define STOP_LISTENING "q"
#define MAX_QTY_REDUCER_THREADS 4

Server::~Server() {
	// Free client proxys
	for (std::vector<ClientProxy*>::iterator it = clients.begin();
			it != clients.end(); ++it) {
		delete (*it);
	}
	clients.clear();
}

Server::Server(const std::string& port) {
	dispatcherSocket = Socket(NULL, port.c_str());
	dispatcherSocket.bind();
}

void Server::run() {
	callAcceptorWorker();

	uint spawnedThreadsCount = 1; // We at least spawn 1
	// Now that we have our map we iterate over it and reduce each key
	for (std::map<uint, std::vector<Value> >::iterator it = dayValuesMap.getMap()->begin();
			it != dayValuesMap.getMap()->end(); ++it) {
		// Each worker accesses only his vector, should be no race condition
		ReducerWorker* reducerWorker = new ReducerWorker((*it).first,
				&(*it).second, &reducedData);
		reducers.push_back(reducerWorker);
		reducerWorker->start();

		// Control spawned threads
		if (spawnedThreadsCount == MAX_QTY_REDUCER_THREADS){
			releaseWorkers();
			spawnedThreadsCount = 1; // Reset count
		} else {
			++spawnedThreadsCount;
		}
	}

	// Join any left over threads if any
	if (spawnedThreadsCount != 0){
		releaseWorkers();
	}

	//Print results here by calling another method
	printFinalResults();
}

void Server::printFinalResults() {
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
			&dayValuesMap);
	acceptorWorker.start();

	while (keepOnListening && std::getline(std::cin, userInput)) {
		if (userInput == STOP_LISTENING) {
			keepOnListening = false;
		}
	}

	// We are done listening so join the worker
	acceptorWorker.join();
}


void Server::releaseWorkers() {
	// join workers
	for (std::vector<Thread*>::iterator it = reducers.begin();
			it != reducers.end(); ++it) {
		(*it)->join();
	}

	// Free reducers
	for (std::vector<Thread*>::iterator it = reducers.begin();
			it != reducers.end(); ++it) {
		delete (*it);
	}
	reducers.clear();
}
