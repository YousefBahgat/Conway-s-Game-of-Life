/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include<stdio.h>


int PhyWidth = 500, PhyHeight = 500;
int logWidth = 100, logHeight = 100;
int status = 0;
int mousex, mousey;
int Cx[25];
int Cy[25];
float sqWid = 3.0;
int flag[25][25];
int flagup[25][25];
int counter;

void GameTitle(char *str,int x,int y) {
    glColor3f (1.0, 1.0, 1.0);
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    glFlush(); }
void text(char *str,int x,int y) {
    glColor3f (0.517, 0.525, 0.960);
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    glFlush(); }

void Drawsquares(){
glColor3f(1.0,1.0,1.0);
int center = 2;
for(int i=0;i<25;i++){
        Cx[i] = center;
        Cy[i] = center;
        center = center +4;
}

for (int i=0;i<25;i++){
    for (int j=0;j<25;j++){
       if(flag[i][j]==0){
          glColor3f(1.0,1.0,1.0);
          glBegin(GL_POLYGON);
            glVertex2f(Cx[j]-sqWid/2, Cy[i]-sqWid/2);
            glVertex2f(Cx[j]+sqWid/2, Cy[i]-sqWid/2);
            glVertex2f(Cx[j]+sqWid/2, Cy[i]+sqWid/2);
            glVertex2f(Cx[j]-sqWid/2, Cy[i]+sqWid/2);
       glEnd();
       }
       else if(flag[i][j]==1){
          glColor3f(0.317, 0.494, 0.858);
          glBegin(GL_POLYGON);
            glVertex2f(Cx[j]-sqWid/2, Cy[i]-sqWid/2);
            glVertex2f(Cx[j]+sqWid/2, Cy[i]-sqWid/2);
            glVertex2f(Cx[j]+sqWid/2, Cy[i]+sqWid/2);
            glVertex2f(Cx[j]-sqWid/2, Cy[i]+sqWid/2);
       glEnd();

       }
    }
}
}



void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(status==0){
              glColor3f(0.517, 0.525, 0.960);
    glBegin(GL_QUADS);
        glVertex2i(37,30);
        glVertex2i(37,39);
        glVertex2i(57,39);
        glVertex2i(57,30);
        glVertex2i(37,55);
        glVertex2i(37,64);
        glVertex2i(57,64);
        glVertex2i(57,55);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_QUADS);
        glVertex2i(38,31);
        glVertex2i(38,38);
        glVertex2i(56,38);
        glVertex2i(56,31);
        glVertex2i(38,56);
        glVertex2i(38,63);
        glVertex2i(56,63);
        glVertex2i(56,56);
    glEnd();
    GameTitle("Conway's Game of Life",25,87);
    text("Play",44,58);
    text("Exit",44,33);
    }
    if(status==1){
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_QUADS);
            glVertex2i(0,0);
            glVertex2i(0,logHeight);
            glVertex2i(logWidth,logHeight);
            glVertex2i(logWidth,0);
        glEnd();
        Drawsquares();
    }
    glutSwapBuffers();
    glFlush();
}
void mouseClick(int btn, int state, int x, int y) {
    mousex = x;
    mousex=0.5+1.0*mousex*logWidth/PhyWidth;
    mousey = PhyHeight - y;
    mousey=0.5+1.0*mousey*logHeight/PhyHeight;
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
            if( mousex>=37 && mousex<=57 && mousey >=55 && mousey <=64 && status==0) {
                    for(int i=0;i<25;i++){
                        for(int j=0;j<25;j++){
                            flag[i][j] = 0;
                          //  flagup[i][j] =0;
                        }
                    }
                    status=1;
            }
            if(mousex>=37 && mousex<=57 && mousey >=30 && mousey <=39 && status==0) {
                    exit(1);
            }
    }
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN && status==1) {
          for(int i=0;i<25;i++){
                for(int j=0;j<25;j++){
                       if( mousex>=(Cx[j]-sqWid/2) && mousex<=(Cx[j]+sqWid/2) && mousey >=(Cy[i]-sqWid/2) && mousey <=(Cy[i]+sqWid/2)) {
                            flag[i][j] = 1;
                           //flagup[i][j] =1;
                            }
                    }
    }
 }
 glutPostRedisplay();
}
void specialKeyboard(int key, int x, int y) {
    if(key==GLUT_KEY_RIGHT && status==1){
            for(int i=0;i<25;i++){
                for(int j=0;j<25;j++){
                    counter = 0;
                    if(flag[i][j++] == 1){
                        counter=counter+1;
                    }
                     if(flag[i--][j++] == 1){
                        counter=counter+1;
                    }
                     if(flag[i++][j++] == 1){
                        counter=counter+1;
                    }
                     if(flag[i--][j] == 1){
                        counter=counter+1;
                    }
                     if(flag[i++][j] == 1){
                       counter=counter+1;
                    }
                     if(flag[i++][j--] == 1){
                        counter=counter+1;
                    }
                     if(flag[i][j--] == 1){
                        counter=counter+1;
                    }
                     if(flag[i--][j--] == 1){
                        counter=counter+1;
                    }
                    if(counter==0 || counter==1){
                            flag[i][j] =0;
                          //  print("/n /n");
                    }
                       // else if(counter==2){
                        //    flagup[i][j] = flag[i][j];
                        //}
                        else if(counter==3){
                            flag[i][j] = 1;
                    }
                        else if(counter>=4){
                            flag[i][j] = 0;
                    }

            }

        }
       // for(int i=0;i<25;i++){
       //     for(int j=0;j<25;j++){
       //        flag[i][j]=flagup[i][j];
       // }
       // }
    }
    if(key==GLUT_KEY_F1){
        for(int i=0;i<25;i++){
            for(int j=0;j<25;j++){
                flag[i][j] = 0;
                        }
                    }
    }
    if(key==GLUT_KEY_F2){
        status = 0;
    }
    glutPostRedisplay();
}

void Init2D(float r, float g, float b) {
    glClearColor(r,g,b,0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, logWidth, 0.0, logWidth);
    }




int main(int argc,char *argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize (PhyWidth, PhyHeight);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("game");
    Init2D(0.760, 0.682, 1);
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
    }
















