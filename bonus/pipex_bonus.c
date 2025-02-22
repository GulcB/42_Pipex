/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:28:56 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/22 13:53:11 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	b_child_process(t_pipex *ppx, char **av, char **env, int i)
{
	close(ppx->pipe_fd[0]);
	dup2(ppx->pipe_fd[1], 1);
	close(ppx->pipe_fd[1]);
	ppx->cmd = ft_split(av[i], ' ');
	ppx->cmd_path[i] = find_cmd_path(ppx, env);
	if (!ppx->cmd_path[i])
	{
		ft_putstr_fd(av[i], 2);
		b_error_msg(ERR_CMD, 1);
	}
	child_dup(ppx, i);
	close(ppx->pipe_fd[0]);
	close(ppx->pipe_fd[1]);
	if (execve(ppx->cmd_path[i], ppx->cmd, env) == -1)
	{
		free_list(ppx);
		b_error_msg(ERR_EXEC, 1);
	}
}

void	b_parent_process(t_pipex *ppx)
{
	close(ppx->pipe_fd[1]);
	dup2(ppx->pipe_fd[0], 0);
	close(ppx->pipe_fd[0]);
	wait(NULL);
}

void	*create_fork_process(t_pipex *ppx, char **av, char **env, int i)
{
	if (ppx->heredoc_mode == 1)
		i = 3;
	else
		i = 2;
	if (pipe(ppx->pipe_fd) == -1)
		b_error_msg(ERR_PIPE, 1);
	ppx->pid = fork();
	if (ppx->pid < 0)
		b_error_msg(ERR_FORK, 1);
	else if (ppx->pid == 0)
		b_child_process(ppx, av, env, i);
	else
		b_parent_process(ppx);
	return (0);
}

void	init_pipeline(t_pipex *ppx, char **av, int ac)
{
	ppx->cmd_count = ac - 3 - ppx->heredoc_mode;
	ppx->cmd_path = malloc(sizeof(char *) * ppx->cmd_count);
	if (!ppx->cmd_path)
		b_error_msg(ERR_CMD, 1);
	if (ppx->heredoc_mode)
	{
		ppx->fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (ppx->fd1 < 0)
			b_error_msg(ERR_OUTFILE, 1);
		process_heredoc(ppx, av);
	}
	else
	{
		ppx->fd0 = open(av[1], O_RDONLY);
		if (ppx->fd0 < 0)
		{
			unlink(av[1]);
			b_error_msg(ERR_INFILE, 1);
		}
		ppx->fd1 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (ppx->fd1 < 0)
			b_error_msg(ERR_OUTFILE, 1);
		dup2(ppx->fd0, 0);
		close(ppx->fd0);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex	ppx;
	int		i;

	i = 0;
	ppx.heredoc_mode = 0;
	if (ac < 5)
		b_error_msg(ERR_ARG, 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		ppx.heredoc_mode = 1;
	if (ac < 6 && ppx.heredoc_mode == 1)
		b_error_msg(ERR_ARG, 1);
	init_pipeline(&ppx, av, ac);
	i = 2 + ppx.heredoc_mode;
	while (i < ac - 1)
	{
		create_fork_process(&ppx, av, env, i);
		waitpid(ppx.pid, NULL, 0);
		i++;
	}
	dup2(ppx.fd1, 1);
	close(ppx.fd1);
	free_list(&ppx);
	return (0);
}
