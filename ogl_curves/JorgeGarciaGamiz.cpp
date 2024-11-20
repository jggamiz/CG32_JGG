#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include <math.h> //functions
//============================
//=====================================================


//------------------------
// Range:
float Xmin = -10, Xmax = 10;
float Ymin = -10, Ymax = 10;
//------------------------

//===============================
void Draw_line(float V1 [2],float V2 [2])
{
glBegin(GL_LINES);
    glVertex2f(V1[0], V1[1]);
    glVertex2f(V2[0], V2[1]);
glEnd();
}
//===============================


//===============================
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Xmin,Xmax,Ymin,Ymax);
}
//===============================




void display()
{
//------
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//---------------------------------
// Coordinate system

//------------------------
// Boundary:
glLineWidth(3);
glColor3f( 0.0, 0.0, 0.0);
float h=.1; //adjust bounday lines

glBegin(GL_LINE_LOOP);
    glVertex2f(Xmin,Ymin+h);
    glVertex2f(Xmax,Ymin+h);
    glVertex2f(Xmax,Ymax);
    glVertex2f(Xmin,Ymax);
glEnd();
//------------------------

//------------------------
// X axis
glLineWidth(2.0);
glColor3f( 0.0, 0.0, 0.0);
float V1 [2] = {Xmin, 0.0f};
float V2 [2] = {Xmax, 0.0f};
Draw_line(V1,V2);

//------------------------
// Axis arrows:
float XarrowW=(Xmax-Xmin)*.01;// arrow width
float XarrowL=(Xmax-Xmin)*.04;// arrow length

glBegin(GL_TRIANGLES);
    glVertex2f(Xmax-XarrowL,-XarrowW);
    glVertex2f(Xmax,0);
    glVertex2f(Xmax-XarrowL,XarrowW);
glEnd();
//------------------------


//------------------------


//------------------------
//// Y axis
glLineWidth(2.0);
glColor3f( 0.0, 0.0, 0.0);
V1[0] = 0.0f, V1[1]= Ymin;
V2[0] = 0.0f, V2[1]= Ymax;
Draw_line(V1,V2);

//------------------------
// Axis arrows:
float YarrowW=(Ymax-Ymin)*.01;// arrow width
float YarrowL=(Ymax-Ymin)*.04;// arrow length

glBegin(GL_TRIANGLES);
    glVertex2f(YarrowW,Ymax-YarrowL);
    glVertex2f(0,Ymax);
    glVertex2f(-YarrowW,Ymax-YarrowL);
glEnd();
//------------------------
//---------------------------------


//------------------------
glColor3f( 1.0, 0.0, 0.0);
float t;

float dt=.1;
for (float t = -10; t < -2*dt; t += dt)
 {
    V1[0]=t;
    V1[1]=t*t;
    t=t+dt;
    V2[0]=t+dt;
    V2[1]=(t+dt)*(t+dt);
    Draw_line(V1,V2);
    t=t-dt;
 }


 for (float t = dt; t < 10; t += dt)
 {
    V1[0]=t;
    V1[1]=t*t;
    t=t+dt;
    V2[0]=t+dt;
    V2[1]=(t+dt)*(t+dt);
    Draw_line(V1,V2);
    t=t-dt;
 }

 /*
  for (float t = dt; t < 10; t += dt)
 {
    V1[0]=t;
    V1[1]=t*t;
    t=t+dt;
    V2[0]=t+dt;
    V2[1]=(t+dt)*(t+dt);
    Draw_line(V1,V2);
    t=t-dt;
 }*/

//------------------------

}



int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(300,300,32,SDL_SWSURFACE|SDL_OPENGL);

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
