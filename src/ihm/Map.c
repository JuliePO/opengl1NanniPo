#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ihm/Map.h"
#include "ihm/Image.h"
#include "ihm/Node.h"
#include "geometry/Color3f.h"

/************* Vérification de la carte *************/
/* Vérifie si la carte est valide : Présence du bon commentaire (@ITD 1) sur la première ligne 		*
*  Présence de chacun de 8 paramètres et de leurs valeurs, vérifie si ces dernières sont correctes	*
*  nombre de noeud correspondant au nombre de lignes restantes. Vérifie que les noeuds sont bien dans   *
*  un pixel de l'image. Prend en paramètre un pointeur vers une map et le chemin vers le fichier ITD.	*
*  Retourne 0 en cas d'erreur sinon retourne 1								*/

int verificationMap(Map* map, char* nameITD){ 

	FILE* itd = NULL;
	itd = fopen(nameITD, "r");	

	if(itd == NULL){
		printf("Erreur : Impossible d'ouvrir le fichier\n");
		return 0;
	}
	else{
		int testCommentaire;
		char test[20];
		//char path[100];
		
		//Récupérer le commentaire du fichier itd
		fscanf(itd, "%s %d\n", &test,  &testCommentaire);

		if(strcmp("@ITD", test) == 0 && 1 == testCommentaire){

			//Récupère "carte"
			fscanf(itd, "%s", &test);
			
			//Vérifie qu'il s'agit bien de carte
			if(strcmp("carte", test) == 0) {

				//Alloue de la mémoire pour une image
				Image* new_img = malloc(sizeof(Image));

				char* path = malloc(50*sizeof(char));
				
				//Récupère le chemin vers l'image ppm
				if(fscanf(itd, "%s\n", path) == 1){
					new_img->path = path;
					openImg(new_img, new_img->path);
					map->img = new_img;			

					//Récupère "énergie"
					fscanf(itd, "%s", &test);

					//Vérifie qu'il s'agit bien de l'énergie
					if(strcmp("energie", test) == 0) {
				
						//Récupère l'énergie
						if(fscanf(itd, "%d\n", &(map->energie)) == 1){

							//Récupère "chemin"
							fscanf(itd, "%s", &test);

							//Vérifie qu'il s'agit bien du chemin
							if(strcmp("chemin", test) == 0) {
								
								int r, v, b;
								
								//Récupère la couleur du chemin
								if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){

									(map->road).r = r/255.0;
									(map->road).g = v/255.0;
									(map->road).b = b/255.0;
									
									//Récupère "noeud"
									fscanf(itd, "%s", &test);

									//Vérifie qu'il s'agit bien du chemin
									if(strcmp("noeud", test) == 0) {
								
										//Récupère la couleur du chemin
										if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){

											(map->node).r = r/255.0;
											(map->node).g = v/255.0;
											(map->node).b = b/255.0;
									
											//Récupère "construct"
											fscanf(itd, "%s", &test);

											//Vérifie qu'il s'agit bien du chemin
											if(strcmp("construct", test) == 0) {
								
												//Récupère la couleur du chemin
												if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){

													(map->construct).r = r/255.0;
													(map->construct).g = v/255.0;
													(map->construct).b = b/255.0;
									
													//Récupère "in"
													fscanf(itd, "%s", &test);

													//Vérifie qu'il s'agit bien du chemin
													if(strcmp("in", test) == 0) {
								
														//Récupère la couleur du chemin
														if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){

															(map->in).r = r/255.0;
															(map->in.g) = v/255.0;
															(map->in.b) = b/255.0;
									
															//Récupère "out"
															fscanf(itd, "%s", &test);

															//Vérifie qu'il s'agit bien du chemin
															if(strcmp("out", test) == 0) {
								
																//Récupère la couleur du chemin
																if(fscanf(itd, "%d %d %d\n", &r, &v, &b) == 3){
																	(map->out).r = r/255.0;
																	(map->out).g = v/255.0;
																	(map->out).b = b/255.0;

//Récupére le nombre de noeuds									
if(fscanf(itd, "%d\n", &(map->number_node)) == 1){
	int i, x, y;

	//Création d'une nouvelle liste de noeuds
	map->list_node = new_LNode();
	if(map->list_node != NULL){

		//Pour chaque noeud (on fait la boucle, le nombre de fois qu'il y a de nombre de noeuds)
		for(i=0; i < (map->number_node); i++){

			//Récupére les coordonnées
			if(fscanf(itd, "%d %d\n", &x, &y) == 2){

				//Vérifie que le noeud se trouve dans l'image
				if(x <= map->img->widthImg && x >= 0 && y <= map->img->heightImg && y >= 0){
					
					//Vérifie que le noeud à bien été ajouté à la liste de noeud
					if(addNode(map->list_node, x, y) != 1) {
						printf("Erreur, ce n'est pas les coordonées d'un noeud");
						return 0;
					}
				}
				else{
					printf("Erreur, le noeud ne se trouve pas sur la carte");
					return 0;
				}
			}
			else {
				printf("Erreur, ce n'est pas les coordonées d'un noeud");
				return 0;
			}
		}
		if(fscanf(itd, "%d %d\n", &x, &y) == 2){
			printf("Erreur, il y a trop de noeuds");
			return 0;
		}
	}
}
else {
	printf("Erreur, ce n'est pas un nombre de noeud");
	return 0;
}													

																}
																else {
																	printf("Erreur, Ce ne sont pas les valeurs de couleurs\n");
																	return 0;
																}
															}
															else {
																printf("Erreur, la huitième ligne ne correspond pas à la sortie\n");
																return 0;
															}

														}
														else {
															printf("Erreur, Ce ne sont pas les valeurs de couleurs\n");
															return 0;
														}
													}
													else {
														printf("Erreur, la septième ligne ne correspond pas à l'entrée\n");
														return 0;
													}

												}
												else {
													printf("Erreur, Ce ne sont pas les valeurs de couleurs\n");
													return 0;
												}
											}
											else {
												printf("Erreur, la sixième ligne ne correspond pas à la zone constructible\n");
												return 0;
											}

										}
										else {
											printf("Erreur, Ce ne sont pas les valeurs de couleurs\n");
											return 0;
										}
									}
									else {
										printf("Erreur, la cinquième ligne ne correspond pas au noeud\n");
										return 0;
									}

								}
								else {
									printf("Erreur, Ce ne sont pas les valeurs de couleurs\n");
									return 0;
								}
							}
							else {
								printf("Erreur, la quatrième ligne ne correspond pas au chemin\n");
								return 0;
							}

						}
						else {
							printf("Erreur, Ce n'est pas une valeur d'énergie\n");
							return 0;
						}
					}
					else {
						printf("Erreur, la troisième ligne ne correspond pas à l'énergie\n");
						return 0;
					}
				}
				else {
					printf("Erreur, ce n'est pas le chemin vers la carte\n");
					return 0;
				}
			}
			else {
				printf("Erreur, la deuxième ligne ne correspond pas au chemin vers la carte\n");
				return 0;
			}
		}
		else {
			printf("Ce n'est pas un fichier ITD\n");
			return 0;
		}
				
			// On ferme le vide le buffer et on ferme le fichier itd
			fflush(itd);
			fclose(itd);
	}
	return 1;
}
