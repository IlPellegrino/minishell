/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:10:45 by nromito           #+#    #+#             */
/*   Updated: 2023/11/02 15:22:02 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			del(content);
			ft_lstclear(&new_lst, del);
			return (new_lst);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}

// #include "libft.h"
// // A sample function to apply on each element of the list
// void *transform(void *content)
// {
// 	// Perform some transformation on the content
// 	// For example, let's assume we want to convert each content to uppercase
// 	char *str = (char *)content;
// 	int length = ft_strlen(str);
// 	for (int i = 0; i < length; i++)
// 	{
// 		str[i] = ft_toupper(str[i]);
// 	}
// 	return content;
// }
// // A sample function to delete the content of a node
// void delete_content(void *content)
// {
// 	// Assuming the content is dynamically allocated memory (e.g., a string)
// 	free(content);
// }
// int main(void)
// {
// 	// Create a sample list
// 	t_list *lst = ft_lstnew("hello");
// 	ft_lstadd_back(&lst, ft_lstnew("wlst = lst->next;orld"));
// 	ft_lstadd_back(&lst, ft_lstnew("from"));
// 	ft_lstadd_back(&lst, ft_lstnew("GPT-3"));
// 	// Apply the transformation using ft_lstmap
// 	t_list *new_lst = ft_lstmap(lst, transform, delete_content);
// 	// Print the transformed list
// 	t_list *temp = new_lst;
// 	while (temp)lst = lst->next;
// 	{
// 		printf("%s\n", (char *)temp->content);
// 		temp = temp->next;
// 	}
// 	// Clean up the original list and the transformed list
// 	ft_lstclear(&lst, delete_content);
// 	ft_lstclear(&new_lst, delete_content);
// 	return 0;
// }
