/*
 * client_Client.h
 *
 *  Created on: Apr 22, 2016
 *      Author: mastanca
 */

#ifndef SRC_CLIENT_CLIENT_CLIENT_H_
#define SRC_CLIENT_CLIENT_CLIENT_H_

#include <sys/types.h>
#include <iostream>
#include <string>

class Client {
private:
	// Processes input in the stream, separating each element into city,
	// temperature and day
	void processInput(std::string& city, float& temperature, uint& day, std::stringstream& inputStream);
public:
	// Constructor
	Client() {}
	// Destroyer
	virtual ~Client();
	// This public method encapsulates the working of the client
	// Runs the client, which inside calls the necessary methods
	void run();
};

#endif /* SRC_CLIENT_CLIENT_CLIENT_H_ */
