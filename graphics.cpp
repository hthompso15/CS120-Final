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

Button levelOne({1, 0, 0}, {250, 250}, 100, 50, "Play!");
Button winButton({0, 1, 0}, {250, 400}, 100, 50, "You Won!");
Quad square({1,0,0},{250,5},10,10);
vector<Quad> confetti;

enum Screen {
    StartScreen,
    WinScreen,
    MazeScreen,
    EndScreen,

};
void spawnConfetti() {
    confetti.push_back(Quad({rand() % 10 / 10.0, rand() % 10 / 10.0, rand() % 10 / 10.0}, {rand() % (int)width, rand() % (int)height}, 10, 10));
}

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
        glRasterPos2i(150, 150);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string label1 = "The rules are simple; Don't touch the walls";
        glColor3f(1, 1, 1);
        glRasterPos2i(100, 175);
        for (const char &letter : label1) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        string label2 = "and get to the purple square! Click Play to start!";
        glColor3f(1, 1, 1);
        glRasterPos2i(75, 200);
        for (const char &letter : label2) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

        levelOne.draw();
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

        Quad wall4({1,1,1}, {250,250}, 25,400);
        wall4.draw();
        walls.push_back(wall4);

        Quad wall5({1,1,1}, {300,250}, 300,25);
        wall5.draw();
        walls.push_back(wall5);

        Quad wall6({1,1,1}, {350,100}, 400,25);
        wall6.draw();
        walls.push_back(wall6);

        Quad wall7({1,1,1}, {100,400}, 200,25);
        wall7.draw();
        walls.push_back(wall7);

        Quad wall9({1,1,1}, {439,300}, 25,321);
        wall9.draw();
        walls.push_back(wall9);

        Quad wall10({1,1,1}, {190 ,250}, 25,180);
        wall10.draw();
        walls.push_back(wall10);

        Quad wall11({1,1,1}, {100,100}, 25,200);
        wall11.draw();
        walls.push_back(wall11);

        Quad wall12({1,1,1}, {100,250}, 25,150);
        wall12.draw();
        walls.push_back(wall12);

        Quad wall13({1,1,1}, {325,350}, 150,25);
        wall13.draw();
        walls.push_back(wall13);

        Quad wall14({1,1,1}, {370,120}, 25,150);
        wall14.draw();
        walls.push_back(wall14);

        Quad wall15({1,1,1}, {310,450}, 25,100);
        wall15.draw();
        walls.push_back(wall15);

        Quad winBox({1,0,1}, {275,225}, 25,25);
        winBox.draw();

        Quad wall16({1,1,1}, {10,175}, 75,25);
        wall16.draw();
        walls.push_back(wall16);

        Quad wall17({1,1,1}, {75,300}, 75,25);
        wall17.draw();
        walls.push_back(wall17);


        square.draw();


        if (winBox.isOverlapping(square)) {
            screenState = WinScreen;
        }


        for(int i = 0; i < walls.size();i++) {
            if(walls[i].isOverlapping(square) ) {
                screenState = EndScreen;
            }
        }
    }

    if (screenState == EndScreen) {
        string label1 = "You Lose :(  Re-Run the program to try again!";
        glColor3f(1, 1, 1);
        glRasterPos2i(100, 250);
        for (const char &letter : label1) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
        }

    }

    if (screenState == WinScreen) {

        winButton.draw();
        int confettis = 0;
        for (const Quad &piece : confetti) {
            piece.draw();
            confettis++;
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
        screenState = WinScreen;
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
    if (levelOne.isOverlapping(x,y)) {
        levelOne.hover();
    }
    else
        levelOne.release();

    if(winButton.isOverlapping(x,y)) {
        winButton.hover();
    }
    else
        winButton.release();

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && levelOne.isOverlapping(x,y)) {
        levelOne.pressDown();
        screenState = MazeScreen;
    }
    else
        levelOne.release();

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && winButton.isOverlapping(x,y)) {
        winButton.pressDown();
        spawnConfetti();
    }
    else
        winButton.release();


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
    wd = glutCreateWindow("Maze Runner" /* title */ );
    
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


