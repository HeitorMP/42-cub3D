/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmoreira <nmoreira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 20:35:59 by nmoreira          #+#    #+#             */
/*   Updated: 2023/07/26 12:52:57 by nmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// char *ft_trim(const char *str)
// {
// 	int i;
// 	int len;
// 	char *result;

// 	len = 0;
// 	i = -1;
// 	while (*str == ' ' || *str == '\t' || *str == '\n')
// 		str++;
// 	while (str[len])
// 		len++;
// 	while (len > 0 && (str[len] == '\n' || str[len] == '\t' || str[len] == ' '))
// 		len--;
// 	printf("2 %d\n", len);
// 	result = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!result)
// 		return (NULL);
// 	result[len] = 0;
// 	i = len;
// 	while (len >=  0)
// 	{
// 		result[len] = str[i];
// 		len--;
// 		i--;
// 	}
// 	return (result);
// }

// char	*ft_trim(const char *str)
// {
// 	int		size;
// 	int		i;
// 	char	*out;

// 	out = NULL;
// 	if (!str)
// 		return (NULL);
// 	while (*str == ' ' || *str == '\t' || *str == '\n')
// 		str++;
// 	i = -1;
// 	size = 0;
// 	while (str[++i])
// 		size++;
// 	while (i > 0 && (str[--i] == ' ' || str[i] == '\t' || str[i] == '\n'))
// 		size--;
// 	out = malloc(sizeof(char) * (size + 1));
// 	if (!out)
// 		return (NULL);
// 	out[size] = 0;
// 	while (--size >= 0)
// 		out[size] = str[i--];
// 	return (out);
// }

char *ft_trim(const char *str)
{
	char *result;
	const char *end;
	size_t	size;
	size_t	i;

	if (!str)
		return NULL;
    // Encontra o início do conteúdo relevante, ignorando espaços em branco, tabulações e quebras de linha
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
		str++;
	if (*str == '\0') // Se a string consiste apenas de espaços em branco, retorna uma string vazia
	{
		char *result = malloc(1);
		if (result)
			result[0] = '\0';
		return (result);
	}
    // Encontra o final do conteúdo relevante
	end = str;
	while (*end)
		end++;
	end--;
    // printf("1 end %d\n", end[0]);
    // Remove espaços em branco, tabs e quebras de linha do final
	while (end >= str && ft_isspace(*end))
		end--;
	// printf("2 end %s\n", end);
	size = end - str + 1; // Tamanho do conteúdo relevante
	// printf("3 %ld\n", size);
	result = malloc(size + 1);
	if (!result)
		return (NULL);
    // Copia o conteúdo relevante para a nova string
	i = 0;
	while (i < size)
	{
		result[i] = str[i];
		i++;
	}
	result[size] = '\0'; // Adiciona o caractere nulo ao final
	return (result);
}
