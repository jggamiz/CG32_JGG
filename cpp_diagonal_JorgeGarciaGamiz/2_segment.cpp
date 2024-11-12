#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>
//============================
//=====================================================
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> // system
using namespace std;


//===============================
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);
}
//===============================


//===============================
void Draw_line_2d(float px,float py,float qx,float qy)
{

glBegin(GL_LINES);
    glVertex2f(px,py);
    glVertex2f(qx,qy);
glEnd();
}
//===============================


void display()
{
//------
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glPushMatrix();


glLineWidth(5);
glColor3f( 1.0, 0.0, 0.0);
Draw_line_2d(1,-1,-1,1);


glPopMatrix();

}



int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(600,400,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;

    SDL_Event zdarzenie;
    init();
    while (petla==1)
    {

        while (SDL_PollEvent(&zdarzenie))
        {
            switch(zdarzenie.type)
            {
                case SDL_QUIT:
                petla=0;
                break;
            }
        }
       display();

        SDL_GL_SwapBuffers();

    }
    SDL_Quit();
    return 0;
}
