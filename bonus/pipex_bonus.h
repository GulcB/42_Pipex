/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:24:12 by gbodur            #+#    #+#             */
/*   Updated: 2025/03/01 04:15:33 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

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
	pid_t		pid;
	int			**pipe_fd;
	int			heredoc_fd[2];
	int			cmd_count;
	int			fd0;
	int			fd1;
	int			heredoc_mode;
	char		**cmd_path;
	char		**full_path;
	char		**cmd;
}				t_pipex;

void	b_child_process(t_pipex *ppx, char **av, char **envp, int i);
void	create_fork_process(t_pipex *ppx, char **av, char **evp, int i);
void	setup_files(t_pipex *ppx, char **av, int ac);
void	init_pipeline(t_pipex *ppx, char **av, int ac);
char	*find_cmd_path(t_pipex *ppx, char **envp);
void	process_heredoc(t_pipex *ppx, char **av);
void	b_setup_cmd_exec(t_pipex *ppx, char **av, char **env, int cmd_i);
void	b_error_msg(char *err_msg, int exit_code);
void	free_list(t_pipex *ppx);
void	ft_free_fullpath(t_pipex *ppx);
void	ft_free(char **del);
void	b_close_pipes(t_pipex *ppx);
void	b_free_pipes(t_pipex *ppx);

#endif
