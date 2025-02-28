/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbodur <gbodur@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 19:20:21 by gbodur            #+#    #+#             */
/*   Updated: 2025/02/28 19:20:24 by gbodur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (const unsigned char *) s1;
	ptr2 = (const unsigned char *) s2;
	if (!n)
		return (0);
	while ((n - 1) && *ptr1 && *ptr2)
	{
		if (*ptr1 > *ptr2)
			return (*ptr1 - *ptr2);
		if (*ptr1 < *ptr2)
			return (*ptr1 - *ptr2);
		ptr1++;
		ptr2++;
		n--;
	}
	return (*ptr1 - *ptr2);
}
