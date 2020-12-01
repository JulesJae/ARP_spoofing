#include "../includes/mitm.h"

static void				convert_ha(char *s, struct s_mac *ha);
static unsigned char	ft_atox(char *s);

void					get_ip(char *s, struct s_ip *ip)
{
	struct hostent	*host;
	char			buff[INET_ADDRSTRLEN];

	if (is_ip(s) == false || (host = gethostbyname(s)) == NULL)
	{
		printf("%s: ", s);
		exit_error("Bad host or IP address");
	}
	ip->s = s;
	inet_pton(AF_INET, s, &ip->add);
}

void					get_ha(char *s, struct s_mac *ha)
{
	if (is_ha(s) == false)
	{
		printf("%s: ", s);
		exit_error("Bad hardware address");
	}
	ha->s = s;
	convert_ha(s, ha);
}

void					exit_error(char *s)
{
	printf("%s\n", s);
	// perror(s);
	exit (0);
}

void					ft_memcpy(void *dest, void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char*)src;
	d = (char*)dest;
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
}

void					ft_bzero(void *p, size_t len)
{
	size_t		i;
	char		*data;

	i = 0;
	data = (char*)p;
	while (i < len)
	{
		data[i] = '\0';
		i++;
	}
}

int						ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int						ft_strlen(char *s)
{
	int		i = 0;

	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

int						ft_atoi(const char *str)
{
		int		res;
		int		negative;

		negative = 1;
		res = 0;
		while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
			*str == '\v' || *str == '\f' || *str == '\r'))
			++str;
		if (*str == '-')
			negative = -1;
		if (*str == '-' || *str == '+')
			++str;
		while (*str && *str >= '0' && *str <= '9')
		{
			res = res * 10 + (*str - 48);
			++str;
		}
		return (res * negative);
}

static void				convert_ha(char *s, struct s_mac *ha)
{
	char	buf[3];
	int		i;

	i = 0;
	while (*s)
	{
		ft_memcpy(buf, s, 2);
		buf[2] = '\0';
		ha->add[i++] = ft_atox(buf);
		s += 2;
		if (*s == ':')
			s++;
	}
}

static unsigned char	ft_atox(char *s)
{
	char			base[] = "0123456789abcdef";
	unsigned char	ret;
	int				i;

	i = 0;
	while (*s != base[i])
		i++;
	ret = i * 16;
	s++;
	i = 0;
	while (*s != base[i])
		i++;
	ret += i;
	return ret;
}