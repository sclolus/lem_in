/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:51:49 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/25 19:05:53 by sclolus          ###   ########.fr       */
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

static int32_t	ft_get_nbr_lem(char *line)
{
	uint32_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("0123456789", line[i]))
			ft_error_exit(1, (char*[]){LEM_IN_ERR}, EXIT_FAILURE);
		i++;
	}
	return (ft_atoi(line)); // (uint32_t) ?
}

t_lem_in_data		*ft_parse(void)
{
	static const t_parsing_action	parsing_action[SUPPORTED_PARSING_CASE] = {
		&ft_error_case,
		&ft_get_new_note,
		&ft_get_new_room,
		&ft_get_new_tube,
		&ft_get_new_cmd,
	};
	static t_lem_in_data			lem_in_data;
	t_mem_block						*data;
	char							*line;
	t_list							*lines;
	t_list							*tmp;
	t_parsing_case					last_case;
	t_parsing_case					current_case;

	data = ft_create_mem_block(DEFAULT_MEM_BLOCK_SIZE);
	lines = NULL;
	line = NULL;
	last_case = ROOM;
	lem_in_data.data = data;
	get_next_line(0, &line);
	if (!(tmp = ft_lstnew(0, 0)))
		ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
	tmp->content = line;
	ft_lstadd(&lines, tmp);
	lem_in_data.lem_nbr = (uint32_t)ft_get_nbr_lem(line);
	while (get_next_line(0, &line) > 0)
	{
		if (!(current_case = ft_get_case(line, last_case)))
		{
			lem_in_data.lines = lines;
			return (&lem_in_data);
		}
		(void)ft_put_case;
//		ft_put_case(current_case);
//		printf("%s\n", line);
		if (!(parsing_action[current_case](line, &lem_in_data)))
			ft_error_case(line, &lem_in_data);
		if (!(tmp = ft_lstnew(0, 0)))
			ft_error_exit(1, (char*[]){MALLOC_FAILURE}, EXIT_FAILURE);
		tmp->content = line;
		ft_lstadd(&lines, tmp);
	}
	lem_in_data.lines = lines;
	return (&lem_in_data);
}
