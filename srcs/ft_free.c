/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:27:19 by blax              #+#    #+#             */
/*   Updated: 2023/09/24 21:29:54 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void	free_cmd(t_data *cmd)
{
	if (cmd->command != NULL)
		(ft_free_split(cmd->command), cmd->command = NULL);
	if (cmd->arr != NULL)
		(ft_free_split(cmd->arr), cmd->arr = NULL);
	if (cmd->path != NULL && cmd->path != cmd->base)
		(free(cmd->path), cmd->path = NULL);
}

void	free_all_and_exit(t_data *cmd_1, t_data *cmd_2, char *msg)
{
	perror(msg);
	free_cmd(cmd_1);
	free_cmd(cmd_2);
	exit(EXIT_FAILURE);
}
