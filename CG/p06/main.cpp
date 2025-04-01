#include <stdio.h>
#include <time.h>
#include <string.h> // Add this for memcpy
#include <IL/il.h>  // DevIL library for image loading

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_TREES 500  // Aumenta o número máximo de árvores
#define RADIUS 50.0f // Raio da clareira
#define RI 35.0f // Raio interno
#define RC 15.0f // Raio central
#define SPEED_RI 0.005f
#define SPEED_RC 0.005f
#define HEIGHT_SCALE 100.0f  // Increased from 30.0f to 60.0f for more dramatic terrain

// Variáveis para o terreno
unsigned int terrainTexture;
int imageWidth, imageHeight;
unsigned char* imageData = NULL;

float treePositionsX[MAX_TREES];
float treePositionsZ[MAX_TREES];
float treeHeights[MAX_TREES];
float treeColors[MAX_TREES][3]; // RGB para cada árvore
int numTrees;

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

float angleRI = 0.0f;  // Ângulo para teapots externos
float angleRC = 0.0f;  // Ângulo para teapots internos

// Add these global variables for first-person camera
bool firstPersonMode = false;  // Toggle between orbital and first-person camera
float fpX = 0.0f, fpY = 0.0f, fpZ = 50.0f;  // First person camera position
float fpLookX = 0.0f, fpLookZ = -1.0f;  // Looking direction (initially looking along -Z)
float fpAngle = 0.0f;  // Current rotation angle of the camera
float moveSpeed = 0.5f;  // Movement speed

void spherical2Cartesian() {
    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}

// Forward declarations - Add these
float getHeight(int x, int z);
float getWorldHeight(float worldX, float worldZ);
void printInfo();

// Modifique a função generateTrees
void generateTrees() {
    numTrees = 500;  // Número fixo de árvores
    float fixedHeight = 15.0f;  // Altura fixa para todas as árvores
    
    for(int i = 0; i < numTrees; i++) {
        treePositionsX[i] = -90.0f + (rand() % 180);
        treePositionsZ[i] = -90.0f + (rand() % 180);
        treeHeights[i] = fixedHeight;  // Usa a altura fixa
        
        // Mantém os tons de verde aleatórios
        treeColors[i][0] = 0.0f;
        treeColors[i][1] = 0.4f + (rand() % 40) / 100.0f;
        treeColors[i][2] = 0.0f;
    }
}

void generateClareira(float radius) {
    for(int i = 0; i < numTrees; i++) {
        // Calcula a distância da árvore até o centro (0,0)
        float distance = sqrt(treePositionsX[i] * treePositionsX[i] + 
                            treePositionsZ[i] * treePositionsZ[i]);
        
        // Se a árvore estiver dentro do círculo, gera nova posição
        while(distance < radius) {
            treePositionsX[i] = -90.0f + (rand() % 180);
            treePositionsZ[i] = -90.0f + (rand() % 180);
            
            // Recalcula a distância com a nova posição
            distance = sqrt(treePositionsX[i] * treePositionsX[i] + 
                          treePositionsZ[i] * treePositionsZ[i]);
        }
    }
}

