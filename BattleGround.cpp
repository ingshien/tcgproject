#include "BattleGround.hpp"
#include <GL/glut.h>
#include <cmath>

BattleGround3D::BattleGround3D(float r, int s)
    : radius(r), segments(s) {}

void BattleGround3D::draw() {

    glColor3f(0.0f, 0.3f, 0.8f);
    glBegin(GL_QUADS);
        glVertex3f(-500, 0, -500);
        glVertex3f( 500, 0, -500);
        glVertex3f( 500, 0,  500);
        glVertex3f(-500, 0,  500);
    glEnd();


    glColor3f(0.5f, 0.5f, 0.5f);
    float height = 1.0f;


    glPushMatrix();
    glTranslatef(0.0f, height, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0.0f, 0.0f, 0.0f);
        for (int i = 0; i <= segments; ++i) {
            float angle = 2.0f * 3.1415926f * i / segments;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            glVertex3f(x, 0.0f, z);
        }
    glEnd();
    glPopMatrix();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * 3.1415926f * i / segments;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, height, z);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}
