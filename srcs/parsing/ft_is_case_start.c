/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_case_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 18:56:24 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 18:56:50 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

inline int32_t	ft_is_case_start(char __attribute__((unused)) *line
								, t_parsing_case last_case)
{
	if (last_case == ERROR)
		return (1);
	return (0);
}
