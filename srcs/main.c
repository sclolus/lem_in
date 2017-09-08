/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:50:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 04:20:11 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static inline t_solve_stack	*ft_make_solve_stack(t_lem_in_data *data)
{
	t_solve_stack	*stack;
	t_room			*current_room;
	uint64_t		i;

	if ((i = (data->end->distance)) == ~0UL)
		ft_error_exit(1, (char*[]){LEM_IN_ERR}, EXIT_FAILURE);
	if (!(stack = (t_solve_stack*)ft_memalloc(sizeof(t_solve_stack)
						* data->room_nbr)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	stack[0].room = data->start;
	current_room = data->end;
	while (i > 0)
	{
		stack[i].room = current_room;
		current_room = current_room->shortest;
		i--;
	}
	return (stack);
}

inline void ft_reset_dijkstra_values(t_mem_block *data, uint32_t value)
{
	t_mem_block	*tmp;
	uint64_t	i;

	tmp = data;
	i = 0;
	while (i * sizeof(t_room) < tmp->offset)
	{
		((t_room*)tmp->block + i)->used = value;
		((t_room*)tmp->block + i)->distance = ~0UL;
		i++;
		if (i * sizeof(t_room) >= tmp->offset && tmp->next && !(i = 0))
			tmp = tmp->next;
	}
}

int			main(int argc, char **argv)
{
	t_lem_in_data	*lem_in_data;
	t_lem_flags		flags;
	t_solve_stack	*stack;

	flags.flags = 0;
	if (argc == 2)
		flags = ft_parse_flags(argv[1]);
	else if (argc > 2)
	{
		ft_putendl_fd(LEM_IN_ERR, 2);
		return (EXIT_FAILURE);
	}
	lem_in_data = ft_parse();
	lem_in_data->flags = flags;
	ft_check_integrity(lem_in_data);
	if (flags.bits.distance_algo)
		ft_dijkstra_distance(lem_in_data);
	else
	{
		ft_dijkstra(lem_in_data, lem_in_data->start);
		stack = ft_make_solve_stack(lem_in_data);
		ft_put_solution(lem_in_data, stack, lem_in_data->end->distance);
	}
}
