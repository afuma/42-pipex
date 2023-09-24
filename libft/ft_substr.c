/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:46:14 by edesaint          #+#    #+#             */
/*   Updated: 2022/12/05 20:46:28 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*nstr;
	int				size_nstr;
	unsigned int	len_s;

	len_s = ft_strlen(s);
	if (start > len_s + 1)
	{
		size_nstr = 0;
		start = 0;
	}
	else
		size_nstr = len_s - start;
	if (size_nstr > (int) len)
		size_nstr = len;
	nstr = malloc(sizeof(char) * (size_nstr + 1));
	if (!nstr)
		return (NULL);
	ft_strlcpy(nstr, s + start, size_nstr + 1);
	return (nstr);
}
