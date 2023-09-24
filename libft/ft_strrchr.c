/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:51:23 by edesaint          #+#    #+#             */
/*   Updated: 2022/12/05 21:14:47 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	n;

	n = (int) ft_strlen(s);
	while (n >= 0)
	{
		if (s[n] == ((char) c))
			return ((char *)(s + n));
		n--;
	}
	return (NULL);
}