// Modifique a função drawTree para aceitar a cor e posicionar na altura correta
void drawTree(float x, float z, float height, float* color) {
    float terrainHeight = getWorldHeight(x, z);
    
    glPushMatrix();
    
    // Translada para a posição da árvore incluindo altura do terreno
    glTranslatef(x, terrainHeight, z);
    
    // Desenha o tronco (cone castanho)
    glColor3f(0.4f, 0.2f, 0.0f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glutSolidCone(height/10, height/3, 10, 10);
    
    // Desenha a copa (cone verde com a cor específica)
    glColor3f(color[0], color[1], color[2]);
    glTranslatef(0.0f, 0.0f, height/4);
    glutSolidCone(height/4, height, 10, 10);
    
    glPopMatrix();
}

// Modifique a função drawTeapots
void drawTeapots() {
    // Função auxiliar para desenhar os eixos

    // Teapots na circunferência externa (RI)
    glPushMatrix();
    int numTeapotsRI = 12;
    for(int i = 0; i < numTeapotsRI; i++) {
        float angle = ((i * 2 * M_PI) / numTeapotsRI) + angleRI;
        float x = RI * cos(angle);
        float z = RI * sin(angle);
        
        glPushMatrix();
        glTranslatef(x, getWorldHeight(x, z) + 2.0f, z); // +2.0f to float above terrain
        glRotatef((-angle * 180.0f/M_PI), 0.0f, 1.0f, 0.0f);
        glColor3f(0.8f, 0.1f, 0.1f);  // Vermelho escuro
        glutSolidTeapot(2.0f);
        glPopMatrix();
    }
    glPopMatrix();
    
    // Teapots na circunferência interna (RC)
    glPushMatrix();
    int numTeapotsRC = 6;

    for(int i = 0; i < numTeapotsRC; i++) {
        float angle = ((i * 2 * M_PI) / numTeapotsRC) + angleRC;
        float x = RC * cos(angle);
        float z = RC * sin(angle);
        
        glPushMatrix();
        glTranslatef(x, getWorldHeight(x, z) + 2.0f, z);
        glRotatef((-angle * 180.0f/M_PI) + 180.0f, 0.0f, 1.0f, 0.0f);
        glColor3f(0.1f, 0.1f, 0.8f);  // Azul escuro
        glutSolidTeapot(1.5f);
        glPopMatrix();
    }
    glPopMatrix();
    
    // Atualiza os ângulos (movimento em direções opostas)
    angleRI -= SPEED_RI;  // Movimento esquerda-direita (sentido anti-horário)
    angleRC += SPEED_RC;  // Movimento direita-esquerda (sentido horário)
    
    // Mantém os ângulos entre 0 e 2π
    if(angleRI < 0) angleRI += 2 * M_PI;
    if(angleRC > 2 * M_PI) angleRC -= 2 * M_PI;
    
    // Força o redesenho da cena
    glutPostRedisplay();
}

// Adicione após as outras definições
void drawCentralTorus() {
    glPushMatrix();
    float centerHeight = getWorldHeight(0.0f, 0.0f);
    glTranslatef(0.0f, centerHeight + 2.0f, 0.0f); // Position above the terrain
	glColor3f(1.0f, 0.4f, 0.7f);  // Cor rosa
    
    // Parâmetros do torus
    float innerRadius = 1.0f;  // Raio do tubo
    float outerRadius = 3.0f;  // Raio do torus
    int sides = 20;           // Segmentos do tubo
    int rings = 20;           // Anéis do torus
    
    glutSolidTorus(innerRadius, outerRadius, sides, rings);
    glPopMatrix();
}

// Função para carregar a imagem do terreno
bool loadTerrainImage(const char* filename) {
    // Inicializa a DevIL
    ilInit();
    
    // Gera uma imagem DevIL
    ILuint imageID;
    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    
    // Carrega a imagem
    if (!ilLoadImage(filename)) {
        printf("Failed to load terrain image: %s\n", filename);
        return false;
    }
    
    // Converte para escala de cinza de 8 bits
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
    
    // Obtém as dimensões e dados da imagem
    imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
    imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);
    imageData = new unsigned char[imageWidth * imageHeight];
    
    // Copia os dados da imagem
    memcpy(imageData, ilGetData(), imageWidth * imageHeight);
    
    // Limpa os recursos DevIL
    ilDeleteImages(1, &imageID);
    
    printf("Terrain image loaded: %dx%d\n", imageWidth, imageHeight);
    return true;
}

// Função para obter a altura do terreno em uma posição específica
float getHeight(int x, int z) {
    // Verifica se estamos dentro dos limites da imagem
    if (x < 0 || x >= imageWidth || z < 0 || z >= imageHeight)
        return 0.0f;
        
    // Obtém o valor do pixel e converte para altura (escala 0-255 para 0-30)
    unsigned char heightValue = imageData[z * imageWidth + x];
    return (heightValue / 255.0f) * HEIGHT_SCALE;
}


