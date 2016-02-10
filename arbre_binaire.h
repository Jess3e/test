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
 *  \file arbre_binaire.h
 *
 *  Fichier d'entête contenant la structure de donnée 'arbre_binaire'.
 *  Un Arbre Binaire est une structure de données qui contient des éléments
 *  appelés 'noeud' et le noeud initiale est appelé 'racine'. Chaque élément
 *  possède au maximum deux enfants : 'premier_enfant' et 'second_enfant'.
 *
 */

#ifndef _arbre_binaire_h
#define _arbre_binaire_h

#include <stdbool.h>


#define ERREUR_TAILLE 255

/**
 * \brief Un arbre binaire qui contient une valeur et des enfants.
 */
typedef struct arbre_binaire_struct arbre_binaire;

/**
 *  \brief Créer un nouvel arbre binaire.
 *  
 *  \param valeur La valeur de la racine de l'arbre
 *
 *  \return L'arbre binaire
 */
arbre_binaire* creer_arbre_binaire(int valeur);

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
arbre_binaire* charger_arbre_binaire(char *nom_fichier);

/**
 *  \brief Effectue la désallocation d'un arbre_binaire
 *
 *  \param arbre L'arbre_binaire à désallouer
 */
void detruire_arbre_binaire(arbre_binaire* arbre);

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
void sauvegarder_arbre_binaire(arbre_binaire* arbre, char * nom_fichier);

/**
 *  \brief Renvoie le nombre d'éléments de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return Le nombre d'éléments dans l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int nombre_elements_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Renvoie le nombre de feuilles de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return Le nombre de feuilles dans l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int nombre_feuilles_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Renvoie la hauteur de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return La hauteur de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int hauteur_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Renvoie l'élément contenu dans la racine de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *
 *  \return La valeur de l'élément contenu dans la racine de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
int element_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Modifie l'élément contenu dans la racine de l''arbre'
 *
 *  \param arbre L'arbre_binaire
 *  \param valeur La valeur à mettre dans la racine de l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void modifier_element_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
 *  \brief Regarde dans l''arbre' s'il contient la 'valeur'.
 *
 *  \param arbre L'arbre_binaire à rechercher la valeur
 *  \param valeur La valeur à rechercher dans l''arbre'
 *
 *  \return true si la valeur existe dans l''arbre'.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
bool contient_element_arbre_binaire(arbre_binaire* arbre, int valeur);

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
arbre_binaire* premier_enfant_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Ajoute un premier enfant d'un 'arbre' et place la valeur dans la
 *         racine de cet enfant.
 *
 *  \param arbre L'arbre_binaire à ajouter un premier enfant
 *  \param valeur La valeur à mettre dans la racine du premier enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void creer_premier_enfant_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
 *  \brief Libère le premier enfant d'un 'arbre'.
 *
 *  \param arbre L'arbre_binaire à retirer le premier enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void retirer_premier_enfant_arbre_binaire(arbre_binaire* arbre);

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
arbre_binaire* second_enfant_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Ajoute un second enfant d'un 'arbre' et place la valeur dans la
 *         racine de cet enfant.
 *
 *  \param arbre L'arbre_binaire à ajouter un second enfant
 *  \param valeur La valeur à mettre dans la racine du second enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void creer_second_enfant_arbre_binaire(arbre_binaire* arbre, int valeur);

/**
 *  \brief Libère le premier enfant d'un 'arbre'.
 *
 *  \param arbre L'arbre_binaire à retirer le premier enfant
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void retirer_second_enfant_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Indique si l''arbre' contient une erreur
 *
 *  \return Vrai si l''arbre' contient une erreur, Faux sinon.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
bool a_erreur_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Indique le texte de l'erreur contenue dans 'arbre'
 *
 *  Si 'a_erreur_arbre_binaire' indique que l''arbre' contient une erreur,
 *  retourne l'erreur qu'elle contient. Si 'a_erreur_arbre_binaire' est Faux,
 *  Retourne une chaine vide.
 *
 *  \return Le texte de l'erreur.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
char* erreur_arbre_binaire(arbre_binaire* arbre);

/**
 *  \brief Inscrit l'erreur dans l''arbre'
 *
 *  \param erreur Le texte de l'erreur.
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void inscrire_erreur_arbre_binaire(arbre_binaire* arbre, const char* erreur);

/**
 *  \brief Retire tout erreur dans l''arbre'
 *
 *  \note 'arbre' ne doit pas être NULL
 */
void retirer_erreur_arbre_binaire(arbre_binaire* arbre);

#endif /* _arbre_binaire_h */

/* vi: set ts=4 sw=4 expandtab: */
