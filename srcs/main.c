/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 03:50:38 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/01 12:42:12 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			main(void)
{
	t_lem_in_data	*lem_in_data;

	lem_in_data = ft_parse();
	ft_check_integrity(lem_in_data);
//	ft_solve(lem_in_data);
	ft_put_lines(lem_in_data->lines);
	ft_static_put(NULL, 0, STATIC_PUT_FLUSH);
	ft_dijsktra(lem_in_data);
	ft_putendl_fd(LEM_IN_ERR, 2);
	return (0);
}
