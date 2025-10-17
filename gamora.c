#include <GL/glut.h>

void DesenhaCabeca() {
    // Cabelo
    glColor3ub(54, 159, 77);
    glBegin(GL_POLYGON);
        glVertex2f(-0.76f, 8.44f);
        glVertex2f(-1.2f, 7.66f);
        glVertex2f(-1.35f, 6.85f);
        glVertex2f(-1.45f, 5.91f);
        glVertex2f(-1.0f, 6.06f);
        glVertex2f(-0.61f, 5.88f);
        glVertex2f(-0.17f, 5.97f);
        glVertex2f(0.55f, 5.88f);
        glVertex2f(0.86f, 6.17f);
        glVertex2f(1.09f, 5.87f);
        glVertex2f(1.39f, 6.62f);
        glVertex2f(1.34f, 7.47f);
        glVertex2f(1.13f, 7.94f);
        glVertex2f(0.82f, 8.44f);
        glVertex2f(0.03f, 8.81f);
    glEnd();

    // Rosto
    glColor3ub(189, 238, 156); // Pele
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 8.5f);
        glVertex2f(-0.57f, 8.29f);
        glVertex2f(-0.98f, 7.74f);
        glVertex2f(-0.86f, 7.07f);
        glVertex2f(-0.62f, 6.40f);
        glVertex2f(0.0f, 6.0f);
        glVertex2f(0.63f, 6.40f);
        glVertex2f(0.93f, 7.20f);
        glVertex2f(0.95f, 7.79f);
        glVertex2f(0.60f, 8.36f);
    glEnd();

    // Olhos
    glColor3ub(255, 230, 77);
    // Olho Direito
    glBegin(GL_POLYGON);
        glVertex2f(-0.60f, 7.73f);
        glVertex2f(-0.51f, 7.77f);
        glVertex2f(-0.43f, 7.77f);
        glVertex2f(-0.35f, 7.73f);
        glVertex2f(-0.34f, 7.69f);
        glVertex2f(-0.41f, 7.647f);
        glVertex2f(-0.51f, 7.645f);
        glVertex2f(-0.58f, 7.67f);
    glEnd();
    // Olho esquerdo
    glBegin(GL_POLYGON);
        glVertex2f(0.34f, 7.72f);
        glVertex2f(0.42f, 7.76f);
        glVertex2f(0.51f, 7.76f);
        glVertex2f(0.59f, 7.72f);
        glVertex2f(0.60f, 7.68f);
        glVertex2f(0.53f, 7.64f);
        glVertex2f(0.43f, 7.637f);
        glVertex2f(0.36f, 7.66f);
    glEnd();

    glColor3ub(0, 0, 25);
    // Boca
    glBegin(GL_POLYGON);
        glVertex2f(-0.30f, 6.55f);
        glVertex2f(-0.23f, 6.60f);
        glVertex2f(-0.15f, 6.63f);
        glVertex2f(0.0f, 6.61f);
        glVertex2f(0.17f, 6.63f);
        glVertex2f(0.27f, 6.59f);
        glVertex2f(0.32f, 6.55f);
        glVertex2f(0.28f, 6.52f);
        glVertex2f(0.15f, 6.48f);
        glVertex2f(0.0f, 6.47f);
        glVertex2f(-0.15f, 6.49f);
        glVertex2f(-0.25f, 6.51f);
    glEnd();

    glColor3ub(169, 218, 136);
    // Nariz
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 7.28f);
        glVertex2f(-0.07f, 7.18f);
        glVertex2f(-0.1f, 7.12f);
        glVertex2f(-0.09f, 7.11f);
        glVertex2f(-0.06f, 7.108f);
        glVertex2f(-0.03f, 7.12f);
        glVertex2f(0.0f, 7.10f);
        glVertex2f(0.04f, 7.117f);
        glVertex2f(0.06f, 7.109f);
        glVertex2f(0.09f, 7.11f);
        glVertex2f(0.10f, 7.12f);
        glVertex2f(0.07f, 7.18f);
        glVertex2f(0.04f, 7.28f);
    glEnd();
}

