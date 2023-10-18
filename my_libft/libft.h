/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:36:16 by hrandria          #+#    #+#             */
/*   Updated: 2023/10/15 17:53:21 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		xstrcmp(char *s1, char *s2);
char	*ft_strdup(const char *s);

#endif
