#ifndef ITD_TEXTURE_H_
#define ITD_TEXTURE_H_

/************* Prototype des fonctions *************/
//Chargement de la texture de la carte
int loadMapTexture(Map*, GLuint*, SDL_Surface*);
//Chargement de texture
int loadTexture(char*, GLuint*, SDL_Surface*);

#endif
