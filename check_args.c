/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:18:34 by vgalmich          #+#    #+#             */
/*   Updated: 2024/11/28 19:08:06 by vgalmich         ###   ########.fr       */
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
		return (write(2, "Invalid number of philosophers\n", 32), 1);
	if (ft_atol(argv[2]) <= 0 || is_digit(argv[2]) == 0)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atol(argv[3]) <= 0 || is_digit(argv[3]) == 0)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atol(argv[4]) <= 0 || is_digit(argv[4]) == 0)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atol(argv[5]) < 0 || is_digit(argv[5]) == 0))
		return (write(2,
				"Invalid number of times each philo must eat\n", 54), 1);
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
