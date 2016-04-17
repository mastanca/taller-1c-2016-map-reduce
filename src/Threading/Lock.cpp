/*
 * Lock.cpp
 *
 *  Created on: Apr 12, 2016
 *      Author: mastanca
 */

#include "Lock.h"

#include "Mutex.h"

Lock::Lock(Mutex &mutex) : aMutex(mutex) {
    aMutex.enableLock();
}

Lock::~Lock() {
	// Upon destruction of lock, mutex is disabled
    aMutex.disableLock();
}

