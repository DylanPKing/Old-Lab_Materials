#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif

/*  Set initial size of the display window.  */
GLsizei winWidth = 600, winHeight = 600;  

/*  Set size of world-coordinate clipping window.  */
GLfloat xwcMin = -50.0, xwcMax = 50.0;
GLfloat ywcMin = -50.0, ywcMax = 50.0;

class wcPt3D {
   public:
      GLfloat x, y, z;
};

int btn;
int startMouseX = 0;
int startMouseY = 0;
int startTransX = 0;
int startTransY = 0;
int cursorTransX = 0;
int cursorTransY = 0;

void MouseCallback(int button, int state, int x, int y)
{
  	btn = button;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        startMouseX = x;
        startMouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
        startTransX = cursorTransX;
        startTransY = cursorTransY;
    }
    
    switch (button)
	{
		case GLUT_WHEEL_UP :
			if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
			{
				xwcMin += 2.5;
				ywcMin += 2.5;
				xwcMax -= 2.5;
				ywcMax -= 2.5;
			}
			break;
		case GLUT_WHEEL_DOWN :
			if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
			{
				xwcMin -= 2.5;
				ywcMin -= 2.5;
				xwcMax += 2.5;
				ywcMax += 2.5;
			}
			break;
		default :
			break;
	}
    glutPostRedisplay();
}
 
void MotionCallback(int x, int y)
{
  	int cursorMouseX = x;
    int cursorMouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
    if (btn == GLUT_LEFT_BUTTON)
    { 
        cursorTransX = startTransX + (cursorMouseX - startMouseX );
        cursorTransY = startTransY + (cursorMouseY - startMouseY );
    }

    glutPostRedisplay();
}

void init(void)
{
   /*  Set color of display window to white.  */
   glClearColor (1.0, 1.0, 1.0, 0.0);
}

void plotPoint (wcPt3D bezCurvePt)
{
    glBegin (GL_POINTS);
        glVertex2f (bezCurvePt.x, bezCurvePt.y);
    glEnd ( );
}

/*  Compute binomial coefficients C for given value of n.  */
void binomialCoeffs (GLint n, GLint * C)
{
   GLint k, j;

   for (k = 0;  k <= n;  k++) {
      /*  Compute n!/(k!(n - k)!).  */
      C [k] = 1;
      for (j = n;  j >= k + 1;  j--)
        C [k] *= j;
      for (j = n - k;  j >= 2;  j--)
        C [k] /= j;
   }
}

void computeBezPt (GLfloat t, wcPt3D * bezPt, GLint nCtrlPts,
                    wcPt3D * ctrlPts, GLint * C)
{
   GLint k, n = nCtrlPts - 1;
   GLfloat bezBlendFcn;

   bezPt->x = bezPt->y = bezPt->z = 0.0;

   /*  Compute blending functions and blend control points. */
   for (k = 0; k < nCtrlPts; k++) {
      bezBlendFcn = C [k] * pow (t, k) * pow (1 - t, n - k);
      bezPt->x += ctrlPts [k].x * bezBlendFcn;
      bezPt->y += ctrlPts [k].y * bezBlendFcn;
      bezPt->z += ctrlPts [k].z * bezBlendFcn;
   }
}

void bezier (wcPt3D * ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
   wcPt3D bezCurvePt;
   GLfloat t;
   GLint *C;

   /*  Allocate space for binomial coefficients  */
   C = new GLint [nCtrlPts];

   binomialCoeffs (nCtrlPts - 1, C);
   for (int i = 0;  i <= nBezCurvePts;  i++) {
      t = GLfloat (i) / GLfloat (nBezCurvePts);
      computeBezPt (t, &bezCurvePt, nCtrlPts, ctrlPts, C);
      plotPoint (bezCurvePt);
   }
   delete [ ] C;
}

void displayFcn () 
{
    // Clear display window.
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);   

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = glutGet(GLUT_WINDOW_WIDTH);
    double h = glutGet(GLUT_WINDOW_HEIGHT);
    glTranslatef(cursorTransX / w * 2, cursorTransY / h * 2, 0);
    gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set example number of control points and number of
    // curve positions to be plotted along the Bezier curve.
    GLint nCtrlPts = 4, nBezCurvePts = 1000;
    wcPt3D ctrlPts [4] = 
    { 
        {-40.0, -40.0, 0.0}, {-10.0, 200.0, 0.0},
        {10.0, -200.0, 0.0}, {40.0, 40.0, 0.0} 
    };

    // Set point color to red.
    glPointSize(4);
    glColor3f(1.0, 0.0, 0.0);      

    bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    glutSwapBuffers();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
   /*  Maintain an aspect ratio of 1.0.  */
   int winSize = ((newWidth > newHeight) ? newHeight : newWidth);
   glViewport (0, 0, winSize, winSize);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ( );

   gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);

   glutPostRedisplay();
}

int main (int argc, char** argv)
{
   glutInit (&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowPosition (50, 50);
   glutInitWindowSize (winWidth, winHeight);
   glutCreateWindow ("Bezier Curve");

   init ( );
   glutDisplayFunc (displayFcn);
   glutReshapeFunc (winReshapeFcn);
   glutMouseFunc(MouseCallback);
   glutMotionFunc(MotionCallback);

   glutMainLoop ( );
}
