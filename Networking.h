#pragma once	
#ifndef __NETWORKING_H__
#define __NETWORKING_H__

#include "Common.h"
#include "Sort.h"

#define	ETHER_ADDR_LEN		6

struct ethhdr
{		
	uint8_t		dhost[ETHER_ADDR_LEN];
	uint8_t		shost[ETHER_ADDR_LEN];
	uint16_t	type;	
};


#ifdef WIN32

	#define AF_INET		2
	

	struct iphdr
	{
		uint8_t  ihl:4,
				 version:4;
		uint8_t  tos;
		uint16_t  tot_len; 
		uint16_t  id; 		
		uint16_t  frag_off;  
		uint8_t  ttl; 
		uint8_t  protocol; 
		uint16_t  check; 
		uint32_t  saddr;
		uint32_t  daddr; 
	};
	

	struct tcphdr 
	{
		uint16_t source; 
		uint16_t dest;
		uint32_t seq; 
		uint32_t ack_seq; 
		uint8_t res1:4,
				doff:4; 
		uint8_t flags; 
		uint16_t window; 
		uint16_t check; 
		uint16_t urg_ptr; 
	};
	


#endif

struct pseudohdr
{
	uint32_t  saddr, daddr;
	uint8_t mbz, ptcl;
	uint16_t tcpl;
};


struct N_DEVICE
{
	char name[128];
	char description[128];	
	unsigned char smac[ETHER_ADDR_LEN];
	unsigned char dmac[ETHER_ADDR_LEN];	
	uint32_t address;
	uint32_t gateway;
};


#define ETHHDRSIZE	sizeof(struct ethhdr)
#define IPHDRSIZE sizeof(struct iphdr)
#define TCPHDRSIZE sizeof(struct tcphdr)
#define PSEUDOHDRSIZE sizeof(struct pseudohdr)


#ifdef WIN32
#define SendPacket(a,b,c) pcap_sendpacket(a,b,c);  
bool ResolveDestMac(N_DEVICE * );
bool GetNetworkDevices(std::vector<N_DEVICE>&);
bool OpenNetworkDevice(const string, pcap_t*&);
void CloseNetworkDevice(pcap_t*&);
#endif

bool  GetNetworkRange(const string, uint32_t&, uint32_t &);
bool ParseNetworkAddress(const string, uint32_t &, uint16_t&);
uint16_t Checksum(uint16_t *, int );	


#endif /*__NETWORKING_H__*/
