/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_new_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 14:12:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 23:10:20 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline int32_t	ft_parse_modified_capacity(char *line)
{
	uint32_t	i;
	uint32_t	u;

	i = sizeof("##capacity ") - 1;
	u = i;
	while (line[u])
	{
		if (!(ft_strchr(DECIMAL_SET + 1, line[u])))
			return (0);
		u++;
	}
	*ft_get_last_modified_capacity() = (uint32_t)ft_atoi(line + i);
	return (1);
}

int32_t			ft_get_new_cmd(char *line
						, t_lem_in_data __attribute__((unused)) *lem_in_data)
{
	static t_cmd	cmd_tab[] = {
		{"start", START, sizeof("start")},
		{"end", END, sizeof("end")},
		{"capacity", CAPACITY, sizeof("capacity")}};
	uint32_t		i;

	i = 0;
	while (i < sizeof(cmd_tab) / sizeof(t_cmd))
	{
		if (ft_strnequ(line + 2, cmd_tab[i].identifier, cmd_tab[i].len - 1))
		{
			if (ft_get_set_states()[i])
				return (0);
			*ft_get_last_attribute() = cmd_tab[i].attr;
			if (cmd_tab[i].attr == CAPACITY)
			{
				return (ft_parse_modified_capacity(line));
			}
			break ;
		}
		i++;
	}
	return (1);
}
