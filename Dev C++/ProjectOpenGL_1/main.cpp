#include <GL/glut.h>

void dibuja() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex2f(0.0, 1.0);
   		glVertex2f(0.5, -0.5);	
   		glVertex2f(-0.5, -0.5);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) 
{
	glutInit(&argc,argv);
	glutCreateWindow("Primer Ejemplo de OpenGL");
	glutDisplayFunc(dibuja);
	glutMainLoop();
	return 0;
}
