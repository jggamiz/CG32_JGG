#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

const double pi = 3.14159265359;

// Parámetros de la superficie
const int NUM_POINTS = 1000;  // Número de puntos para dibujar la curva
const int NUM_Y = 20;  // Número de segmentos a lo largo del eje Y
const float AMPLITUD = 1.0f;  // Amplitud de la onda (cuánto sube o baja)
const float FRECUENCIA = 1.0f;  // Frecuencia de la onda (cuántas oscilaciones)
const float LONGITUD_Y = 10.0f; // Longitud total a lo largo del eje Y

// Variables para controlar la cámara
double cameraAngleX = pi / 4;  // Ángulo de la cámara en el eje X (horizontal)
double cameraAngleY = pi / 4;  // Ángulo de la cámara en el eje Y (vertical)
double cameraDistance = 15.0;  // Distancia de la cámara

// Cámara para visualizar la escena
void Camera_position()
{
    gluLookAt(cameraDistance * cos(cameraAngleX) * cos(cameraAngleY),  // X
              cameraDistance * sin(cameraAngleX) * cos(cameraAngleY),  // Y
              cameraDistance * sin(cameraAngleY),                      // Z
              0.0, 0.0, 0.0,  // Mira hacia el origen
              0.0, 0.0, 1.0);  // Eje Z
}

// Función para dibujar un segmento de línea
void Draw_segment(float V1[3], float V2[3])
{
    glBegin(GL_LINES);
        glVertex3f(V1[0], V1[1], V1[2]);
        glVertex3f(V2[0], V2[1], V2[2]);
    glEnd();
}

// Función para dibujar el sistema de coordenadas
void Draw_coord_system()
{
    glLineWidth(5.0);

    // Eje X (rojo)
    glColor3f(1.0, 0.0, 0.0);
    float V1[3] = {-5.0, 0.0f, 0.0f};
    float V2[3] = {5.0, 0.0f, 0.0f};
    Draw_segment(V1, V2);

    // Eje Y (verde)
    glColor3f(0.0, 1.0, 0.0);
    V1[0] = 0.0;
    V1[1] = -5.0;
    V2[0] = 0.0;
    V2[1] = 5.0;
    Draw_segment(V1, V2);

    // Eje Z (azul)
    glColor3f(0.0, 0.0, 1.0);
    V1[1] = 0.0;
    V1[2] = -5.0;
    V2[1] = 0.0;
    V2[2] = 5.0;
    Draw_segment(V1, V2);
}

// Función para dibujar el coseno en 3D extendido en el eje Y usando triangle strips
void DrawCosineSurface()
{
    glColor4f(0,0,1.0f,0.4);
    float stepX = 10.0f / NUM_POINTS;  // Paso en X
    float stepY = LONGITUD_Y / NUM_Y;  // Paso en Y

    // Dibujamos la superficie usando triangle strip
    for (int j = 0; j < NUM_Y - 1; ++j) {
        glBegin(GL_TRIANGLE_STRIP);  // Iniciamos una tira de triángulos

        for (int i = 0; i < NUM_POINTS; ++i) {
            // Calculamos las coordenadas (x, y, z)
            float x = i * stepX - 5.0f;  // Coordenada X, desplazada
            float y = j * stepY - LONGITUD_Y / 2.0f;  // Coordenada Y, desplazada
            float z = AMPLITUD * cos(FRECUENCIA * x);  // Calculamos Z con la función coseno

            // Añadimos el primer vértice de la tira de triángulos
            glVertex3f(x, y, z);

            // Para el siguiente Y (en la siguiente tira de triángulos)
            float y2 = (j + 1) * stepY - LONGITUD_Y / 2.0f;  // Y del siguiente paso
            float z2 = AMPLITUD * cos(FRECUENCIA * x);  // Z para el siguiente Y

            // Añadimos el segundo vértice de la tira de triángulos
            glVertex3f(x, y2, z2);
        }

        glEnd();  // Finalizamos la tira de triángulos
    }
}

// Función de inicialización de OpenGL
void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Fondo blanco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);  // Proyección en perspectiva
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);  // Habilitar prueba de profundidad
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);  // Habilitar transparencia
}

// Función para dibujar la escena
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpiar el buffer

    glLoadIdentity();  // Restablecer la matriz de modelo

    // Posicionar la cámara
    Camera_position();

    // Dibujar el sistema de coordenadas y la superficie coseno
    Draw_coord_system();
    DrawCosineSurface();
}

// Función principal
int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);  // Inicializar SDL

    // Crear la ventana con contexto OpenGL
    SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_OPENGL);

    int loop = 1;
    SDL_Event event;
    init();  // Inicializar OpenGL

    // Bucle principal
    while (loop == 1)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                loop = 0;  // Salir del bucle si se cierra la ventana
            }
            // Detectar la tecla presionada para mover la cámara
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:  // Tecla izquierda
                        cameraAngleX -= 0.1;  // Girar la cámara hacia la izquierda
                        break;
                    case SDLK_RIGHT:  // Tecla derecha
                        cameraAngleX += 0.1;  // Girar la cámara hacia la derecha
                        break;
                    case SDLK_UP:  // Tecla arriba
                        cameraAngleY += 0.1;  // Subir la cámara (aumentar ángulo Y)
                        if (cameraAngleY > pi / 2) cameraAngleY = pi / 2;  // Limitar el ángulo
                        break;
                    case SDLK_DOWN:  // Tecla abajo
                        cameraAngleY -= 0.1;  // Bajar la cámara (disminuir ángulo Y)
                        if (cameraAngleY < -pi / 2) cameraAngleY = -pi / 2;  // Limitar el ángulo
                        break;
                }
            }
        }

        display();  // Mostrar la escena

        SDL_GL_SwapBuffers();  // Intercambiar buffers para mostrar la imagen
    }

    SDL_Quit();  // Limpiar SDL
    return 0;
}
