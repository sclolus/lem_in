/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 05:38:27 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/04 23:18:20 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>//

inline static void		ft_print_path(t_solve_stack *stack, int32_t nbr
									, uint32_t u, uint32_t i)
{
	static char	buffer[11];
	uint32_t	index;
	int64_t		divider;
	uint32_t	len;

	index = 0;
	divider = 1;
	len = 1;
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
	ft_static_put(stack[i - u].room->name, stack[i - u].room->len, 0);
	ft_static_put(" ", 1, 0);
}

inline static void		ft_print_stack(t_lem_in_data *lem_in_data
							, t_solve_stack *stack, uint64_t index)
{
	uint32_t	lem_nbr;
	uint32_t	i;
	uint32_t	u;

	lem_nbr = lem_in_data->lem_nbr;
	i = 1;
	while (lem_nbr != 0)
	{
		u = 0;
		while (u < i && u < lem_nbr)
		{
			ft_print_path(stack, (int)((int)(lem_in_data->lem_nbr - lem_nbr)
							+ (int)u + 1), u, i);
			u++;
		}
		ft_static_put("\n", 1, 0);
		if (i != index - 1)
			i++;
		else
			lem_nbr--;
	}
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
}

inline static void		ft_show_path(t_lem_in_data __attribute__((unused))*lem_in_data
							, t_solve_stack *stack, uint64_t index)
{
	uint32_t	i;

	i = 1;
	ft_static_put(LEM_SHOW_PATH, sizeof(LEM_SHOW_PATH), 0);
	while (i < index)
	{
		ft_static_put(stack[i].room->name, stack[i].room->len, 0);
		ft_static_put("\n", 1, 0);
		i++;
	}
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
}

/* inline static uint64_t	ft_get_nbr_path(t_lem_in_data *lem_in_data) */
/* { */

/* } */

/* inline static void	ft_print_stack(t_lem_in_data *lem_in_data) */
/* { */
/* 	t_room		*base; */
/* 	uint64_t	i; */

/* 	base = lem_in_data->end; */
/* 	i = 0; */
/* 	while (i < base->nbr_tube) */
/* 	{ */
/* 		base->tubes[i] */
/* 		i++; */
/* 	} */
/* } */

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
		if (/* (*((t_room**)tmp->block + i))->distance < stack[0].room->distance && */ (*((t_room**)tmp->block + i))->distance < distance
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
	while (stack[i].room->attribute != START)
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
	while (stack[i].room->attribute != START)
	{
		stack[i].room->flow.flow += flow;
		stack[i].room->used = 1;
		i++;
	}
	stack[i].room->used = 1; // gros bug on frere sur simple
}

inline static void		ft_put_stack(t_solve_stack *stack)
{
	uint32_t	i;

	i = 0;
	printf("Made path: ");
	while (42)
	{
		printf("%s ", stack[i].room->name);
		if (stack[i].room->attribute == START)
			break ;
		i++;
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

inline static void		ft_multi_path(t_lem_in_data *lem_in_data)
{
	t_room			*room;
	t_solve_stack	*stack;
	uint32_t		lem_nbr;
	uint32_t		flow;

	if (!(stack = (t_solve_stack*)ft_memalloc(sizeof(t_solve_stack)
						* lem_in_data->room_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	lem_in_data->end->flow.capacity = ~0U;
	lem_in_data->start->flow.capacity = ~0U;
	stack[0].room = lem_in_data->end;
	room = lem_in_data->end;
	lem_nbr = lem_in_data->lem_nbr;
	while (ft_make_path_stack(stack) && lem_nbr)
	{
		ft_put_stack(stack);
		ft_add_flow_to_path(stack, (flow = ft_get_max_flow(stack)));
		if (lem_nbr < flow)
			lem_nbr = 0;
		else
			lem_nbr -= flow;
	}
//	ft_put_capacities(lem_in_data->data);
	free(stack);
}

void					ft_put_solution(t_lem_in_data *lem_in_data
						, t_solve_stack *stack, uint64_t index)
{
	if (!lem_in_data->flags.bits.quiet)
		ft_put_lines(lem_in_data->lines);
	ft_print_stack(lem_in_data, stack, index + 1);
	if (lem_in_data->flags.bits.show_path)
		ft_show_path(lem_in_data, stack, index + 1);
	ft_multi_path(lem_in_data);
	exit(EXIT_SUCCESS);
}
