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
    Poligono cabeca;
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

    glColor3ub(0, 0, 0); // contorno preto
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < p.n; i++)
        glVertex2f(p.v[i].x, p.v[i].y);
    glEnd();
}

// --- Desenha personagem diretamente no mesmo sistema de coordenadas ---
void DesenhaPersonagem(Personagem p) {
    DesenhaPoligono(p.corpo);
    DesenhaPoligono(p.cabeca);
    DesenhaPoligono(p.bracoEsq);
    DesenhaPoligono(p.bracoDir);
    DesenhaPoligono(p.pernaEsq);
    DesenhaPoligono(p.pernaDir);
}

// --- Variável global ---
Personagem personagem;

// --- Display ---
void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaPersonagem(personagem);
    glFlush();
}

// --- Inicialização OpenGL ---
void Inicializa(void) {
    glClearColor(1, 1, 1, 1); // fundo branco
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10); // mesmo sistema de coordenadas para todas as partes
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// --- Programa principal ---
int main(int argc, char **argv) {
    // Carrega todas as partes (coordenadas já no mesmo sistema de referência)
    
    personagem.pernaEsq = LerPoligono("pe_esq.txt");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Modelagem OpenGL 2D Gamora");
    Inicializa();
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}
