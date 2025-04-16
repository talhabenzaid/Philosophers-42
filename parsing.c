/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenzaid <tbenzaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:54:26 by tbenzaid          #+#    #+#             */
/*   Updated: 2025/04/16 17:46:47 by tbenzaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_atoi(char *str)
{
    int i;
    int r;

    i = 0;
    r = 1;
    if(!str)
        return(0);
    while(str[i])
    {
        r = r * 10 + str[i] - '0';
        i++;
    }
    return(r);
}
int pars(char **str,int argc)
{
    int i;
    int j;

    if(argc != 5 && argc != 6)
        printf("invalide argument\n");
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
    if(str[1] && ft_atoi(str[1]) >= 200)
    {
        printf("number_of_philosophers must be less than 200\n");
        return(1);
    }
    return(0);
}