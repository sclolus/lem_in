/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_case.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 04:07:59 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 18:56:51 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline static int32_t	ft_is_case_note(char *line
							, t_parsing_case __attribute__((unused)) last_case)
{
	if (*line && *line == '#' && line[1] != '#')
		return (1);
	return (0);
}

inline static int32_t	ft_is_case_cmd(char *line
						, t_parsing_case __attribute__((unused)) last_case)
{
	if (*line && *line == '#' && line[1] == '#')
		return (1);
	return (0);
}

inline static int32_t	ft_is_case_room(char *line, t_parsing_case last_case)
{
	uint32_t	i;
	uint32_t	word_count;

	i = 0;
	word_count = 0;
	if (last_case == TUBE)
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			word_count++;
		if (word_count > 3)
			return (0);
		i++;
	}
	return (word_count == 2 ? 1 : 0);
}

inline static int32_t	ft_is_case_tube(char *line, t_parsing_case last_case)
{
	uint32_t	i;
	int32_t		bool;

	i = 0;
	bool = 0;
	if (last_case == CMD &&
		(*ft_get_last_attribute() == START
		|| *ft_get_last_attribute() == END))
		return (0);
	while (line[i])
	{
		if (i && line[i] == '-' && line[i + 1])
			bool = 1;
		i++;
	}
	return (bool);
}

t_parsing_case			ft_get_case(char *line, t_parsing_case last_case)
{
	static t_parsing_case_identifier	case_f_tab[] = {
		{&ft_is_case_start, BEGIN, {0}},
		{&ft_is_case_room, ROOM, {0}},
		{&ft_is_case_note, NOTE, {0}},
		{&ft_is_case_cmd, CMD, {0}},
		{&ft_is_case_tube, TUBE, {0}}};
	uint32_t							i;

	i = 0;
	while (i < sizeof(case_f_tab) / sizeof(t_parsing_case_identifier))
	{
		if (case_f_tab[i].f(line, last_case))
			return (case_f_tab[i].identifier_case);
		i++;
	}
	return (ERROR);
}
