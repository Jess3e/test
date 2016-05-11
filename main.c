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
 *  \file main.c
 *
 *  Effectue les testes de la librairie d'arbre binaire.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "arbre_binaire.h"

/**
 * \brief Teste la librairie d'arbre binaire
 */
int main()
{
	arbre_binaire* arbre1;
	arbre_binaire* arbre2;
	arbre1 = creer_arbre_binaire(10);
	if (arbre1) {
		printf("Arbre créée.\n");
		creer_premier_enfant_arbre_binaire(arbre1, 9);
		creer_second_enfant_arbre_binaire(arbre1, 8);
		arbre_binaire* enfant1 = premier_enfant_arbre_binaire(arbre1);
		creer_second_enfant_arbre_binaire(enfant1, 7);
		sauvegarder_arbre_binaire(arbre1, "test.bin");
		arbre2 = charger_arbre_binaire("test.bin");
		arbre_binaire* enfant2 = premier_enfant_arbre_binaire(arbre2);
		if (nombre_elements_arbre_binaire(arbre2) != 4) {
			printf("Erreur lors du comptage d'éléments\n");
		}
		if (hauteur_arbre_binaire(arbre2) != 3) {	
			printf("Erreur lors du calcul de la hauteur\n");
		}
		if (element_arbre_binaire(enfant2) != 9) {
			printf("Erreur lors de la lecture de la valeur\n");
		}
		if (nombre_feuilles_arbre_binaire(arbre2) != 2) {
			printf("Erreur lors du compte de feuilles\n");
		}
		retirer_second_enfant_arbre_binaire(arbre2);
		if (a_erreur_arbre_binaire(arbre2)) {
			printf("Erreur : %s\n", erreur_arbre_binaire(arbre2));
		}
		if (contient_element_arbre_binaire(arbre2, 8)) {
			printf("Erreur lorsque la valeur à été retirée\n");
		}
		creer_second_enfant_arbre_binaire(arbre2, 6);
		if (contient_element_arbre_binaire(arbre2, 8)) {
			printf("Erreur lorsque la valeur à été retirée\n");
		}
		if (a_erreur_arbre_binaire(arbre2)) {
			printf("Une erreur s'est produite\n");
		}
		arbre_binaire* enfant3 = second_enfant_arbre_binaire(enfant2);
		retirer_premier_enfant_arbre_binaire(enfant3);
		if (!a_erreur_arbre_binaire(arbre2)) {
			printf("Une erreur était supposé être là et elle ne l'est pas\n");
		}
		retirer_erreur_arbre_binaire(enfant2);
		if (a_erreur_arbre_binaire(arbre2)) {
			printf("L'erreur ne s'est pas enlevée\n");
		}
		
		printf("Tests terminés");
	} else {
		printf("Une erreur s'est produite\n");
	}
	return 0;
}
