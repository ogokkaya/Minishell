/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:58:22 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/20 18:25:02 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// "_" KONTROLÜ DE OLAN BİR SİLME KONTROLÜ YAPILACAK

int check__unset(t_mshell *shell, char *name)
{
    if (ft_strcmp(name, "_") == 0)
    {
        printf("minishell: unset: _: not allowed\n");
        return (1);
    }
    return (0);
}


//SİLME İŞLEMİ SIRASINDA ENVİRONMENT LİSTESİNDE OLMAYAN BİR DEĞİŞKEN SİLİNMEYE ÇALIŞILIRSA HATA MESAJI VERİLECEK

//SİLME İŞLEMİ SIRASINDA ENVİRONMENT LİSTESİNDE OLAN BİR DEĞİŞKEN SİLİNİRSE SİLİNDİ MESAJI VERİLECEK
//BURADA ENV YAPISINDA OLAN BİR DEĞİŞKENSE DİREKT LİSTEDEKİ SIRASINDA GÜNCELLENEBİLİR