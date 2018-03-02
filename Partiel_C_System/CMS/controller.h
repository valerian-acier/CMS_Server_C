/**
 * \file controller.h
 * \brief Fichier de définitions de la logique des routes
 * \author Valerian Acier
 * \version 0.1
 * \date 12 février 2018
 *
 *
 * Définitions des différentes fonctions appellées par des routes
 * elles constituents l'ensemble des routes appelable via le routeur
 */

#ifndef controller_h
#define controller_h

#include <stdio.h>
#include <dirent.h>
#include "router.h"

/**
 * \fn void searchForFile (request *re)
 * \brief Fonction appelée lorsque aucune route n'est trouvée, elle va chercher pour un fichier correspondant à la route pour le renvoyer
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void searchForFile(request *re);

///*************************SUJET GROUPE 1*******************************//

/**
 * \fn void stockImage(request *re)
 * \brief Fonction appelée pour stocker une image, l'image va être stockée en base64 en interne
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void stockImage(request *re);

/**
 * \fn void displayImage(request *re)
 * \brief Fonction appelée pour afficher une des images qui a été enregistée
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void displayImage(request *re);

///*************************SUJET GROUPE 2*******************************//

/**
 * \fn void cryptMot (request *re)
 * \brief Fonction appelée pour crypter en code César d'un mot envoyé en GET
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void cryptMot(request *re);

/**
 * \fn void decryptMot (request *re)
 * \brief Fonction appelée pour décrypter un code César d'un mot envoyé en GET
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void decryptMot(request *re);

/**
 * \fn void cryptMotPost(request *re)
 * \brief Fonction appelée pour crypter un code César de données envoyé en POST
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void cryptMotPost(request *re);

/**
 * \fn void decryptMotPost(request *re)
 * \brief Fonction appelée pour décrypter un code César de données envoyé en POST
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void decryptMotPost(request *re);

/**
 * \fn void cryptFile(request *re)
 * \brief Fonction appelée pour crypter un fichier en code César envoyé via la méthode HTTP UPLOAD
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void cryptFile(request *re);

/**
 * \fn void decryptFile(request *re)
 * \brief Fonction appelée pour décrypter un fichier en code César envoyé via la méthode HTTP UPLOAD
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void decryptFile(request *re);


///*************************SUJET GROUPE 3*******************************//

/**
 * \fn void stockFile(request *re)
 * \brief Fonction appelée pour stocker un fichier sur le serveur, le fichier va être compressé dans un dossier spécifique
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void stockFile(request *re);

/**
 * \fn void getFile(request *re)
 * \brief Fonction appelée pour récupérer un des fichiers qui a été compressé
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void getFile(request *re);

/**
 * \fn void displayFiles(request *re)
 * \brief Fonction appelée pour afficher la liste des fichiers stockés dans le serveur
 *
 * \param re Contient les différentes informations sur la requête de l'utilisateur
 */
void displayFiles(request *re);



#endif /* controller_h */
