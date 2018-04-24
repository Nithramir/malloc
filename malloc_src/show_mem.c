/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:49:05 by bandre            #+#    #+#             */
/*   Updated: 2018/04/24 17:07:29 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_zone(t_mem_zone *first)
{
	size_t		i;
	t_allocated	elem;
	size_t		allocated_mem;

	allocated_mem = 0;
	while (first && (i = 0))
	{
		ft_putendl("\nNew allocation zone");
		while (i < first->list_malloc_size)
		{
			elem = first->list_malloc[i];
			if (elem.size != 0)
			{
				ft_printf("%p - %p : %zu\n", elem.position, elem.position +
					elem.size, elem.size);
				allocated_mem += elem.size;
			}
			i++;
		}
		first = first->next;
	}
	ft_printf("Allocated size: %zu\n\n", allocated_mem);
}
