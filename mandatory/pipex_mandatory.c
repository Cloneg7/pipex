/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mandatory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudar <hboudar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:03:09 by hboudar           #+#    #+#             */
/*   Updated: 2024/04/15 14:34:42 by hboudar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_mandatory.h"

void	error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

int	main(int ac, char *av[], char *env[])
{
	int	fd[2];
	int	pid;

	if (ac != 5)
	{
		write(2, "error: Invalid number of arguments\n", 35);
		return (1);
	}
	if (pipe(fd) == -1)
		error("pipe function");
	pid = fork();
	if (pid == -1)
		error("fork function");
	if (pid == 0)
		first_process(av, env, fd);
	else
	{
		if (waitpid(pid, NULL, 0) == -1)
			error("waitpid function");
		check_files(dup2(fd[0], 0), 0, close(fd[0]), close(fd[1]));
		last_process(av, env, fd);
	}
	check_env(env, 0);
	exit (EXIT_SUCCESS);
}
