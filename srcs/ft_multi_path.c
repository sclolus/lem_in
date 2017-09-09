/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 04:37:45 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/09 05:34:40 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static uint64_t	ft_get_t_mem_block_room_index(t_mem_block **tmp
									, t_solve_stack *stack, uint64_t *tmp_index)
{
	uint64_t	i;
	uint64_t	index;

	index = stack[0].index;
	i = 0;
	while (i * sizeof(t_room*) < (*tmp)->offset && i < index)
	{
		i++;
		if (i * sizeof(t_room*) >= (*tmp)->offset && (*tmp)->next)
		{
			index -= i;
			(*tmp) = (*tmp)->next;
			i = 0;
		}
	}
	*tmp_index = stack[0].index;
	return (i);
}

inline static t_room	*ft_get_next_available_room(t_solve_stack *stack)
{
	t_mem_block		*tmp;
	t_room			*next;
	uint64_t		distance;
	uint64_t		i;
	uint64_t		index;

	tmp = stack[0].room->tubes;
	next = NULL;
	distance = ~0UL;
	i = ft_get_t_mem_block_room_index(&tmp, stack, &index);
	while (i * sizeof(t_room*) < tmp->offset && ++index)
	{
		if ((*((t_room**)tmp->block + i))->distance < distance
	&& (*((t_room**)tmp->block + i))->flow.capacity > (*((t_room**)tmp->block
	+ i))->flow.flow && (*((t_room**)tmp->block + i))->used == 1)
		{
			next = *((t_room**)tmp->block + i);
			distance = (*((t_room**)tmp->block + i))->distance;
			stack[0].index = index;
		}
		i++;
		if (i * sizeof(t_room*) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
	return (next);
}

inline static uint32_t	ft_make_path_stack(t_solve_stack *stack)
{
	uint32_t	i;
	t_room		*room;

	i = 1;
	room = stack[0].room;
	stack[0].index = 0;
	room->used = 0;
	while (42)
	{
		while (room->attribute != START)
		{
			if (!(stack[i].room = ft_get_next_available_room(stack + i - 1)))
				break ;
			stack[i].room->used = 0;
			stack[i].index = 0;
			room = stack[i++].room;
		}
		if (room->attribute == START)
			return (i);
		room->used = 1;
		if (--i == 0)
			return (0);
	}
}

uint32_t				*ft_multi_path(t_lem_in_data *lem_in_data
									, uint32_t nbr_path_to_find)
{
	t_list			*paths;
	t_solve_stack	*stack;
	uint32_t		lem_nbr;
	uint32_t		len_path;
	uint32_t		nbr_path;

	if (!(stack = (t_solve_stack*)ft_memalloc(sizeof(t_solve_stack)
						* lem_in_data->room_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	stack[0].room = lem_in_data->end;
	lem_nbr = lem_in_data->lem_nbr;
	nbr_path = 0;
	paths = NULL;
	while (lem_nbr && nbr_path_to_find--)
	{
		if (!(len_path = ft_make_path_stack(stack)))
			break ;
		ft_add_flow_to_path(stack, ft_get_max_flow(stack), &lem_nbr);
		nbr_path++;
		ft_add_one_path(&paths, stack, len_path);
	}
	free(stack);
	return (ft_put_multi_path(lem_in_data, paths, nbr_path));
}
