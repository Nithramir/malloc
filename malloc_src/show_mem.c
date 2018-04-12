/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:49:05 by bandre            #+#    #+#             */
/*   Updated: 2018/04/12 17:43:57 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_zone(t_mem_zone *first)
{
	size_t		i;
	t_allocated	elem;
	int			index;
	size_t		allocated_mem = 0;
	int memszones = 0;

	index = 0;
	while (first)
	{
		i = 0;
		while (i < first->list_malloc_size)
		{
			elem = first->list_malloc[i];
			if (elem.size != 0)
			{
				// ft_printf("%p - %p : %zu\n", elem.position, elem.position + elem.size, elem.size);
				index++;
				allocated_mem += elem.size;
			}
			i++;
		}
		ft_putendl("new mem_zone");
		memszones += 1;
		first = first->next;
	}
	ft_printf("Number of allocations: %d\n\n", index);
	// ft_printf("qllocqted size: %zu\n", allocated_mem);
}
