#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define BAR 0
#define PIE 1
#define LINE 2
#define QUIT 3

class scrPt {
public:
    GLint x, y;
};

const GLdouble twoPi = 6.283185;
bool bar = true, line = false;
double zoom = 1.0f;

void circleMidpoint (scrPt , GLint ); // fn. defined in circle.cc

GLsizei winWidth = 400, winHeight = 300;    // Initial display window size.

GLfloat xwcMin = 0.0, xwcMax = 400.0;
GLfloat ywcMin = 0.0, ywcMax = 300.0;

GLint xRaster = 25, yRaster = 150; // Initial raster position

GLubyte label[36] = { 'J', 'a', 'n',   'F', 'e', 'b',   'M', 'a', 'r',
		      'A', 'p', 'r',   'M', 'a', 'y',   'J', 'u', 'n',
		      'J', 'u', 'l',   'A', 'u', 'g',   'S', 'e', 'p',
		      'O', 'c', 't',   'N', 'o', 'v',   'D', 'e', 'c' };

GLint dataValue[12] = { 420, 342, 324, 310, 262, 185,
			190, 196, 217, 240, 213, 438 };

void init (void)
{
  glClearColor (1.0, 1.0, 1.0, 1.0);

  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (0.0, (GLdouble)winWidth, 0.0, (GLdouble)winHeight);
}

void zoomIn()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	zoom += 0.1;
	glScalef(zoom, zoom, 1.0f);
	if (bar || line)
	{
    	glViewport (0, 0, winWidth, winHeight);
    	gluOrtho2D (0, GLdouble (xwcMax), 0, GLdouble (ywcMax));
    }
    else if (!bar && !line)
    	gluOrtho2D(0, winWidth, 0, winHeight);
}

void zoomOut()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	zoom -= 0.1;
	glScalef(zoom, zoom, 1.0f);
	if (bar || line)
	{
    	glViewport (0, 0, winWidth, winHeight);
    	gluOrtho2D (0, GLdouble (xwcMax), 0, GLdouble (ywcMax));
    }
    else if (!bar && !line)
		gluOrtho2D(0, winWidth, 0, winHeight);
}


void barChart (void)
{
  GLint month, k;

  glColor3f (1.0, 0.0, 0.0);           //  Set bar color to red.
  for (k = 0; k < 12; k++)
    glRecti (20 + k*30, 25, 40 + k*30, dataValue [k] -140);

  glColor3f (0.0, 0.0, 0.0);          //  Set text color to black.
  xRaster = 20;                       //  Display chart labels.
  for (month = 0; month < 12; month++) {
    glRasterPos2i (xRaster, yRaster / 2 -60);
    for (k = 3*month; k < 3*month + 3; k++)
      glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, label [k]);
    xRaster += 30;
  }
}

void lineChart (void)
{
  GLint x = 30;

  xRaster = 25;
  yRaster = 150;

  glClear(GL_COLOR_BUFFER_BIT);	// clear display window

  glColor3f(0.0, 0.0, 1.0);	// set line colour to blue
  glBegin(GL_LINE_STRIP);
    for (int k = 0; k < 12; k++)
      glVertex2i(x + k*30, dataValue[k] - yRaster);
  glEnd();

  glColor3f(1.0, 0.0, 0.0);	// Set marker colour to red
  for (int k = 0; k < 12; k++)
  {
    glRasterPos2i(xRaster + k*30, dataValue[k]-4 - yRaster);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
  }

  glColor3f(0.0, 0.0, 0.0);	// black
  xRaster = 20;
  for (int m = 0; m < 12; m++)
  {
    glRasterPos2i(xRaster, yRaster / 2 -60);
    for (int k = 3*m; k < 3*m+3; k++)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
    xRaster += 30;
  }
}

void pieChart (void)
{
    scrPt circCtr, piePt;
    GLint radius = winWidth / 4;               // Circle radius.

    GLdouble sliceAngle, previousSliceAngle = 0.0;

    GLint k, nSlices = 12;                     // Number of Slices. 
    GLfloat dataValues[12] = {10.0, 7.0, 13.0, 5.0, 13.0, 14.0,
                               3.0, 16, 5.0, 3.0, 17.0, 8.0};
    GLfloat dataSum = 0.0;
 
    circCtr.x = winWidth / 2;                  // Circle center position.
    circCtr.y = winHeight / 2;
    circleMidpoint (circCtr, radius);  // Call midpoint circle-plot routine.

    for (k = 0; k < nSlices; k++)
        dataSum += dataValues[k];

    for (k = 0; k < nSlices; k++) {
        sliceAngle = twoPi * dataValues[k] / dataSum + previousSliceAngle;
        piePt.x = (GLint) (circCtr.x + radius * cos (sliceAngle));
        piePt.y = (GLint) (circCtr.y + radius * sin (sliceAngle));
        glBegin (GL_LINES);
            glVertex2i (circCtr.x, circCtr.y);
            glVertex2i (piePt.x, piePt.y);
        glEnd ( );
        previousSliceAngle = sliceAngle;
    }
}

void
idle(void)
{
    /* Redraw the screen.  */
    glutPostRedisplay();
}

void processMenuEvents(int option) {

	switch (option) {
		case BAR :
		    bar = true;
		    line = false;
		    break;
		case PIE :
		    bar = false;
		    line = false;
		    break;
		case LINE :
			bar = false;
			line = true;
			break;
		case QUIT :
		    exit(0);
		    break;
		default :
			break;
	}
}

void keyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'b' || key == 'B')
	{
		bar = true;
		line = false;
	}
	else if (key == 'p' || key == 'P')
	{
		bar = false;
		line = false;
	}
	else if (key == 'l' || key == 'L')
	{
		bar = false;
		line = true;
	}
	else if (key == 'z')
		zoomIn();
	else if (key == 'Z')
		zoomOut();
}

void createGLUTMenus() {

	int menu;

	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Bar Chart", BAR);
	glutAddMenuEntry("Pie Chart", PIE);
	glutAddMenuEntry("Line Chart", LINE);
	glutAddMenuEntry("Quit", QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void winReshapeFcn (int newWidth, int newHeight)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    
    int winSizeWidth = winWidth, winSizeHeight = winHeight;
    if (newWidth % 400 == 0 && newHeight % 300 == 0)
    {
    	winSizeWidth = newWidth;
    	winSizeHeight = newHeight;
    }
    if (!bar && !line)
    {
    	glViewport (0, 0, winSizeWidth, winSizeHeight);
		glScalef(zoom, zoom, 1.0f);
		gluOrtho2D(0, newWidth, 0, newHeight);
    }
    else if (bar || line)
    {
    	glViewport (0, 0, newWidth, newHeight);
		gluOrtho2D (0, GLdouble (xwcMax), 0, GLdouble (ywcMax));
	}
	glClear (GL_COLOR_BUFFER_BIT);

    /*  Reset display-window size parameters.  */
    winWidth = newWidth;
    winHeight = newHeight;
    glutPostRedisplay();
}

void displayFcn (void)
{
    glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.
	
    glColor3f (0.0, 0.0, 1.0);       //  Set circle color to blue
	
    if (bar)
    	barChart ( );
    else if (line)
    	lineChart();
    else
    	pieChart ( );
    glutSwapBuffers ( );
    glFlush();
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Charts");

    init ( );
    glutDisplayFunc (displayFcn);
    glutReshapeFunc (winReshapeFcn);
    glutKeyboardFunc(keyboardFunc);
    glutIdleFunc(idle);
    
    createGLUTMenus();

    glutMainLoop ( );
}
