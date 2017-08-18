/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 15:32:28 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/18 02:20:48 by sclolus          ###   ########.fr       */
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
							, t_solve_stack *stack, uint32_t index)
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

static void					ft_cleanup_solve_stack(t_solve_stack **stack)
{
	free(*stack);
}

__attribute__((hot)) void	ft_solve(t_lem_in_data *lem_in_data)
{
	t_solve_stack	*stack __attribute__((cleanup(ft_cleanup_solve_stack)));
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
					ft_put_lines(lem_in_data->lines);
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
