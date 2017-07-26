/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:50:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 18:46:14 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_put_lines(t_mem_block *lines)
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
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
}

static void	ft_put_tubes(t_room *room)
{
	uint32_t	i;
	t_mem_block	*data;

	i = 0;
	data = room->tubes;
	printf("block->offset: %llu\n", data->offset);
	while (i * sizeof(t_room*) < data->offset)
	{
		printf("	tube: %s \n", (*((t_room**)data->block + i))->name);
		i++;
		if (i * sizeof(t_room) >= data->offset && data->next)
		{
			data = data->next;
			i = 0;
		}
	}
}

static void	ft_put_rooms(t_lem_in_data *lem_in_data)
{
	uint32_t	i;
	t_mem_block	*data;

	i = 0;
	data = lem_in_data->data;
	while (i * sizeof(t_room) < data->offset)
	{
		printf("room: %s has %u tubes: \n", ((t_room*)data->block + i)->name
			, ((t_room*)data->block + i)->nbr_tube);
		ft_put_tubes(((t_room*)data->block + i));
		i++;
		if (i * sizeof(t_room) >= data->offset && data->next)
		{
			data = data->next;
			i = 0;
		}
	}
}

int			main(void)
{
	t_lem_in_data	*lem_in_data;

	lem_in_data = ft_parse();
	ft_check_integrity(lem_in_data);
	(void)ft_put_lines(lem_in_data->lines);
	fflush(NULL);
	(void)ft_put_rooms;
	ft_solve(lem_in_data);
	return (0);
}
