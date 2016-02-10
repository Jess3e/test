/*

    Copyright (c) 2015 Jessee Lefebvre

    L'autorisation est accordée, gracieusement, à toute personne acquérant une
    copie de cette bibliothèque et des fichiers de documentation associés
    (la "Bibliothèque"), de commercialiser la Bibliothèque sans restriction,
    notamment les droits d'utiliser, de copier, de modifier, de fusionner, de
    publier, de distribuer, de sous-licencier et / ou de vendre des copies de
    la Bibliothèque, ainsi que d'autoriser les personnes auxquelles la
    Bibliothèque est fournie à le faire, sous réserve des conditions suivantes:

    La déclaration de copyright ci-dessus et la présente autorisation doivent
    être incluses dans toutes copies ou parties substantielles de la
    Bibliothèque.

    LA BIBLIOTHÈQUE EST FOURNIE "TELLE QUELLE", SANS GARANTIE D'AUCUNE SORTE,
    EXPLICITE OU IMPLICITE, NOTAMMENT SANS GARANTIE DE QUALITÉ MARCHANDE,
    D’ADÉQUATION À UN USAGE PARTICULIER ET D'ABSENCE DE CONTREFAÇON. EN AUCUN
    CAS, LES AUTEURS OU TITULAIRES DU DROIT D'AUTEUR NE SERONT RESPONSABLES DE
    TOUT DOMMAGE, RÉCLAMATION OU AUTRE RESPONSABILITÉ, QUE CE SOIT DANS LE
    CADRE D'UN CONTRAT, D'UN DÉLIT OU AUTRE, EN PROVENANCE DE, CONSÉCUTIF À OU
    EN RELATION AVEC LA BIBLIOTHÈQUE OU SON UTILISATION, OU AVEC D'AUTRES
    ÉLÉMENTS DE LA BIBLIOTHÈQUE.

*/

/**
 *  \file arbre_binaire.c
 *
 *  Fichier d'implémentation contenant la structure de donnée 'arbre_binaire'.
 *  Un Arbre Binaire est un arbre qui contient une valeur à la racine et qui
 *  peut avoir aucun, un ou deux enfants qui eux aussi ont une valeur et qu'ils
 *  peuvent avoir des enfants.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


#include "arbre_binaire.h"

/**
 * \brief Un arbre binaire qui contient une valeur et des enfants.
 */
struct arbre_binaire_struct {
    struct arbre_binaire_struct* premier_enfant;
	struct arbre_binaire_struct* second_enfant;
	int valeur;
    bool a_erreur;
    char* erreur;
};

/**
 *  \brief Créer un nouvel arbre binaire.
 *  
 *  \param valeur La valeur de la racine de l'arbre
 *
 *  \return L'arbre binaire
 */
arbre_binaire* creer_arbre_binaire(int a_valeur)
{
	arbre_binaire* l_result;
	l_result = calloc(1, sizeof(arbre_binaire));
	if (l_result) {
		l_result->premier_enfant = NULL;
		l_result->second_enfant = NULL;
		l_result->valeur = a_valeur;
		l_result->a_erreur = false;
        l_result->erreur = calloc(ERREUR_TAILLE, sizeof(char));
	}
	return l_result;
}

/**
 *  \brief Lire dans un fichier un arbre binaire
 *  
 *  \param arbre L'arbre_binaire à lire du fichier
 *  \param fichier Le fichier à lire
 */
void lire_arbre_binaire(arbre_binaire* a_arbre, FILE* a_fichier)
{
	int l_contenu[3];
	fread(l_contenu, sizeof(int), 3, a_fichier);
	modifier_element_arbre_binaire(a_arbre, l_contenu[0]);
	if (l_contenu[1] == 1) {
		creer_premier_enfant_arbre_binaire(a_arbre, 0);
		lire_arbre_binaire(a_arbre->premier_enfant, a_fichier);
	}
	if (l_contenu[2] == 1) {
		creer_second_enfant_arbre_binaire(a_arbre, 0);
		lire_arbre_binaire(a_arbre->second_enfant, a_fichier);
	}
}

/**
 *  \brief Créer un nouvel arbre_binaire depuis un fichier.
 *
 *  Créer un nouvel liste_tableau et charge le contenue du fichier
 *  'nom_fichier' dans l'arbre. Si le fichier n'est pas valide, indique
 *  l'erreur dans 'arbre'->'erreur'.
 *
 *  \param nom_fichier Le nom du fichier contenant l'arbre
 *
 *  \return L'arbre_binaire
 *
 *  \note Le fichier doit être créé à l'aide de la routine 
 *  “sauvegarder_arbre_binaire”
 */
