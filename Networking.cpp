#include "Networking.h"


#ifdef WIN32


bool GetNetworkDevices(vector<N_DEVICE>& devs)
{
	
	devs.clear();

    PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
    DWORD dwRetVal = 0;
	bool i = false;
    ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);

    pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL)
	{
        cout << endl <<endl << "Problem allocating memory needed to call GetAdaptersinfo" << endl <<endl;
        return 0;
    }


    if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW)
	{
        free(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *)malloc(ulOutBufLen);
        if (pAdapterInfo == NULL) 
		{
            cout << endl <<endl << "Problem allocating memory needed to call GetAdaptersinfo" << endl <<endl;
            return 1;
        }
    }

    if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
	{
        pAdapter = pAdapterInfo;
        while (pAdapter)
		{

			N_DEVICE dev ;
            
			memset(&dev, 0, sizeof(N_DEVICE));
			strcpy(dev.name, pAdapter->AdapterName);
			strcpy(dev.description, pAdapter->Description);			
			memcpy(dev.smac, pAdapter->Address, ETHER_ADDR_LEN);	
            dev.address = inet_addr( pAdapter->IpAddressList.IpAddress.String);          
            dev.gateway = inet_addr( pAdapter->GatewayList.IpAddress.String);           						
			pAdapter = pAdapter->Next;

			devs.push_back(dev);

			i=true;
		}
    } 
	else 
	{
       cout << endl <<endl << "GetAdaptersInfo failed with error: " << dwRetVal <<endl <<endl;

    }
    if (pAdapterInfo)
	{
        free(pAdapterInfo);
	}
	


	
	return i;
	
}


bool ResolveDestMac(N_DEVICE *dev)
{

	/*
	DWORD dwRetVal;
     ULONG MacAddr[2];       
    ULONG PhysAddrLen = 6;  
	    
    char *SrcIpString = NULL;
    BYTE *bPhysAddr;
    unsigned int i;
	

	memset(&MacAddr, 0xff, sizeof (MacAddr));

    dwRetVal = SendARP(dev->gateway, 0, &MacAddr, &PhysAddrLen);
	

    if (dwRetVal == NO_ERROR) 
	{
        bPhysAddr = (BYTE *) & MacAddr;
        if (PhysAddrLen)
		{
			memcpy(dev->dmac, bPhysAddr, ETHER_ADDR_LEN);
        }
		else
		{
            cout << endl <<endl << "Warning: SendArp completed successfully, but returned length=0" << endl <<endl ;
		}
    } 
	else 	
	{
      
		cout << endl << endl << "ARP request failed!" << endl <<endl;
		return false;
    }*/

	
	memcpy(dev->dmac, "\xFF\xFF\xFF\xFF\xFF\xFF", ETHER_ADDR_LEN);


	return true;

}

bool OpenNetworkDevice(const string name, pcap_t * &device)
{
	
	char errorBuf[256];
	if((device = pcap_open_live(name.c_str(),BUFSIZ, 1, 1000, errorBuf)) == NULL)
	{
		return false;
	}

	pcap_setnonblock(device, 1, errorBuf) ;   

	return true;
}

void CloseNetworkDevice(pcap_t* &device)
{
	if (device!= NULL)
	{
		pcap_close(device);
	}
}


#endif

uint16_t Checksum(uint16_t *addr, int len)
{	
   int		nleft = len;
    u_int16_t	*w = addr;
    u_int32_t	sum = 0;
    u_int16_t	answer = 0;


    while( nleft > 1 )
    {
	sum += *w++;
	nleft -= 2;
    }

    
    if( nleft == 1 )
    {
        answer=0;
        *(u_char *)(&answer) = *(u_char *)w ;
        sum += answer;
    }

   
    sum = (sum >> 16) + (sum & 0xffff);    
    sum += (sum >> 16);                     
    answer = ~sum;                         
    return answer;

}


bool  GetNetworkRange(const string input, uint32_t & min, uint32_t & max )
{	

	int prefixSize;
	uint32_t address;

	size_t pos = input.find("/");	

	if (pos == string::npos)
	{
		if ((pos = input.find("*")) == string::npos)
		{

			if ((pos = input.find("-")) != string::npos)
			{
				min = inet_addr(input.substr(0,pos).c_str());
				max = inet_addr(input.substr(pos+1,input.length()-pos).c_str());
			}
			else
			{
				return false;
			}

		}	
		else
		{
			string tmp = input;
			min = inet_addr(ReplaceAll(tmp, "*", "0").c_str());
			max = inet_addr(ReplaceAll(input, "*", "255").c_str());
		}
	}
	else
	{
		prefixSize = (uint8_t)atoi(input.substr(pos+1, input.length() - pos).c_str());		
		address = htonl(inet_addr(input.substr(0,pos).c_str()));

		if ((prefixSize < 0 || prefixSize > 32) || address == INADDR_NONE )
		{
			return false;
		}
		else
		{
			uint32_t mask = 0xfffffff << (32 - prefixSize);
			uint32_t bcast = 0xffffffff >> (prefixSize);

			min = address & mask ;
			max= (address & mask) + bcast ;
			
		}
	}
		
	return true;
}
/*
bool ParseNetworkAddress(const string input, uint32_t &address, uint16_t& port)
{
	size_t pos;
	if ((pos = input.find(":")) != string::npos)
	{				
		port = (uint16_t)atoi(input.substr(pos + 1, input.length() - pos ).c_str());
		address = inet_addr(input.substr(0, pos).c_str());

		if ((port < 0 || port > 65535) || address == INADDR_NONE )
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;
}
*/


