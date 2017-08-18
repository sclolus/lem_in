/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:50:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/18 02:24:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* static void	ft_put_tubes(t_room *room) */
/* { */
/* 	uint32_t	i; */
/* 	t_mem_block	*data; */

/* 	i = 0; */
/* 	data = room->tubes; */
/* 	printf("block->offset: %llu\n", data->offset); */
/* 	while (i * sizeof(t_room*) < data->offset) */
/* 	{ */
/* 		printf("	tube: %s \n", (*((t_room**)data->block + i))->name); */
/* 		i++; */
/* 		if (i * sizeof(t_room) >= data->offset && data->next) */
/* 		{ */
/* 			data = data->next; */
/* 			i = 0; */
/* 		} */
/* 	} */
/* } */

/* static void	ft_put_rooms(t_lem_in_data *lem_in_data) */
/* { */
/* 	uint32_t	i; */
/* 	t_mem_block	*data; */

/* 	i = 0; */
/* 	data = lem_in_data->data; */
/* 	while (i * sizeof(t_room) < data->offset) */
/* 	{ */
/* 		printf("room: %s has %u tubes: \n", ((t_room*)data->block + i)->name */
/* 			, ((t_room*)data->block + i)->nbr_tube); */
/* 		ft_put_tubes(((t_room*)data->block + i)); */
/* 		i++; */
/* 		if (i * sizeof(t_room) >= data->offset && data->next) */
/* 		{ */
/* 			data = data->next; */
/* 			i = 0; */
/* 		} */
/* 	} */
/* } */

int			main(void)
{
	t_lem_in_data	*lem_in_data;

	lem_in_data = ft_parse();
	ft_check_integrity(lem_in_data);
	ft_solve(lem_in_data);
	return (0);
}
