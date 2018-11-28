#ifdef __APPLE__
#include <GLUT/glut.h>
#else

#include <windows.h>
#include <glut.h>

#endif

#include <iostream>
#include <vector>
#include "SOIL\SOIL.h"

#define MENU_NEW_GAME  1
#define MENU_LOAD_GAME 2
#define MENU_SAVE_GAME 3
#define MENU_SETTINGS  4
#define MENU_EXIT      5

using namespace std;

struct Point {
    int x;
    int y;

    Point(int x, int y) {
        this->x = x;
        this->y = y;

    }

    //Point() {}
};

struct Button {
    Point points_1;
    Point points_2;
    int id;

    Button(Point p_1, Point p_2, int id) {
        this->points_1 = p_1;
        this->points_2 = p_2;
        this->id = id;
    }

    //  Button() {}
};

struct Object {
    int strenght;
    int counter;
    int cost;
    int armor;
};

struct Stas {
    int helthpoint;
    vector<Object> inventory;
    int strenght;
    int intelligence;
    int agility;
    int endurance;
    int intoxication; // опьянение
};

#define GL_GLEXT_PROTOTYPES

void LoadTextures();

vector<Button> buttons;

GLfloat eye[3];
GLfloat center[3];

int Send_ID(int x, int y) {
    int ID=0;
    for (auto &but : buttons) {
        if (x < but.points_1.x || x > but.points_2.x || y < but.points_1.y || y > but.points_2.y){
            continue;
        }
        ID=but.id;
       break;
    }
    return ID;
}


void klickUp() {
    cout << "верх" << endl;
}

void klickDown() {
    cout << "низ" << endl;
}

void klickLeft() {
    cout << "лево" << endl;
}

void klickRight() {
    cout << "право" << endl;
}

void klickInventory() {
    cout << "инвентарь" << endl;
}

void mouseKlickLeft(int a, int b) {
    cout << "левая кнопка\tx = " << a << "\ty = " << b << endl;
    switch (Send_ID(a, b)) {
        case MENU_NEW_GAME:
            cout << "новая игра\n";
            break;
        case MENU_LOAD_GAME:
            cout << "загрузить\n";
            break;
        case MENU_SAVE_GAME:
            cout << "сохран\n";
            break;
        case MENU_SETTINGS:
            cout << "настройкт\n";
            break;
        case MENU_EXIT:
            cout << "выход\n";
            exit(0);
        default:
            cout<<"неопознано\n";
            break;
    }
}

void mouseKlickRight(int a, int b) {
    cout << "правая кнопка\tx = " << a << "\ty = " << b << endl;
}

void key(unsigned char key, int a, int b) {
    switch (key) {
        case 27:
            exit(0);
        case 'w':
            klickUp();
            break;
        case 'a':
            klickLeft();
            break;
        case 's':
            klickDown();
            break;
        case 'd':
            klickRight();
            break;
        case 'i':
            klickInventory();
    }
}

void initMenu() {
    //960       540
    //640       360
    buttons.emplace_back(Button(Point(640, 360), Point(1280, 432), MENU_NEW_GAME));
    buttons.emplace_back(Button(Point(640, 432), Point(1280, 504), MENU_LOAD_GAME));
    buttons.emplace_back(Button(Point(640, 504), Point(1280, 576), MENU_SAVE_GAME));
    buttons.emplace_back(Button(Point(640, 576), Point(1280, 648), MENU_SETTINGS));
    buttons.emplace_back(Button(Point(640, 648), Point(1280, 720), MENU_EXIT));
    LoadTextures();
}

void key(int key, int a, int b) {
    switch (key) {
        case GLUT_KEY_UP:
            klickUp();
            break;
        case GLUT_KEY_LEFT:
            klickLeft();
            break;
        case GLUT_KEY_DOWN:
            klickDown();
            break;
        case GLUT_KEY_RIGHT:
            klickRight();
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        //mouseKlickLeft(x,y);
    }
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
        mouseKlickLeft(x, y);
    }
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
        //mouseKlickRight(x,y);
    }
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {
        mouseKlickRight(x, y);
    }
}

void initWithCoder() {
    eye[0] = 0.0f;
    eye[1] = 0.2f;
    eye[2] = 0.0f;

    center[0] = 0.000000001f;
    center[1] = -0.8f;
    center[2] = 0.0f;
}

void LoadTextures() {
    GLuint tex_2d = SOIL_load_OGL_texture("Menu_texture.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
                                          SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB |
                                          SOIL_FLAG_COMPRESS_TO_DXT);

/* check for an error during the load process */
    if (0 == tex_2d) {
        cout << "SOIL loading error: '%s'\n", SOIL_last_result();
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Initialize() {
    glEnable(GL_TEXTURE_2D);
    glClearColor(1.0, 1.0, 1.0, 0.0);//+++

    glMatrixMode(GL_PROJECTION);//+++
    glLoadIdentity();//+++

    glMatrixMode(GL_MODELVIEW);//+++
    initWithCoder();
    initMenu();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0.0, 1.0, 0.0);
    //glRotatef(180, 2.5, 0.0, 0.0); // ? = 1;
    glRotatef(180, 0.0, 2.5, 0.0); // ? = 1;
    glBegin(GL_QUADS);//?????1 | ?????
    glTexCoord2f(0.0f, 0.0f);
    glVertex3d(1, 0.0, 1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3d(1, 0.0, -1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3d(-1, 0.0, -1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3d(-1, 0.0, 1);
    glEnd();
    glFlush();

    glutSwapBuffers();
}


int main(int argc, char *argv[]) {
    SetConsoleOutputCP(1251);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Degradan++");
    glutFullScreen();
    Initialize();
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(key);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
