#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include <math.h>
#include <cmath>
//============================
//=====================================================
double pi=3.14159265359;


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
    float V1[3] = {-5.0, 0.0f,0.0f};
    float V2[3] = {5.0, 0.0f,0.0f};
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


void DrawCylinder(float radius, float height, int segments) {
    float angle_step = 2 * M_PI / segments;

    // Set the transparency color (Red with some transparency)
    glColor4f(1.0f, 0.0f, 0.0f, 0.4f);  // Red with 40% opacity

    // Bottom Circle (z = -height / 2)
    glBegin(GL_TRIANGLE_FAN);  // Using triangle fan for bottom circle
    glVertex3f(0.0f, 0.0f, -height / 2);  // Center of bottom circle
    for (float angle = 0.0f; angle < 2 * M_PI; angle += angle_step) {
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, -height / 2);
    }
    glEnd();

    // Top Circle (z = height / 2)
    glBegin(GL_TRIANGLE_FAN);  // Using triangle fan for top circle
    glVertex3f(0.0f, 0.0f, height / 2);  // Center of top circle
    for (float angle = 0.0f; angle < 2 * M_PI; angle += angle_step) {
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, height / 2);  // Vertex on the top circle
    }
    glEnd();

    // Side Walls
    for (float z = -height / 2; z < height / 2; z += 0.1f) {
        glBegin(GL_QUADS);  // Draw a quad for each height slice
        for (float angle = 0.0f; angle < 2 * M_PI; angle += angle_step) {
            // Bottom circle vertices at current height
            float x1 = radius * cos(angle);
            float y1 = radius * sin(angle);

            float angle_next = angle + angle_step;
            if (angle_next >= 2 * M_PI) angle_next -= 2 * M_PI;  // Wrap around

            float x2 = radius * cos(angle_next);
            float y2 = radius * sin(angle_next);

            glVertex3f(x1, y1, z);
            glVertex3f(x2, y2, z);
            glVertex3f(x2, y2, z + 0.1f);
            glVertex3f(x1, y1, z + 0.1f);
        }
        glEnd();
    }
}

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

    Camera_position(pi / 4, 15, 7);
    Draw_coord_system();

    float radius = 2.0f;
    // Draw the cylinder
    DrawCylinder(radius, 6.0f, 30);

    // Draw the blue point at the intersection of the red axis and the cylinder
    glPointSize(50);  // Set point size
    glColor3f(0.0, 0.0, 1.0);  // Set color to blue
    glBegin(GL_POINTS);
        glVertex3f(radius, 0.0f, 0.0f);  // Point at (r, 0, 0) where r = radius
    glEnd();

    float origin[3] = {0.0f, 0.0f, 0.0f};
    glColor3f(0.5f, 1.0f, 0.5f);  // Set color to green

    // Create temporary arrays to pass to Draw_segment
    float segment1[3] = {4.0f, 0.0f, 0.0f};
    float segment2[3] = {0.0f, 1.5f * radius, 0.0f};
    float segment3[3] = {0.0f, 0.0f, 1.5f * radius};
    float segment4[3] = {0.0f, -1.5f * radius, 0.0f};

    float aux[3] =  {2.5f,0.0f,0.0f};

    // Draw the segments
    glLineWidth(20);
    Draw_segment(aux, segment1);
    Draw_segment(origin, segment2);
    Draw_segment(origin, segment3);
    Draw_segment(origin, segment4);
}




int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

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
