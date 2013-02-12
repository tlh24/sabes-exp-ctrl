#include <pcap.h>
#include <stdio.h>
#include <string.h>

// gcc pcap.c -lpcap
// sudo setcap cap_net_raw,cap_net_admin=eip a.out
// source: https://blog.wireshark.org/2010/02/running-wireshark-as-you/

/* Ethernet addresses are 6 bytes */
#define ETHER_ADDR_LEN	6

/* Ethernet header */
struct sniff_ethernet {
	u_char ether_dhost[ETHER_ADDR_LEN]; /* Destination host address */
	u_char ether_shost[ETHER_ADDR_LEN]; /* Source host address */
	u_short ether_type; /* IP? ARP? RARP? etc */
};

/* IP header */
struct sniff_ip {
	u_char ip_vhl;		/* version << 4 | header length >> 2 */
	u_char ip_tos;		/* type of service */
	u_short ip_len;		/* total length */
	u_short ip_id;		/* identification */
	u_short ip_off;		/* fragment offset field */
#define IP_RF 0x8000		/* reserved fragment flag */
#define IP_DF 0x4000		/* dont fragment flag */
#define IP_MF 0x2000		/* more fragments flag */
#define IP_OFFMASK 0x1fff	/* mask for fragmenting bits */
	u_char ip_ttl;		/* time to live */
	u_char ip_p;		/* protocol */
	u_short ip_sum;		/* checksum */
	u_int ip_src,ip_dst; /* source and dest address */
};
#define IP_HL(ip)		(((ip)->ip_vhl) & 0x0f)
#define IP_V(ip)		(((ip)->ip_vhl) >> 4)

/* TCP header */
struct sniff_tcp {
	u_short th_sport;	/* source port */
	u_short th_dport;	/* destination port */
	u_int th_seq;		/* sequence number */
	u_int th_ack;		/* acknowledgement number */

	u_char th_offx2;	/* data offset, rsvd */
#define TH_OFF(th)	(((th)->th_offx2 & 0xf0) >> 4)
	u_char th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
#define TH_FLAGS (TH_FIN|TH_SYN|TH_RST|TH_ACK|TH_URG|TH_ECE|TH_CWR)
	u_short th_win;		/* window */
	u_short th_sum;		/* checksum */
	u_short th_urp;		/* urgent pointer */
};

int main(int argc, char *argv[])
{
  pcap_t *handle;			/* Session handle */
  char dev[PCAP_ERRBUF_SIZE];			/* The device to sniff on */
  char errbuf[PCAP_ERRBUF_SIZE];	/* Error string */
  struct bpf_program fp;		/* The compiled filter */
  char filter_exp[] = "src port 10000";	/* The filter expression */
  bpf_u_int32 mask;		/* Our netmask */
  bpf_u_int32 net;		/* Our IP */
  struct pcap_pkthdr header;	/* The header that pcap gives us */
  const u_char *packet;		/* The actual packet */
  int i, j, k, len; 
  	/* ethernet headers are always exactly 14 bytes */
	#define SIZE_ETHERNET 14
	const struct sniff_ethernet *ethernet; /* The ethernet header */
	const struct sniff_ip *ip; /* The IP header */
	const struct sniff_tcp *tcp; /* The TCP header */
	const unsigned char *payload; /* Packet payload */

	u_int size_ip;
	u_int size_tcp;
	unsigned int * u; 
	float * f; 

  /* Define the device */
  strcpy(dev, "eth1"); 
  /*dev = pcap_lookupdev(errbuf);
  if (dev == NULL) {
	  fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
	  return(2);
  }*/
  /* Find the properties for the device */
  if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
	  fprintf(stderr, "Couldn't get netmask for device %s: %s\n", dev, errbuf);
	  net = 0;
	  mask = 0;
  }else{
	  printf("net %x mask %x\n", net, mask); 
  }
  /* Open the session in promiscuous mode */
  handle = pcap_open_live(dev, 1024, 1, 10, errbuf); //second to last argument: timeout. 
  if (handle == NULL) {
	  fprintf(stderr, "Couldn't open device %s: %s\n", "eth1", errbuf);
	  return(2);
  }
  /* Compile and apply the filter */
  if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
	  fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
	  return(2);
  }
  if (pcap_setfilter(handle, &fp) == -1) {
	  fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
	  return(2);
  }
  /* Grab a packet */
  for(i=0; i<400;){
    packet = pcap_next(handle, &header);
    /* Print its length */
    if(packet){
      //printf("Jacked a packet with length of [%d]\n", header.len);
		i++; 
		
		ethernet = (struct sniff_ethernet*)(packet);
		ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
		size_ip = IP_HL(ip)*4;
		//printf("size_ip = %d; tl = %d\n", size_ip, htons(ip->ip_len)); 
		if (size_ip < 20) {
			printf("   * Invalid IP header length: %u bytes\n", size_ip);
			return;
		}
		tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
		size_tcp = TH_OFF(tcp)*4;
		//printf("from %d to %d flags %02x ", htons(tcp->th_sport), htons(tcp->th_dport), tcp->th_flags); 
		/*if(tcp->th_flags & TH_FIN)printf("fin ");
		if(tcp->th_flags & TH_SYN)printf("syn "); 
		if(tcp->th_flags & TH_RST)printf("rst "); 
		if(tcp->th_flags & TH_PUSH)printf("psh "); 
		if(tcp->th_flags & TH_ACK)printf("ack "); 
		if(tcp->th_flags & TH_URG)printf("urg "); 
		printf("\n"); */
		if (size_tcp >= 20) {
			k++; 
			payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
			u = (unsigned int*)payload; 
			f = (float*)payload; 
			len = header.len - SIZE_ETHERNET - size_ip - size_tcp; 
			if(0){
				printf("%ld.%ld\t:", header.ts.tv_sec, header.ts.tv_usec); 
				for(j=0; j<len; j++){
					printf("%02x ", *payload++); 
				}
				printf("\n");
			}
			if(u[0] == 0x1f && u[1] == 0x050001){
				k = 0;  
			}
			if(k == 1){
				printf("timestamp: %d\n", u[1]); 
			}
			if(k == 2){
				printf("float val: "); 
				for(j=0; j<(len/4);j++){
					printf("%f ", *f++); 
				}
				printf("\n"); 
			}
		}else{
			printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
		}
    }
  }
  /* And close the session */
  pcap_close(handle);
  return(0);
}