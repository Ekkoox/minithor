/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roane <roane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:54:39 by enschnei          #+#    #+#             */
/*   Updated: 2025/01/31 17:12:02 by roane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_var = 0;

int main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	t_pipex pipex;
	t_token *token;
	t_minishell minishell;

	token = ft_calloc(sizeof(t_token), 1);
	pipex.ev = ev;
	creat_the_prompt(ev, &pipex, token, &minishell);
	return (EXIT_SUCCESS);
}

/*
regarde les pipe avec les heredoc genre :
minishell-:ls | << salut
1: la commande ne s'excute pas avec un heredoc qu'il soit avant ou apres
0: faut regarder la suppression du heredoc la solution doit etre la bas
regarde les expand genre;
minishell-:echo "$PWD"
1:le echo affiche bien la valeur de $PWD mais je sexfault juste apres
0:ca doit  etre un probleme au niveau des free
regarde la premier evariable de l'env et le controle C dasn le cat
*/

// echo $ ca bloque on peut plus faire de commande, le prompt bug
// echo '$PWD' ca segfault il expande alors quil ne devrait pas
// cat donne un prompt avec >> au lieu de >, ignorer le signaus dans le parents
// unset premiere variable denvironnement ne marche pas