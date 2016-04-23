/*
 * client_ServerProxy.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "client_ServerProxy.h"

#include <iostream>

ServerProxy::~ServerProxy() {
}

void ServerProxy::send(const std::string& data) {
	std::cout << data << std::endl;
	// TODO: Make this right
}
