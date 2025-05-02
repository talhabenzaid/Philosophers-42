/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:26 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/05/02 18:52:36 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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


int is_valid_number_format(char *str)
{
    int j = 0;
    
    while (str[j])
    {
        if ((str[j] == '+' && str[j + 1] == '+') || (str[j]=='+' && str[j - 1]))
        {
            printf("invalide argument\n");
            return (0);
        }
        if (str[j] != '+' && (str[j] < '0' || str[j] > '9'))
        {
            printf("invalide argument\n");
            return (0);
        }
        j++;
    }
    return (1);
}

int check_value_limits(char **str)
{
    if (ft_atoi(str[1]) > 200)
    {
        printf("number_of_philosophers must be less than 200\n");
        return (0);
    }
    return (1);
}

int validate_arg_values(char **str)
{
    int i = 1;
    int val;
    
    while (str[i])
    {
        if (ft_atoi(str[i]) == 0)
        {
            printf("invalide argument\n");
            return (0);
        }
        if (!is_valid_number_format(str[i]))
            return (0);
        val = ft_atoi(str[i]);
        if (val == -1)
        {
            printf("invalide argument\n");
            return (0);
        }
        i++;
    }
    return (check_value_limits(str));
}

int pars(char **str, int argc)
{
    if (argc != 5 && argc != 6)
    {
        printf("invalide argument\n");
        return (0);
    }
    
    if (!validate_arg_values(str))
        return (0);
    return (1);
}