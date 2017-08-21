

#include <GL/glut.h>
#include<vector>
#include"Point.h"
#include <iostream>
using namespace std;
#define LINE 1
#define RECTANGLE 2
#define POLYGON 3
#define CIRCLE 4
#define CLEAR 5
#define EDIT 6 
#define EDITED 7

bool foundpoint = false;
GLfloat pointsize = 5000;
GLfloat start_x, start_y;
GLfloat cx, cy;
GLfloat finish_x, finish_y;
GLfloat BLUE[3] = { 0,0,1};
GLfloat RED[3] = { 1,0,0 };
GLfloat sizes[2];   
GLfloat step;         
GLfloat SIDE = 50;
bool isedit = false;

int drawoption = 0;



std::vector<Point> linePoints;
std::vector<Point> rectPoints;
std::vector<Point> circlePoints;
std::vector<Point> polygonPoints;

Point* currentPoint;


unsigned int currdraw = LINE;


void drawLines()
{


	glPointSize(pointsize);
	glPointSize(5);

	
	glBegin(GL_POINTS);
	glColor3fv(RED);
	for (int i = 0; i < linePoints.size(); i += 2)
	{
		glVertex2f(linePoints[i].getx(), linePoints[i].gety());
		glVertex2f(linePoints[i + 1].getx(), linePoints[i + 1].gety());
	}
	glEnd();
	glBegin(GL_LINES);
	glColor3fv(BLUE);

	for (int i = 0; i < linePoints.size(); i += 2)
	{
	
	
		glVertex2f(linePoints[i].getx(), linePoints[i].gety());
		glVertex2f(linePoints[i + 1].getx(), linePoints[i + 1].gety());
		cout << "Points for line 1st :" << linePoints[i].getx() << " ," << linePoints[i].gety() << std::endl;
		cout << "Points for line 2nd :" << linePoints[i + 1].getx() << " ," << linePoints[i + 1].gety() << std::endl;
	}
	glEnd();


}

void Rec()
{
	glColor3fv(BLUE);
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3fv(RED);
	for (int i = 0; i < rectPoints.size(); i += 2)
	{
		glVertex2i(rectPoints[i].getx(), rectPoints[i].gety());
		glVertex2i(rectPoints[i + 1].getx(), rectPoints[i + 1].gety());
	}
	glEnd();

	glBegin(GL_LINES);

	glColor3fv(BLUE);

	for (int i = 0; i < rectPoints.size(); i += 2)
	{
		cout << "rec";
		cout << rectPoints[i].getx() << "," << rectPoints[i].gety();
		glVertex2f(rectPoints[i].getx(), rectPoints[i].gety());
		glVertex2f(rectPoints[i].getx(), rectPoints[i + 1].gety());

		glVertex2f(rectPoints[i + 1].getx(), rectPoints[i + 1].gety());
		glVertex2f(rectPoints[i + 1].getx(), rectPoints[i].gety());

		glVertex2f(rectPoints[i].getx(), rectPoints[i + 1].gety());
		glVertex2f(rectPoints[i + 1].getx(), rectPoints[i + 1].gety());

		glVertex2f(rectPoints[i].getx(), rectPoints[i].gety());
		glVertex2f(rectPoints[i + 1].getx(), rectPoints[i].gety());
	}
	glEnd();

	
}

void Circle()
{
	glColor3fv(BLUE);

	int i;
	int segmentCount = 20;

	for (i = 0; i < circlePoints.size(); i += 2)
	{
		float start_x = circlePoints[i].getx();
		float start_y = circlePoints[i].gety();
		float finish_x = circlePoints[i + 1].getx();
		float finish_y = circlePoints[i + 1].gety();

		float radius = sqrt((finish_x - start_x)*(finish_x - start_x) +
			(finish_y - start_y)*(finish_x - start_x));

		GLfloat twicePi = 2.0f * (22.0f / 7.0f);
		glColor3fv(BLUE);
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2f(circlePoints[i].getx(), circlePoints[i].gety());
		glEnd();
		glBegin(GL_LINE_LOOP);
		
		for (int i = 0; i < segmentCount; i++) {
			glVertex2f(
				start_x + (radius * cos(i *  twicePi / (float)segmentCount)),
				start_y + (radius * sin(i * twicePi / (float)segmentCount))
			);
		}
		glEnd();
	}

}

void Polygon()
{

	glColor3fv(BLUE);
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3fv(RED);
	for (int i = 0; i < polygonPoints.size(); i++)
	{
		glVertex2f(polygonPoints[i].getx(), polygonPoints[i].gety());
		
	}
	glEnd();
	glPointSize(pointsize);
	
	glBegin(GL_LINES);

	for (int i = 1; i < polygonPoints.size(); i++)
	{
		cout << polygonPoints[i].getx() << "," << polygonPoints[i].gety();
		glVertex2f(polygonPoints[i].getx(), polygonPoints[i].gety());
		glVertex2f(polygonPoints[i - 1].getx(), polygonPoints[i - 1].gety());
	}

	glEnd();

}

