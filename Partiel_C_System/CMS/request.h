/**
 * \file request.h
 * \brief Fichier de définitions de la gestion des requêtes
 * \author Valerian Acier
 * \version 0.1
 * \date 12 février 2018
 *
 *
 * Définitions des différentes fonctions pour la gestion des requêtes, permet un code plus lisible en segmentant la
 * partie redirection des routes et traitement du client et de la partie "logique" contenue dans le fichier
 * controller
 */

#ifndef request_h
#define request_h

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define BUFFLEN 1024


/**
 * \struct _request
 * \brief Structure contenant les différentes informations pour une requête d'un client.
 *
 * _request est une structure contenant toute les informations envoyé par le client lors de sa connection.
 * Elle contient l'url du client, la methode utilisée, les arguments passés (parsé en fonction de la route),
 * ainsi que les données post et le socket du client
 */
struct _request{
    char url[255];
    char method[255];
    char ** argv;
    char *postData;
    int socket;
};

typedef struct _request request;


/**
 * \fn request*  readRequest (int socket)
 * \brief Fonction permettant le parsage de la requête via le socket (lis les données client)
 * \param socket Le socket vers le client, permettant de lire les données reçu par le biais du navigateur ou d'un client
 * \return request La requête parsée avec les données du client.
 */
request *readRequest(int socket);

/**
 * \fn char * readAll(int std)
 * \brief Fonction permettant de récuperer tout ce qui est écrit dans un flux
 * \param std Flux dans lequel récuperer les données
 * \return char* Tableau d'octets contenant les données récupéré dans le flux
 */
char *readAll(int std);

/**
 * \fn char * extractHeadersFromSocket(int socket)
 * \brief Fonction utilitaire pour extraire les headers d'un socket (pour les requêtes HTTP)
 * \param socket Socket vers le client
 * \return char* Tableau d'octets contenant les headers
 */
char* extractHeadersFromSocket(int socket);

/**
 * \fn void cleanRequest(request *re)
 * \brief Fonction utilitaire pour désallouer la mémoire utilisée par la requête et fermer le socket
 * \param re La requête à désallouer et fermer
 */
void cleanRequest(request *re);

#endif /* request_h */
