#include <GL/glut.h>
#define ancho 640
#define alto 480
#define profundidad 500

void dibuja();
void ejes();
void tecladoNormal(unsigned char tecla, int x, int y);
void tecladoEspecial(int tecla, int x, int y);
void texto(int x, int y, char *palabra);
void desocupado();
void redimensionado(int width, int height);
void luces();
void crear_menu();
void menu(int opcion);
void menupoligono(int opcion);
void menutipo(int opcion);
void alterna_movimiento();
void alterna_pantalla();

int posx=0, posy=0;
float angulo=0;
float esc=1;
unsigned int figura=1;
GLfloat material_ambient[] = {0.05, 0.05, 0.05, 1.0f};
GLfloat material_diffuse[] = { 0.8, 0.0, 0.0, 1.0f};
GLfloat material_specular[] = {0.9, 0.8, 0.8, 1.0f};
GLfloat luz_ambient[] = { 0.75, 0.75, 0.75, 0.0 };
GLfloat luz_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat luz_specular[] = { 1.0, 1.0, 1.0, 0.0 };
GLfloat luz_position[] = { 1.0, 1.0, 1.0, 0.0 };
unsigned int luz=1;
unsigned int movimiento=1;
unsigned int pantalla=0;

int main(int argc, char** argv) {
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_STENCIL | GLUT_DOUBLE | GLUT_DEPTH);
glutInitWindowPosition(100, 0);
glutInitWindowSize(ancho, alto);
glutCreateWindow("Menu");
glOrtho(-(ancho/2), (ancho/2), -(alto/2), (alto/2), -profundidad, profundidad);
glClearColor(1, 1, 1, 0);
crear_menu();
glutDisplayFunc(dibuja);
glutKeyboardFunc(tecladoNormal);
glutSpecialFunc(tecladoEspecial);
glutIdleFunc(desocupado);
glutReshapeFunc(redimensionado);
glutMainLoop();
return 0;
}

void dibuja() {
glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
ejes();
luces();
glPushMatrix();
   glTranslatef(posx, posy, 0);
   glRotatef(angulo, 1, 0, 0);
   glRotatef(angulo, 0, 1, 0);
   glRotatef(angulo, 0, 0, 1);
   glScalef(esc, esc, esc);
   glColor3f(1, 0, 0);
   if(luz==1)
      glEnable(GL_LIGHTING);
   switch(figura) {
      case 1: glutSolidTorus(20, 80, 18, 18);break;
      case 2: glutSolidSphere(100, 18, 18);break;
      case 3: glutSolidCone(50, 200, 18, 18);break;
      case 4: glutSolidCube(100);break;
   }
   glDisable(GL_LIGHTING);
glPopMatrix();
glutSwapBuffers();
}

void ejes() {
glColor3f(0.9, 0.9, 0.9);
glBegin(GL_LINES);
   glVertex3f(-ancho/2, 0, 0);
   glVertex3f(ancho/2, 0, 0);
   glVertex3f(0, alto/2, 0);
   glVertex3f(0, -alto/2, 0);
glEnd();
}

void tecladoNormal(unsigned char tecla, int x, int y) {
switch(tecla) {
   case 27: exit(0);break;
}
}

void tecladoEspecial(int tecla, int x, int y) {
switch(tecla) {
   case GLUT_KEY_UP : posy++;break;
   case GLUT_KEY_DOWN : posy--;break;
   case GLUT_KEY_RIGHT : posx++;break;
   case GLUT_KEY_LEFT : posx--;break;
   case GLUT_KEY_PAGE_UP : esc=esc*1.01;break;
   case GLUT_KEY_PAGE_DOWN : esc=esc*0.99;break;
   case GLUT_KEY_F1 : figura=1;break;
   case GLUT_KEY_F2 : figura=2;break;
   case GLUT_KEY_F3 : figura=3;break;
   case GLUT_KEY_F4 : figura=4;break;
   case GLUT_KEY_F5 : alterna_movimiento();break;
   case GLUT_KEY_F6 : alterna_pantalla();break;
   case GLUT_KEY_F9 : luz=0;glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);break;
   case GLUT_KEY_F10 : luz=0;glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break;
   case GLUT_KEY_F11 : luz=1;glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);break;
}
glutPostRedisplay();
}

void texto(int x, int y, char *palabra) {
int i;
glColor3f(0,0,0);
glRasterPos2f(x, y);
for (i = 0; palabra[i]; i++)
   glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, palabra[i]);
}

void desocupado() {
if (movimiento==1) {
   angulo=angulo+0.3;
   if (angulo>=360)
      angulo=0;
   glutPostRedisplay();
}
}

void redimensionado(int anchop, int altop) {
glViewport(0,0,anchop,altop);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60.0f,(GLfloat)ancho/(GLfloat)alto,0.1,profundidad*2);
gluLookAt(0,0,profundidad/1.2,0,0,0,0,1,0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void luces() {
glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0f);
glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, luz_specular);
glLightfv(GL_LIGHT0, GL_POSITION, luz_position);
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHT0);
}

void crear_menu() {
int submenupoligono, submenutipo;
submenupoligono = glutCreateMenu(menupoligono);
   glutAddMenuEntry("Toroide", 0);
   glutAddMenuEntry("Esfera", 1);
   glutAddMenuEntry("Cono", 2);
   glutAddMenuEntry("Cubo", 3);
submenutipo = glutCreateMenu(menutipo);
   glutAddMenuEntry("Puntos", 0);
   glutAddMenuEntry("Lineas", 1);
   glutAddMenuEntry("Relleno", 2);
glutCreateMenu(menu);
   glutAddSubMenu("Poligono", submenupoligono);
   glutAddSubMenu("Tipo", submenutipo);
   glutAddMenuEntry("Alternar Movimiento", 1);
   glutAddMenuEntry("Alternar Pantalla", 2);
   glutAddMenuEntry("------------------", 999);
   glutAddMenuEntry("Salir", 3);
glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menu(int opcion) {
switch (opcion) {
   case 1: alterna_movimiento();break;
   case 2: alterna_pantalla();break;
   case 3: exit(0);break;
   default: break;
}
}

void menupoligono(int opcion) {
switch (opcion) {
   case 0 : figura=1;break;
   case 1 : figura=2;break;
   case 2 : figura=3;break;
   case 3 : figura=4;break;
   default: break;
}
}

void menutipo(int opcion) {
switch (opcion) {
   case 0: luz=0;glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);break;
   case 1: luz=0;glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break;
   case 2: luz=1;glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);break;
   default: break;
}
}

void alterna_movimiento() {
if(movimiento==0)
   movimiento=1;
else
   movimiento=0;
}

void alterna_pantalla() {
if(pantalla==0) {
   glutFullScreen();
   pantalla=1;
}
else {
   glutReshapeWindow(ancho,alto);
   pantalla=0;
}
glutPostRedisplay();
}
