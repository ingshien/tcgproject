// main.cpp
#include <GL/glut.h>
#include <cmath>
#include <algorithm>
#include "BattleGround.hpp"


struct Fighter {
    float x, z;
    float color[3];
    bool attacking;
    int health;

    void draw() {
        glPushMatrix();
            glTranslatef(x, 1.5f, z);
            glColor3fv(color);
            glutSolidCube(20.0f);
        glPopMatrix();

        if (attacking) {
            glColor3f(1, 1, 0);
            glPushMatrix();
                glTranslatef(x + (color[0] > 0 ? 10 : -10), 1.5f, z);
                glutSolidSphere(5.0, 16, 16);
            glPopMatrix();
        }
    }
};

BattleGround3D* bg;
Fighter p1 { -50.0f, 0.0f, {1, 0, 0}, false, 100 };
Fighter p2 {  50.0f, 0.0f, {0, 0, 1}, false, 100 };

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 200, 200, 0, 0, 0, 0, 1, 0); // 摄像机视角

    bg->draw();
    p1.draw();
    p2.draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (float)w / h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
}

void update(int) {
    if (p1.attacking && fabs(p1.x - p2.x) < 25.0f) {
        p2.health = std::max(0, p2.health - 1);
    }
    if (p2.attacking && fabs(p2.x - p1.x) < 25.0f) {
        p1.health = std::max(0, p1.health - 1);
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
        case 'a': p1.x -= 5.0f; break;
        case 'd': p1.x += 5.0f; break;
        case 'q': p1.attacking = true;  break;
        case 'w': p1.attacking = false; break;
        case 'j': p2.x -= 5.0f; break;
        case 'l': p2.x += 5.0f; break;
        case 'u': p2.attacking = true;  break;
        case 'i': p2.attacking = false; break;
        case 27:  exit(0); break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Circular Battleground");

    glEnable(GL_DEPTH_TEST);

    bg = new BattleGround3D(100.0f, 64);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
