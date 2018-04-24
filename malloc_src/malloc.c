/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:32:15 by bandre            #+#    #+#             */
/*   Updated: 2018/04/24 18:43:27 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_malloc g_malloc = {NULL, NULL, NULL, NULL, NULL};

void	*malloc(size_t asked_mem)
{
	if (asked_mem < (size_t)MALLOC_TINY)
		return (get_tiny_memory(asked_mem, &g_malloc.tiny,
			(size_t)MALLOC_TINY));
	else if (asked_mem < (size_t)MALLOC_SMALL)
		return (get_tiny_memory(asked_mem, &g_malloc.small,
			(size_t)MALLOC_SMALL));
	else
	{
		return (get_large_memory(asked_mem, &g_malloc.large, asked_mem + 1));
	}
	return (NULL);
}

void	show_alloc_mem(void)
{
	ft_putendl("TINY");
	show_zone(g_malloc.tiny);
	ft_putendl("SMALL");
	show_zone(g_malloc.small);
	ft_putendl("LARGE");
	show_zone(g_malloc.large);
}

void	free(void *ptr)
{
	int result;

	if (!ptr)
		return;
	result = 0;
	if (g_malloc.large)
		result = ft_search_ptr(ptr, &g_malloc.large);
	if (!result && g_malloc.small)
		result = ft_search_ptr(ptr, &g_malloc.small);
	if (!result && g_malloc.tiny)
	{
		result = ft_search_ptr(ptr, &g_malloc.tiny);
	}
}

size_t	find_size(void *ptr)
{
	size_t size;

	size = 0;
	if (g_malloc.large)
		size = ft_search_size(ptr, g_malloc.large);
	if (!size && g_malloc.small)
		size = ft_search_size(ptr, g_malloc.small);
	if (!size && g_malloc.tiny)
		size = ft_search_size(ptr, g_malloc.tiny);
	return (size);
}

void	*realloc(void *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	size;
	size_t	i;
	char	*ptr2;

	ptr2 = ptr;
	i = 0;
	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
		free(ptr);
	if (!(size = find_size(ptr)))
		return (NULL);
	new_ptr = (char*)malloc(new_size);
	if (!new_ptr)
		return (NULL);
	size = (size < new_size) ? size : new_size;
	while (i < size)
	{
		new_ptr[i] = ptr2[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}
