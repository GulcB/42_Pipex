/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:55:55 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/19 15:38:06 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define ERR_ARG "Invalid number of arguments\n"
# define ERR_PIPE "Pipe error.\n"
# define ERR_CMD "Command not found\n"
# define ERR_FORK "Fork error.\n"
# define ERR_EXEC "Exec format error.\n"
# define ERR_INFILE "Input file error.\n"
# define ERR_OUTFILE "Output file error.\n"
# define ERR_DUP "Dup2 error.\n"

typedef struct s_pipex
{
	int			fd[2];
	int			fd0;
	int			fd1;
	char		*path;
	char		**full_path;
	char		**cmd;
	pid_t		pid1;
	pid_t		pid2;
}				t_pipex;

void	fork_pipex(t_pipex *ppx, char **av, char **envp);
char	*get_cmd_path(t_pipex *ppx, char **envp);
void	child_process(t_pipex *ppx, char **av, char **envp);
void	parent_process(t_pipex *ppx, char **av, char **envp);
void	close_pipes(t_pipex *ppx);
void	error_msg(char *err_msg, int exit_code);
void	ft_free(char **var);
void	free_src(t_pipex *ppx);

#endif
