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

void debug_print(char *msg)
{
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
}

void	b_child_process(t_pipex *ppx, char **av, char **env, int i)
{
	int	cmd_i;

    debug_print("child_process: starting");

	cmd_i = i - 2 - ppx->heredoc_mode;
	debug_print("File descriptors before redirection:");
	if (i != 2 || ppx->heredoc_mode == 1)
	{
		if (dup2(ppx->pipe_fd[0], 0) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	close(ppx->pipe_fd[0]);
	if (cmd_i != ppx->cmd_count - 1)
	{
		if (dup2(ppx->pipe_fd[1], 1) == -1)
			b_error_msg(ERR_DUP, 1);
	}
	close(ppx->pipe_fd[1]);
	ppx->cmd = ft_split(av[i], ' ');
	debug_print("child_process: executing command");
	b_setup_cmd_exec(ppx, av, env, cmd_i);
	debug_print("child_process: completed (should not see this)");
}

void	b_parent_process(t_pipex *ppx)
{
	debug_print("parent_process: starting");
	close(ppx->pipe_fd[1]);
	if (dup2(ppx->pipe_fd[0], 0) == -1)
		b_error_msg(ERR_DUP, 1);
	close(ppx->pipe_fd[0]);
	debug_print("parent_process: completed");
}

void	*create_fork_process(t_pipex *ppx, char **av, char **env, int i)
{
	debug_print("create_fork: starting");
	if (pipe(ppx->pipe_fd) == -1)
		b_error_msg(ERR_PIPE, 1);
	ppx->pid = fork();
	if (ppx->pid < 0)
		b_error_msg(ERR_FORK, 1);
    else if (ppx->pid == 0)
    {
        debug_print("create_fork: child process starting");
        b_child_process(ppx, av, env, i);
    }
    else
    {
        debug_print("create_fork: parent process starting");
        b_parent_process(ppx);
        debug_print("create_fork: parent process completed");
    }
    debug_print("create_fork: completed");
	return (0);
}

void	init_pipeline(t_pipex *ppx, char **av, int ac)
{
	int	i;

	ppx->cmd_count = ac - 3 - ppx->heredoc_mode;
	ppx->cmd_path = malloc(sizeof(char *) * (ppx->cmd_count * 2));
	if (!ppx->cmd_path)
		b_error_msg(ERR_CMD, 1);
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
	ppx.heredoc_mode = 0;
	if (ac < 5)
		b_error_msg(ERR_ARG, 1);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		ppx.heredoc_mode = 1;
	if (ac < 6 && ppx.heredoc_mode == 1)
		b_error_msg(ERR_ARG, 1);
	init_pipeline(&ppx, av, ac);
	debug_print("main: pipeline initialized");
	i = 2 + ppx.heredoc_mode;
	while (i < ac - 1)
	{
		debug_print("main: creating fork process");
		create_fork_process(&ppx, av, env, i);
        debug_print("main: waiting for child");
		waitpid(ppx.pid, NULL, 0);
		debug_print("main: child completed");
		i++;
	}
	debug_print("main: all processes completed");

	dup2(ppx.fd1, 1);
	close(ppx.fd1);
	free_list(&ppx);
	return (0);
}
