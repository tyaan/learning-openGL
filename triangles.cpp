//#include <windows.h>
#include <math.h>
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h==0)
		h=1;

	float ratio =  1.0;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the the same ratio
	if(h>w)
		glViewport(0, (h-w)/2, w, w);
	else
		glViewport((w-h)/2, 0, h, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

int numTri = 50; //number of triangles
int t = 0;

/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void renderScene() {
	// Clear the color buffer with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 200.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	t = glutGet(GLUT_ELAPSED_TIME);

	int i=numTri; //draw numTri triangles
	for(; i>0; i--)
	{
		int k = floor(1.0*t/20);
		glLineWidth(3.0f);
		if(i==k%(numTri*4))
			glColor3f(1.0f, 1.0f, 1.0f);
		else if(i==(k+10)%(numTri*4))
			glColor3f(1.0f, 1.0f, 0.0f);
		else if(i==(k+17)%(numTri*4))
			glColor3f(0.0f, 1.0f, 0.25f);
		else if(i==(k+22)%(numTri*4))
			glColor3f(0.0f, 0.5f, 1.0f);
		else if(i==(k+25)%(numTri*4))
			glColor3f(1.0f, 0.0f, 1.0f);
		else
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			glLineWidth(1.0f);
		}

		glBegin(GL_LINE_LOOP);

			float fi = 0.1*i;
			glVertex3f(-cos((1.0*t/800)-fi)*i, -1.0*i, -sin((1.0*t/800)-fi)*i);
			glVertex3f(cos((1.0*t/800)-fi)*i, -1.0*i, sin((1.0*t/800)-fi)*i);
			glVertex3f(0, (sqrt(3)-1)*i, 0);

		glEnd();
	}

	glutSwapBuffers();  // Render now
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutMainLoop();
	return 0;
}

