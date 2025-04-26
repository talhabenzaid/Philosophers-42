/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:26 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/26 20:17:20 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <limits.h>

int ft_atoi(char *str)
{
    int i = 0;
    long result = 0;

    if (!str)
        return (0);
    while (str[i] == '+' || str[i] == ' ')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        if (result > INT_MAX)
            return (-1);
        i++;
    }
    return ((int)result);
}


int pars(char **str, int argc)
{
    int i, j, val;

    if (argc != 5 && argc != 6)
    {
        printf("invalide argument\n");
        return (0);
    }
    i = 1;
    while (str[i])
    {
        j = 0;
        if (str[i][0] == '0')
        {
            printf("invalide argument\n");
            return (0);
        }
        while (str[i][j])
        {
            if (str[i][j] == '+' && str[i][j + 1] == '+')
            {
                printf("invalide argument\n");
                return (0);
            }
            if (str[i][j] != '+' && (str[i][j] < '0' || str[i][j] > '9'))
            {
                printf("invalide argument\n");
                return (0);
            }
            j++;
        }
        val = ft_atoi(str[i]);
        if (val == -1)
        {
            printf("invalide argument\n");
            return (0);
        }
        i++;
    }
    if (ft_atoi(str[1]) > 200)
    {
        printf("number_of_philosophers must be less than 200\n");
        return (0);
    }
    return (1);
}
