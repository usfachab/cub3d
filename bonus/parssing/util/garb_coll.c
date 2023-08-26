/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garb_coll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabr <ysabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:03:50 by yachaab           #+#    #+#             */
/*   Updated: 2023/08/26 14:08:49 by ysabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

void	*gc_malloc(size_t size, t_list **lst)
{
	void	*ptr;

	ptr = malloc(size);
	ft_lstadd_back(lst, ft_lstnew(ptr));
	return (ptr);
}

void	gc_free(t_list **lst)
{
	t_list	*head;
	t_list	*hold;

	head = *lst;
	while (head)
	{
		hold = head->next;
		free(head->ptr);
		free(head);
		head = hold;
	}
}