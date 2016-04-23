/*
 * main.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: mastanca
 */

#include <stdlib.h>
#include <iostream>

#include "Client/client_Client.h"


int main(){
	std::cout<< "Hello Client!" << std::endl;
	Client client;
	client.run();

	return EXIT_SUCCESS;

}


