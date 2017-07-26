/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 15:32:28 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 15:39:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static t_room	*ft_get_start_room(t_lem_in_data *lem_in_data)
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

inline static void		ft_print_stack(t_lem_in_data *lem_in_data
							, t_solve_stack *stack, uint32_t index)
{
	uint32_t	lem_nbr;
	uint32_t	i;
	uint32_t	u;

	i = 0;
	lem_nbr = lem_in_data->lem_nbr;
/* 	while (i < index) */
/* 	{ */
/* 		printf("%s\n", stack[i].room->name); */
/* 		i++; */
/* 	} */
	i = 1;
	while (lem_nbr != 0)
	{
		u = 0;
		while (u < i && u < lem_nbr)
		{
			ft_putchar('L');
			ft_putnbr((int)((int)(lem_in_data->lem_nbr - lem_nbr) + (int)u + 1));
			ft_putchar('-');
			ft_putstr(stack[i - u].room->name);
			ft_putchar(' ');
			u++;
		}
		ft_putchar('\n');
		if (i != index - 1)
			i++;
		else
			lem_nbr--;
	}
}

void	ft_solve(t_lem_in_data *lem_in_data)
{
	t_solve_stack	*stack;
	uint32_t		i;

	if (!(stack = (t_solve_stack*)ft_memalloc(sizeof(t_solve_stack)
		* lem_in_data->room_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	i = 0;
	if (!(stack[i].room = ft_get_start_room(lem_in_data)))
		ft_error_exit(1, (char*[]){LEM_IN_ERR}, EXIT_FAILURE);
	while (42)
	{
		while (stack[i].tube_index < stack[i].room->nbr_tube)
		{
			if (i + 1 == lem_in_data->room_nbr)
				break ;
			if (!(*((t_room**)stack[i].room->tubes->block + stack[i].tube_index))->used) // if next == true
			{
				(*((t_room**)stack[i].room->tubes->block + stack[i].tube_index))->used = 1;
				i++;
				if ((*((t_room**)stack[i - 1].room->tubes->block + stack[i - 1].tube_index))->attribute == END)
				{
					stack[i].room = *((t_room**)stack[i - 1].room->tubes->block + stack[i - 1].tube_index);
					ft_print_stack(lem_in_data, stack, i + 1);
					return ;
				}
				stack[i].room = *((t_room**)stack[i - 1].room->tubes->block + stack[i - 1].tube_index);
				stack[i - 1].tube_index++;
			}
			else
				stack[i].tube_index++;
		}
		stack[i].tube_index = 0;
		stack[i].room->used = 0;
		if (i == 0)
			break ;
		i--;
	}
	ft_putendl(LEM_IN_ERR);
	return ;
}
