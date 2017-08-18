/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 02:19:49 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/18 02:20:22 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline void	ft_put_lines(t_mem_block *lines)
{
	uint32_t	i;
	t_mem_block	*data;

	i = 0;
	data = lines;
	while (i * sizeof(char*) < data->offset)
	{
		ft_static_put(*((char**)data->block + i)
					, (uint32_t)ft_strlen(*((char**)data->block + i)), 0);
		ft_static_put("\n", 1, 0);
		i++;
		if (i * sizeof(t_room) >= data->offset && data->next)
		{
			data = data->next;
			i = 0;
		}
	}
	ft_static_put("\n", 1, 0);
}
