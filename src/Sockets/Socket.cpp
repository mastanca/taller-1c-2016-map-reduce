/*
 * Socket.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: mastanca
 */

#include "Socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <syslog.h>


Socket::Socket(std::string hostname, std::string port) {
	int s = 0;
	struct addrinfo hints;
	int flag = 0;

	if (hostname == "" || (hostname == "127.0.0.1")){
		hostname = "";
		flag = AI_PASSIVE; // Flag for server
	}
	// Port is received as a parameter from user, no need to convert to net
	const char *serviceName = port.c_str();

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
	hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
	hints.ai_flags = flag;     	/* 0 (or AI_PASSIVE for server)           */

	s = getaddrinfo(hostname.c_str(), serviceName, &hints, &(this->result));

	if (s != 0) {
		syslog(LOG_ERR, "There was an error when creating socket, "
				"getaddrinfo returned 0");
	}

	this->fd = socket(this->result->ai_family, this->result->ai_socktype,
			this->result->ai_protocol);

	if (this->fd == -1){
		syslog(LOG_ERR, "There was an error when creating socket, "
				"socket fd was -1");
	}
}

Socket::~Socket() {
	shutdown(this->fd, SHUT_RDWR);
	close(this->fd);
}

int Socket::bind() {
	if (::bind(this->fd, this->result->ai_addr, this->result->ai_addrlen) == -1){
		close(this->fd);
		freeaddrinfo(this->result);
		syslog(LOG_ERR, "There was an error when binding the socket, "
				"bind returned -1");
		return EXIT_FAILURE;
	}
	freeaddrinfo(this->result);
	return EXIT_SUCCESS;
}

int Socket::listen(int maxQueueSize) {
	if (::listen(this->fd, maxQueueSize) == -1){
		syslog(LOG_ERR, "There was an error when listening, "
				"listen returned -1");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int Socket::accept(Socket* client) {
	client->fd = ::accept(this->fd, NULL, NULL);
	if (client->fd == -1){
		syslog(LOG_ERR, "There was an error when accepting a new client, "
				"accept returned -1");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int Socket::connect() {
	int s = 0;
	struct addrinfo *ptr;
	bool are_we_connected = false;
	for (ptr = this->result; ptr != NULL && are_we_connected == false;
			ptr = ptr->ai_next) {
		s = ::connect(this->fd, ptr->ai_addr, ptr->ai_addrlen);
		if (s == -1){
			close(this->fd);
			this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		}
		are_we_connected = (s != -1);
	}
	freeaddrinfo(this->result);
	if (are_we_connected == false){
		syslog(LOG_ERR, "There was an error when connecting");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int Socket::receive(std::string* buffer, int size) {
	int received = 0;
	int response = 0;
	bool is_a_valid_socket = true;

	while (received < size && is_a_valid_socket) {
		response = recv(this->fd, &buffer[received], size-received, MSG_NOSIGNAL);

		if (response == 0){
			// Socket was closed
			is_a_valid_socket = false;
			syslog(LOG_WARNING, "There was an error when receiving data from socket, "
					"socket was closed");
		}else if (response < 0) {
			// There was an error
			is_a_valid_socket = false;
			syslog(LOG_WARNING, "There was an error when receiving data from socket ");
		} else {
			received += response;
		}
	}

	if (is_a_valid_socket) {
		return received;
	} else {
		return -EXIT_FAILURE;
	}
}

int Socket::send(std::string* buffer, int size) {
	int sent =0;
	int response = 0;
	bool is_a_valid_socket = true;

	while (sent < size && is_a_valid_socket) {
		response = ::send(this->fd, &buffer[sent], size-sent, MSG_NOSIGNAL);

		if (response == 0){
			// Socket was closed
			is_a_valid_socket = false;
			syslog(LOG_WARNING, "There was an error when sending data from socket, "
					"socket was closed");
		}else if (response < 0) {
			// There was an error
			is_a_valid_socket = false;
			syslog(LOG_ERR, "There was an error when receiving data from socket ");
		} else {
			sent += response;
		}
	}

	if (is_a_valid_socket) {
		return sent;
	} else {
		return -EXIT_FAILURE;
	}
}
