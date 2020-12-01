#include "../includes/mitm.h"

int			can_send = 1;

void		exit_usage()
{
	printf("Usage: ft_malcolm [Options] <source_ip> <source_mac> <target_ip> <target_mac>\n"
		"---			Options			---\n"
		"-c Number	stop after sending Number arp packets\n"
		"-i Number	wait Number second between sending each packet\n"
		"-d Device	listen and send arp request on Device\n"
		"-f		flood the target\n"
		"-v		show content of the arp packets send and receive\n"
	);
	exit(0);
}

static void	get_if(t_env *env)
{
	struct ifaddrs		*ifap;
	struct ifaddrs		*ifaps;
	int					family;

	getifaddrs(&ifaps);
	ifap = ifaps;
	while (ifap)
	{
		family = ifap->ifa_addr->sa_family;
		if (family == AF_INET)
		{
			if (!(ifap->ifa_flags & IFF_LOOPBACK) && ifap->ifa_flags & (IFF_UP | IFF_RUNNING))
			{
				if (!(env->flags & FL_INTERFACE) || !ft_strcmp(ifap->ifa_name, env->if_name))
				{
					ft_memcpy(env->if_name, ifap->ifa_name, ft_strlen(ifap->ifa_name));
					printf("Interface %s is running\n", env->if_name);
					break;
				}
			}
		}
		ifap = ifap->ifa_next;
	}
	freeifaddrs(ifaps);
	if (ifap == NULL)
	{
		if (env->flags & FL_INTERFACE)
			printf("%s: ", env->if_name);
		exit_error("No interface is running");
	}
}

void		sig_handler(int signum)
{
	if (signum == SIGALRM)
		can_send = 1;
}

int			main(int ac, char *av[])
{
	t_env	env;

	env.argcur = av[1];
	env.argind = 1;
	env.ac = ac;
	env.av = av;
	env.flags = 0;
	env.interval = 1;
	env.count = 1;
	if (ac < 5)
		exit_usage();
	if (getuid() != 0)
		exit_error("Permission needed");
	parse_args(&env);
	get_if(&env);
	if ((env.socketfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1)
		exit_error("Socket error");
	signal(SIGALRM, sig_handler);
	configure_send(&env);
	arp_spoof(&env);
}