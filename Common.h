#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <algorithm>


#ifdef WIN32	
	#include <Winsock2.h>   
	#include <Iphlpapi.h>
	#include <Assert.h>
#else
  #include <unistd.h>
  #include <stdint.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <netinet/ip.h>
  #include <netinet/tcp.h>
  #include <arpa/inet.h>
#endif

#ifdef WIN32
	#include <pcap.h>
#endif

#include "Settings.h"
#include "Definitions.h"


using namespace std;


#endif /*__COMMON_H__*/
