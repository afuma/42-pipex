/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:13:27 by blax              #+#    #+#             */
/*   Updated: 2023/09/24 21:28:52 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_all(t_data *data)
{
	data->command = NULL;
	data->base = NULL;
	data->path = NULL;
	data->pathes = NULL;
	data->arr = NULL;
	data->envp = NULL;
}

int	init_cmd(t_data *data, char *arg, char *envp[])
{
	init_all(data);
	data->command = ft_split(arg, ' ');
	if (data->command == NULL)
		return (-1);
	data->base = data->command[0];
	if (data->base == NULL)
		return (-1);
	data->envp = envp;
	if (access(data->base, F_OK) != -1)
		data->path = data->base;
	else
	{
		if (init_pathes(data, envp) == -1)
			return (-1);
		find_cmd_path(data);
	}
	if (data->path == NULL)
		return (-1);
	data->arr = ft_split(arg, ' ');
	if (data->arr == NULL)
		return (-1);
	return (1);
}

void	child_one(t_data *cmd_1, t_data *cmd_2, char *arg, int fd[2])
{
	int	infile;

	infile = open(arg, O_RDONLY, 0777);
	if (infile == -1)
		free_all_and_exit(cmd_1, cmd_2, "infile");
	if (dup2(infile, STDIN_FILENO) == -1)
		free_all_and_exit(cmd_1, cmd_2, "dup2");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		free_all_and_exit(cmd_1, cmd_2, "dup2");
	close(infile);
	close(fd[0]);
	close(fd[1]);
	if (execve(cmd_1->path, cmd_1->arr, cmd_1->envp) == -1)
		free_all_and_exit(cmd_1, cmd_2, "execve");
}

void	child_two(t_data *cmd_1, t_data *cmd_2, char *arg, int fd[2])
{
	int	outfile;

	outfile = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		free_all_and_exit(cmd_1, cmd_2, "outfile");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		free_all_and_exit(cmd_1, cmd_2, "dup2");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		free_all_and_exit(cmd_1, cmd_2, "dup2");
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	if (execve(cmd_2->path, cmd_2->arr, cmd_2->envp) == -1)
		free_all_and_exit(cmd_1, cmd_2, "execve");
}

void	pipex(t_data *cmd_1, t_data *cmd_2, char *argv[])
{
	int	fd[2];
	int	pid_1;
	int	pid_2;
	int	status;

	if (pipe(fd) == -1)
		free_all_and_exit(cmd_1, cmd_2, "pipe");
	pid_1 = fork();
	if (pid_1 < 0)
		free_all_and_exit(cmd_1, cmd_2, "fork");
	if (pid_1 == 0)
		child_one(cmd_1, cmd_2, argv[1], fd);
	pid_2 = fork();
	if (pid_2 < 0)
		free_all_and_exit(cmd_1, cmd_2, "fork");
	if (pid_2 == 0)
		child_two(cmd_1, cmd_2, argv[4], fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
}
