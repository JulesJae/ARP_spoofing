# include "../includes/mitm.h"

static char	*get_current_arg(t_env *env)
{
	char	*cur;

	if (env->argind == env->ac)
		exit_usage();
	cur = env->argcur;
	env->argind++;
	env->argcur = env->av[env->argind];
	return cur;
}

static char	get_current_opt(t_env *env)
{
	char	opt;

	opt = env->argcur[1];
	env->argind++;
	env->argcur = env->av[env->argind];
	return opt;
}

static int	numeric_value(char *s)
{
	int		ret;

	ret = ft_atoi(s);
	if (ret == 0 || !is_numeric_str(s))
	{
		printf("%s: ", s);
		exit_error("Bad value");
	}
	return (ret);
}

static void	cp_if_name(t_env *env)
{
	char	*if_name;
	int		len;

	if_name = get_current_arg(env);
	len = ft_strlen(if_name);
	if (len >= IF_NAME_LEN)
	{
		printf("%s: ", if_name);
		exit_error("too long");
	}
	ft_memcpy(env->if_name, if_name, len);
	env->if_name[len] = '\0';
}

static void	parse_opt(t_env *env)
{
	char	opt;

	while(env->argcur && env->argcur[0] == '-')
	{
		opt = get_current_opt(env);
		if (opt == 'f')
			env->flags |= FL_FLOOD;
		else if (opt == 'v')
			env->flags |= FL_VERBOSE;
		else if (opt == 'c')
		{
			env->flags |= FL_COUNT;
			env->count = numeric_value(get_current_arg(env));
		} else if (opt == 'i')
		{
			env->flags |= FL_INTERVAL;
			env->interval = numeric_value(get_current_arg(env));

		} else if (opt == 'd')
		{
			env->flags |= FL_INTERFACE;
			cp_if_name(env);
		}
	}
}

void		parse_args(t_env *env)
{
	parse_opt(env);
	get_ip(get_current_arg(env), &env->sip);
	get_ha(get_current_arg(env), &env->smac);
	get_ip(get_current_arg(env), &env->tip);
	get_ha(get_current_arg(env), &env->tmac);
}