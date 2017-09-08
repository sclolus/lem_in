/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 05:38:27 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 09:15:16 by sclolus          ###   ########.fr       */
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

inline static uint32_t	*ft_print_stack(t_lem_in_data *lem_in_data
							, t_solve_stack *stack, uint64_t index)
{
	static uint32_t	stats[2];
	uint32_t		lem_nbr;
	uint32_t		i;
	uint32_t		u;

	lem_nbr = lem_in_data->lem_nbr;
	i = 1;
	while (lem_nbr != 0)
	{
		u = 0;
		while (u < i && u < lem_nbr)
		{
			ft_print_path(stack, (int)((int)(lem_in_data->lem_nbr - lem_nbr)
							+ (int)u + 1), u, i);
			stats[1]++;
			u++;
		}
		ft_static_put("\n", 1, 0);
		stats[0]++;
		if (i != index - 1)
			i++;
		else
			lem_nbr--;
	}
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
	return (stats);
}

inline static void		ft_show_path(
							t_lem_in_data __attribute__((unused)) *lem_in_data
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

inline static void		ft_print_verbose(uint32_t *stats)
{
	char	*tmp;

	ft_static_put("Number of moves: ", sizeof("Number of moves: "), 0);
	if (!(tmp = ft_itoa((int)stats[1])))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	ft_static_put(tmp, (uint32_t)ft_strlen(tmp), 0);
	free(tmp);
	ft_static_put("\n", 1, 0);
	ft_static_put("Number of turns: ", sizeof("Number of turns: "), 0);
	if (!(tmp = ft_itoa((int)stats[0])))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	ft_static_put(tmp, (uint32_t)ft_strlen(tmp), 0);
	ft_static_put("\n", 1, 0);
	free(tmp);
}

void					ft_put_solution(t_lem_in_data *lem_in_data
						, t_solve_stack *stack, uint64_t index)
{
	uint32_t	*stats;

	if (!lem_in_data->flags.bits.quiet)
		ft_put_lines(lem_in_data->lines);
	if (lem_in_data->flags.bits.multi_path)
		stats = ft_multi_path(lem_in_data);
	else
		stats = ft_print_stack(lem_in_data, stack, index + 1);
	if (lem_in_data->flags.bits.show_path)
		ft_show_path(lem_in_data, stack, index + 1);
	if (lem_in_data->flags.bits.verbose)
		ft_print_verbose(stats);
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
	exit(EXIT_SUCCESS);
}
