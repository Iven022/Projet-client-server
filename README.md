# Projet-client-server

L'application client-serveur a 3 fonction:
1) une requête pour obtenir un document disponible sur le serveur 
2) une requête pour obtenir la liste des documents disponible sur le serveur 
3) une requête pour supprimer un document dans la liste

Quand le client est connecter au serveur, la liste des requetes sont affiché et pourra donc choisir la requête qu'il veut entre 1, 2 ou 3.
L'application serveur accepte et traite les demandes des clients en IPv4 et utilise l'adresse IP 127.0.0.1. La connexion peut avoir lieu en local ou sur un réseau LAN (appareils connectés au même réseau).

# Installation
Pour exécuter le programme, vous allez ouvrir un terminal sur le dossier où se trouve tcpServer.c et un autre sur le dossier où se trouve tcpClient.c, sur différents appareils ou un seul s'il s'agit d'une connexion client serveur en local.

Vous allez ensuite exécutez les code suivant:
Pour serveur: gcc tcpServer.c -o tcpServer
              ./tcpServer
Pour client: gcc tcpClient.c -o tcpClient
              ./tcpCLient

# Author
Moonien Iven et Rahman Henna