// Function to get height at any arbitrary point using bilinear interpolation
float hf(float px, float pz) {
    // Convert world coordinates to image coordinates
    float imagePx = ((px + 100.0f) / 200.0f) * (imageWidth - 1);
    float imagePz = ((pz + 100.0f) / 200.0f) * (imageHeight - 1);
    
    // Get grid cell coordinates
    int x1 = floor(imagePx);
    int z1 = floor(imagePz);
    int x2 = x1 + 1;
    int z2 = z1 + 1;
    
    // Check boundaries
    if (x2 >= imageWidth) x2 = imageWidth - 1;
    if (z2 >= imageHeight) z2 = imageHeight - 1;
    
    // Calculate fractional parts
    float fx = imagePx - x1;
    float fz = imagePz - z1;
    
    // Get heights at the 4 corners of the grid cell
    float h_x1_z1 = getHeight(x1, z1);
    float h_x1_z2 = getHeight(x1, z2);
    float h_x2_z1 = getHeight(x2, z1);
    float h_x2_z2 = getHeight(x2, z2);
    
    // Interpolate along z
    float h_x1_z = h_x1_z1 * (1.0f - fz) + h_x1_z2 * fz;
    float h_x2_z = h_x2_z1 * (1.0f - fz) + h_x2_z2 * fz;
    
    // Interpolate along x
    return h_x1_z * (1.0f - fx) + h_x2_z * fx;
}


// Função para obter a altura em coordenadas do mundo
float getWorldHeight(float worldX, float worldZ) {
    return hf(worldX, worldZ);
}

void drawTerrain() {
    if (!imageData) return;
    
    glColor3f(0.2f, 0.8f, 0.2f);
    
    // Define o número de vértices a renderizar em cada direção
    int step = 1; // Pode ser aumentado para melhorar o desempenho
    
    // Desenha o terreno usando GL_TRIANGLE_STRIP
    for(int z = 0; z < imageHeight - step; z += step) {
        glBegin(GL_TRIANGLE_STRIP);
        for(int x = 0; x < imageWidth; x += step) {
            // Calcula as coordenadas do mundo a partir das coordenadas da imagem
            float worldX = ((float)x / (imageWidth - 1) * 200.0f) - 100.0f;
            float worldZ1 = ((float)z / (imageHeight - 1) * 200.0f) - 100.0f;
            float worldZ2 = ((float)(z + step) / (imageHeight - 1) * 200.0f) - 100.0f;
            
            // Obtém as alturas
            float y1 = getHeight(x, z);
            float y2 = getHeight(x, z + step);
            
            // Adiciona cor com base na altura (tons de verde para vales e marrom para montanhas)
            float colorValue1 = y1 / HEIGHT_SCALE;  // Normaliza entre 0 e 1
            float colorValue2 = y2 / HEIGHT_SCALE;
            
            // Primeiro vértice (z)
            glColor3f(0.2f, 0.5f + 0.3f * colorValue1, 0.2f);  // Tom de verde
            glVertex3f(worldX, y1, worldZ1);
            
            // Segundo vértice (z + step)
            glColor3f(0.2f, 0.5f + 0.3f * colorValue2, 0.2f);  // Tom de verde
            glVertex3f(worldX, y2, worldZ2);
        }
        glEnd();
    }
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



// Update renderScene to use the first-person camera when in that mode
void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    
    if (firstPersonMode) {
        // Use first-person camera
        gluLookAt(
            fpX, fpY, fpZ,                      // Camera position
            fpX + fpLookX, fpY, fpZ + fpLookZ,  // Look at point
            0.0f, 1.0f, 0.0f                    // Up vector
        );
    } else {
        // Use orbital camera
        gluLookAt(
            camX, camY, camZ,
            0.0, 0.0, 0.0,
            0.0f, 1.0f, 0.0f
        );
    }
            
    // Desenha o terreno
    drawTerrain();
    
    // Draw trees
    for(int i = 0; i < numTrees; i++) {
        drawTree(treePositionsX[i], treePositionsZ[i], treeHeights[i], treeColors[i]);
    }
    
    // Draw teapots
    drawTeapots();
    drawCentralTorus(); // Desenha o torus central
    
    glutSwapBuffers();
}

