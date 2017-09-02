/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 05:38:27 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/02 14:08:50 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void					ft_put_solution(t_lem_in_data *lem_in_data
						, t_solve_stack *stack, uint64_t index)
{
	if (!lem_in_data->flags.bits.quiet)
		ft_put_lines(lem_in_data->lines);
	ft_print_stack(lem_in_data, stack, index + 1);
	exit(EXIT_SUCCESS);
}
