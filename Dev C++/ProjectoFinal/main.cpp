#include <GL/glut.h>
#define ancho 500
#define alto 500
#define profundidad 500

/*
AQUI SE CREAN UN ARREGLO DONDE SE COLOCAN LOS VERTICES DE LA FIGURA DE FORMA [X,Y,Z]
*/
float vertice[8][3] = 
{
    {-1.0,-1.0,1.0},
    {-1.0,1.0,1.0},
    {1.0,1.0,1.0},
    {1.0,-1.0,1.0},
    {-1.0,-1.0,-1.0},
    {-1.0,1.0,-1.0},
    {1.0,1.0,-1.0},
    {1.0,-1.0,-1.0},
};

/*
AQUI SE CREAN UN ARREGLO DONDE SE COLOCA UN ARREGLO DE COLORES, VAN DESDE NEGRO A BLANCO
DEGRADANDOSE POR RGB
*/
GLfloat color[8][3] = 
{    
    {0.3,0.3,0.3},
    {0.0,0.0,1.0},
    {0.0,1.0,0.0},
    {0.0,1.0,1.0},
    {1.0,0.0,0.0},
    {1.0,0.0,1.0},
    {1.0,1.0,0.0},
    {1.0,1.0,1.0},
    /*
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    {0.0,0.0,0.0},
    */
};

/*
MATODO PARA CREAR UNA CARA DEL CUBO Y DARLE COLOR.
SE UTILIZAN LOS ARREGLOS Color y Vertices.
*/
void Cara(int a,int b,int c,int d)
{
    glBegin(GL_QUADS);
    glColor3fv(color[a]);
    glVertex3fv(vertice[a]);

    glColor3fv(color[b]);
    glVertex3fv(vertice[b]);

    glColor3fv(color[c]);
    glVertex3fv(vertice[c]);

    glColor3fv(color[d]);
    glVertex3fv(vertice[d]);
    glEnd();
}

/*
SE UTILIZA EL METODO Y SE ASIGNAN LAS POSICIONES DE LOS VERTICES.
CADA NUMERO ES LA UBICACION DEL VERTICE EN EL ARREGLO:
ES DECIR, 0 = {-1.0,-1.0,1.0}, 1 = {-1.0,1.0,1.0},, etc.
*/
void Cubo()
{
    Cara(0,3,2,1);
    Cara(2,3,7,6);
    Cara(0,4,7,3);
    Cara(1,2,6,5);
    Cara(4,5,6,7);
    Cara(0,1,5,4);
}

/*
VARIABLES UTILIZADAS PARAPODER MOVER LA FIGURA SEGUN LA POSICION (rotate_n)
Y MOVER LA CAMARA (tN)
*/
double rotate_y = 0; 
double rotate_x = 0;
double rotate_z = 0;
double tX = 0;
double tY = 0;
double tZ = 0;

/*
TECLAS ASIGNADAS PARA EL MOVIMIENTO DE LA FIGURA Y LA CAMARA
*/
void Teclado( int key, int x, int y ) 
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    else if (key == GLUT_KEY_F1)
        rotate_z += 5;
    else if (key == GLUT_KEY_F9)
        rotate_z -= 5;	 
    else if (key == GLUT_KEY_F2)
        tY += 0.5;
    else if (key == GLUT_KEY_F3)
        tY -= 0.5;
    else if (key == GLUT_KEY_F4)
        tX += 0.5;
    else if (key == GLUT_KEY_F5)
        tX -= 0.5;
    else if (key == GLUT_KEY_F6)
        tZ += 0.5;
    else if (key == GLUT_KEY_F7)
        tZ -= 0.5;
    
    glutPostRedisplay();
}

/*
CREACION DE LAS LINEAS X, Y, Z EN EL PLANO DE LA FIGURA
SE CREAN PRIMERO LA LINEA X
DESPUES LA LINEA Y
Y AL FINAL LA LINEA Z
*/
void ejes() {
glColor3f(1, 1, 1);
glBegin(GL_LINES);
   glVertex3f(-ancho/2, 0, 0);
   glVertex3f(ancho/2, 0, 0);
   glVertex3f(0, alto/2, 0);
   glVertex3f(0, -alto/2, 0);
   glVertex3f(0, 0, ancho/2);
   glVertex3f(0, 0, -alto/2);
	glEnd();
}

/*
CREACION TOTAL DE LA FIGURA Y COMO SE OBSERVA SEGUN LA POSICION DE LA CAMARA
*/
void Mostrar()
{
    glClearColor( 0, 0, 0, 1 );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ejes();
    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    int w = glutGet( GLUT_WINDOW_WIDTH );
    int h = glutGet( GLUT_WINDOW_HEIGHT );
    gluPerspective( 45, w / h, 0.1, profundidad );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( 5, 5, 5, tX, tY, tZ, 0, 0, 1);
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    Cubo();

    glutSwapBuffers();
}

/*
CREACION DE LA VENTNA EN WINDOWS Y EJECUCION DEL PROGRAMA
*/
int main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    glutInitWindowSize( ancho, alto );
    glutCreateWindow("CUADRADO 3D CHIDO ¯\_(T^T)_/¯");
    glutDisplayFunc(Mostrar);
    glutSpecialFunc(Teclado);
    glEnable( GL_DEPTH_TEST );
    glutMainLoop();
    return 0;
}
