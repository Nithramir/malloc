/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bandre <bandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:45:02 by bandre            #+#    #+#             */
/*   Updated: 2018/04/24 18:25:54 by bandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# include "../libft/ft_printf/ft_printf.h"
# include <sys/mman.h>
# define MALLOC_TINY getpagesize()
# define MALLOC_SMALL getpagesize() * 64

/*
** describe a allocated zone
*/

typedef struct			s_allocated {
	size_t				size;
	void				*position;
}						t_allocated;

/*
** List of allocated zone
*/

typedef struct			s_mem_zone {
	void				*mem_zone;
	t_allocated			*list_malloc;
	size_t				list_malloc_size;
	size_t				memory_size;
	size_t				memory_used;
	struct s_mem_zone	*next;
	struct s_mem_zone	*before;
}						t_mem_zone;

/*
** Main struct with pointer on different malloc list
*/

typedef struct			s_malloc {
	t_mem_zone			*tiny;
	t_mem_zone			*small;
	t_mem_zone			*large;
	void				*list_mem_zone;
	void				*list_allocated;
}						t_malloc;

t_mem_zone				*create_mem_zone(size_t size, t_mem_zone *before);
t_mem_zone				*get_memory_position(t_mem_zone *zone,
	size_t asked_memory_size, size_t zone_size);
void					*create_initialized_memory(size_t size);
int						ft_search_ptr(void *ptr, t_mem_zone **zone);
void					clean_zone(t_mem_zone *zone, size_t pos);
size_t					ft_search_size(void *ptr, t_mem_zone *first_zone);
void					show_alloc_mem();
void					*malloc(size_t size);
void					free(void *ptr);
void					*realloc(void *ptr, size_t new_size);
void					show_zone(t_mem_zone *first);
t_allocated				*set_bigger_list_malloc(t_mem_zone *zone);
void					*get_tiny_memory(size_t asked_mem_size,
	t_mem_zone **zone, size_t size);
void					*get_large_memory(size_t asked_memory_size,
	t_mem_zone **zone, size_t zone_size);
#endif
