/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:50:08 by edesaint          #+#    #+#             */
/*   Updated: 2022/12/05 20:04:07 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bsd/string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len_src;

	len_src = ft_strlen(src);
	if (!src)
		return (0);
	if (size == 0)
		return (len_src);
	if (size <= len_src)
	{
		ft_memcpy(dst, src, size - 1);
		dst[size - 1] = '\0';
	}
	else
	{
		ft_memcpy(dst, src, len_src);
		dst[len_src] = '\0';
	}
	return (len_src);
}
