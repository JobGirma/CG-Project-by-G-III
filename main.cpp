#include <GL/glut.h>
#include <cmath>

// Define the number of teeth on the gears
const int numTeeth = 20;

// Define the number of gears
const int numGears = 4;

// Define gear parameters: radius and width
const float gearRadius[numGears] = {0.8f, 0.6f, 0.4f, 0.2f};
const float gearWidth[numGears] = {0.2f, 0.15f, 0.1f, 0.05f};

// Define rotation speed for each gear
const float rotationSpeed[numGears] = {1.0f, -1.5f, 2.0f, -2.5f};

void gear(float inner_radius, float outer_radius, float width, int teeth, float tooth_depth) {
    int i;
    float angle, da;
    float u, v, len;

    da = 2.0 * M_PI / teeth / 4.0;

    glShadeModel(GL_FLAT);

    /* draw front face */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++) {
        angle = i * 2.0 * M_PI / teeth;
        glVertex3f(inner_radius * cos(angle), inner_radius * sin(angle), width * 0.5);
        glVertex3f(outer_radius * cos(angle), outer_radius * sin(angle), width * 0.5);
        glVertex3f(inner_radius * cos(angle), inner_radius * sin(angle), width * 0.5);
        glVertex3f(outer_radius * cos(angle + 3 * da), outer_radius * sin(angle + 3 * da), width * 0.5);
    }
    glEnd();

    /* draw front sides of teeth */
    glBegin(GL_QUADS);
    da = 2.0 * M_PI / teeth / 4.0;
    for (i = 0; i < teeth; i++) {
        angle = i * 2.0 * M_PI / teeth;

        glVertex3f(outer_radius * cos(angle), outer_radius * sin(angle), width * 0.5);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + da), (outer_radius + tooth_depth) * sin(angle + da), width * 0.5);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + 2 * da), (outer_radius + tooth_depth) * sin(angle + 2 * da), width * 0.5);
        glVertex3f(outer_radius * cos(angle + 3 * da), outer_radius * sin(angle + 3 * da), width * 0.5);
    }
    glEnd();

    /* draw back face */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++) {
        angle = i * 2.0 * M_PI / teeth;
        glVertex3f(outer_radius * cos(angle), outer_radius * sin(angle), -width * 0.5);
        glVertex3f(inner_radius * cos(angle), inner_radius * sin(angle), -width * 0.5);
        glVertex3f(outer_radius * cos(angle + 3 * da), outer_radius * sin(angle + 3 * da), -width * 0.5);
        glVertex3f(inner_radius * cos(angle), inner_radius * sin(angle), -width * 0.5);
    }
    glEnd();

    /* draw back sides of teeth */
    glBegin(GL_QUADS);
    da = 2.0 * M_PI / teeth / 4.0;
    for (i = 0; i < teeth; i++) {
        angle = i * 2.0 * M_PI / teeth;

        glVertex3f(outer_radius * cos(angle + 3 * da), outer_radius * sin(angle + 3 * da), -width * 0.5);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + 2 * da), (outer_radius + tooth_depth) * sin(angle + 2 * da), -width * 0.5);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + da), (outer_radius + tooth_depth) * sin(angle + da), -width * 0.5);
        glVertex3f(outer_radius * cos(angle), outer_radius * sin(angle), -width * 0.5);
    }
    glEnd();

    /* draw outward faces of teeth */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i < teeth; i++) {
        angle = i * 2.0 * M_PI / teeth;

        glVertex3f(outer_radius * cos(angle), outer_radius * sin(angle), width * 0.5);
        glVertex3f(outer_radius * cos(angle), outer_radius * sin(angle), -width * 0.5);
        u = (outer_radius + tooth_depth) * cos(angle + da) - outer_radius * cos(angle);
        v = (outer_radius + tooth_depth) * sin(angle + da) - outer_radius * sin(angle);
        len = sqrt(u * u + v * v);
        u /= len;
        v /= len;
        glNormal3f(v, -u, 0.0);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + da), (outer_radius + tooth_depth) * sin(angle + da), width * 0.5);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + da), (outer_radius + tooth_depth) * sin(angle + da), -width * 0.5);
        glNormal3f(cos(angle), sin(angle), 0.0);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + 2 * da), (outer_radius + tooth_depth) * sin(angle + 2 * da), width * 0.5);
        glVertex3f((outer_radius + tooth_depth) * cos(angle + 2 * da), (outer_radius + tooth_depth) * sin(angle + 2 * da), -width * 0.5);
        u = outer_radius * cos(angle + 3 * da) - (outer_radius + tooth_depth) * cos(angle + 2 * da);
        v = outer_radius * sin(angle + 3 * da) - (outer_radius + tooth_depth) * sin(angle + 2 * da);
        len = sqrt(u * u + v * v);
        u /= len;
        v /= len;
        glNormal3f(v, -u, 0.0);
        glVertex3f(outer_radius * cos(angle + 3 * da), outer_radius * sin(angle + 3 * da), width * 0.5);
        glVertex3f(outer_radius * cos(angle + 3 * da), outer_radius * sin(angle + 3 * da), -width * 0.5);
        glNormal3f(cos(angle), sin(angle), 0.0);
    }
    glVertex3f(outer_radius * cos(0), outer_radius * sin(0), width * 0.5);
    glVertex3f(outer_radius * cos(0), outer_radius * sin(0), -width * 0.5);

    glEnd();

    glShadeModel(GL_SMOOTH);

    /* draw inside radius cylinder */
    glBegin(GL_QUAD_STRIP);
    for (i = 0; i <= teeth; i++) {
        angle = i * 2.0 * M_PI / teeth;
        glNormal3f(-cos(angle), -sin(angle), 0.0);
        glVertex3f(inner_radius * cos(angle), inner_radius * sin(angle), -width * 0.5);
        glVertex3f(inner_radius * cos(angle), inner_radius * sin(angle), width * 0.5);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glColor3f(0.8, 0.1, 0.0); // Red color for gears

    // Set up light
    GLfloat light_position[] = {0.0, 0.0, 5.0, 0.0}; // Light positioned at (0, 0, 5)
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Translate to a position where we want to draw the gears
    glTranslatef(-1.5, 0.0, -6.0);

    // Draw the gears
    for (int i = 0; i < numGears; ++i) {
        glPushMatrix();
        glRotatef(i * 360.0 / numGears, 0.0, 0.0, 1.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0, gearRadius[i], 0.0);
        glRotatef(rotationSpeed[i] * glutGet(GLUT_ELAPSED_TIME) / 1000.0, 0.0, 0.0, 1.0);
        gear(0.1, gearRadius[i], gearWidth[i], numTeeth, 0.2);
        glPopMatrix();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL); // Enable color material for coloring
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Moving Connected Gear");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
