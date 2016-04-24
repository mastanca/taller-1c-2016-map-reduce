/*
 * server_Server.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "server_Server.h"

#include <iostream>
#include <iterator>

#include "../MapReduce/common_Reducer.h"
#include "../Others/common_InputParser.h"
#include "server_AcceptorWorker.h"

#define STOP_LISTENING "q"

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
	// Move this to a thread eventually
//	dispatcherSocket.listen(MAX_QUEUE_SIZE);
//	clients.push_back(new ClientProxy());
//	clients.back()->acceptNewConnection(dispatcherSocket);
}

void Server::run() {
	callAcceptorWorker();
//	std::string inputLine;
//	// TODO: Use multiple clients
//	clients.back()->receive(inputLine);
	// We will receive all the data in inputline and then parse it all
	InputParser parser;
	// Big structure here
	std::vector< std::vector<std::pair<uint, Value> > > vectorOfTuplesVectors;
	for (std::vector<std::string>::iterator it =
			mappedData.begin(); it != mappedData.end(); ++it) {
		std::vector<std::pair<uint, Value> > tuplesVector = parser.parse(*it);
		vectorOfTuplesVectors.push_back(tuplesVector);
	}

	Reducer reducer;

	// We need to create a map of (day, [Values])
	std::map<uint, std::vector<Value> > map;
	for (std::vector< std::vector<std::pair<uint, Value> > >::iterator bigIt =
			vectorOfTuplesVectors.begin(); bigIt != vectorOfTuplesVectors.end(); ++bigIt) {
		for (std::vector<std::pair<uint, Value> >::iterator it =
				(*bigIt).begin(); it != (*bigIt).end(); ++it) {
			Value value = (*it).second;
			uint day = (*it).first;
			map[day].push_back(value);
		}
	}


	// Now that we have our map we iterate over it and reduce each key
	for (std::map<uint, std::vector<Value> >::iterator it = map.begin();
			it != map.end(); ++it) {
		reducer.reduce((*it).first, (*it).second);
	}

}

void Server::callAcceptorWorker(){
	bool keepOnListening = true;
	std::string userInput;

	// Initiate AcceptorWorker and get him to work
	AcceptorWorker acceptorWorker(&dispatcherSocket, &keepOnListening, &mappedData);
	acceptorWorker.start();

	while (keepOnListening && std::getline(std::cin, userInput)){
		if (userInput == STOP_LISTENING){
			keepOnListening = false;
		}
	}

	// We are done listening so join the worker
	acceptorWorker.join();
}
