/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:32:15 by bandre            #+#    #+#             */
/*   Updated: 2018/04/12 19:26:54 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static t_malloc g_malloc = {NULL, NULL, NULL, NULL, NULL};

void	*get_tiny_memory(size_t asked_memory_size,
	t_mem_zone **zone, size_t zone_size)
{
	if (!(*zone))
		*zone = create_mem_zone(zone_size * 2, NULL);
	if (!(*zone))
		return (NULL);
	void* retour = get_memory_position(*zone, asked_memory_size, zone_size * 2);
	ft_putendl("sortie");
	return retour;
}

void	*get_large_memory(size_t asked_memory_size,
	t_mem_zone **zone, size_t zone_size)
{
	if (!(*zone))
		*zone = create_mem_zone(zone_size, NULL);
	return (get_memory_position(*zone, asked_memory_size, zone_size));
}

void	*malloc(size_t asked_mem_size)
{
		ft_putendl("entree");
	
	if (asked_mem_size < (size_t)MALLOC_TINY)
		return (get_tiny_memory(asked_mem_size, &g_malloc.tiny, (size_t)MALLOC_TINY));
	else if (asked_mem_size < (size_t)MALLOC_SMALL)
		return (get_tiny_memory(asked_mem_size, &g_malloc.small, (size_t)MALLOC_SMALL));
	else
	{
		ft_putendl("plop");
		return (get_large_memory(asked_mem_size, &g_malloc.large,
			asked_mem_size + 1));
	}
	return (NULL);
}

void	show_alloc_mem()
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

void	*realloc(void *ptr, size_t new_size)
{
	char	*new_ptr;
	size_t	size;

	size = 0;
	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
		free(ptr);
	if (g_malloc.large)
		size = ft_search_size(ptr, g_malloc.large);
	if (!size && g_malloc.small)
		size = ft_search_size(ptr, g_malloc.small);
	if (!size && g_malloc.tiny)
	{
		size = ft_search_size(ptr, g_malloc.tiny);
	}
	if (!size)
	{
		ft_putendl("NOT FOUND");
		return (NULL);
	}
	
	new_ptr = (char*)malloc(new_size);

	if (!new_ptr)
	{
		exit(0);
		return (NULL);
	}
	int i = 0;
	char *ptr2 = ptr;
	size = (size < new_size) ? size : new_size;
	ft_putnbr(size);
	ft_putendl("");
	while (i < size) {
		new_ptr[i] = ptr2[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}