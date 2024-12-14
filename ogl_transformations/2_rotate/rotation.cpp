#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include <math.h>
//============================
//=====================================================
double pi=3.14159265359;

double angle=pi/4; // Camera angle
double h=7.0; // Camera height
double R=15;  // Camera radius


//---------------------------
// Camera position:
void Camera_position(double a, double R, double h)
{
gluLookAt(R*cos(a), R*sin(a), h, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}
//---------------------------

//-------------------------------------
// Drawing:


//-------------------------------
void Draw_segment(float V1 [3],float V2 [3])
{

glBegin(GL_LINES);
    glVertex3f(V1[0], V1[1], V1[2]);
    glVertex3f(V2[0], V2[1], V2[2]);
glEnd();
}
//-------------------------------


//--------------------------------------
// Coordinate system
void Draw_coord_system()
{
//------------------------
// X axis
glLineWidth(5.0);
glColor3f( 1.0, 0.0, 0.0);
float V1 [3] = {-5.0, 0.0f,0.0f};
float V2 [3] = {5.0, 0.0f,0.0f};
Draw_segment(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 1.0, 0.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(5,0,0);
glEnd();
//-----------------
//------------------------


//------------------------
// Y axis
glColor3f( 0.0, 1.0, 0.0);
V1[0] = 0.0;
V1[1] = -5.0;
V2[0] = 0.0;
V2[1] = 5.0;
Draw_segment(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 1.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(0,5,0);
glEnd();
//-----------------

//------------------------

//------------------------
// Z axis
glColor3f( 0.0, 0.0, 1.0);
V1[1] = 0.0;
V1[2] = -5.0;
V2[1] = 0.0;
V2[2] = 5.0;
Draw_segment(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 0.0, 1.0, .4);
glBegin(GL_POINTS);
    glVertex3f(0,0,5);
glEnd();
//-----------------
// end: Z axis
//------------------------

}
//End: coord system
//--------------------------------------



//--------------------------------------


//--------------------------------------
void DrawCube()
{
		glBegin(GL_QUADS);			// top face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// front face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// right face
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
		glBegin(GL_QUADS);			// left face
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// bottom face
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();
		glBegin(GL_QUADS);			// back face
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
}
//--------------------------------------



void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
}


void display()
{
    //------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    Camera_position(angle, R, h);
    Draw_coord_system();


    glPushMatrix();
    glColor3f(0.0,0.0,1.0);
    //glTranslatef(0,2,0); // first way of doing the first task
    glRotatef(90,1,0,0); // second task
    glScalef(0.5, 4, 0.7);
    //glTranslatef(0,0.5,0); // second way of doing the first task
    DrawCube();
    glPopMatrix();
}



int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;

    SDL_Event myevent;
    init();
    while (petla==1)
    {

        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                petla=0;
                break;

                case SDL_KEYDOWN:
                if (myevent.key.keysym.sym==SDLK_LEFT) angle+=0.1;// rotate camera
                if (myevent.key.keysym.sym==SDLK_RIGHT) angle-=0.1;// rotate camera
                if (myevent.key.keysym.sym==SDLK_UP) h+=0.5;// move camera up
                if (myevent.key.keysym.sym==SDLK_DOWN) h-=0.5;// move camera down

                break;
            }
        }
       display();

        SDL_GL_SwapBuffers();

    }
    SDL_Quit();
    return 0;
}
