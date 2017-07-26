/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:51:49 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 14:22:23 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	ft_put_case(t_parsing_case current_case)
{
	ft_putstr("Parsing case: ");
	if (current_case == NOTE)
		ft_putstr("NOTE");
	else if (current_case == ROOM)
		ft_putstr("ROOM");
	else if (current_case == TUBE)
		ft_putstr("TUBE");
	else if (current_case == CMD)
		ft_putstr("CMD");
	ft_putchar('\n');
}

t_lem_in_data		*ft_parse(void)
{
	static const t_parsing_action	parsing_action[SUPPORTED_PARSING_CASE] = {
		&ft_error_case, &ft_get_lem_nbr, &ft_get_new_note,
		&ft_get_new_room, &ft_get_new_tube, &ft_get_new_cmd};
	static t_lem_in_data			lem_in_data;
	char							*line;
	t_parsing_case					last_case;
	t_parsing_case					current_case;

	lem_in_data.data = ft_create_mem_block(DEFAULT_MEM_BLOCK_SIZE);
	lem_in_data.lines = ft_create_mem_block(DEFAULT_MEM_BLOCK_SIZE);
	line = NULL;
	last_case = ERROR;
	while (get_next_line(0, &line) > 0)
	{
		if (!(current_case = ft_get_case(line, last_case))
			|| !(parsing_action[current_case](line, &lem_in_data)))
			return (&lem_in_data);
		(void)ft_put_case;
		ft_mem_block_push_back_elem(lem_in_data.lines, &line, sizeof(line));
		last_case = current_case;
	}
	return (&lem_in_data);
}