// Update special keys function to handle camera rotation in first person mode
void processSpecialKeys(int key, int xx, int yy) {
    if (firstPersonMode) {
        switch (key) {
            case GLUT_KEY_RIGHT: // Look right
                fpAngle -= 0.05f;
                fpLookX = sin(fpAngle);
                fpLookZ = -cos(fpAngle);
                break;
                
            case GLUT_KEY_LEFT: // Look left
                fpAngle += 0.05f;
                fpLookX = sin(fpAngle);
                fpLookZ = -cos(fpAngle);
                break;
        }
    } else {
        // Original orbital camera controls
        switch (key) {
            case GLUT_KEY_RIGHT:
                alfa -= 0.1; 
                break;

            case GLUT_KEY_LEFT:
                alfa += 0.1; 
                break;

            case GLUT_KEY_UP:
                beta += 0.1f;
                if (beta > 1.5f)
                    beta = 1.5f;
                break;

            case GLUT_KEY_DOWN:
                beta -= 0.1f;
                if (beta < -1.5f)
                    beta = -1.5f;
                break;

            case GLUT_KEY_PAGE_DOWN: 
                radius -= 1.0f;
                if (radius < 1.0f)
                    radius = 1.0f;
                break;

            case GLUT_KEY_PAGE_UP: 
                radius += 1.0f; 
                break;
        }
        spherical2Cartesian();
    }
    glutPostRedisplay();
}

// Update processKeys function to toggle camera mode and handle first-person movement
void processKeys(unsigned char c, int xx, int yy) {
    switch (c) {
        case 'o': // Zoom in
            radius -= 5.0f;
            if (radius < 1.0f)
                radius = 1.0f;
            break;

        case 'p': // Zoom out
            radius += 5.0f;
            break;
            
        // Toggle between camera modes
        case 'c':
            firstPersonMode = !firstPersonMode;
            break;
            
        // First person camera controls
        case 'w': // Move forward
            if (firstPersonMode) {
                // Calculate forward vector
                fpX += fpLookX * moveSpeed;
                fpZ += fpLookZ * moveSpeed;
                // Update Y position to follow terrain
                fpY = getWorldHeight(fpX, fpZ) + 5.0f; // 5.0f is camera height above terrain
            }
            break;
            
        case 's': // Move backward
            if (firstPersonMode) {
                // Calculate backward vector
                fpX -= fpLookX * moveSpeed;
                fpZ -= fpLookZ * moveSpeed;
                // Update Y position to follow terrain
                fpY = getWorldHeight(fpX, fpZ) + 5.0f;
            }
            break;
            
        case 'a': // Strafe left
            if (firstPersonMode) {
                // Calculate left vector (perpendicular to look direction)
                float leftX = -fpLookZ;  // Cross product with up vector (0,1,0)
                float leftZ = fpLookX;
                
                fpX += leftX * moveSpeed;
                fpZ += leftZ * moveSpeed;
                // Update Y position to follow terrain
                fpY = getWorldHeight(fpX, fpZ) + 5.0f;
            }
            break;
            
        case 'd': // Strafe right
            if (firstPersonMode) {
                // Calculate right vector
                float rightX = fpLookZ;
                float rightZ = -fpLookX;
                
                fpX += rightX * moveSpeed;
                fpZ += rightZ * moveSpeed;
                // Update Y position to follow terrain
                fpY = getWorldHeight(fpX, fpZ) + 5.0f;
            }
            break;
    }
    
    spherical2Cartesian();
    glutPostRedisplay();
}


int main(int argc, char **argv) {
    // init random seed
    srand(time(NULL));
    
    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI-UM");
        
    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    
    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);


    // Carrega a imagem do terreno
    if (!loadTerrainImage("/Users/diogokeeper12/Documents/GitHub/LCCCode/CG/p06/terreno.jpg")) {
        printf("Failed to load terrain image. Exiting.\n");
        return 1;
    }
    
    generateTrees();  // Gera as árvores uma única vez
    generateClareira(RADIUS);  // Cria uma clareira com raio específico
    
    spherical2Cartesian();
    

    // enter GLUT's main cycle
    glutMainLoop();
    
    // Cleanup
    if (imageData) {
        delete[] imageData;
    }
    
    return 0;
}
