/*
 * client_ServerProxy.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: mastanca
 */

#include "client_ServerProxy.h"

#include <syslog.h>
#include <cstring>
#include <errno.h>

ServerProxy::~ServerProxy() {
}

void ServerProxy::send(const std::string& data) {
	if (this->socket.send((char*)data.c_str(), data.length()) == -1){
		syslog(LOG_ERR, "There was an error while sending data %s", strerror(errno));
	}
}
