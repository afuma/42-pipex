/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:57:17 by blax              #+#    #+#             */
/*   Updated: 2023/09/24 21:29:02 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(char *envp[])
{
	const char	*prefix = "PATH=";
	char		**env;

	env = envp;
	while (*env)
	{
		if (ft_strncmp(*env, prefix, ft_strlen(prefix)) == 0)
			return (ft_strdup(*env + ft_strlen(prefix)));
		env++;
	}
	return (NULL);
}

int	init_pathes(t_data *cmd, char *envp[])
{
	char	*path;

	path = get_path(envp);
	if (path)
	{
		cmd->pathes = ft_split(path, ':');
		if (cmd->pathes == NULL)
			return (-1);
		free(path);
		path = NULL;
	}
	else
	{
		write(2, "Error: No path found!\n", 23);
		free_cmd(cmd);
		exit(EXIT_FAILURE);
	}
	return (1);
}

char	*ft_three_join(char *str_1, char *str_2, char *str_3)
{
	int		len;
	char	*result;

	len = ft_strlen(str_1) + ft_strlen(str_2) + ft_strlen(str_3);
	result = (char *) ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcat(result, str_1, ft_strlen(str_1) + 1);
	ft_strlcat(result, str_2, ft_strlen(str_1) + ft_strlen(str_2) + 1);
	ft_strlcat(result, str_3, len + 1);
	return (result);
}

void	find_cmd_path(t_data *data)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (data->pathes[i])
	{
		cmd_path = ft_three_join(data->pathes[i], "/", data->base);
		free(data->pathes[i]);
		if (access(cmd_path, F_OK) != -1)
		{
			if (data->path != NULL)
				(free(data->path), data->path = NULL);
			data->path = cmd_path;
		}
		else
			(free(cmd_path), cmd_path = NULL);
		i++;
	}
	free(data->pathes);
}
