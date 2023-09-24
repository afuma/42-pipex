/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 21:51:05 by blax              #+#    #+#             */
/*   Updated: 2023/09/24 21:33:59 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_data
{
	char	**command;
	char	*base;
	char	*path;
	char	**pathes;
	char	**arr;
	char	**envp;
}	t_data;

// ft_pipex.c
void	init_all(t_data *data);
int		init_cmd(t_data *cmd, char *chaine, char *envp[]);
void	child_one(t_data *cmd_1, t_data *cmd_2, char *arg, int fd[2]);
void	child_two(t_data *cmd_1, t_data *cmd_2, char *arg, int fd[2]);
void	pipex(t_data *cmd_1, t_data *cmd_2, char *argv[]);

// ft_free.c
void	ft_free_split(char **tab);
void	free_cmd(t_data *cmd);
void	free_all_and_exit(t_data *cmd_1, t_data *cmd_2, char *msg);

// ft_paths.c
char	*get_path(char *envp[]);
void	print_pathes(char **chaine);
int		init_pathes(t_data *data, char *envp[]);
char	*ft_three_join(char *str_1, char *str_2, char *str_3);
void	find_cmd_path(t_data *data);

#endif