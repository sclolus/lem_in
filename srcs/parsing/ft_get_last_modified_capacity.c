/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_modified_capacity.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sclolus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 22:51:55 by sclolus           #+#    #+#             */
/*   Updated: 2017/09/08 22:56:45 by sclolus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

uint32_t	*ft_get_last_modified_capacity(void)
{
	static uint32_t	capacity = 1;

	return (&capacity);
}
