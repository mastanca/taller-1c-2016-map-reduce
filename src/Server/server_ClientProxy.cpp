/*
 * server_ClientProxy.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "server_ClientProxy.h"

#include <syslog.h>
#include <cstring>
#include <string>

#define MAX_BUFFER_SIZE 64
#define STOP_RECEIVING_CONDITION "End\n"

ClientProxy::ClientProxy() {
	connected = false;
	socket = Socket();
}

bool ClientProxy::isConnected() const {
	return connected;
}

ClientProxy::~ClientProxy() {
}

void ClientProxy::acceptNewConnection(const Socket& dispatcherSocket) {
	dispatcherSocket.accept(&socket);
}

void ClientProxy::receive(std::string& incomingData) {
	// I should receive a list or something where to store all the data
	// and then start reducing, use a string for testing
	bool keepReceiving = true;
	std::string newData;
	char buffer[MAX_BUFFER_SIZE];
	memset(&buffer[0], 0, sizeof(buffer));
	while (keepReceiving){
		 if (socket.receive(&buffer[0], MAX_BUFFER_SIZE) == -1){
			 keepReceiving = false;
			 syslog(LOG_ERR, "There was an error receiving from socket");
		 } else {
			 newData.append(buffer);
			 // If we find an "End\n" client was done sending
			 if (newData.find(STOP_RECEIVING_CONDITION) != std::string::npos)
				 keepReceiving = false;
		 }
	}
	// Lets play with this a little and just erase the end condition
	newData.erase(newData.length() - sizeof(STOP_RECEIVING_CONDITION) + 1, newData.length());
	incomingData = newData;
}
