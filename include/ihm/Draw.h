#ifndef ITD_DRAW_H_
#define ITD_DRAW_H_


/************* Appel de fonction *************/
int drawMap (GLuint*);
int drawMenu (GLuint*, GLuint*, GLuint*, GLuint*, GLuint*, int);
int drawTower (GLuint*, GLuint*, LTower*, LMonster*, Monster*, float, float, int, int);
int drawShot (GLuint*, LShot*);
int drawMonster(GLuint*, LMonster*, Node* p_tail, float, float);
int drawPVMonster(LMonster*);
void drawDisque(float);
void drawCercle(float);
void drawRectangle (int, int, int, int);
void drawRectangleLine (int, int, int, int);
void writeString(int, int,  char*);

#endif
