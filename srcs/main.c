/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edesaint <edesaint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:46:24 by edesaint          #+#    #+#             */
/*   Updated: 2023/09/24 21:29:11 by edesaint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	cmd_1;
	t_data	cmd_2;

	if (argc != 5)
		(write(1, "Invalid number of arguments !", 30), exit(1));
	if (init_cmd(&cmd_1, argv[2], envp) == -1)
		(perror(argv[2]), free_cmd(&cmd_1), exit(1));
	if (init_cmd(&cmd_2, argv[3], envp) == -1)
		(perror(argv[3]), free_cmd(&cmd_1), free_cmd(&cmd_2), exit(1));
	pipex(&cmd_1, &cmd_2, argv);
	free_cmd(&cmd_1);
	free_cmd(&cmd_2);
	return (0);
}
