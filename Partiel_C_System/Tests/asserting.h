/**
 * \file asserting.h
 * \brief Fichier definissant les différentes fonctions permettant les tests unitaires
 * \author Valerian Acier
 * \version 0.1
 * \date 26 fevrier 2018
 *
 * Contient différentes déclarations de fonctions permettant de réaliser des assertions
 */
#ifndef asserting_h
#define asserting_h

#include "router.h"


/**
 * \fn void assertHTMLEquals(char *title, char *expected, char *actual)
 * \brief Fonction appelée pour verifier la différence entre un texte et du contenu HTML
 * \param title Le nom du test (Chaque test est nommé pour connaitre lequel echoue)
 * \param expected Le contenu attendu
 * \param actual Le contenu reçu
 */
void assertHTMLEquals(char *title, char *expected, char *actual);

/**
 * \fn void assertEquals(char *title, char *expected, char *actual)
 * \brief Fonction appelée pour verifier la différence entre deux chaines
 * \param title Le nom du test (Chaque test est nommé pour connaitre lequel echoue)
 * \param expected Le contenu attendu
 * \param actual Le contenu reçu
 */
void assertEquals(char *title, char *expected, char *actual);

/**
 * \fn void assertFileEquals(char *title, char *filename, char *crypted_uncrypted)
 * \brief Fonction appelée pour verifier la différence entre deux fichiers
 * \param title Le nom du test (Chaque test est nommé pour connaitre lequel echoue)
 * \param filename Le path du fichier avec le contenu attendu
 * \param crypted_uncrypted Le path du fichier avec le contenu reçu
 */
void assertFileEquals(char* title, char *filename, char *crypted_uncrypted);

/**
 * \fn void assertFileExist(char *title, char *path)
 * \brief Fonction appelée pour verifier l'existence d'un fichier
 * \param title Le nom du test (Chaque test est nommé pour connaitre lequel echoue)
 * \param path Le path où verifier l'existence du fichier
 */
void assertFileExist(char *title, char *path);



#endif /* asserting_h */
