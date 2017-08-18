/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 15:32:28 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/18 05:49:37 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static t_room		*ft_get_start_room(t_lem_in_data *lem_in_data)
{
	t_mem_block	*data;
	uint32_t	i;

	i = 0;
	data = lem_in_data->data;
	while (i * sizeof(t_room) < data->offset)
	{
		if (((t_room*)data->block + i)->attribute == START)
		{
			((t_room*)data->block + i)->used = 1;
			return (((t_room*)data->block + i));
		}
		i++;
		if (i * sizeof(t_room) >= data->offset && data->next)
		{
			data = data->next;
			i = 0;
		}
	}
	return (NULL);
}

static void					ft_cleanup_solve_stack(t_solve_stack **stack)
{
	free(*stack);
}

inline static t_room		*ft_get_next_room(t_solve_stack *stack
											, uint32_t index)
{
	t_mem_block	*tmp;
	uint32_t	tube_index;
	uint32_t	i;

	tmp = stack[index].room->tubes;
	tube_index = stack[index].tube_index;
	while (tube_index * sizeof(t_room*) > tmp->offset && tmp->next)
	{
		tube_index -= tmp->offset;
		tmp = tmp->next;
	}
	if (tube_index * sizeof(t_room*) > tmp->offset || !tmp)
		return (NULL);
	i = tube_index;
	while (i * sizeof(t_room*) < tmp->offset)
	{
		stack[index].tube_index++;
		if (!(*((t_room**)tmp->block + i))->used)
			return (*((t_room**)tmp->block + i));
		i++;
		if (i * sizeof(t_room*) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
	return (NULL);
}

void						ft_solve(t_lem_in_data *lem_in_data)
{
	t_solve_stack	*stack __attribute__((cleanup(ft_cleanup_solve_stack)));
	static uint32_t	i = 0;

	stack = NULL;
	if (!(stack = (t_solve_stack*)ft_memalloc(sizeof(t_solve_stack)
		* lem_in_data->room_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	if (!(stack[i].room = ft_get_start_room(lem_in_data)))
		ft_error_exit(1, (char*[]){LEM_IN_ERR}, EXIT_FAILURE);
	while (42)
	{
		while (stack[i].tube_index < stack[i].room->nbr_tube)
		{
			if (i + 1 == lem_in_data->room_nbr
				|| !(stack[i + 1].room = ft_get_next_room(stack, i)))
				break ;
			stack[i++ + 1].room->used = 1;
			if (stack[i].room->attribute == END)
				ft_put_solution(lem_in_data, stack, i);
		}
		stack[i].tube_index = 0;
		stack[i].room->used = 0;
		if (i-- == 0)
			break ;
	}
}
