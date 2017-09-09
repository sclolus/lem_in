/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_max_flow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 05:29:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/09 05:31:03 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline uint32_t	ft_get_max_flow(t_solve_stack *stack)
{
	uint32_t	max_flow;
	uint32_t	tmp;
	uint32_t	i;

	max_flow = stack[0].room->flow.capacity - stack[0].room->flow.flow;
	i = 1;
	while (stack[i].room->attribute != START)
	{
		tmp = stack[i].room->flow.capacity - stack[i].room->flow.flow;
		if (!tmp)
		{
			max_flow = 0;
			break ;
		}
		else if (tmp < max_flow)
			max_flow = tmp;
		i++;
	}
	return (max_flow);
}

inline void		ft_add_flow_to_path(t_solve_stack *stack, uint32_t flow
											, uint32_t *lem_nbr)
{
	uint32_t	i;

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
	stack[i - 1].room->used = 1;
	stack[0].room->used = 1;
	if (*lem_nbr < flow || !flow)
		*lem_nbr = 0;
	else
		*lem_nbr -= flow;
}