arbre_binaire* charger_arbre_binaire(char* a_nom_fichier)
{
	FILE* l_fichier;
	l_fichier = fopen(a_nom_fichier, "rb");
	arbre_binaire* l_result = creer_arbre_binaire(0);
	if (l_fichier) {
		lire_arbre_binaire(l_result, l_fichier);
		fclose(l_fichier);
	} else {
		inscrire_erreur_arbre_binaire(l_result, 
			"Ne peux pas ouvrir le fichier en lecture.");
	}
	return l_result;
}

/**
 *  \brief Effectue la désallocation d'un arbre_binaire
 *
 *  \param arbre L'arbre_binaire à désallouer
 */
void detruire_arbre_binaire(arbre_binaire* a_arbre)
{
	if (a_arbre->premier_enfant) {
		detruire_arbre_binaire(a_arbre->premier_enfant);
		a_arbre->premier_enfant = NULL;
	}
	if (a_arbre->second_enfant) {
		detruire_arbre_binaire(a_arbre->second_enfant);
		a_arbre->second_enfant = NULL;
	}
	free(a_arbre->erreur);
	free(a_arbre);
}

/**
 *  \brief Écrit dans un fichier un arbre binaire
 *  
 *  \param arbre L'arbre_binaire à écrire dans le fichier
 *  \param fichier Le fichier à écrire
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void ecrire_arbre_binaire(arbre_binaire* a_arbre, FILE* a_fichier)
{
	int l_contenu[3];
	l_contenu[0] = a_arbre->valeur;
	if (a_arbre->premier_enfant) {
		l_contenu[1] = 1;
	} else {
		l_contenu[1] = 0;
	}
	if (a_arbre->second_enfant) {
		l_contenu[2] = 1;
	} else {
		l_contenu[2] = 0;
	}
	fwrite(l_contenu, sizeof(int), 3, a_fichier);
	if (a_arbre->premier_enfant) {
		ecrire_arbre_binaire(a_arbre->premier_enfant, a_fichier);
	}
	if (a_arbre->second_enfant) {
		ecrire_arbre_binaire(a_arbre->second_enfant, a_fichier);
	}
}

/**
 *  \brief Sauvegarder l'arbre_binaire dans un fichier
 *
 *  Sauvegarde le contenue de l''arbre' dans le fichier 'nom_fichier'.
 *  Si le fichier n'est pas valide, indique l'erreur dans 'arbre'->'erreur'.
 *
 *  \param arbre L'arbre_binaire
 *  \param nom_fichier Le nom du fichier à sauvegarder l'arbre
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void sauvegarder_arbre_binaire(arbre_binaire* a_arbre, char* a_nom_fichier)
{
	FILE* l_fichier;
	retirer_erreur_arbre_binaire(a_arbre);
	l_fichier = fopen(a_nom_fichier, "wb");
	if (l_fichier) {
		ecrire_arbre_binaire(a_arbre, l_fichier);
		fclose(l_fichier);
	} else {
		inscrire_erreur_arbre_binaire(a_arbre, 
			"Ne peux pas ouvrir le fichier en écriture.");
	}
}
 
/**
 *  \brief Renvoie le nombre d'éléments de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return Le nombre d'éléments dans l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int nombre_elements_arbre_binaire(arbre_binaire* a_arbre)
{
	int l_nombre_elements = 1;
	if (a_arbre->premier_enfant) {
		l_nombre_elements = l_nombre_elements + 
			nombre_elements_arbre_binaire(a_arbre->premier_enfant);
	}
	if (a_arbre->second_enfant) {
		l_nombre_elements = l_nombre_elements + 
			nombre_elements_arbre_binaire(a_arbre->second_enfant);
	}
	return l_nombre_elements;
}

/**
 *  \brief Renvoie le nombre de feuilles de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return Le nombre de feuilles dans l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int nombre_feuilles_arbre_binaire(arbre_binaire* a_arbre)
{
	int l_nombre_feuilles = 0;
	if (!a_arbre->premier_enfant && !a_arbre->second_enfant) {
		l_nombre_feuilles = 1;
	} else {
		if (a_arbre->premier_enfant) {
			l_nombre_feuilles = l_nombre_feuilles + 
				nombre_feuilles_arbre_binaire(a_arbre->premier_enfant);
		}
		if (a_arbre->second_enfant) {
			l_nombre_feuilles = l_nombre_feuilles + 
				nombre_feuilles_arbre_binaire(a_arbre->second_enfant);
		}
	}
	return l_nombre_feuilles;
}

/**
 *  \brief Renvoie la hauteur de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return La hauteur de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int hauteur_arbre_binaire(arbre_binaire* a_arbre)
{
	int l_hauteur = 1;
	if (a_arbre->premier_enfant || a_arbre->second_enfant) {
		int l_hauteur_premier_enfant;
		int l_hauteur_second_enfant;
		if (a_arbre->premier_enfant) {
			l_hauteur_premier_enfant = 
				hauteur_arbre_binaire(a_arbre->premier_enfant);
		} else {
			l_hauteur_premier_enfant = 0;
		}
		if (a_arbre->second_enfant) {
			l_hauteur_second_enfant = 
				hauteur_arbre_binaire(a_arbre->second_enfant);
		} else {
			l_hauteur_second_enfant = 0;
		}
		if (l_hauteur_premier_enfant >= l_hauteur_second_enfant) {
			l_hauteur = l_hauteur + l_hauteur_premier_enfant;
		} else {
			l_hauteur = l_hauteur + l_hauteur_second_enfant;
		}
	}
	return l_hauteur;
}

/**
 *  \brief Renvoie l'élément contenu dans la racine de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return La valeur de l'élément contenu dans la racine de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int element_arbre_binaire(arbre_binaire* a_arbre)
{
	return a_arbre->valeur;
}

/**
 *  \brief Modifie l'élément contenu dans la racine de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *  \param valeur La valeur à mettre dans la racine de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void modifier_element_arbre_binaire(arbre_binaire* a_arbre, int a_valeur)
{
	a_arbre->valeur = a_valeur;
}

/**
 *  \brief Regarde dans l''arbre' s'il contient la 'valeur'.
 *
 *  \param arbre L'arbre_binaire à rechercher la valeur
 *  \param valeur La valeur à rechercher dans l''arbre'
 *
 *  \return true si la valeur existe dans l''arbre', false sinon.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
bool contient_element_arbre_binaire(arbre_binaire* a_arbre, int a_valeur)
{
	bool l_contient = false;
	if (a_arbre->valeur == a_valeur) {
		l_contient = true;
	} else {
		if (a_arbre->premier_enfant) {
			if (contient_element_arbre_binaire(a_arbre->premier_enfant,
			a_valeur)) {
				l_contient = true;
			}
		}
		if (a_arbre->second_enfant) {
			if (contient_element_arbre_binaire(a_arbre->second_enfant,
			a_valeur)) {
				l_contient = true;
			}
		}
	}
	return l_contient;
}

/**
 *  \brief Retourne le premier enfant de l''arbre' ou 'NULL' si l''arbre' n'a
 *         pas de premier enfant.
 *
 *  \param arbre L'arbre_binaire à regarder son premier enfant.
 *
 *  \return le premier enfant de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
arbre_binaire* premier_enfant_arbre_binaire(arbre_binaire* a_arbre)
{
	retirer_erreur_arbre_binaire(a_arbre);
	arbre_binaire* l_premier_enfant = NULL;
	if (a_arbre->premier_enfant) {
		l_premier_enfant = a_arbre->premier_enfant;
	} else {
		inscrire_erreur_arbre_binaire(a_arbre,
			"L'arbre n'a aucun premier enfant.");
	}
	return l_premier_enfant;
}

/**
 *  \brief Ajoute un premier enfant d'un 'arbre' et place la valeur dans la
 *         racine de cet enfant.
 *
 *  \param arbre L'arbre_binaire à ajouter un premier enfant
 *  \param valeur La valeur à mettre dans la racine du premier enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void creer_premier_enfant_arbre_binaire(arbre_binaire* a_arbre, int a_valeur)
{
	if (!a_arbre->premier_enfant) {
		arbre_binaire* l_premier_enfant = creer_arbre_binaire(a_valeur);
		a_arbre->premier_enfant = l_premier_enfant;
	} else {
		inscrire_erreur_arbre_binaire(a_arbre, "Premier enfant déja existant.");
	}
}

/**
 *  \brief Libère le premier enfant d'un 'arbre'.
 *
 *  \param arbre L'arbre_binaire à retirer le premier enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void retirer_premier_enfant_arbre_binaire(arbre_binaire* a_arbre)
{
	if (a_arbre->premier_enfant) {
		detruire_arbre_binaire(a_arbre->premier_enfant);
		a_arbre->premier_enfant = NULL;
	} else {
		inscrire_erreur_arbre_binaire(a_arbre,
			"Aucun premier enfant à enlever.");
	}
}

/**
 *  \brief Retourne le second enfant de l''arbre' ou 'NULL' si l''arbre' n'a
 *         pas de second enfant.
 *
 *  \param arbre L'arbre_binaire à regarder son second enfant.
 *
 *  \return le second enfant de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
arbre_binaire* second_enfant_arbre_binaire(arbre_binaire* a_arbre)
{
	retirer_erreur_arbre_binaire(a_arbre);
	arbre_binaire* l_second_enfant = NULL;
	if (a_arbre->second_enfant) {
		l_second_enfant = a_arbre->second_enfant;
	} else {
		inscrire_erreur_arbre_binaire(a_arbre,
			"L'arbre n'a aucun premier enfant.");
	}
	return l_second_enfant;
}

/**
 *  \brief Ajoute un second enfant d'un 'arbre' et place la valeur dans la
 *         racine de cet enfant.
 *
 *  \param arbre L'arbre_binaire à ajouter un second enfant
 *  \param valeur La valeur à mettre dans la racine du second enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void creer_second_enfant_arbre_binaire(arbre_binaire* a_arbre, int a_valeur)
{
	if (!a_arbre->second_enfant) {
		arbre_binaire* l_second_enfant = creer_arbre_binaire(a_valeur);
		a_arbre->second_enfant = l_second_enfant;
	} else {
		inscrire_erreur_arbre_binaire(a_arbre, "Second enfant déja existant.");
	}
}

/**
 *  \brief Libère le premier enfant d'un 'arbre'.
 *
 *  \param arbre L'arbre_binaire à retirer le premier enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void retirer_second_enfant_arbre_binaire(arbre_binaire* a_arbre)
{
	if (a_arbre->second_enfant) {
		detruire_arbre_binaire(a_arbre->second_enfant);
		a_arbre->second_enfant = NULL;
	} else {
		inscrire_erreur_arbre_binaire(a_arbre,
			"Aucun second enfant à enlever.");
	}
}

/**
 *  \brief Indique si l''arbre' contient une erreur
 *
 *  \return true si l''arbre' contient une erreur, false sinon.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
bool a_erreur_arbre_binaire(arbre_binaire* a_arbre)
{
	bool l_erreur = a_arbre->a_erreur;
	if (!l_erreur) {
		if (a_arbre->premier_enfant) {
			if (a_erreur_arbre_binaire(a_arbre->premier_enfant)) {
				l_erreur = true;
			}
		}
		if (!l_erreur) {
			if (a_arbre->second_enfant) {
				if (a_erreur_arbre_binaire(a_arbre->second_enfant)) {
					l_erreur = true;
				}
			}
		}
	}
	return l_erreur;
}

/**
 *  \brief Indique le texte de l'erreur contenue dans 'arbre'
 *
 *  Si 'a_erreur_arbre_binaire' indique que l''arbre' contient une erreur,
 *  retourne l'erreur qu'il contient. Si 'a_erreur_arbre_binaire' est Faux,
 *  Retourne une chaine vide.
 *
 *  \return Le texte de l'erreur.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
char* erreur_arbre_binaire(arbre_binaire* a_arbre)
{
	char* l_erreur = NULL;
	if (!a_erreur_arbre_binaire(a_arbre)) {
        strncpy(a_arbre->erreur, "", ERREUR_TAILLE);
		l_erreur = a_arbre->erreur;
    } else {
		if (!a_arbre->a_erreur) {
			if (a_arbre->premier_enfant) {
				if (a_erreur_arbre_binaire(a_arbre->premier_enfant)) {
					l_erreur = erreur_arbre_binaire(a_arbre->premier_enfant);
				}
			}
			if (a_arbre->second_enfant) {
				if (a_erreur_arbre_binaire(a_arbre->premier_enfant)) {
					l_erreur = erreur_arbre_binaire(a_arbre->second_enfant);
				}
			}
		} else {
			l_erreur = a_arbre->erreur;
		}
	}
    return l_erreur;
}

/**
 *  \brief Inscrit l'erreur dans l''arbre'
 *
 *  \param erreur Le texte de l'erreur.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void inscrire_erreur_arbre_binaire(arbre_binaire* a_arbre, const char* a_erreur)
{
	a_arbre->a_erreur = true;
    strncpy(a_arbre->erreur, a_erreur, ERREUR_TAILLE);
}

/**
 *  \brief Retire tout erreur dans l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void retirer_erreur_arbre_binaire(arbre_binaire* a_arbre)
{
	a_arbre->a_erreur = false;
	if (a_arbre->premier_enfant) {
		retirer_erreur_arbre_binaire(a_arbre->premier_enfant);
	}
	if (a_arbre->second_enfant) {
		retirer_erreur_arbre_binaire(a_arbre->second_enfant);
	}
}

/* vi: set ts=4 sw=4 expandtab: */
/* Indent style: 1TBS */
