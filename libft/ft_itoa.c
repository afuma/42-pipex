/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:33:14 by edesaint          #+#    #+#             */
/*   Updated: 2022/12/05 21:14:41 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h> // printf
#include <stdint.h> //INT_MAX

static unsigned int	ft_abs(int nbr)
{
	if (nbr < 0)
		return ((unsigned int)(-nbr));
	return ((unsigned int) nbr);
}

static int	ft_neg(int nbr)
{
	return (nbr < 0);
}

static unsigned int	ft_cptdigit(unsigned int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len_n;
	int				neg;
	unsigned int	nbr;

	neg = ft_neg(n);
	nbr = ft_abs(n);
	len_n = ft_cptdigit(nbr) + neg;
	str = (char *) malloc(sizeof(char) * (len_n + 1));
	if (!str)
		return (NULL);
	str[len_n] = '\0';
	while (--len_n >= 0)
	{
		if (!len_n && neg)
			str[0] = '-';
		else
		{
			str[len_n] = (nbr % 10) + '0';
			nbr /= 10;
		}
	}
	return (str);
}

/*
int main(void)
{
    int n;

    n = 3402; printf("%d: %s\n", n, ft_itoa(n));
    n = 0; printf("%d: %s\n", n, ft_itoa(n));
    n = 1; printf("%d: %s\n", n, ft_itoa(n));
    n = 9; printf("%d: %s\n", n, ft_itoa(n));
    n = 10; printf("%d: %s\n", n, ft_itoa(n));
    n = 30025; printf("%d: %s\n", n, ft_itoa(n));
    n = 900; printf("%d: %s\n", n, ft_itoa(n));
    n = -4; printf("%d: %s\n", n, ft_itoa(n));
    n = -478888; printf("%d: %s\n", n, ft_itoa(n));
    n = -2200; printf("%d: %s\n", n, ft_itoa(n));
    
    return (0);
}
*/