#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// --- Estruturas ---
typedef struct {
    float x, y;
} Ponto;

typedef struct {
    int n;                 // número de vértices
    unsigned char r, g, b; // cor (0-255)
    Ponto *v;              // vetor de vértices
} Poligono;

typedef struct {
    Poligono cabelo;
    Poligono cabeca;
    Poligono nariz;
    Poligono bocaCima;
    Poligono bocaBaixo;
    Poligono olhoEsq;
    Poligono irisEsq;
    Poligono olhoDir;
    Poligono irisDir;
    Poligono corpo;
    Poligono bracoEsq;
    Poligono antebracoEsq;
    Poligono maoEsq;
    Poligono bracoDir;
    Poligono antebracoDir;
    Poligono maoDir;
    Poligono coxaEsq;
    Poligono panturrilhaEsq;
    Poligono peEsq;
    Poligono coxaDir;
    Poligono panturrilhaDir;
    Poligono peDir;
} Personagem;

// --- Funções ---
Poligono LerPoligono(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "r");
    if (!f) {
        printf("Erro ao abrir %s!\n", nomeArquivo);
        exit(1);
    }

    Poligono p;
    fscanf(f, "%d %hhu %hhu %hhu", &p.n, &p.r, &p.g, &p.b);
    p.v = malloc(p.n * sizeof(Ponto));
    for (int i = 0; i < p.n; i++)
        fscanf(f, "%f %f", &p.v[i].x, &p.v[i].y);

    fclose(f);
    return p;
}

void DesenhaPoligono(Poligono p) {

    glColor3ub(p.r, p.g, p.b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < p.n; i++)
        glVertex2f(p.v[i].x, p.v[i].y);
    glEnd();

    glColor3ub(0, 0, 0);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < p.n; i++)
        glVertex2f(p.v[i].x, p.v[i].y);
    glEnd();
    
}

// --- Desenha personagem hierarquicamente ---
void DesenhaPersonagemHier(Personagem p) {
    glPushMatrix();

        // Perna esquerda
        glPushMatrix();
            glTranslatef(-0.54, -0.58, 0); // quadril
            glRotatef(0, 0, 0, 1);
            DesenhaPoligono(p.coxaEsq);

            glPushMatrix();
                glTranslatef(-1.26, -3.55, 0); // joelho
                glRotatef(0, 0, 0, 1);
                DesenhaPoligono(p.panturrilhaEsq);

                glPushMatrix();
                    glTranslatef(-1.0, -2.83, 0); // pé
                    glRotatef(0, 0, 0, 1);
                    DesenhaPoligono(p.peEsq);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        // Perna direita
        glPushMatrix();
            glTranslatef(0.54, -0.58, 0); // quadril
            glRotatef(0, 0, 0, 1);
            DesenhaPoligono(p.coxaDir);

            glPushMatrix();
                glTranslatef(1.26, -3.55, 0); // joelho
                glRotatef(0, 0, 0, 1);
                DesenhaPoligono(p.panturrilhaDir);

                glPushMatrix();
                    glTranslatef(1.0, -2.83, 0); // pé
                    glRotatef(0, 0, 0, 1);
                    DesenhaPoligono(p.peDir);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        // Corpo como referência central
        DesenhaPoligono(p.corpo);

        // Cabeça (posição relativa ao corpo)
        glPushMatrix();
            glTranslatef(0, 3.17, 0); // ajuste conforme o ponto de articulação do pescoço
            DesenhaPoligono(p.cabelo);
            DesenhaPoligono(p.cabeca);
            DesenhaPoligono(p.nariz);
            DesenhaPoligono(p.bocaCima);
            DesenhaPoligono(p.bocaBaixo);
            DesenhaPoligono(p.olhoEsq);
            DesenhaPoligono(p.irisEsq);
            DesenhaPoligono(p.olhoDir);
            DesenhaPoligono(p.irisDir);
        glPopMatrix();

        // Braço esquerdo
        glPushMatrix();
            glTranslatef(-0.81, 2.77, 0); // ombro
            glRotatef(0, 0, 0, 1);  // ângulo inicial
            DesenhaPoligono(p.bracoEsq);

            glPushMatrix();
                glTranslatef(-0.69, -0.03, 0); // cotovelo
                glRotatef(0, 0, 0, 1);
                DesenhaPoligono(p.antebracoEsq);

                glPushMatrix();
                    glTranslatef(-0.62, 0.26, 0); // mão
                    glRotatef(0, 0, 0, 1);
                    DesenhaPoligono(p.maoEsq);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        // Braço direito
        glPushMatrix();
            glTranslatef(0.81, 2.77, 0); // ombro
            glRotatef(0, 0, 0, 1);
            DesenhaPoligono(p.bracoDir);

            glPushMatrix();
                glTranslatef(0.69, -0.03, 0); // cotovelo
                glRotatef(0, 0, 0, 1);
                DesenhaPoligono(p.antebracoDir);

                glPushMatrix();
                    glTranslatef(0.62, 0.26, 0); // mão
                    glRotatef(0, 0, 0, 1);
                    DesenhaPoligono(p.maoDir);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}

// --- Variável global ---
Personagem personagem;

// --- Display ---
void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaPersonagemHier(personagem);
    glFlush();
}

// --- Inicialização OpenGL ---
void Inicializa(void) {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// --- Programa principal ---
int main(int argc, char **argv) {
    personagem.peEsq = LerPoligono("pe_esq.txt");
    personagem.panturrilhaEsq = LerPoligono("panturrilha_esq.txt");
    personagem.coxaEsq = LerPoligono("coxa_esq.txt");
    personagem.peDir = LerPoligono("pe_dir.txt");
    personagem.panturrilhaDir = LerPoligono("panturrilha_dir.txt");
    personagem.coxaDir = LerPoligono("coxa_dir.txt");
    personagem.bracoEsq = LerPoligono("braco_esq.txt");
    personagem.antebracoEsq = LerPoligono("antebraco_esq.txt");
    personagem.maoEsq = LerPoligono("mao_esq.txt");
    personagem.bracoDir = LerPoligono("braco_dir.txt");
    personagem.antebracoDir = LerPoligono("antebraco_dir.txt");
    personagem.maoDir = LerPoligono("mao_dir.txt");
    personagem.corpo = LerPoligono("corpo_new.txt");
    personagem.cabelo = LerPoligono("cabelo.txt");
    personagem.cabeca = LerPoligono("cabeca.txt");
    personagem.nariz = LerPoligono("nariz.txt");
    personagem.bocaCima = LerPoligono("boca_cima.txt");
    personagem.bocaBaixo = LerPoligono("boca_baixo.txt");
    personagem.olhoEsq = LerPoligono("cont_olho_esq.txt");
    personagem.irisEsq = LerPoligono("iris_esq.txt");
    personagem.olhoDir = LerPoligono("cont_olho_dir.txt");
    personagem.irisDir = LerPoligono("iris_dir.txt");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Personagem Hierarquico");
    Inicializa();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}
