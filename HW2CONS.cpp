/*********
   CTIS164 - Template Source Program
----------
STUDENT :Eren Tarak
SECTION :
HOMEWORK:
----------
PROBLEMS:
----------
ADDITIONAL FEATURES:
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 700

#define TIMER_PERIOD  150 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
/* GLOBAL VARIABLES and CONSTANTS */
float t = 0;
int temp = 0;
int countforre = 0;
#define  START 0
#define  RUN   1
#define  SPACE   2
#define  OPEN  3


int appState = START;
int clickCount = 0;
bool inStartButton = false;
bool activeTimer = true;
int counter = 0;
int x_cloud1=-270,x_cloud2=270,ufo_y=-140;
int animating = 1;
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height

//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

void display_start()
{
    //  Begınnıng of the COMMON   BACKGROUND RECTANGLE
  //(255,228,225 misty rose)
    glColor3f(255 / 255.0, 228 / 255.0, 225 / 255.0);
    glRectf(-550, 400, 535, -400);


    // DRAWING TV
    glColor3f(0.2, 228 / 255.0, 225 / 255.0);
    glRectf(-490, 300, 490, -275);
    
    // body of tv
    // trıangle

    // DRAW  TRIANGLE
   //
    glColor3f(0.2, 228 / 255.0, 225 / 255.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-1, -258);
    glVertex2f(-116, -354);
    glVertex2f(106, -354);
    glEnd();
    glColor3f(255 / 255.0, 215 / 255.0, 0); // red
    //vprint(-26, -315, GLUT_BITMAP_8_BY_13, "ON/OFF");



    // border rect

    
    glColor3f(198 / 255.0, 226 / 255.0, 255 / 255.0);
 
    glRectf(-485, 295, 485, -270);
    // on off button circle   186,85,211
    glColor3f(186 / 255.0, 85 / 255.0, 211 / 255.0);
    circle(-4, -302, 24);
    //inside circle
    glColor3f(221 / 255.0, 160 / 255.0, 221 / 255.0);
    circle(-4, -302, 22);
    // restart button
    glColor3f(221 / 255.0, 160 / 255.0, 221 / 255.0);
    glRectf(-82, -329, 66, -348);
    glColor3f(1, 0, 0);
    vprint(-58, -343, GLUT_BITMAP_8_BY_13, "PAUSE/RESTART");
    vprint(-15, -300, GLUT_BITMAP_8_BY_13, "ON");
    vprint(-15, -310, GLUT_BITMAP_8_BY_13, "Off");
    // END OF THE COMMON BACKGROUND



}

