/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 08:22:35 by atverdok          #+#    #+#             */
/*   Updated: 2017/10/11 08:24:46 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

t_pipe	*create_t_pipe(void)
{
	t_pipe *node;

	node = ft_memalloc(sizeof(t_pipe));
	return (node);
}

void	add_list_t_pipe(t_pipe **head, t_pipe *new_node)
{
	t_pipe *current;

	if (*head == NULL)
	{
		new_node->next = *head;
		*head = new_node;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void	del_t_pipe(t_pipe **pipes)
{
	t_pipe *next;

	while (*pipes)
	{
		if ((*pipes)->cmd_full_path)
			ft_strdel(&(*pipes)->cmd_full_path);
		ft_memdel((void *)&(*pipes)->arg);
		next = (*pipes)->next;
		ft_memdel((void *)pipes);
		*pipes = next;
	}
}

void	insert_d_list(t_string **head, t_string *new_node)
{
	t_string *cur;

	if (*head == NULL)
		*head = new_node;
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new_node;
		new_node->prev = cur;
	}
}
