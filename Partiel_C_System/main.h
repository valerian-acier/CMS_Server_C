/**
 * \file main.h
 * \brief Serveur CMS en C (fichier de démarrage)
 * \author Valerian Acier
 * \version 0.1
 * \date février 2018
 *
 * Implémentation d'un serveur de système de gestion de contenu en C.
 * Features : Multiclients, Tests unitaire, Définitions de routes avec arguments (gestion de POST etc..)
 * TODO : Remplacer la gestion des routes faites avec une liste chainée en hashmap, JSON helper
 * Functions are defined using lowerCamelCase
 */



#ifndef main_h
#define main_h

#include "testing.h"
#include "router.h"
#include "server.h"
#include "controller.h"
#include <signal.h>
#include "log.h"
#include "asserting.h"

#define UNIT_TESTING
//#define EXECLP

void (*notFoundHandler)(request*);
route *router;

pid_t pid = 0, client_pid = 0;

FILE* logFile = NULL;
char tmpFolder[255];

/**
 * \fn void end(int signo)
 * \brief Fonction permettant l'arrêt du serveur et de tout les fils qui ont été crées
 * \param signo Le numéro du signal (SIGTERM)
 */
void end(int signo);

/**
 * \fn void setTmpFileStorage(int signo)
 * \brief Fonction permettant de modifier le dossier de stockage des fichiers
 * \param signo Le numéro du signal (SIGUSR1)
 */
void setTmpFileStorage(int signo);

/**
 * \fn void signalDefinitions()
 * \brief Fonction d'initialisation des signaux
 */
void signalDefinitions(void);

/**
 * \fn void initGlobalVariables()
 * \brief Fonction d'initialisation des variables globales
 */
void initGlobalVariables(void);

/**
 * \fn void routesRegistering()
 * \brief Fonction de définitions des routes
 */
void routesRegistering(void);

/**
 * \fn void executeTesting()
 * \brief Lance les tests
 */
void executeTesting(void);


#endif /* main_h */