void DesenhaCorpo() {
    // Tronco
    glColor3ub(0,0,0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.2f, 6.0f);
        glVertex2f(1.2f, 6.0f);
        glVertex2f(1.0f, 2.5f);
        glVertex2f(-1.0f, 2.5f);
    glEnd();

    // Detalhes do uniforme
    glColor3ub(102, 255, 102);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 2.5f);
        glVertex2f(-1.20f, 6.0f);
        glVertex2f(1.20f, 6.0f);
    glEnd();

    // Cinto
    glColor3ub(179, 128, 26);
    glBegin(GL_QUADS);
        glVertex2f(-1.05f, 3.2f);
        glVertex2f(1.05f, 3.2f);
        glVertex2f(1.05f, 3.0f);
        glVertex2f(-1.05f, 3.0f);
    glEnd();

    // Fivela
    glColor3ub(230, 204, 77);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 3.3f);
        glVertex2f(-0.25f, 3.1f);
        glVertex2f(0.25f, 3.1f);

        glVertex2f(0.0f, 2.9f);
        glVertex2f(-0.25f, 3.1f);
        glVertex2f(0.25f, 3.1f);
    glEnd();
}

void DesenhaBracoDireito() {
    // Braço
    glColor3ub(102, 255, 102);
    glBegin(GL_QUADS);
        glVertex2f(1.2f, 6.0f);
        glVertex2f(1.8f, 6.0f);
        glVertex2f(2.2f, 2.5f);
        glVertex2f(1.5f, 2.5f);
    glEnd();

    // Luva
    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f(1.5f, 2.5f);
        glVertex2f(2.1f, 2.5f);
        glVertex2f(2.2f, 2.2f);
        glVertex2f(1.4f, 2.2f);
    glEnd();
}

void DesenhaBracoEsquerdo() {
    glColor3ub(102, 255, 102);
    glBegin(GL_QUADS);
        glVertex2f(-1.2f, 6.0f);
        glVertex2f(-1.8f, 6.0f);
        glVertex2f(-2.2f, 2.5f);
        glVertex2f(-1.5f, 2.5f);
    glEnd();

    glColor3ub(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f(-1.5f, 2.5f);
        glVertex2f(-2.1f, 2.5f);
        glVertex2f(-2.2f, 2.2f);
        glVertex2f(-1.4f, 2.2f);
    glEnd();
}

void DesenhaPernaDireita() {
    glColor3ub(102,255,102);
    glBegin(GL_QUADS);
        glVertex2f(0.4f, 2.5f);
        glVertex2f(1.0f, 2.5f);
        glVertex2f(1.0f, -0.5f);
        glVertex2f(0.4f, -0.5f);
    glEnd();

    glColor3ub(13,13,13);
    glBegin(GL_QUADS);
        glVertex2f(0.4f, -0.5f);
        glVertex2f(1.0f, -0.5f);
        glVertex2f(1.0f, -1.5f);
        glVertex2f(0.4f, -1.5f);
    glEnd();
}

void DesenhaPernaEsquerda() {

    glColor3ub(102,255,102);
    glBegin(GL_QUADS);
        glVertex2f(-0.4f, 2.5f);
        glVertex2f(-1.0f, 2.5f);
        glVertex2f(-1.0f, -0.5f);
        glVertex2f(-0.4f, -0.5f);
    glEnd();

    glColor3ub(13,13,13);
    glBegin(GL_QUADS);
        glVertex2f(-0.4f, -0.5f);
        glVertex2f(-1.0f, -0.5f);
        glVertex2f(-1.0f, -1.5f);
        glVertex2f(-0.4f, -1.5f);
    glEnd();
}

void DesenhaCapa() {
    glColor3ub(0, 77, 0);
    glBegin(GL_POLYGON);
        glVertex2f(-1.8f, 6.0f);
        glVertex2f(1.8f, 6.0f);
        glVertex2f(3.0f, 1.0f);
        glVertex2f(-3.0f, 1.0f);
    glEnd();
}

//Desenho completo
void DesenhaGamora() {
    DesenhaCapa();
    DesenhaCabeca();
    DesenhaCorpo();
    DesenhaBracoDireito();
    DesenhaBracoEsquerdo();
    DesenhaPernaDireita();
    DesenhaPernaEsquerda();
}

//Executando o OpenGL
void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    DesenhaGamora();
    glFlush();
}

void Inicializa() {
    glClearColor(0.05f,0.05f,0.10f,1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10.00, 10.00, -10.00, 10.00);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Gamora 2D - Versao HQ");
    Inicializa();
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}
