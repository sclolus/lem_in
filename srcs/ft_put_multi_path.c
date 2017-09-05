/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_multi_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 04:39:40 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/05 11:48:32 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static t_room	*ft_get_lem_path(t_lem *lem)
{
	t_mem_block		*tmp;
	t_room			*next;
	uint64_t		i;
	uint64_t		distance;


	tmp = lem->room->tubes;
	distance = ~0UL;
	next = NULL;
	i = 0;
//	printf("-----Start------ room->distance: %u\n", lem->room->distance);
	while (i * sizeof(t_room*) < tmp->offset)
	{
//		printf("%s: capacity: %u, flow: %u, distance: %llu\n", (*((t_room**)tmp->block + i))->name, (*((t_room**)tmp->block + i))->flow.capacity, (*((t_room**)tmp->block + i))->flow.flow, (*((t_room**)tmp->block + i))->distance);
		if ((*((t_room**)tmp->block + i))->distance < distance &&
			(*((t_room**)tmp->block + i))->flow.flow && (*((t_room**)tmp->block + i))->flow.capacity)
		{
			distance = (*((t_room**)tmp->block + i))->distance;
			next = (*((t_room**)tmp->block + i));
//			return ((*((t_room**)tmp->block + i)));
		}
		i++;
		if (i * sizeof(t_room*) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
//			printf("selected ----> %s: capacity: %u\n", (*((t_room**)tmp->block + i))->name, (*((t_room**)tmp->block + i))->flow.capacity);
/* 	if (next) */
/* 		printf("selected ----> %s: capacity: %u\n", next->name, next->flow.capacity); */
/* 	else */
/* 		printf("lem->index: %llu is blocked \n", lem->index); */
	return (next);
}

inline static void		ft_put_lem_move(t_lem *lem)
{
	static char	buffer[11];
	uint32_t	index;
	int64_t		divider;
	uint32_t	len;
	uint32_t	nbr;

	index = 0;
	divider = 1;
	len = 1;
	nbr = lem->index;
	while (divider * 10 <= nbr)
	{
		divider *= 10;
		len++;
	}
	while (nbr != 0 || !index)
	{
		buffer[len - index - 1] = nbr % 10 + '0';
		nbr /= 10;
		index++;
	}
	buffer[index] = '\0';
	ft_static_put("L", 1, 0);
	ft_static_put(buffer, index, 0);
	ft_static_put("-", 1, 0);
	ft_static_put(lem->room->name, lem->room->len, 0);
	ft_static_put(" ", 1, 0);

}

inline static void		ft_send_lem_to_path(t_lem *lem, t_room *room)
{
	if (!room)
		return ;
	lem->room->flow.capacity++;
	lem->room = room;
	room->flow.capacity--;
	ft_put_lem_move(lem);
}

void					ft_put_multi_path(t_lem_in_data *lem_in_data)
{
	t_lem		*lems;
	uint32_t	i;
	uint32_t	u;

	if (!(lems = ft_memalloc(sizeof(t_lem) * lem_in_data->lem_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	i = 0;
	while (i < lem_in_data->lem_nbr)
	{
		lems[i].room = lem_in_data->start;
		lems[i].index = i + 1;
		i++;
	}
	i = 0;
	while (i < lem_in_data->lem_nbr)
	{
		u = 0;
		while (u < lem_in_data->lem_nbr)
		{
			if (lems[u].room->attribute == END)
			{
				u++;
				continue ;
			}
			ft_send_lem_to_path(lems + u, ft_get_lem_path(lems + u));
			if (lems[u].room->attribute == END)
				i++;
			u++;
		}
		ft_static_put("\n", 1, 0);
	}
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
}
