/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_integrity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 13:48:13 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 23:23:28 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_check_integrity(t_lem_in_data *lem_in_data)
{
	if (!lem_in_data->room_nbr || !lem_in_data->lem_nbr
		|| !ft_get_set_states()[0] || !ft_get_set_states()[1])
		ft_put_lem_in_error();
}
