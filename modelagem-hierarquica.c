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

typedef struct{
    Poligono chao;
    Poligono planeta1;
    Poligono planeta2;
} Cenario;

// --- Ângulos para os movimentos gerais ---
float tx = 0.0f, ty = 0.0f;
float anguloGeral = 0.0f;
float escala = 1.0f;
float passoTrans = 0.2f;
float passoRot = 5.0f;
float passoEscala = 0.05f;

// --- Ângulos locais das articulações ---
float angBracoEsq = 0, angBracoDir = 0;
float angAntebracoEsq = 0, angAntebracoDir = 0;
float angMaoEsq = 0, angMaoDir = 0;
float angPernaEsq = 0, angPernaDir = 0;
float angPanturrilhaEsq = 0, angPanturrilhaDir = 0;
float angPeEsq = 0, angPeDir = 0;
float angCabeca = 0;

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

        glTranslatef(tx, ty, 0);
        glRotatef(anguloGeral, 0, 0, 1);
        glScalef(escala, escala, 1);

        // Perna esquerda
        glPushMatrix();
            glTranslatef(-0.54, -0.58, 0); // quadril
            glRotatef(angPernaEsq, 0, 0, 1); // Ângulo para rotação da perna esq.
            DesenhaPoligono(p.coxaEsq);

            glPushMatrix();
                glTranslatef(-1.26, -3.55, 0); // joelho
                glRotatef(angPanturrilhaEsq, 0, 0, 1); // Ângulo para rotação do joelho esq.
                DesenhaPoligono(p.panturrilhaEsq);

                glPushMatrix();
                    glTranslatef(-1.0, -2.83, 0); // pé
                    glRotatef(angPeEsq, 0, 0, 1); // Ângulo para rotação do pé esq.
                    DesenhaPoligono(p.peEsq);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        // Perna direita
        glPushMatrix();
            glTranslatef(0.54, -0.58, 0); // quadril
            glRotatef(angPernaDir, 0, 0, 1); // Ângulo para rotação da perna dir.
            DesenhaPoligono(p.coxaDir);

            glPushMatrix();
                glTranslatef(1.26, -3.55, 0); // joelho
                glRotatef(angPanturrilhaDir, 0, 0, 1); // Ângulo para rotação do joelho dir.
                DesenhaPoligono(p.panturrilhaDir);

                glPushMatrix();
                    glTranslatef(1.0, -2.83, 0); // pé
                    glRotatef(angPeDir, 0, 0, 1); // Ângulo para rotação do pé dir.
                    DesenhaPoligono(p.peDir);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        // Corpo como referência central
        DesenhaPoligono(p.corpo);

        // Cabeça (posição relativa ao corpo)
        glPushMatrix();
            glTranslatef(0, 3.17, 0);
            glRotatef(angCabeca, 0, 0, 1); // Ângulo para rotação no pescoço
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
            glRotatef(angBracoEsq, 0, 0, 1); // Ângulo para rotação no ombro esq.
            DesenhaPoligono(p.bracoEsq);

            glPushMatrix();
                glTranslatef(-0.69, -0.03, 0); // cotovelo
                glRotatef(angAntebracoEsq, 0, 0, 1); // Ângulo para rotação no cotovelo esq.
                DesenhaPoligono(p.antebracoEsq);

                glPushMatrix();
                    glTranslatef(-0.62, 0.26, 0); // mão
                    glRotatef(angMaoEsq, 0, 0, 1); // Ângulo para rotação na mão esq.
                    DesenhaPoligono(p.maoEsq);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

        // Braço direito
        glPushMatrix();
            glTranslatef(0.81, 2.77, 0); // ombro
            glRotatef(angBracoDir, 0, 0, 1); // Ângulo para rotação no ombro dir.
            DesenhaPoligono(p.bracoDir);

            glPushMatrix();
                glTranslatef(0.69, -0.03, 0); // cotovelo
                glRotatef(angAntebracoDir, 0, 0, 1); // Ângulo para rotação no cotovelo dir.
                DesenhaPoligono(p.antebracoDir);

                glPushMatrix();
                    glTranslatef(0.62, 0.26, 0); // mão
                    glRotatef(angMaoDir, 0, 0, 1); // Ângulo para rotação na mão dir.
                    DesenhaPoligono(p.maoDir);
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
}

void DesenhaCenario(Cenario c){
    DesenhaPoligono(c.chao);
    DesenhaPoligono(c.planeta1);
    DesenhaPoligono(c.planeta2);
}

// --- Variável global ---
Personagem personagem;
Cenario cenario;

// --- Display ---
void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    DesenhaCenario(cenario);
    DesenhaPersonagemHier(personagem);
    glFlush();
}

void Teclado(unsigned char key, int x, int y) {
    switch (key) {
        // --- Translação ---
        case 'w': ty += passoTrans; break;
        case 's': ty -= passoTrans; break;
        case 'a': tx -= passoTrans; break;
        case 'd': tx += passoTrans; break;

        // --- Rotação ---
        case 'q': anguloGeral += passoRot; break;
        case 'e': anguloGeral -= passoRot; break;

        // --- Escala ---
        case 'z': escala += passoEscala; break;
        case 'x': escala -= passoEscala; 
                  if (escala < 0.1f) escala = 0.1f; 
                  break;

        // --- Reset ---
        case '3':
            tx = ty = anguloGeral = 0;
            escala = 1.0f;
            break;

        // --- Movimentos locais ---
        case 'r': angBracoEsq += 5; break;
        case 't': angBracoEsq -= 5; break;

        case 'f': angAntebracoEsq += 5; break;
        case 'g': angAntebracoEsq -= 5; break;

        case 'v': angMaoEsq += 5; break;
        case 'b': angMaoEsq -= 5; break;

        case 'y': angBracoDir += 5; break;
        case 'u': angBracoDir -= 5; break;

        case 'h': angAntebracoDir += 5; break;
        case 'j': angAntebracoDir -= 5; break;

        case 'n': angMaoDir += 5; break;
        case 'm': angMaoDir -= 5; break;

        case 'i': angPernaEsq += 5; break;
        case 'o': angPernaEsq -= 5; break;

        case 'k': angPanturrilhaEsq += 5; break;
        case 'l': angPanturrilhaEsq -= 5; break;

        case ',': angPeEsq += 5; break;
        case '.': angPeEsq -= 5; break;

        case '7': angPernaDir += 5; break;
        case '8': angPernaDir -= 5; break;

        case '4': angPanturrilhaDir += 5; break;
        case '5': angPanturrilhaDir -= 5; break;

        case '1': angPeDir += 5; break;
        case '2': angPeDir -= 5; break;

        case '9': angCabeca += 5; break;
        case '6': angCabeca -= 5; break;

    }

    glutPostRedisplay(); // redesenha após qualquer tecla
}

// --- Inicialização OpenGL ---
void Inicializa(void) {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
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

    cenario.chao = LerPoligono("chao.txt");
    cenario.planeta1 = LerPoligono("planeta1.txt");
    cenario.planeta2 = LerPoligono("planeta2.txt");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Personagem Hierarquico");
    Inicializa();
    glutDisplayFunc(Display);
    glutKeyboardFunc(Teclado);
    glutMainLoop();

    return 0;
}
