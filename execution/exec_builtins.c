/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahel-bah <ahel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 08:17:37 by waelhamd          #+#    #+#             */
/*   Updated: 2022/09/11 01:53:45 by ahel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtins(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp(cmd, "cd"))
		return (true);
	else if (!ft_strcmp(cmd, "pwd"))
		return (true);
	else if (!ft_strcmp(cmd, "echo"))
		return (true);
	else if (!ft_strcmp(cmd, "env"))
		return (true);
	else if (!ft_strcmp(cmd, "export"))
		return (true);
	else if (!ft_strcmp(cmd, "unset"))
		return (true);
	else if (!ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

int	exec_builtins(char **cmd, t_red *red, t_env *env)
{
	int	fd[2];

	if (!cmd[0] || is_builtins(cmd[0]) == false)
		return (0);
	fd[0] = dup(0);
	fd[1] = dup(1);
	if (check_redirections(red))
	{
		if (!ft_strcmp(cmd[0], "cd"))
			ft_cd(cmd, env);
		else if (!ft_strcmp(cmd[0], "pwd"))
			ft_pwd(cmd, env);
		else if (!ft_strcmp(cmd[0], "echo"))
			ft_echo(cmd);
		else if (!ft_strcmp(cmd[0], "env"))
			ft_env_cmd(env, cmd);
		else if (!ft_strcmp(cmd[0], "export"))
			ft_export(cmd, &env);
		else if (!ft_strcmp(cmd[0], "unset"))
			ft_unset(cmd, env);
		else if (!ft_strcmp(cmd[0], "exit"))
			ft_exit(cmd, env);
	}
	return (dup2(fd[0], 0), dup2(fd[1], 1), close(fd[0]), close(fd[1]), 1);
}
