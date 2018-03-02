/**
 * \file server.h
 * \brief Fichier de définitions de la partie serveur
 * \author Valerian Acier
 * \version 0.1
 * \date 11 février 2018
 *
 *
 * Définitions des différentes fonctions du serveur, elle permet pour l'instant simplement la création
 * d'un serveur, sur le port 9090 par default, mais incrémente le port tant qu'il n'en trouve pas un disponible
 */

#ifndef server_h
#define server_h

#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>


/**
 * \fn void createServer(void (*clientConnected)(int))
 * \brief Fonction permettant de démarrer le serveur
 * \param clientConnected Pointeur sur fonction appelée lorsqu'un client va se connecter sur le serveur
 */
void createServer(void (*clientConnected)(int));

#endif /* server_h */
