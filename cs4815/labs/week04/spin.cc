/*
 * CS4815 - Computer Graphics
 *
 * spin.cc - skeleton file for week 04 assignment.
 */


#include <math.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>



#define WINDOW_WIDTH        512
#define WINDOW_HEIGHT       512
#define WINDOW_CAPTION      "CS4815: Week 04"
#define RED 1
#define BLUE 2
#define GREEN 3
#define REVERSE 4
#define CLOCKWISE 5
#define ANTICLOCKWISE 6
#define MINUS5 7
#define PLUS5 8
#define HALF 9
#define DOUBLE 10
#define QUIT 11

/*
 * Globals
 */
int timer = 0;
float angle = 0, red = 1.0, blue = 1.0, green = 1.0;
int rotate = 0, speed = 1;


void idle(void);


/**
 * Return number of timer ticks (miliseconds).
 */
int
get_ticks()
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL))
        return 0;

    return tv.tv_sec * 1000 + (tv.tv_usec / 1000);
}

    
/**
 * Initialise OpenGL state variables.
 */
void
init_gl()
{
    /* Set the background color to be light blue.  */
    glClearColor(0.75f, 0.75f, 1.0f, 1.0f);
}


/**
 * Re-display callback funcion.
 *
 * This function is called when contents of the window need to be
 * repainted.
 */
void
display(void)
{
    int dt;

    /* Clear the colour buffer.  */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Update timer value and calulate time elapsed from the last frame.
     * Limit delta time to maximum of one second.
     */
    dt = get_ticks() - timer;
    timer += dt;
    if (dt < 0) dt = 0;
    if (dt > 1000) dt = 1000;
    
    /* Calucate rotation (if enabled).  */
    if (rotate && angle > 0) {
        angle += 0.090f * ((float) dt) * speed; /* 15 RPM */
        if (angle > 360.0f) angle -= 360.0f;
    }
    else if (rotate) {
        angle -= 0.090f * ((float) dt) * speed; /* 15 RPM */
        if (angle < -360.0f) angle += 360.0f;
    }

    glPushMatrix();
    /* Rotate rectangle.  */
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    /* Draw rectangles.  */
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    float w = 1.0/20;
    glColor3f(red, green, blue);
    glRectf(-0.5f, 0.5f-w, -0.5f+w, 0.5f);

    glPopMatrix();


    /* Display contents of the back buffer (the draw buffer).  */
    glutSwapBuffers();
}


/**
 * Window resize callback function.
 *
 * This function is called when application window is resized.
 */
void
reshape(int width, int height)
{
    /* Update the viewport area to occupy the entire window.  */
    glViewport(0, 0, width, height);


    /* Refresh the screen contents.  */
    glutPostRedisplay();
}


/**
 * Keyboard callback function.
 *
 * This function is called when a key is pressed/released.
 */
void
keyboard(unsigned char key, int x, int y)
{
}


/**
 * Special key callback function.
 *
 * This function is called when a special key is pressed/released.
 * Special keys include: SHIFT, ALT ...
 */
void
special(int key, int x, int y)
{
}


/**
 * Mouse button callback function.
 *
 * This function is called when a mouse button is pressed/releassed.
 */
void
mouse(int button, int state, int x, int y)
{
    /* Left button starts rotatation.  */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        timer = get_ticks();
        glutIdleFunc(idle); /* Start updating the screen.  */
        rotate = 1; /* Start rotation.  */
    }
    /* Middle button stops rotation.  */
    if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        rotate = 0; /* Stop updating angle value.  */
        glutIdleFunc(NULL); /* Stop updating the screen.  */
    }
    

}


/**
 * Mouse motion callback function. 
 *
 * This function is called when mouse is moved (passive) and one of the
 * buttons is pressed (normal).
 */
void
motion(int x, int y)
{
}


/**
 * Idle callback function.
 *
 * This function is called when the program is idle (nothing to do).
 */
void
idle(void)
{
    /* Redraw the screen.  */
    glutPostRedisplay();
}

void processMenuEvents(int option) {

	switch (option) {
		case RED :
		    red = 1.0;
		    green = 0.0; 
		    blue = 0.0;
		    break;
		case GREEN :
		    red = 0.0;
		    green = 1.0;
		    blue = 0.0;
		    break;
		case BLUE :
		    red = 0.0;
		    green = 0.0;
		    blue = 1.0;
		    break;
		case REVERSE :
		    angle *= -1;
		    break;
		case CLOCKWISE :
		    if (angle > 0)
		        angle *= -1;
		    break;
		case ANTICLOCKWISE :
		    if (angle < 0)
		        angle *= -1;
		    break;
		case PLUS5 :
		    speed += 5;
		    break;
		case MINUS5 :
		    speed -= 5;
		    break;
		case HALF :
		    if (speed > 3)
		        speed /= 2;
		    break;
		case DOUBLE :
		    if (speed < 10000)
		        speed *= 2;
		    break;
		case QUIT :
		    exit(0);
		    break;
	}
}

void createGLUTMenus() {

	int menu, rgbMenu, directionMenu, speedMenu;
	
	directionMenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Reverse", REVERSE);
	glutAddMenuEntry("Clockwise", CLOCKWISE);
	glutAddMenuEntry("Anti-Clockwise", ANTICLOCKWISE);

    speedMenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Speed -5", MINUS5);
	glutAddMenuEntry("Speed +5", PLUS5);
	glutAddMenuEntry("Speed /2", HALF);
	glutAddMenuEntry("Speed *2", DOUBLE);

	rgbMenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Blue",BLUE);
	glutAddMenuEntry("Green",GREEN);

	menu = glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Direction", directionMenu);
	glutAddSubMenu("Speed", speedMenu);
	glutAddSubMenu("RGB Menu",rgbMenu);
	glutAddMenuEntry("Quit", QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/** 
 * `main' function is every C program entry point.
 *
 * This is where the execution starts.
 */
int
main(int argc, char *argv[])
{
    /* Initialise the GLUT library.  */
    glutInit(&argc, argv);

    /* Specify bufffer format, double buffered RGBA.  */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    /* Create an OpenGL capable window. This also initialises OpenGL
     * context.
     *
     * NOTE: You are not allowed to call any OpenGL function prior to
     * the window creation!
     */
    glutInitWindowPosition(0,0);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_CAPTION);


    /* Initialise application state.  */
    init_gl();

    /* Register callback functions. Callback functions are called by
     * GLUT in response to various events.
     */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    /* glutSpecialFunc(special); */
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    /* glutPassiveMotionFunc(motion); */
    glutIdleFunc(idle);
    
    createGLUTMenus();

    /* Enter the event processing loop. All the mouse, keyboard, screen
     * events will be processed and dispatchted to earlier registered
     * callback functions.
     */
    glutMainLoop();
    return EXIT_SUCCESS;
}

/* vi:set tw=72 sw=4 ts=4 et: */
