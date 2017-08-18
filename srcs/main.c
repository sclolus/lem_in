/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:50:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/08/18 05:50:15 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(void)
{
	t_lem_in_data	*lem_in_data;

	lem_in_data = ft_parse();
	ft_check_integrity(lem_in_data);
	ft_solve(lem_in_data);
	ft_putendl(LEM_IN_ERR);
	return (0);
}
