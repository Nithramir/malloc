/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 17:58:52 by bandre            #+#    #+#             */
/*   Updated: 2016/11/08 19:43:01 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *str, char (*f)(char))
{
	char			*chainretour;
	unsigned int	len;

	if (str && f)
	{
		len = 0;
		while (str[len])
			len++;
		chainretour = (char*)mem_stock(sizeof(char) * len + 1);
		if (chainretour == NULL)
			return (NULL);
		len = 0;
		while (str[len])
		{
			chainretour[len] = (*f)(str[len]);
			len++;
		}
		chainretour[len] = '\0';
		return (chainretour);
	}
	else
		return (NULL);
}
