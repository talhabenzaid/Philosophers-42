/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:26 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/18 15:47:36 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_atoi(char *str)
{
    int i = 0;
    int result = 0;

    if (!str)
        return (0);
    
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}

int pars(char **str,int argc)
{
    int i;
    int j;

    if(argc != 5 && argc != 6)
    {
        printf("invalide argument\n");
        return(1);
    }
    i = 1;
    while(str[i])
    {
        j = 0;
        while(str[i][j])
        {
            if(str[i][j] != '+' && (str[i][j] < '0' || str[i][j] > '9'))
            {
                printf("invalide argument\n");
                return(1);
            }
            j++;
        }
        i++;
    }
    if(ft_atoi(str[1]) >= 200)
    {
        printf("number_of_philosophers must be less than 200\n");
        return(1);
    }
    return(0);
}