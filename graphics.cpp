#include "graphics.h"
#include "Button.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;

GLdouble width, height;
int wd;
const int SIDE_LENGTH = 20;
vector<Quad> walls;

Button levelOne({1, 0, 0}, {100, 250}, 100, 50, "Play!");
Quad square({1,0,0},{250,5},10,10);


enum Screen {
    StartScreen,
    MenuScreen,
    MazeScreen,
    EndScreen,

};

Screen screenState = StartScreen;

void init() {
    width = 500;
    height = 500;
    srand(time(0));
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */
    // Starting Display screen press space bar to move to the Menu
    if (screenState == StartScreen) {
        string label = "Welcome to Maze runner!";
        glColor3f(1, 1, 1);
        glRasterPos2i(250, 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if (screenState == MenuScreen) {
        string label = "Press the button to play!";
        glColor3f(1, 1, 1);
        glRasterPos2i(200, 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);

            levelOne.draw();

        }
    }

    if(screenState == MazeScreen) {



        Quad wall({1,1,1}, {125,0}, 225,25);
        wall.draw();
        walls.push_back(wall);

        Quad topWall1({1,1,1}, {375,0}, 225,25);
        topWall1.draw();
        walls.push_back(topWall1);

        Quad wall1({1,1,1}, {0,250}, 25,500);
        wall1.draw();
        walls.push_back(wall1);

        Quad wall2({1,1,1}, {500,250}, 25,500);
        wall2.draw();
        walls.push_back(wall2);

        Quad wall3({1,1,1}, {250,500}, 500,25);
        wall3.draw();
        walls.push_back(wall3);

        Quad wall4({1,1,1}, {250,250}, 25,450);
        wall4.draw();
        walls.push_back(wall4);

        Quad wall5({1,1,1}, {250,250}, 400,25);
        wall5.draw();
        walls.push_back(wall5);

        Quad wall6({1,1,1}, {250,100}, 405,25);
        wall6.draw();
        walls.push_back(wall6);

        square.draw();


        for(int i = 0; i < walls.size();i++) {
            if( square.isOverlapping(walls[i]) ) {
                screenState = EndScreen;
            }
        }

    }



    glFlush();// Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    if (key == 32) {
        screenState = MenuScreen;
    }

    if(key == '1') {
        screenState = MazeScreen;
    }

    if(key == 'e') {
        screenState = EndScreen;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            square.move(0, 5);

            break;
        case GLUT_KEY_LEFT:
            square.move(-5, 0);
            break;
        case GLUT_KEY_RIGHT:
            square.move(5, 0);
            break;
        case GLUT_KEY_UP:
            square.move(0, -5);
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {


    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {

    glutPostRedisplay();
}

void timer(int dummy) {
    
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Art Expo!" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}


