/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_be_fair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmougino <nmougino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 21:25:18 by nmougino          #+#    #+#             */
/*   Updated: 2017/10/25 14:04:43 by nmougino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	to_be_fair(void)
{
	history_add("base64 /dev/urandom | head -c 1000 | grep 42 | wc -l | se\
d -e 's/1/Yes/g' -e 's/0/No/g'");
	history_add("mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; c\
at fifi");
	history_add("cd /tmp; sort << EOF | cat -e > sorted_poem ; sed -e 's/Roses\
/Turnips/' < sorted_poem > better_poem; cd -; echo \"I prefer turnips any\
way\" >> /tmp/better_poem; cat /tmp/better_poem");
	history_add("mkdir toto; cd toto ; rm -rf ../toto ; cd . ; cd .. ; cd -");
	history_add("chmod 777 toto; rm -rf toto; mkdir toto; cd toto; chmod 00\
0 .; unsetenv PWD OLDPWD; cd ..");
	history_add("mkdir toto ; cd toto ; rm -rf ../toto ; cd ..");
	history_add("mkdir toto ; cd toto ; rm -rf ../toto ; unsetenv PWD OLD\
PWD; cd .");
}
