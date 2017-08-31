/*
 * sphere.cpp
 *
 * draws cool sphere graphic, wow so good!
 *
 *  Created on: 29/08/2017
 *      Author: singh
 */

#include <math.h>
#include <GL/glut.h>

#define PI 3.14159265

/*
 * Draws a circle. rotY is rotation about the y axis
 * in degrees. Must be between -90 and 90
 */
void drawCircle(float r, float rotY){
	float y = rotY*PI/180; //rotation around y axis in radians
	int i = 0;
	for(;i<360;i++)
	{
		float iRad = i*PI/180;
		glVertex3f(r*cos(y)*cos(iRad),r*sin(iRad),r*sin(y)*cos(iRad));
	}
}

int frame = 0;
float rad = 1.0; //radius of sphere;
float k = 0; //increment

int circleSpacing = 10; // spacing between circles in degrees

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(-1.0f, 1.0f, 3.0f,
			  -0.5f, 0.4f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	int count = 0; // count for drawing loop

	//drawing loop. Draws spheres of varying radius
	for(rad=0.2;rad<=2.4;rad=rad+0.4)
	{

		if(frame%20 == count && count < 5)
			glColor3f(1.0f, 0.0f, 0.0f);
		else
			glColor3f(1.0f, 1.0f, 1.0f);

		//draw circles rotating around y axis
		float j = k;
		for(;j<180;j=j+circleSpacing)
		{
			glBegin(GL_LINE_LOOP);
			drawCircle(rad, j);
			glEnd();
		}

		//draw flat circles moving up and down y axis
		int i;
		float y=0.0;
		for(;y<=PI/2;y=y+0.1)
		{
			glBegin(GL_LINE_LOOP);
			i=0; //angle in degrees for drawing circle
			for(;i<360;i++)
				{
					float iRad = i*PI/180; //i in radians
					glVertex3f(rad*cos(y)*cos(iRad), rad*sin(y), rad*cos(y)*sin(iRad));
				}
			glEnd();
			glBegin(GL_LINE_LOOP);
			i=0;
			for(;i<360;i++)
				{
					float iRad = i*PI/180;
					glVertex3f(rad*cos(y)*cos(iRad), -rad*sin(y), rad*cos(y)*sin(iRad));
				}
			glEnd();
		}

		count++;
	}
	//end of drawing loop


	//increment frame
	k=k+0.1;
	if(k>=circleSpacing)
		k=0;

	frame++;

	glutSwapBuffers();
}

void changeSize(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h==0)
		h=1;

	float ratio =  1.0;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to stay the same ratio
	if(w<h)
		glViewport(0, (h-w)/2, w, w);
	else
		glViewport((w-h)/2, 0, h, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(400, 10);
	glutCreateWindow("");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);


	glutMainLoop();

	return 0;
}
