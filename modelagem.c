#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

typedef struct{
    float x, y;
} Ponto;

typedef struct{
    int n;
    unsigned char r, g, b;
    Ponto *v;
} Poligono;

Poligono *poligonos = NULL;
int nPoligonos = 0;

// Função para ler as coordenadas do arquivo texto
void LerTxt(const char *nomeArquivo){
    FILE *f = fopen(nomeArquivo, "r");
    if (!f){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    while(!feof(f)){
        Poligono p;

        if(fscanf(f, "%d %hhu %hhu %hhu", &p.n, &p.r, &p.g, &p.b) != 4) break;

        p.v = (Ponto*) malloc(p.n * sizeof(Ponto));
        for(int i = 0; i < p.n; i++){
            fscanf(f, "%f %f", &p.v[i].x, &p.v[i].y);
        }

        poligonos = realloc(poligonos, (nPoligonos + 1) * sizeof(Poligono));
        poligonos[nPoligonos++] = p;
    }

    fclose(f);
}

// Função de desenho
void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = 0; i < nPoligonos; i++){

        // Polígono
        glColor3ub(poligonos[i].r, poligonos[i].g, poligonos[i].b);
        glBegin(GL_POLYGON);
        for(int j = 0; j < poligonos[i].n; j++){
            glVertex2f(poligonos[i].v[j].x, poligonos[i].v[j].y);
        }
        glEnd();
        
        // Contorno
        glColor3ub(0, 0, 0);
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        for(int j = 0; j < poligonos[i].n; j++){
            glVertex2f(poligonos[i].v[j].x, poligonos[i].v[j].y);
        }
        glEnd();
    }

    glFlush();
}

// Inicialização do OpenGL
void Inicializa(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0); // fundo branco
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-10.0, 10.0, -10.0, 10.0);
}

// Programa principal
int main(int argc, char **argv) {
    LerTxt("pe-esquerdo.txt");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Poligonos Coloridos (glColor3ub)");
    Inicializa();
    glutDisplayFunc(Display);
    glutMainLoop();

    for (int i = 0; i < nPoligonos; i++)
        free(poligonos[i].v);
    free(poligonos);

    return 0;
}