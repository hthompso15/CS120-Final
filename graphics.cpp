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

Button smileButton({1, 0, 0}, {250, 100}, 100, 50, "Smiley Face");

Button balloonButton({0,1,0},{100,250},100,50,"Balloon");

Button starButton({0,0,1},{250,400}, 100,50,"Star");

Button heartButton({1,0,1},{400,250}, 100,50,"Heart");

enum Screen {
    StartScreen,
    MenuScreen,
    EndScreen,
    SmileFace,
    Balloon,
    Star,
    Heart,
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
        string label = "Welcome to the Art Expo!";
        glColor3f(1, 1, 1);
        glRasterPos2i(250, 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
    }

    if (screenState == MenuScreen) {
        string label = "Use the Keys";
        glColor3f(1, 1, 1);
        glRasterPos2i(200, 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string label1 = "To choose an option!";
        glColor3f(1, 1, 1);
        glRasterPos2i(170, 270);
        for (const char &letter : label1) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }
        string label2 = "(Press Space to go Back)";
        glColor3f(1, 1, 1);
        glRasterPos2i(155, 290);
        for (const char &letter : label2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        smileButton.draw();
        balloonButton.draw();
        starButton.draw();
        heartButton.draw();
    }

    // Determine what image to display


    // Smiley face
    if (screenState == SmileFace) {
        ifstream inFile("../smile.txt");
        inFile >> noskipws;
        int xCoord = 0, yCoord = 0;
        char letter;
        bool draw;
        while (inFile >> letter) {
            draw = true;
            switch (letter) {
                case 'r':
                    glColor3f(1, 0, 0);
                    break;
                case 'g':
                    glColor3f(0, 1, 0);
                    break;
                case 'b':
                    glColor3f(0, 0, 1);
                    break;
                case 'y':
                    glColor3f(1, 1, 0);
                    break;
                case 'm':
                    glColor3f(1, 0, 1);
                    break;
                case 'c':
                    glColor3f(0, 1, 1);
                    break;
                case ' ':
                    glColor3f(0, 0, 0);
                    break;
                case 'w':
                    glColor3f(1,1,1);
                    break;
                default: // newline
                    draw = false;
                    xCoord = 0;
                    yCoord += SIDE_LENGTH;
            }
            if (draw) {
                glBegin(GL_QUADS);
                glVertex2i(xCoord, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord + SIDE_LENGTH);
                glVertex2i(xCoord, yCoord + SIDE_LENGTH);
                glEnd();
                xCoord += SIDE_LENGTH;
            }
        }
        inFile.close();
    }

    // Balloon
    if (screenState == Balloon) {
        ifstream inFile("../balloon.txt");
        inFile >> noskipws;
        int xCoord = 0, yCoord = 0;
        char letter;
        bool draw;
        while (inFile >> letter) {
            draw = true;
            switch (letter) {
                case 'r':
                    glColor3f(1, 0, 0);
                    break;
                case 'g':
                    glColor3f(0, 1, 0);
                    break;
                case 'b':
                    glColor3f(0, 0, 1);
                    break;
                case 'y':
                    glColor3f(1, 1, 0);
                    break;
                case 'm':
                    glColor3f(1, 0, 1);
                    break;
                case 'c':
                    glColor3f(0, 1, 1);
                    break;
                case ' ':
                    glColor3f(0, 0, 0);
                    break;
                case 'w':
                    glColor3f(1,1,1);
                    break;
                default: // newline
                    draw = false;
                    xCoord = 0;
                    yCoord += SIDE_LENGTH;
            }
            if (draw) {
                glBegin(GL_QUADS);
                glVertex2i(xCoord, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord + SIDE_LENGTH);
                glVertex2i(xCoord, yCoord + SIDE_LENGTH);
                glEnd();
                xCoord += SIDE_LENGTH;
            }
        }
        inFile.close();
    }

    // Star
    if (screenState == Star) {
        ifstream inFile("../star.txt");
        inFile >> noskipws;
        int xCoord = 0, yCoord = 0;
        char letter;
        bool draw;
        while (inFile >> letter) {
            draw = true;
            switch (letter) {
                case 'r':
                    glColor3f(1, 0, 0);
                    break;
                case 'g':
                    glColor3f(0, 1, 0);
                    break;
                case 'b':
                    glColor3f(0, 0, 1);
                    break;
                case 'y':
                    glColor3f(1, 1, 0);
                    break;
                case 'm':
                    glColor3f(1, 0, 1);
                    break;
                case 'c':
                    glColor3f(0, 1, 1);
                    break;
                case ' ':
                    glColor3f(0, 0, 0);
                    break;
                case 'w':
                    glColor3f(1,1,1);
                    break;
                default: // newline
                    draw = false;
                    xCoord = 0;
                    yCoord += SIDE_LENGTH;
            }
            if (draw) {
                glBegin(GL_QUADS);
                glVertex2i(xCoord, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord + SIDE_LENGTH);
                glVertex2i(xCoord, yCoord + SIDE_LENGTH);
                glEnd();
                xCoord += SIDE_LENGTH;
            }
        }
        inFile.close();
    }

    // Heart
    if (screenState == Heart) {
        ifstream inFile("../heart.txt");
        inFile >> noskipws;
        int xCoord = 0, yCoord = 0;
        char letter;
        bool draw;
        while (inFile >> letter) {
            draw = true;
            switch (letter) {
                case 'r':
                    glColor3f(1, 0, 0);
                    break;
                case 'g':
                    glColor3f(0, 1, 0);
                    break;
                case 'b':
                    glColor3f(0, 0, 1);
                    break;
                case 'y':
                    glColor3f(1, 1, 0);
                    break;
                case 'm':
                    glColor3f(1, 0, 1);
                    break;
                case 'c':
                    glColor3f(0, 1, 1);
                    break;
                case ' ':
                    glColor3f(0, 0, 0);
                    break;
                case 'w':
                    glColor3f(1,1,1);
                    break;
                default: // newline
                    draw = false;
                    xCoord = 0;
                    yCoord += SIDE_LENGTH;
            }
            if (draw) {
                glBegin(GL_QUADS);
                glVertex2i(xCoord, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord);
                glVertex2i(xCoord + SIDE_LENGTH, yCoord + SIDE_LENGTH);
                glVertex2i(xCoord, yCoord + SIDE_LENGTH);
                glEnd();
                xCoord += SIDE_LENGTH;
            }
        }
        inFile.close();
    }

    if (screenState == EndScreen) {
        initGL();
        string label = "Woooo Party Time!";
        glColor3f(1, 1, 1);
        glRasterPos2i(250, 250);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
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

    if(key == 'e') {
        screenState = EndScreen;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            screenState = Star;
            break;
        case GLUT_KEY_LEFT:
            screenState = Balloon;
            break;
        case GLUT_KEY_RIGHT:
            screenState = Heart;
            break;
        case GLUT_KEY_UP:
            screenState = SmileFace;
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


