/**
 * \file testing.h
 * \brief Fichier definissant les différentes fonctions permettant les tests unitaires
 * \author Valerian Acier
 * \version 0.1
 * \date 13 fevrier 2018
 *
 * Contient différentes déclarations de fonctions permettant de réaliser des test unitaire sur différentes routes du serveur
 */

#ifndef testing_h
#define testing_h

#include "router.h"

/**
 * \fn char *get (char *url)
 * \brief Fonction appelée pour réaliser une requête GET sur une url
 *
 * \param url URL à appeler sur le serveur
 * \return char* Contenu de la page renvoyé
 */
char *get(char *url);

/**
 * \fn char *getRequest(char *url)
 * \brief Fonction appelée pour réaliser l'initalisation d'une requête GET, renvoi le socket, sans aucun traitement
 *
 * \param url URL à appeler sur le serveur
 * \return int Socket vers le serveur
 */
int getRequest(char *url);

/**
 * \fn void post(char *url, char *data)
 * \brief Fonction appelée pour réaliser une requête POST sur une url
 *
 * \param url URL à appeler sur le serveur
 * \param data Les données POST à envoyer avec la requête
 * \return char* Contenu de la page renvoyé
 */
char *post(char *url, char *data);

/**
 * \fn int upload(char *url, char *filename)
 * \brief Fonction appelée pour réaliser l'upload d'un fichier sur une url
 *
 * \param url URL à appeler sur le serveur
 * \param filename Path vers le fichier à upload
 * \return int Le socket vers le serveur
 */
int upload(char *url, char* filename);

/**
 * \fn void uploadAndGetResult(char *url, char *filename)
 * \brief Fonction appelée pour réaliser l'upload d'un fichier sur une url et récuperer le contenu de la page renvoyé
 *
 * \param url URL à appeler sur le serveur
 * \param filename Path vers le fichier à upload
 * \return char* Contenu de la page renvoyé
 */
char* uploadAndGetResult(char *url, char* filename);

/**
 * \fn void getAndDownloadResult(char *url, char *resultfilename)
 * \brief Fonction appelée pour réaliser une requête GET sur une url et stocker le résultat dans un autre fichier
 *
 * \param url URL à appeler sur le serveur
 * \param resultfilename Path vers le fichier dans lequel stocker le résultat
 */
void getAndDownloadResult(char *url, char* resultfilename);

/**
 * \fn void uploadAndDownloadResult(char *url, char *filename, char *resultfilename)
 * \brief Fonction appelée pour réaliser l'upload d'un fichier sur une url et stocker le résultat dans un autre fichier
 *
 * \param url URL à appeler sur le serveur
 * \param filename Path vers le fichier à upload
 * \param filenameresult Path vers le fichier dans lequel stocker le résultat
 */
void uploadAndDownloadResult(char *url, char* filename, char *filenameresult);


#endif /* testing_h */
