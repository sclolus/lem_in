/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_new_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 14:12:18 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 19:03:58 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int32_t			ft_get_new_cmd(char *line
						, t_lem_in_data __attribute__((unused)) *lem_in_data)
{
	static t_cmd	cmd_tab[] = {
		{"start", START, {0}},
		{"end", END, {0}}};
	uint32_t		i;

	i = 0;
	while (i < sizeof(cmd_tab) / sizeof(t_cmd))
	{
		if (ft_strequ(line + 2, cmd_tab[i].identifier))
		{
			if (ft_get_set_states()[i])
				return (0);
			*ft_get_last_attribute() = cmd_tab[i].attr;
			break ;
		}
		i++;
	}
	return (1);
}
