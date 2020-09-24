/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commas.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casubmar <casubmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 19:44:16 by casubmar          #+#    #+#             */
/*   Updated: 2020/09/22 19:44:16 by casubmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commas		*ft_prev_last(t_commas *head)
{
	t_commas *temp;

	if (!head)
		return (head);
	temp = head;
	while (temp->next->next)
		temp = temp->next;
	return (temp);
}

t_commas		*ft_last_commas(t_commas *head)
{
	t_commas *temp;

	if (!head)
		return (head);
	temp = head;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void			ft_commas_clear(t_commas *head)
{
	t_commas	*temp;
	int 		i;

	while (head)
	{
		i = 0;
		while (head->argv[i])
		{
			free(head->argv[i]);
			++i;
		}
		temp = head->next;
		free(head);
		head = temp;
	}
}

int 			ft_add_back(t_commas **head, char **content)
{
	if (!(*head))
	{
		if (!(*head = ft_new_commas(content)))
			return (0);
	}
	else
	{
		while ((*head)->next)
			(*head) = (*head)->next;
		if (!((*head)->next = ft_new_commas(content)))
			return (0);
	}
	return (1);
}

t_commas		*ft_new_commas(char **content)
{
	t_commas *new;

	if (!(new = (t_commas *)malloc(sizeof(t_commas))))
		return (0);
	new->argv = content;
	new->fds[0] = 0;
	new->fds[1] = 1;
	new->next = NULL;
	return (new);
}