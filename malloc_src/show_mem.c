/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:49:05 by bandre            #+#    #+#             */
/*   Updated: 2018/04/10 17:08:05 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_zone(t_mem_zone *first)
{
	size_t		i;
	t_allocated	elem;
	int			index;

	index = 0;
	while (first)
	{
		i = 0;
		while (i < first->list_malloc_size)
		{
			elem = first->list_malloc[i];
			if (elem.size != 0)
			{
				ft_printf("%p - %p : %zu\n", elem.position,
					elem.position + elem.size, elem.size);
				index++;
			}
			i++;
		}
		first = first->next;
	}
	ft_printf("Number of allocations: %d\n\n", index);
}

void	show_alloc_mem(t_malloc g_malloc)
{
	ft_putendl("TINY");
	show_zone(g_malloc.tiny);
	ft_putendl("SMALL");
	show_zone(g_malloc.small);
	ft_putendl("LARGE");
	show_zone(g_malloc.large);
}
