/*
 * server_main.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: mastanca
 */

#include <stdlib.h>
#include <iostream>

#include "Server/server_Server.h"


int main(){
	std::cout<< "Hello Server!" << std::endl;
	Server server;
	server.run();
	return EXIT_SUCCESS;

}



