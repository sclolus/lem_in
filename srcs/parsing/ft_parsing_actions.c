/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_actions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 04:38:48 by sclolus           #+#    #+#             */
/*   Updated: 2017/07/26 18:49:07 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int32_t			ft_error_case(char *line
							, t_lem_in_data *lem_in_data)
{
	(void)line;
	(void)lem_in_data;
	ft_putendl_fd(LEM_IN_ERR "\n", 2);
	return (0);
}
