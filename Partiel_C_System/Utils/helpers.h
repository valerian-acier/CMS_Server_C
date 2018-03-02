/**
 * \file helper.h
 * \brief Fichier definissant les différentes fonctions permettant les tests unitaires
 * \author Valerian Acier
 * \version 0.1
 * \date 13 fevrier 2018
 *
 * Contient différentes déclarations de fonctions permettant de réaliser des test unitaire sur différentes routes du serveur
 */

#ifndef helpers_h
#define helpers_h

/**
 * \fn void readToWrite(int fildes, int fildes2)
 * \brief Fonction utilitaire permettant d'écrire dans un flux le contenu d'un autre flux
 * \param readFildes Le read file descriptor, l'endroit où on va lire les données
 * \param writeFildes Le write file descriptor, l'endroit où on va écrire les données
 */
void readToWrite(int readFildes, int writeFildes);


/**
 * \fn void toFile(int fildes, char *filename)
 * \brief Fonction utilitaire permettant d'écrire le contenu d'un flux dans un fichier
 * \param fildes Le read file descriptor, l'endroit où on va lire les données
 * \param filename Le chemin vers le fichier où on va écrire les données
 */
void toFile(int fildes, char* filename);

/**
 * \fn void uniqid(char *str)
 * \brief Fonction utilitaire permettant de generer un ID unique (fonction prise de PHP)
 * \param str Pointeur vers l'endroit où on va écrire l'id
 */
void uniqid(char *str);

/**
 * \fn void cryptExec(char *data)
 * \brief Fonction utilitaire permettant d'execlp le crypteur avec les arguments
 * \param data contenu à crypter
 */
void cryptExec(char *data);

/**
 * \fn void decryptExec(char *data)
 * \brief Fonction utilitaire permettant d'execlp le decrypteur avec les arguments
 * \param data contenu à decrypter
 */
void decryptExec(char *data);

#endif /* helpers_h */
