/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atverdok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 10:49:37 by atverdok          #+#    #+#             */
/*   Updated: 2016/12/02 17:19:10 by atverdok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_struct;
	char	*content_cop;

	new_struct = (t_list *)ft_memalloc(sizeof(t_list));
	if (new_struct)
	{
		if (content)
		{
			content_cop = (char *)ft_memalloc(content_size);
			ft_memmove(content_cop, content, content_size);
			new_struct->content = content_cop;
			new_struct->content_size = content_size;
		}
	}
	return (new_struct);
}
