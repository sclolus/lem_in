/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 04:37:45 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/05 12:03:03 by sclolus          ###   ########.fr       */
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

inline static t_room	*ft_get_next_flowed_room(t_solve_stack *stack, uint32_t __attribute__((unused))distance_plage)
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
		if ((*((t_room**)tmp->block + i))->distance < distance
			&& (*((t_room**)tmp->block + i))->flow.capacity > 0 && (*((t_room**)tmp->block + i))->used == 1)
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

inline static uint32_t	ft_make_path_stack(t_solve_stack *stack, uint32_t distance_plage)
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
			if (!(stack[i].room = ft_get_next_available_room(stack + i - 1)) && !distance_plage)
				break ;
			else if (!(stack[i].room))
			{
				if (i == 1 || !(stack[i].room = ft_get_next_flowed_room(stack + i - 1, distance_plage--)))
					break ;
			}
			stack[i].room->used = 0;
			stack[i].index = 0;
			room = stack[i++].room;
		}
		if (room->attribute == START)
			return (i);
		room->used = 1;
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
		if (!tmp)
			break ;
		else if (tmp < max_flow)
			max_flow = tmp;
		i++;
	}
	return (max_flow);
}

inline static void		ft_add_flow_to_path(t_solve_stack *stack, uint32_t flow)
{
	uint32_t	i;
	uint32_t	u;

	i = 1;
	stack[0].room->flow.flow += flow;
	while (stack[i - 1].room->attribute != START)
	{
		if (stack[i].room->flow.flow + flow > stack[i].room->flow.capacity)
			break ;
		stack[i].room->flow.flow += flow;
		stack[i].room->used = 1;
		i++;
	}
	stack[i - 1].room->used = 1; // gros bug on frere sur simple
	stack[0].room->used = 1;
/* 	u = i - 1; */
/* 	while (i > 0) */
/* 	{ */
/* 		i--; */
/* 		stack[i].room->distance = u - i; */
/* 	} */
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
	uint32_t		len_path;

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
		if (!(len_path = ft_make_path_stack(stack, distance_plage)))
		{
			distance_plage++;
			if (distance_plage >= lem_in_data->room_nbr)
				break;
			continue ;
		}
		(void)ft_put_stack;
		ft_put_stack(stack);
		ft_add_flow_to_path(stack, (flow = ft_get_max_flow(stack)));
		if (lem_nbr < flow || !flow)
			lem_nbr = 0;
		else
			lem_nbr -= flow;
	}
	ft_put_capacities(lem_in_data->data);
	free(stack);
	ft_reset_dijkstra_values(lem_in_data->data, 0);
	ft_dijkstra(lem_in_data, lem_in_data->end);
	ft_put_multi_path(lem_in_data);
}