void display_spaceship()
{// DRAW a QUAD for the body of spaceship
   //
    glColor3f(1, 1, 0.3);
    glBegin(GL_QUADS);
    glVertex2f(-150, ufo_y);
    glVertex2f(-25, ufo_y + 50);
    glVertex2f(30, ufo_y + 50);
    glVertex2f(150, ufo_y - 5);

    glEnd();

    //

    // draw a circle
    float radius = 20;
    float twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001)
        glVertex2f((-4 * cos(i) * radius), (-4 * sin(i) * radius + ufo_y - 10));

    glEnd();
    glFlush();
    // inside half circle
    glColor3f(1, 0, 0);
    radius = 8;
    twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001) {

        glVertex2f((-8 * cos(i) * radius), (-4 * sin(i) * radius + ufo_y + 30));
        glColor3f(0, 1, 0);
    }
    glEnd();
    glFlush();
    // subhalf1 left one 

    glColor3f(0.5, 0, 0);
    radius = 3;
    twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001) {

        glVertex2f((3 * cos(i) * radius - 20), (4 * sin(i) * radius + ufo_y - 10));
        glColor3f(0, 0.4, 0);
    }
    glEnd();
    glFlush();

    // subhalf right one
    glColor3f(0.5, 0, 0);
    radius = 3;
    twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001) {

        glVertex2f((3 * cos(i) * radius + 20), (4 * sin(i) * radius + ufo_y - 10));
        glColor3f(0, 0.4, 0);
    }
    glEnd();
    glFlush();



    //subright triangle 
    glColor3f(0.8, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(53, ufo_y - 10);
    glVertex2f(60, ufo_y - 10);
    // color transition
    glColor3f(255 / 255.0, 140 / 255.0, 0);
    glVertex2f(57, ufo_y - 38);
    glEnd();


    // subleft triangle
    glColor3f(0.8, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-53, ufo_y - 10);
    glVertex2f(-46, ufo_y - 10);
    // color transition
    glColor3f(255 / 255.0, 140 / 255.0, 0);

    glVertex2f(-49, ufo_y - 38);
    glEnd();
    // 


  
    

    // line 1
    glColor3f(0.8, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-2, ufo_y - 10);
    glVertex2f(4, ufo_y - 10);
    glColor3f(255 / 255.0, 140 / 255.0, 0);
    glVertex2f(2, ufo_y - 38);
    glEnd();

}
void display_run() {

    
    //glColor3f(198/ 255.0, 226/ 255.0, 255 / 255.0);
    glColor3f(245 / 255.0, 245 / 255.0, 245 / 255.0);
    glRectf(-485, 295, 485, -270);
    //154 192 205  198 226 255

    //quad
    // DRAW a QUAD for the body of spaceship
   //
    glColor3f(1, 1, 0.3);
    glBegin(GL_QUADS);
    glVertex2f(-150, ufo_y);
    glVertex2f(-25, ufo_y+50);
    glVertex2f(30, ufo_y+50);
    glVertex2f(150, ufo_y-5);
    
    glEnd();

    //

    // draw a circle
    float radius = 20;
    float twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001)
        glVertex2f((-4*cos(i) * radius ), (-4*sin(i) * radius +ufo_y-10));

    glEnd();
    glFlush();
    // inside half circle
    glColor3f(1, 0, 0);
     radius = 8;
     twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001) {
       
        glVertex2f((-8 * cos(i) * radius), (-4 * sin(i) * radius +ufo_y+30));
        glColor3f(0, 1, 0);
    }
    glEnd();
    glFlush();
    // subhalf1 left one 
    
    glColor3f(0.5, 0, 0);
    radius = 3;
    twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001) {

        glVertex2f((3 * cos(i) * radius-20), (4 * sin(i) * radius +ufo_y-10));
        glColor3f(0, 0.4, 0);
    }
    glEnd();
    glFlush();

    // subhalf right one
    glColor3f(0.5, 0, 0);
    radius = 3;
    twoPI = 2 * PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = PI; i <= twoPI; i += 0.001) {

        glVertex2f((3 * cos(i) * radius +20), (4 * sin(i) * radius +ufo_y-10));
        glColor3f(0, 0.4, 0);
    }
    glEnd();
    glFlush();



    //subright triangle 
    glColor3f(0.8, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(53, ufo_y-10);
    glVertex2f(60, ufo_y-10);
    // color transition
    glColor3f(255 / 255.0, 140 / 255.0, 0);
    glVertex2f(57, ufo_y-38);
    glEnd();


    // subleft triangle
    glColor3f(0.8, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-53, ufo_y-10);
    glVertex2f(-46, ufo_y-10);
    // color transition
    glColor3f(255/255.0, 140/255.0, 0);
    
    glVertex2f(-49, ufo_y-38);
    glEnd();
    // 
   
    
   // glColor3f(1, 0, 0);
    //circle(-1, -74, 30);
    // cloud left -270=xcloud1
    glColor3f(0, 0, 0.7);
    circle(x_cloud1, 260, 20);
    circle(x_cloud1+10, 260, 16);
    circle(x_cloud1-10, 260, 16);
    circle(x_cloud1-10, 256, 16);
    circle(x_cloud1+25, 256, 16);

    //cloud right
    glColor3f(0, 0, 1);
    circle(x_cloud2, 260, 20);
    circle(x_cloud2-10, 260, 16);
    circle(x_cloud2+10, 258, 16);
    circle(x_cloud2+10, 256, 16);
    circle(x_cloud2-15, 256, 16);
    //tree left
    glColor3f(150/ 255.0, 75 / 255.0, 0);
    glRectf(-382, -270, -350, -160);
    glColor3f(0, 1, 0);

    circle(-380, -160, 40);
    circle(-370, -160, 36);
    circle(-380, -158, 36);
    circle(-380, -156, 36);
    circle(-365, -156, 46);
    
    // tree right
    glColor3f(150 / 255.0, 75 / 255.0, 0);
    glRectf(362, -270, 390, -160);
    glColor3f(0, 1, 0);

    circle(380, -160, 35);
    circle(370, -160, 31);
    circle(380, -158, 31);
    circle(380, -156, 32);
    circle(365, -156, 41);
    //
  
    // line 1
    glColor3f(0.8, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(-2, ufo_y-10);
    glVertex2f(4, ufo_y-10);
    glColor3f(255 / 255.0, 140 / 255.0, 0);
    glVertex2f(2, ufo_y-38);
    glEnd();
}


//
// To display onto window using OpenGL commands
//
void display_space()
{
    display_start();
    //star
   
   
    glColor3f(0.7 , 0.1 ,1);

    glRectf(-485, 295, 485, -270);
    display_spaceship();
    glColor3f(1, 1, 0);
    circle(-250, 190, 25);
   
   
}
void display() {
    //
    // clear window to black
    //
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
     
    //  Begınnıng of the COMMON   BACKGROUND RECTANGLE
    //(255,228,225 misty rose)
    display_start();
 

    // DISPLAY RUN(ON button clıcked) STATE BACKGROUND AND SHAPES
    switch (appState) {
    case START:display_start(); break;
    case RUN: display_run(); 
     break;
    case SPACE:display_space();
        break;
    default:printf("\nYou didnt run it yet");
    }

    glutSwapBuffers();
}



//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//










void onClick(int button, int stat, int x, int y)
{
    // Write your codes here. open button
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        if (x > 658 && x<701 && y > 633 && y < 670) {
            // open the tv
            
            appState = RUN;
            
            clickCount++;
            if (clickCount %2==0)
                appState = START;
            printf("\nOPENEd!");
        }

        else if (x>600 &&x<748&&y<698&&y>681)
        {
            
            
            if (animating == 0){
               
                animating = 1;
                
                
            }
            else if (animating == 1)
                animating = 0;
            
            printf("\nRESTART");
        }
        
        
        }
    

        printf("Event : CLK %d %d\n", x, y);


    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function
    glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {
    if (animating) {
        glutTimerFunc(TIMER_PERIOD, onTimer, 0);
        // Write your codes here.
        if (appState == RUN || appState == SPACE) {
            t += 1;

            if (x_cloud1 < 437)
            {

                x_cloud1 += 1;

            }

            else if (x_cloud1 > 436)
            {
                x_cloud1 = -455;

            }
            if (x_cloud2 < 437)
                x_cloud2 += 1;
            else if (x_cloud2 > 436)
            {

                x_cloud2 = -455;
            }

            if (ufo_y > -155 && ufo_y < 200)
                ufo_y += 15;
            else if (ufo_y > 200)
            {
                ufo_y = -150;
                appState = SPACE;
            }

            if (t > 6.00f) {
                t = 0.0f;  // go to starting point.

                activeTimer = !activeTimer; //to stop or resume timer
            }


        }
        if (appState == START)
        {
            x_cloud1 = -270;
            x_cloud2 = 270;
            ufo_y = -140;
        }
        // to refresh the window it calls display() function
        glutPostRedisplay(); // display()
    }
}
#endif




void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Television By Eren Tarak");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    
    
    glutMouseFunc(onClick);

    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
    // timer event
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

    Init();

    glutMainLoop();
}