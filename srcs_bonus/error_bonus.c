/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bterral <bterral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:59:01 by bterral           #+#    #+#             */
/*   Updated: 2022/02/09 10:31:36 by bterral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	perror_exit(char *error_msg)
{
	perror(error_msg);
	exit(1);
}

int	return_error(char *err_msg)
{
	write(2, err_msg, ft_strlen(err_msg));
	return (1);
}
