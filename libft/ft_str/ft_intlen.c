/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctycho <ctycho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:30:04 by ctycho            #+#    #+#             */
/*   Updated: 2021/03/20 06:11:15 by ctycho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_intlen(int line)
{
	int				count;

	count = 0;
	while (line)
	{
		line = line / 10;
		count++;
	}
	return (count);
}
