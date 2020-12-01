#include "../includes/mitm.h"

bool			is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

bool			is_numeric_str(char *s)
{
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		if (!is_numeric(s[i]))
			return false;
		i++;
	}
	return true;
}

bool			is_hex(char c)
{
	if (is_numeric(c) || (c >= 'a' && c <= 'f'))
		return true;
	return false;
}

bool			is_ha(char *s)
{
	int		point;
	int		i;

	point = 0;
	i = 0;
	while (*s)
	{
		if (is_hex(*s))
			i++;
		else if (*s == ':')
		{
			if (i != 2)
				return false;
			point++;
			i = 0;
		} else
			return false;
		s++;
	}
	return (i == 2 && point == 5) ? true : false;
}

bool			is_ip(char *s)
{
	int		point;
	int		i;

	i = 0;
	point = 0;
	while (*s)
	{
		if (is_numeric(*s))
			i++;
		else if (*s == '.')
		{
			if (i < 1 || i > 3)
				return false;
			point++;
			i = 0;
		} else
			return false;
		s++;
	}
	if (point == 3 && i > 0 && i < 4)
		return true;
	return false;
}