void display(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	drawLines();
	Rec();
	Circle();
	Polygon();

	glFlush();
}

void MenuEvents(int option)
{
	switch (option)
	{
	case LINE:
		currdraw = LINE;
		break;
	case RECTANGLE:
		currdraw = RECTANGLE;
		break;
	case CIRCLE:
		currdraw = CIRCLE;
		break;
	case POLYGON:
		currdraw = POLYGON;
		break;
	case CLEAR:
		linePoints.clear();
		glutPostRedisplay();
		rectPoints.clear();
		glutPostRedisplay();
		polygonPoints.clear();
		glutPostRedisplay();
		circlePoints.clear();
		glutPostRedisplay();
		break;
	case EDIT :
		isedit = true;
		break;
	case EDITED :
		isedit = !isedit;
		break;
	default:
		break;
	}
}

int CreateGLUTMenus()
{
	int menu;

	menu = glutCreateMenu(MenuEvents);

	glutAddMenuEntry("Lines", LINE);
	glutAddMenuEntry("Rectangle", RECTANGLE);
	glutAddMenuEntry("Polygon", POLYGON);
	glutAddMenuEntry("Circle", CIRCLE);
	glutAddMenuEntry("Clear", CLEAR);
	glutAddMenuEntry("EDIT", EDIT);
	glutAddMenuEntry("EDITED", EDITED);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	return menu;
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	//glOrtho(0.0, 1368, 768, 0, -1.0, 1.0);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void cler()
{
	glutDisplayFunc(display);
}

void mouse(int btn, int state, int x, int y)
{  
	if (!isedit )
	{
	
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
	
			if (currdraw == LINE)
			{
				linePoints.push_back(Point(x, y));
			}
			if (currdraw == RECTANGLE)
			{
				rectPoints.push_back(Point(x, y));
			}
			if (currdraw == POLYGON)
			{
				polygonPoints.push_back(Point(x, y));
			}
			if (currdraw == CIRCLE)
			{
				circlePoints.push_back(Point(x, y));
			}
			/*
				go through all points;
				for(...all shapes)
				for(i..linepoints)
				for(i..rect points)
				if found point within range. break;
				currentPoint = &linePoint[i];
				if currentpointnot nullptr then
				currPoint->setX(mouse pos); -whenmouse lift up
				currPoint->sety(mouse pos); -whenmouse lift up
				currPoint = nullptr;
			*/

		}
		if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			if (currdraw == LINE)
			{
				linePoints.push_back(Point(x, y));
			}
			if (currdraw == RECTANGLE)
			{
				rectPoints.push_back(Point(x, y));
			}
			if (currdraw == POLYGON)
			{
				polygonPoints.push_back(Point(x, y));
			}
			if (currdraw == CIRCLE)
			{
				circlePoints.push_back(Point(x, y));
			}
		}
	}
	else
	{
		
		if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			
			for (int i = 0; i < linePoints.size(); i++)
			{
				if (linePoints[i].getx() > x - 20 && linePoints[i].getx() < x + 20 && linePoints[i].gety() > y - 20 && linePoints[i].gety() < y + 20)
				{
					cout << "foundrthepoint";
					currentPoint = &linePoints[i];
					
					break;
				}

			}
			if (!foundpoint)
			{

				for (int i = 0; i < rectPoints.size(); i++)
				{
					if (rectPoints[i].getx() > x - 20 && rectPoints[i].getx() < x + 20 && rectPoints[i].gety() > y - 20 && rectPoints[i].gety() < y + 20)
					{
						cout << "foundrthepoint";
						currentPoint = &rectPoints[i];

						break;
					}

				}
			}
			if (!foundpoint)
			{
				for (int i = 0; i < circlePoints.size(); i++)
				{
					if (circlePoints[i].getx() > x - 20 && circlePoints[i].getx() < x + 20 && circlePoints[i].gety() > y - 20 && circlePoints[i].gety() < y + 20)
					{
						cout << "foundrthepoint";
						currentPoint = &circlePoints[i];

						break;
					}

				}

			}
			if (!foundpoint)
			{
				for (int i = 0; i < polygonPoints.size(); i++)
				{
					if (polygonPoints[i].getx() > x - 20 && polygonPoints[i].getx() < x + 20 && polygonPoints[i].gety() > y - 20 && polygonPoints[i].gety() < y + 20)
					{
						cout << "foundrthepoint";
						currentPoint = &polygonPoints[i];
						
						

						break;
					}

				}
			}

		}
		if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			
			
				if (currentPoint != nullptr)
				{
					cout << "position at "<<x <<" "<<y;
					currentPoint->setx(x);
					currentPoint->sety(y);
				}
			
		}
	}

}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("Paint");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(cler);
	CreateGLUTMenus();

	glutMainLoop();
}

