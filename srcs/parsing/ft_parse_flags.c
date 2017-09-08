/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 13:31:46 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 06:08:58 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

NORETURN			ft_flags_usage(char invalid_flag)
{
	static char	buf[2];

	buf[0] = invalid_flag;
	ft_error(2, (char*[]){ERR_INVALID_FLAG, buf}, EXIT_FAILURE);
	ft_error_exit(1, (char*[]){FLAG_USAGE}, EXIT_FAILURE);
}

inline t_lem_flags	ft_parse_flags(char *argv)
{
	static char	flags_char[] = {'d', 'v', 'q', 's', 'm'};
	t_lem_flags	flags;
	uint32_t	i;
	uint32_t	u;

	flags.flags = 0;
	if (*argv != '-' || (argv[0] && !argv[1]))
		ft_error_exit(1, (char*[]){INVALID_FLAGS_FORMAT}, EXIT_FAILURE);
	u = 1;
	while (argv[u])
	{
		i = 0;
		while (i < sizeof(flags_char) / sizeof(char))
		{
			if (flags_char[i] == argv[u])
			{
				flags.flags |= 1 << i;
				break ;
			}
			if (++i >= sizeof(flags_char) / sizeof(char))
				ft_flags_usage(argv[u]);
		}
		u++;
	}
	return (flags);
}
