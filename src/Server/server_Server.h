/*
 * server_Server.h
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#ifndef SRC_SERVER_SERVER_SERVER_H_
#define SRC_SERVER_SERVER_SERVER_H_

class Server {
public:
	// Constructor
	Server() {}
	// Destroyer
	virtual ~Server();
	// This method encapsulates the server work
	// and calls the rest of the methods
	void run();
};

#endif /* SRC_SERVER_SERVER_SERVER_H_ */
