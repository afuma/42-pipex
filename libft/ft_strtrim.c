/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:23:02 by blax              #+#    #+#             */
/*   Updated: 2022/12/05 20:20:56 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_offset(char const *s1, char const *set, int sens)
{
	int	offset;
	int	i;

	offset = 0;
	if (sens)
		i = ft_strlen(s1) - 1;
	else
		i = 0;
	while (s1[i] && i >= 0 && ft_strchr(set, s1[i]))
	{
		offset += 1;
		if (sens)
			i--;
		else
			i++;
	}
	return (offset);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*nstr;
	unsigned int	len_nstr;
	unsigned int	offset_left;
	unsigned int	offset_right;

	offset_left = ft_offset(s1, set, 0);
	offset_right = ft_offset(s1, set, 1);
	len_nstr = ft_strlen(s1) + 1;
	if (offset_left + offset_right > len_nstr)
		len_nstr = 1;
	else
		len_nstr -= (offset_left + offset_right);
	nstr = malloc(sizeof(char) * len_nstr);
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s1 + offset_left, len_nstr);
	return (nstr);
}
