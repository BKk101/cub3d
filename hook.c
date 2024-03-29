/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bykim <bykim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 03:28:57 by bykim             #+#    #+#             */
/*   Updated: 2020/11/16 11:10:20 by bykim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 13)
		vars->player.key = 'W';
	else if (keycode == 0)
		vars->player.key = 'A';
	else if (keycode == 1)
		vars->player.key = 'S';
	else if (keycode == 2)
		vars->player.key = 'D';
	else if (keycode == 124)
		vars->player.key = 'R';
	else if (keycode == 123)
		vars->player.key = 'L';
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	vars->player.key = 0;
	return (keycode);
}

int	mouse(int button, int x, int y, t_vars *vars)
{
	printf("%d x:%d y:%d\n", button, x, y);
	(void)vars;
	return (0);
}

int	exit_prog(int vars)
{
	exit(0);
	return (vars);
}
