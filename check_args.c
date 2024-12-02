/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:18:34 by vgalmich          #+#    #+#             */
/*   Updated: 2024/12/02 16:51:08 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

// utiliser atol

int	is_digit(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9' || ft_strlen(argv[i] > 10))
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5)
		return (0);
	if (ft_atol(argv[1]) <= 0 || is_digit(argv[1]) == 0)
		return (printf("Invalid number of philosophers\n"));
	if (ft_atol(argv[2]) <= 0 || is_digit(argv[2]) == 0)
		return (printf("Invalid time to die\n"));
	if (ft_atol(argv[3]) <= 0 || is_digit(argv[3]) == 0)
		return (printf("Invalid time to eat\n", 21));
	if (ft_atol(argv[4]) <= 0 || is_digit(argv[4]) == 0)
		return (printf("Invalid time to sleep\n", 23));
	if (argv[5] && (ft_atol(argv[5]) < 0 || is_digit(argv[5]) == 0))
		return (printf("Invalid number of times each philo must eat\n"));
	return (1);
}

/*
int main(int argc, char **argv)
{
	if (check_args(argc, argv) == 1)
		return (1);
	return (0);
}
*/
