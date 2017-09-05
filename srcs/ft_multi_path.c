/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 04:37:45 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/05 07:03:31 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	i = 0;
	index = stack[0].index;
	while (i * sizeof(t_room*) < tmp->offset && i < index)
	{
		i++;
		if (i * sizeof(t_room*) >= tmp->offset && tmp->next)
		{
			index -= i;
			tmp = tmp->next;
			i = 0;
		}
	}
	index = stack[0].index;
	while (i * sizeof(t_room*) < tmp->offset)
	{
		index++;
//		printf("check next_room: %s, used: %u\n", (*((t_room**)tmp->block + i))->name, (*((t_room**)tmp->block + i))->used);
		if (/* (*((t_room**)tmp->block + i))->distance < stack[0].room->distance &&  */(*((t_room**)tmp->block + i))->distance < distance
			&& (*((t_room**)tmp->block + i))->flow.capacity > (*((t_room**)tmp->block + i))->flow.flow && (*((t_room**)tmp->block + i))->used == 1)
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

inline static int32_t	ft_make_path_stack(t_solve_stack *stack)
{
	uint32_t	i;
	t_room		*room;

	i = 1;
	room = stack[0].room;
	stack[0].index = 0;
	room->used = 0;
//	printf("Start: \n");
	while (42)
	{
		while (room->attribute != START)
		{
//			printf("%s: %u\n", room->name, i - 1);
			if (!(stack[i].room = ft_get_next_available_room(stack + i - 1)))
				break ;
//			printf("%s ", stack[i].room->name);
			stack[i].room->used = 0;
			stack[i].index = 0;
			room = stack[i++].room;
		}
		if (room->attribute == START)
			return (1);
		room->used = 1;
//		stack[i].index = 0;
		i--;
		if (i == 0)
			return (0);
	}
}

inline static uint32_t	ft_get_max_flow(t_solve_stack *stack)
{
	uint32_t	max_flow;
	uint32_t	tmp;
	uint32_t	i;

	max_flow = stack[1].room->flow.capacity - stack[1].room->flow.flow;
	i = 1;
	while (stack[i - 1].room->attribute != START)
	{
		tmp = stack[i].room->flow.capacity - stack[i].room->flow.flow;
		if (tmp < max_flow)
			max_flow = tmp;
		i++;
	}
	return (max_flow);
}

inline static void		ft_add_flow_to_path(t_solve_stack *stack, uint32_t flow)
{
	uint32_t	i;

	i = 1;
	stack[0].room->flow.flow += flow;
	while (stack[i - 1].room->attribute != START)
	{
		stack[i].room->flow.flow += flow;
		stack[i].room->used = 1;
		i++;
	}
	stack[i - 1].room->used = 1; // gros bug on frere sur simple
}

inline static void		ft_put_stack(t_solve_stack *stack)
{
	uint32_t	i;

	i = 0;
	printf("Made path: ");
	while (42)
	{
		printf("%s ", stack[i].room->name);
		i++;
		if (stack[i].room->attribute == START)
			break ;
	}
	printf("\n");
}

inline static void		ft_put_capacities(t_mem_block *data)
{
	uint64_t	i;

	i = 0;
	while (i * sizeof(t_room) < data->offset)
	{
		printf("%s: capacity: %u, flow: %u\n", ((t_room*)data->block + i)->name, ((t_room*)data->block + i)->flow.capacity, ((t_room*)data->block + i)->flow.flow);
		i++;
	}
}

void		ft_multi_path(t_lem_in_data *lem_in_data)
{
	t_room			*room;
	t_solve_stack	*stack;
	uint32_t		lem_nbr;
	uint32_t		flow;
	uint32_t		distance_plage;

	if (!(stack = (t_solve_stack*)ft_memalloc(sizeof(t_solve_stack)
						* lem_in_data->room_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	lem_in_data->end->flow.capacity = ~0U;
	lem_in_data->start->flow.capacity = ~0U;
	stack[0].room = lem_in_data->end;
	room = lem_in_data->end;
	lem_nbr = lem_in_data->lem_nbr;
	distance_plage = 0;
	while (lem_nbr)
	{
		if (!(ft_make_path_stack(stack)))
			break;
		ft_put_stack(stack);
		ft_add_flow_to_path(stack, (flow = ft_get_max_flow(stack)));
		if (lem_nbr < flow)
			lem_nbr = 0;
		else
			lem_nbr -= flow;
	}
//	ft_put_capacities(lem_in_data->data);
	free(stack);
//	ft_put_multi_path(lem_in_data);
}
