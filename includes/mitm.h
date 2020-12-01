#ifndef MITM_H
# define MITM_H

# include <sys/socket.h>
# include <sys/types.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/ether.h>
# include <netinet/if_ether.h>
# include <netinet/ip.h>
# include <net/if.h>
# include <sys/ioctl.h>
# include <net/if_arp.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <ifaddrs.h>
# include <string.h>
# include <stdbool.h>
# include <netpacket/packet.h>
# include <sys/ioctl.h>
# include <signal.h>

# define FL_FLOOD 1
# define FL_COUNT 1 << 1
# define FL_INTERVAL 1 << 2
# define FL_VERBOSE 1 << 3
# define FL_INTERFACE 1 << 4

# define ETHER_HRD_LEN 6
# define IP_PROTO_LEN 4
# define IF_NAME_LEN 16
# define MTU 1500
# define ARP_SIZE 42

extern int					can_send;

struct						s_arphdr
{
	unsigned short			hrd;
	uint16_t				pro;
	unsigned char			hlen;
	unsigned char			plen;
	uint16_t				op;
	unsigned char			sha[ETHER_HRD_LEN];
	unsigned char			spa[IP_PROTO_LEN];
	unsigned char			dha[ETHER_HRD_LEN];
	unsigned char			dpa[IP_PROTO_LEN];
};

struct						s_ip
{
	char					*s;
	struct in_addr			add;
};

struct						s_mac
{
	char					*s;
	unsigned char			add[ETHER_HRD_LEN];
};

typedef struct				s_env
{
	char					*argcur;
	int						ac;
	int						argind;
	char					**av;
	struct s_ip				sip;
	struct s_ip				tip;
	struct s_mac			smac;
	struct s_mac			tmac;
	struct sockaddr_ll		sa;
	struct sockaddr_ll		sa_rcv;
	struct ethhdr			*eth;
	struct s_arphdr			*arp;
	unsigned char			flags;
	char					if_name[IF_NAME_LEN];
	int						if_index;
	unsigned char			if_ha[ETHER_HRD_LEN];
	int						socketfd;
	char					sendbuf[ARP_SIZE];
	char					recvbuf[MTU];
	int						count;
	int						interval;
}							t_env;

void						exit_error(char *s);
void						exit_usage();
void						get_ip(char *s, struct s_ip*);
void						get_ha(char *s, struct s_mac *ha);
void						parse_args(t_env *env);
void						configure_send(t_env *env);
void						print_arp(struct s_arphdr *arp);
void						arp_spoof(t_env *env);

/* ---------------------- LIB ---------------------- */

bool						is_numeric(char c);
bool						is_numeric_str(char *s);
bool						is_hex(char c);
bool						is_ip(char *s);
bool						is_ha(char *s);
void						ft_memcpy(void *dest, void *src, size_t len);
void						ft_bzero(void *p, size_t len);
int							ft_strlen(char *s);
int							ft_atoi(const char *str);
int							ft_strcmp(const char *s1, const char *s2);

#endif