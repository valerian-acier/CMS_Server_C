/**
 * \file router.h
 * \brief Fichier de définitions de la gestion des routes
 * \author Valerian Acier
 * \version 0.1
 * \date 12 février 2018
 *
 *
 * Définitions des différentes fonctions pour la gestion des routes, permet un code plus lisible en segmentant la
 * partie redirection des routes et traitement du client et de la partie "logique" contenue dans le fichier
 * controller
 */

#ifndef router_h
#define router_h

#include "request.h"


// HTTP HEADER to send to a browser to display the content
#define HTTP "HTTP/1.1 200 OK\r\n\r\n"



/**
 * \struct _route
 * \brief Liste chainée de routes.
 *
 * _route est une liste chainées contenant les paramétres des routes.
 * Elle contient l'url de la route, la méthode, le callback, le nombre d'argument
 * et enfin un pointeur vers la prochaine route
 */
struct _route{
    char *url; /*!< URL de la route. */
    char *method; /*!< Méthode de la route. */
    void (*controllerAction)(request*); /*!< fonction appellée quand la route match. */
    int argc; /*!< Nombre d'argument (en GET) que prend la route. */
    struct _route *next; /*!< Route suivante. */
};

typedef struct _route route;

/**
 * \fn void registerRoute (route** router, char *method, char* url, int argc, void (*controllerAction)(request*))
 * \brief Fonction d'enregistrement d'une route, qui va l'ajouter dans la liste chainée
 *
 * \param router Pointeur vers l'adresse du router (le routeur peut être NULL) en revanche le pointeur vers celui ci ne peut être NULL (route **router -> 0x00000a | NULL)
 * \param method Méthode HTTP de la route permettant d'identifier le type de requête (GET / POST / PUT / UPLOAD etc...)
 * \param url URL de la route
 * \param argc Nombre d'argument prit par la route (séparé par des slashs)
 * \param controllerAction Fonction à appeler lorsque cette route est appellée
 */
void registerRoute(route** router, char *method, char* url, int argc, void (*controllerAction)(request*));



/**
 * \fn void callControllerAction
 * \brief Fonction qui gére le lien entre une requête et les routes définies, elle va appeller la fonction définit dans la route si elle match avec la requête reçu
 *
 * \param router Le router qui est en faite la liste des routes
 * \param request La requête d'un client
 */
void callControllerAction(route *router, request *request);



/**
 * \fn void clientConnected(int socket)
 * \brief Fonction appelée lorsqu'un client vient de se connecter au serveur, va parser la requête de l'utilisateur et gérer la route appelée
 *
 * \param socket Le socket du client venant de se connecter au serveur
 */
void clientConnected(int socket);


#endif /* router_h */
