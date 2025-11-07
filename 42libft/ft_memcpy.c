/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rucosta <rucosta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:04:44 by rucosta         #+#    #+#             */
/*   Updated: 2025/04/07 18:46:03 by rucosta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

/* int main()
{
	char csrc[] = "GeeksforGeeks"; 
	char cdest[100]; 
	ft_memcpy(cdest, csrc, strlen(csrc)+1); 
	printf("Copied string is %s", cdest); 

	int isrc[] = {10, 20, 30, 40, 50}; 
	int n = sizeof(isrc)/sizeof(isrc[0]); 
	int idest[n], i; 
	ft_memcpy(idest, isrc, sizeof(isrc)); 
	printf("\nCopied array is "); 
	for (i=0; i<n; i++) 
		printf("%d ", idest[i]); 
	return 0; 
} */