/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <ylahssin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:39:23 by ylahssin          #+#    #+#             */
/*   Updated: 2024/10/25 12:41:44 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
#include <stdio.h>
#include <stdlib.h>

void	print_list(t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		printf("%d ", *(int *)(current->content));
		current = current->next;
	}
	printf("\n");
}

int	main(void)
{
	int	content1;

	content1 = 10, content2 = 20, content3;
	// Create initial nodes
	t_list *node1, *node2, *node3;
	content1 = 10, content2 = 20, content3 = 30;
	// Allocate memory and create new nodes
	node1 = ft_lstnew(&content1);
	node2 = ft_lstnew(&content2);
	node3 = ft_lstnew(&content3);
	// Initialize the list with one node
	t_list *head = node1;  // List: 10
	node1->next = NULL;    // Ensure it’s a proper single-node list
	// Add new nodes to the front of the list
	ft_lstadd_front(&head, node2);  // List: 20 -> 10
	ft_lstadd_front(&head, node3);  // List: 30 -> 20 -> 10
	// Print the list to verify the nodes are in the correct order
	print_list(head);
	return (0);
}
*/
