# Projet de Programmation Orientée objet, CS-112
## Projet de deuxième semestre, réalisé par Salya Diallo et Marie Widehem-Courgnaud


1.  Installation et utilisation du projet
	
	Ce projet, ayant pour but de simuler la formation de nuages et de la pluie en présence de montagnes, se présente sous deux formes différentes: une version texte possédant l’entièreté du code, tous les tests et fichiers.dat associés et une version graphique plus légère. L’utilisation de ces 2 versions mises dans 2 fichiers différents est expliqué ci-dessous.

2. Les différentes versions du projet:

	2.1 Version texte
	
	Cette version a pour but de fournir un affichage brut du projet, c’est à dire qu’il ne fourni que les valeurs brutes caractéristiques de chaque objets qui compose se projet.

	    A. Installation du projet
	
	    Pour accéder à la version texte de ce projet, il suffit d’ouvrir projet/projet.pro

	    B.  Affichage texte

	    Pour un affichage texte, cela se fait directement dans le main.cpp, toute la structure est déjà mise en place, il suffit donc d’exécuter le code. L’affichage se fait en passant par la class TextViewer et affiche la composition du système. Il a été supposé dans ce projet qu’un système possède toujours au moins ces 3 objets, à savoir un champ potentiel, un ciel et une montagne. Il devrait alors s’afficher le noms des objets présents dans le système directement suivis de leurs différentes caractéristiques. Il a d’ailleurs été choisi de garder les mêmes que pour les affichages de base des différents objets, c’est à dire que toutes les valeurs sont présentes et non pas juste celles servant à l’affichage graphique.

	    C. Utilisation des différents tests
	
	    Pour l’utilisation des différents tests, ces derniers ont été mis dans le projet sous forme de méthodes que l’on appelle directement dans le main.cpp. Il suffira de suivre l’indication mise en commentaire dans ce main.cpp pour : 
        commenter la partie affichage texte, qui n’a pas été mise sous forme de fonction car elle demeure la base de la version texte de ce projet .
        Pour décommenter comme expliqué dans le main.cpp le test qui souhaite être exécuté. Tous les #include nécessaire ont déjà été ajouté pour faciliter l’utilisation et le nom de tous les tests on déjà été entré en commentaire pour faciliter leur utilisation.

	    D. Remarque générale sur le code

	    Il a été choisi de laissé apparent en commentaire et à la fin de chaque fichier.h ou .cpp un certains nombres de tests de debugging utilisés. Un trait a été tiré à la fin de chaque fichier pour bien faire la séparation avec ces tests commenté ce qui ne gène en aucun cas la lecture du code et au contraire permet de mettre en exergue les méthodes ou nous avions eu le plus de problèmes.

	
	2.2  Version graphique

 	Cette version a pour but de montrer un affichage visuel de toutes ces valeurs de l’affichage texte et donc de rendre un peu plus concret qui a été réalisé durant ce semestre.

	    A. Installation du projet

	    Pour accéder à la version graphique de ce projet, il suffit d’ouvrir exerciceP11/exerciceP11.pro

	    B. Affichage graphique

	    Pour un affichage graphique, il suffit d’ouvrir et d’utiliser les commandes qmake et make de l’exercice P11, puis de construire et lancer l’exercice. Une montagne s’affichera ainsi que des nuages et de la pluie. Pour voir la pluie et les nuages se « déplacer » à une plus (ou moins) grande vitesse, il suffit de changer le dt dans constante.h (dans général de l’exerciceP11). 

	    C. Remarque générale sur le code
	
	    Nous n’avons pas eu beaucoup de temps pour faire le graphisme (5 jours non-stop) car nous avons eu beaucoup de problèmes de valeurs (laplacien, ciel, etc…) et nos classes Systeme et TextViewer ne compilaient pas. Donc nous n’avons pas eu beaucoup de temps pour debuguer la pluie et le déplacement de nuages. 