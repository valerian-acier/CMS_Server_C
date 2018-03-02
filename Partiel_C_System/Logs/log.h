/**
 * \file log.h
 * \brief Fichier definissant les différentes fonctions de log
 * \author Valerian Acier
 * \version 0.1
 * \date 26 septembre 2017
 *
 * Contient différentes déclarations de fonctions permettant l'écriture de données dans un fichier de log
 */



#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * \fn void log_ouvrir(const char* path)
 * \brief Fonction permettant l'ouverture d'un fichier de log
 * \param path Le chemin du fichier de log
 * \return FILE* Pointeur sur le fichier
 */
FILE * log_ouvrir(const char* path);

/**
 * \fn void log_ecrire(FILE *f, char* content)
 * \brief Fonction permettant l'écriture dans un fichier de log
 * \param f Pointeur sur le fichier
 * \param content Contenu à inserer dans le fichier
 * \return int Si succés
 */
int log_ecrire(FILE *f, char* content);

/**
 * \fn void log_fermer(FILE* f)
 * \brief Fonction permettant de fermer le fichier de log
 * \param f Le fichier à fermer
 * \return intSsi succés
 */
int log_fermer(FILE *f);

/**
 * \fn void log_write_to_disk(FILE* f)
 * \brief Fonction permettant de forcer l'écriture dans le fichier
 * \param f Pointeur sur le fichier
 */
void log_write_to_disk(FILE *f);


#endif /* log_h */
