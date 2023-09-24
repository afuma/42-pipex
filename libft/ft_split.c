/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:43:33 by edesaint          #+#    #+#             */
/*   Updated: 2022/12/06 19:49:02 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static void	ft_free(char **tab, int i)
{
	while (i-- > 0)
		free(tab[i]);
	free(tab);
}

static int	ft_nb_words(char const *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			words++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (words);
}

static void	ft_create(char **tab, char const *str, char c, size_t nb_words)
{
	size_t	i;
	size_t	j;
	size_t	len_str;

	len_str = 0;
	i = 0;
	j = 0;
	while (str[len_str + i] && j < nb_words)
	{
		while (str[len_str + i] && str[len_str + i] == c)
			len_str++;
		while (str[len_str + i] && str[len_str + i] != c)
			i++;
		tab[j] = ft_substr(str, len_str, i);
		if (!tab[j++])
			ft_free(tab, --j);
		len_str += i;
		i = 0;
	}
	if (tab != NULL)
		tab[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	nb_words;

	if (!s)
		return (NULL);
	nb_words = ft_nb_words(s, c);
	tab = (char **) malloc(sizeof(char *) * (nb_words + 1));
	if (!tab)
		return (NULL);
	ft_create(tab, s, c, nb_words);
	return (tab);
}
