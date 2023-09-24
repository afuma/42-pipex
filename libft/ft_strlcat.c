/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blax <blax@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:50:34 by edesaint          #+#    #+#             */
/*   Updated: 2023/07/20 08:07:41 by blax             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsd/string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	init_dst_len;

	i = 0;
	init_dst_len = ft_strlen(dst);
	if (init_dst_len >= size)
		return (size + ft_strlen(src));
	if (!size)
		return (init_dst_len + ft_strlen(src));
	while (src[i] != '\0' && i < (size - init_dst_len - 1))
	{
		dst[init_dst_len + i] = src[i];
		i++;
	}
	dst[init_dst_len + i] = '\0';
	return (init_dst_len + ft_strlen(src));
}
