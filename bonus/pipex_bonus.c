/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:28:56 by gbodur            #+#    #+#             */
/*   Updated: 2025/03/03 01:02:48 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	b_check_arg(t_pipex *ppx, int ac, char **av)
{
	if (ac < 5)
		b_error_msg(ERR_ARG, 2);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		ppx->heredoc_mode = 1;
	if (ac < 6 && ppx->heredoc_mode == 1)
		b_error_msg(ERR_ARG, 2);
}

void	b_child_process(t_pipex *ppx, char **av, char **env, int i)
{
	int	cmd_i;

	cmd_i = i - 2 - ppx->heredoc_mode;
	if (cmd_i == 0)
	{
		if (dup2(ppx->pipe_fd[cmd_i][1], 1) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	else if (cmd_i < ppx->cmd_count - 1)
	{
		if (dup2(ppx->pipe_fd[cmd_i - 1][0], 0) == -1)
			b_error_msg(ERR_DUP, 1);
		if (dup2(ppx->pipe_fd[cmd_i][1], 1) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	else
	{
		if (dup2(ppx->pipe_fd[cmd_i - 1][0], 0) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	b_close_pipes(ppx);
	ppx->cmd = ft_split(av[i], ' ');
	b_setup_cmd_exec(ppx, av, env, cmd_i);
}

void	create_fork_process(t_pipex *ppx, char **av, char **env, int i)
{
	ppx->pid = fork();
	if (ppx->pid < 0)
		b_error_msg(ERR_FORK, 1);
	else if (ppx->pid == 0)
		b_child_process(ppx, av, env, i);
}

void	init_pipeline(t_pipex *ppx, char **av, int ac)
{
	int	i;

	ppx->cmd_count = ac - 3 - ppx->heredoc_mode;
	ppx->cmd_path = malloc(sizeof(char *) * (ppx->cmd_count * 2));
	ppx->pipe_fd = malloc(sizeof(int *) * (ppx->cmd_count + 1));
	if (!ppx->pipe_fd)
		b_error_msg(ERR_PIPE, 1);
	i = 0;
	while (i < ppx->cmd_count)
	{
		ppx->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!ppx->pipe_fd[i])
			b_error_msg(ERR_PIPE, 1);
		if (pipe(ppx->pipe_fd[i]) == -1)
			b_error_msg(ERR_PIPE, 1);
		i++;
	}
	if (!ppx->cmd_path)
		b_error_msg(ERR_CMD, 127);
	i = 0;
	while (i < (ppx->cmd_count * 2))
		ppx->cmd_path[i++] = NULL;
	setup_files(ppx, av, ac);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	ppx;
	int		i;

	ppx.cmd_path = NULL;
	ppx.full_path = NULL;
	ppx.cmd = NULL;
	ppx.pipe_fd = NULL;
	ppx.heredoc_mode = 0;
	b_check_arg(&ppx, ac, av);
	init_pipeline(&ppx, av, ac);
	i = 2 + ppx.heredoc_mode;
	while (i < ac - 1)
	{
		create_fork_process(&ppx, av, env, i);
		i++;
	}
	b_close_pipes(&ppx);
	waitpid(ppx.pid, NULL, 0);
	close(ppx.fd1);
	free_list(&ppx);
	b_free_pipes(&ppx);
	return (0);
}
