/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <cristianiusca13@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:43:46 by ciusca            #+#    #+#             */
/*   Updated: 2023/10/30 20:47:58 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	init(t_list **nl, t_list **nh, t_list **lst, void *(*f)(void *))
{
	(*nl)->content = f((*lst)->content);
	(*nl)->next = NULL;
	*nh = *nl;
	*lst = (*lst)->next;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_head;

	if (lst == NULL)
		return (NULL);
	new_lst = malloc(sizeof(t_list));
	if (new_lst == NULL)
		return (NULL);
	init(&new_lst, &new_head, &lst, f);
	while (lst != NULL)
	{
		new_lst->next = malloc(sizeof(t_list));
		if (new_lst->next == NULL)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		new_lst = new_lst->next;
		new_lst->content = f(lst->content);
		new_lst->next = NULL;
		lst = lst->next;
	}
	return (new_head);
}
