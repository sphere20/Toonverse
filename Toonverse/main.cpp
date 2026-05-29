#include <iostream>
using namespace std;
#include <GL/glut.h>
#include <math.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
GLuint logoTexture;

bool musicOn = true;
float spongebobtx=0.0f;
float spongebobty=0.0f;
float submarinetx =0.0f;
 float submarinety=0.0f;
 float bubbletx =0.0f;
 float bubblety=0.0f;
 float cartx=0.0f;
 float carty=0.0f;
  float loontx=0.0f;
 float loonty=0.0f;
 float loonsx = 1.0f;
 float loonsy = 1.0f;
  float cloudtx=0.0f;
 float cloudty=0.0f;
 float jumptx=0.0f;
 float jumpty=0.0f;
 bool jumpflag=false;
 float jump=0.0f;
int playScene1 =0;
 int       playScene2 = 0;
   int      playScene3 = 0;
     int     playScene4 = 0;
     int playScene5=1;
     int currentScene = 5;
     int runSubmarine=0;

float waveOffset = 0.0f;

GLfloat scartx = 0.0f;
GLfloat scarty = 0.0f;
GLfloat boatx = 0.0f;
GLfloat boaty = 0.0f;
bool boat = true;
GLfloat cloudx = 0.0f;
GLfloat cloudy = 0.0f;
GLfloat birdtx = 0.0f;
GLfloat birdty = 60.0f;
GLfloat birdangle = 0.0f;
GLfloat balltx = 0.0f;
GLfloat ballty = 0.0f;
int bounce = 0;
bool bounceflag = false;
float balljump = 0.0f;
GLfloat impostertx = 0.0f;
GLfloat imposterty = 0.0f;
GLfloat housetx = 0.0f;
GLfloat housety = 0.0f;
GLfloat housescale = 1.0f;

float beancartx=0;
float beancarty=10;
float snowOffset = 0.0f;
float snowDriftOffset = 0.0f;
float snowX[300];
float snowY[300];
bool snowInitialized = false;
float bustx=0;
float busty=0;
float londonEyeAngle = 0.0f;
float bigBenClockAngle = 0.0f;
float rainX[200];
float rainY[200];
float rainFallOffset = 0.0f;      // master fall offset for translate
float rainDriftOffset = 0.0f;     // master drift offset for translate
bool rainInitialized = false;
void dda(float x1,float x2,float y1 ,float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float m = dy / dx;
    float x = x1;
    float y = y1;

    glPointSize(5);
    glBegin(GL_POINTS);
    if (fabs(m) < 1)
    {
        while (x <= x2 && y <= y2)
            {
            glVertex2f(x, y);
            x = x + 1;
            y = y + m;
        }
    }
    else
    {
        while (y <= y2)
            {
            glVertex2f(x, y);
            y = y + 1;
            x = x + (1/m);
        }
    }
    glEnd();

}
void midLine(float x1,float x2,float y1 ,float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float x = x1;
    float y = y1;

float dOLD = 2*dy-dx; // dstart

    glPointSize(5);
    glBegin(GL_POINTS);
    while (x <= x2)
    {
        if (dOLD< 0)//e
            {
            glVertex2f(x, y);
            x = x +  1;
        dOLD= 2*dy + dOLD;
    }
         else //ne
            {
            glVertex2f(x, y);
            y = y + 1;
            x = x + 1;
        dOLD= 2*(dy-dx) + dOLD;
    }
    }
    glEnd();

}
void circle( float centerX, float centerY,float radius)
{
     glBegin(GL_POLYGON);
        for(int i = 0;i<360;i++)
        {
            float angle = i * 3.1416 /180;
            float x = centerX + radius * cos(angle);
             float y = centerY + radius * sin(angle);
              glVertex2f(x,y);
        }
        glEnd();

}

void semiCircle(float centerX, float centerY,float radius)
{
     glBegin(GL_POLYGON);
        for(int i = 0;i<=180;i++)
        {
            float angle = i * 3.1416 /180;
            float x = centerX + radius * cos(angle);
             float y = centerY + radius * sin(angle);
              glVertex2f(x,y);
        }
        glEnd();

}

void mickeyLeg(float centerX, float centerY,float radius)
{
     glBegin(GL_POLYGON);
        for(int i = 90;i<=270;i++)
        {
            float angle = i * 3.1416 /180;
            float x = centerX + radius * cos(angle);
             float y = centerY + radius * sin(angle);
              glVertex2f(x,y);
        }
        glEnd();

}

void triangle(float x1,float y1,float x2,float y2,float x3,float y3)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
 glEnd();
}

void line(float x1,float y1,float x2,float y2)
{
     glBegin(GL_LINES);
     glVertex2f(x1,y1);
     glVertex2f(x2,y2);
     glEnd();
}

void polygon (float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{

glBegin(GL_POLYGON);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
 glEnd();

}
void midpointCircle(int xc,int yc,int r)
{
    int x = 0;
    int y = r;
    int d = 1 - r;

    glBegin(GL_POINTS);
    while(x <= y)
    {
        // 8-symmetry
        glVertex2f(xc + x, yc + y);
        glVertex2f(xc - x, yc + y);
        glVertex2f(xc + x, yc - y);
        glVertex2f(xc - x, yc - y);

        glVertex2f(xc + y, yc + x);
        glVertex2f(xc - y, yc + x);
        glVertex2f(xc + y, yc - x);
        glVertex2f(xc - y, yc - x);

        if(d >= 0) //se
        {
            d = d + 2*x - 2*y + 5;
            x++;
            y--;
        }
        else //e
        {
            d = d + 2*x + 3;
            x++;
        }
    }
    glEnd();
}

void PokemonSemiCircle(float centerX, float centerY,float radius)
{
    glBegin(GL_POLYGON);
        for(int i = 180;i<=360;i++)
        {
            float angle = i * 3.1416 /180;
            float x = centerX + radius * cos(angle);
             float y = centerY + radius * sin(angle);
              glVertex2f(x,y);
        }
        glEnd();

}
void brick3D()
{
    glBegin(GL_QUADS);

    //front
    glColor3ub(205,129,98);
    glVertex3f(-20, -50, 0);
    glVertex3f(-30, -50, 0);
    glVertex3f(-30, -45, 0);
    glVertex3f(-20, -45, 0);

    //back
 glColor3ub(139,87,66);
    glVertex3f(-20, -50, -5);
    glVertex3f(-30, -50, -5);
    glVertex3f(-30, -45, -5);
    glVertex3f(-20, -45, -5);

    //left

    glVertex3f(-30, -50, 0);
    glVertex3f(-30, -50, -5);
    glVertex3f(-30, -45, -5);
    glVertex3f(-30, -45, 0);

    //right

    glVertex3f(-20, -50, 0);
    glVertex3f(-20, -50, -5);
    glVertex3f(-20, -45, -5);
    glVertex3f(-20, -45, 0);

    //up
 glColor3ub(238,149,114);
    glVertex3f(-20, -45, 0);
    glVertex3f(-30, -45, 0);
    glVertex3f(-30, -45, -5);
    glVertex3f(-20, -45, -5);

    //down
 glColor3ub(139,87,66);
    glVertex3f(-20, -50, 0);
    glVertex3f(-30, -50, 0);
    glVertex3f(-30, -50, -5);
    glVertex3f(-20, -50, -5);

    glEnd();
}

void simpsonsCar()
{



    //simpsons car
     glPushMatrix();
     glTranslatef(scartx, scarty, 0.0f);
     //body
     glColor3ub(255, 110, 180);
     polygon(32, -87.5, 96, -87.5, 96, -75, 32, -75);
     //side part
     glColor3ub(191, 239, 255);
     polygon(30, -87.5, 32, -87.5, 32, -75, 30, -75);
     polygon(96, -87.5, 98, -87.5, 98, -75, 96, -75);
     //upper body
     glColor3ub(255, 110, 180);
     polygon(44, -75, 86, -75, 80, -62.5, 54, -62.5);
     //left window
     glColor3ub(224, 255, 255);
     polygon(46, -75, 64, -75, 64, -65, 54, -65);
     //right window
     polygon(68, -75, 84, -75, 78, -65, 68, -65);
     //left door
     glColor3ub(238, 106, 167);
     polygon(46, -85, 84, -85, 84, -75, 46, -75);
     glColor3ub(255, 110, 180);
     semiCircle(43, -87.5, 8);//left
     semiCircle(87, -87.5, 8);//right
     //door divider
     glColor3ub(50, 10, 50);
     line(66, -62.5, 66, -85);
     //door handle
     glColor3ub(130, 130, 130);
     polygon(60, -78.75, 64, -78.75, 64, -76.25, 60, -76.25);
     polygon(78, -78.75, 82, -78.75, 82, -76.25, 78, -76.25);
     //headlight
     glColor3ub(173, 216, 230);
     polygon(28, -87.5, 34, -87.5, 34, -82.5, 28, -82.5);
     if(playScene1==1)
     {
     glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4ub(237, 230, 133, 80);   // 80 out of 255 = ~30% opacity, very transparent
    polygon(-20, -90, 10, -90, 28, -82.5, 30, -75);
    triangle(28, -82.5, 30, -82.5, 30, -75);

    glDisable(GL_BLEND);
     }
     //left tire
     //shade
     glColor3ub(64, 64, 64);
     semiCircle(43, -87.5, 7);
     glColor3ub(99, 99, 99);
     circle(43, -87.5, 5);
     glColor3ub(191, 239, 255);
     circle(43, -87.5, 2.5);
     //right tire
     //shade
     glColor3ub(64, 64, 64);
     semiCircle(87, -87.5, 7);
     glColor3ub(99, 99, 99);
     circle(87, -87.5, 5);
     glColor3ub(191, 239, 255);
     circle(87, -87.5, 2.5);
     //door line
     glColor3ub(250, 220, 250);
     line(34, -77.5, 42, -77.5);
     glPopMatrix();
}
  void drawText(float x, float y, char *string) {
    glRasterPos2f(x, y);

    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *string);
        string++;
    }
}
void drawTextBus(float x, float y, char *string) {
    glRasterPos2f(x, y);

    while (*string) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string);
        string++;
    }
}



void scene1()
{
    //sky
   glColor3ub(10, 10, 60);
polygon(-100, 0, 100, 0, 100, 100, -100, 100);


    //moon
    glColor3ub(255, 255, 255);
    circle(75, 81.25, 7);
//stars
glColor3ub(255, 255, 255);
glPointSize(2.0f);
glBegin(GL_POINTS);
float starX[] = {-90,-75,-60,-45,-30,-15, 0, 15, 30, 45, 60, 80,
                 -85,-55,-35,-10, 10, 35, 55, 70,-70,-40, 20, 50, 90,
                 -95,-50,-20,  5, 25, 65, 85,-65,-25, 40, 75};
float starY[] = { 95, 90, 95, 88, 93, 85, 90, 87, 94, 89, 92, 96,
                  82, 84, 80, 83, 86, 78, 81, 88, 76, 79, 77, 85, 91,
                  74, 72, 75, 70, 73, 71, 78, 68, 66, 69, 64};
int starCount = 36;
for(int i = 0; i < starCount; i++) {
    glVertex2f(starX[i], starY[i]);
}
glEnd();
glPointSize(1.0f);

// stars(slightly bigger, animated)
glColor3ub(255, 255, 200);
float twinkle = (sin(waveOffset * 2.0f) + 1.0f) / 2.0f; // 0.0 to 1.0
glPointSize(1.0f + twinkle * 2.5f);                       // size 1 to 3.5
glBegin(GL_POINTS);
float tStarX[] = {-80, -20, 20, 55, -45, 10, 70, -60, 40, -5};
float tStarY[] = { 88,  92, 80, 86,  94, 75, 82,  70, 91, 84};
for(int i = 0; i < 10; i++) {
    glVertex2f(tStarX[i], tStarY[i]);
}
glEnd();
glPointSize(1.0f);

     //cloud
     glPushMatrix();
glTranslatef(cloudx, cloudy, 0.0f);

// cloud 1 - left
glColor3ub(45, 45, 55);
circle(-64, 87.5, 5);
circle(-60, 87.5, 6);
circle(-56, 87.5, 5);
circle(-62, 90.5, 4);
circle(-58, 90.5, 4);
circle(-60, 92.5, 3);
// moonlit highlight
glColor3ub(90, 90, 105);
circle(-60, 91.5, 2);
circle(-62, 89.5, 1.5);

// cloud 2 - center big
glColor3ub(40, 40, 52);
circle(-28, 75, 7);
circle(-20, 75, 10);
circle(-12, 75, 7);
circle(-24, 80, 6);
circle(-16, 80, 6);
circle(-20, 83, 5);
// mid layer
glColor3ub(58, 58, 72);
circle(-26, 79, 4);
circle(-14, 79, 4);
circle(-20, 82, 4);
// highlight
glColor3ub(85, 85, 100);
circle(-20, 81, 2.5);
circle(-23, 78, 2);

// cloud 3 - right
glColor3ub(42, 42, 54);
circle(34, 80, 6);
circle(40, 80, 7);
circle(46, 80, 6);
circle(37, 83.5, 4);
circle(43, 83.5, 4);
circle(40, 86, 3.5);
// highlight
glColor3ub(80, 80, 95);
circle(40, 85, 2);

// cloud 4 - far left off screen
glColor3ub(38, 38, 50);
circle(-120, 75, 8);
circle(-128, 75, 6);
circle(-112, 75, 6);
circle(-125, 79, 5);
circle(-115, 79, 5);
circle(-120, 82, 4);
glColor3ub(72, 72, 88);
circle(-120, 81, 2);

glPopMatrix();



    //road
    glColor3ub(0,0,0);
    polygon(-100, -100, 100, -100, 100, -50, -100, -50);

    //road divider
     glColor3ub(255,255,255);
    polygon(-100,-75,-80,-75,-80,-70,-100,-70);
    polygon(-60,-75,-40,-75,-40,-70,-60,-70);
    polygon(-20,-75,0,-75,0,-70,-20,-70);
    polygon(20,-75,40,-75,40,-70,20,-70);
    polygon(60,-75,80,-75,80,-70,60,-70);


    //forest
    //forest 1st layer (left to right)
    glColor3ub(5, 25, 5);
circle(-85, 16.5, 8);
circle(-65, 16.5, 8);
circle(-45, 16.5, 8);
circle(-25, 16.5, 8);
circle(-5,  16.5, 8);
circle(20,  16.5, 8);
circle(40,  16.5, 8);
circle(60,  16.5, 8);
circle(80,  16.5, 8);

// forest 2nd layer — deep night green
glColor3ub(0, 55, 10);
circle(-95, 10, 8);
circle(-80, 10, 8);
circle(-65, 10, 8);
circle(-50, 10, 8);
circle(-35, 10, 8);
circle(-20, 10, 8);
circle(-5,  10, 8);
circle(10,  10, 8);
circle(25,  10, 8);
circle(40,  10, 8);
circle(55,  10, 8);
circle(70,  10, 8);
circle(85,  10, 8);
circle(100, 10, 8);

// forest 3rd layer — slightly lighter night green
glColor3ub(15, 80, 20);
circle(-100, 5, 6.5);
circle(-90,  5, 6.5);
circle(-80,  5, 6.5);
circle(-70,  5, 6.5);
circle(-60,  5, 6.5);
circle(-50,  5, 6.5);
circle(-40,  5, 6.5);
circle(-30,  5, 6.5);
circle(-20,  5, 6.5);
circle(-10,  5, 6.5);
circle(0,    5, 6.5);
circle(10,   5, 6.5);
circle(20,   5, 6.5);
circle(30,   5, 6.5);
circle(40,   5, 6.5);
circle(50,   5, 6.5);
circle(60,   5, 6.5);
circle(70,   5, 6.5);
circle(80,   5, 6.5);
circle(90,   5, 6.5);
circle(100,  5, 6.5);

    //river
    glColor3ub(0, 0, 205);
    glBegin(GL_POLYGON);
    glVertex2f(-100, -50);
    glVertex2f(100, -50);
    glColor3ub(0, 0, 139);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glEnd();
//waves



//filled wave band
glColor3ub(0, 0, 100);
glBegin(GL_TRIANGLE_STRIP);
for(float x = -100; x <= 100; x += 0.5f) {
    float y = -10.0f + sin((x + waveOffset) * 0.4f) * 2.0f
                     + sin((x + waveOffset * 1.3f) * 0.7f) * 0.8f;
    glVertex2f(x, y);
    glVertex2f(x, y - 4.0f);
}
glEnd();

//layered wave lines
float nightWaveY[3]    = {-10.0f,  -25.0f,  -40.0f};  // top, mid, bottom
float nightWaveAmp[3]  = { 1.5f,    2.0f,    1.2f};
float nightWaveFreq[3] = { 0.3f,    0.45f,   0.6f};
float nightWaveSpeed[3]= { 1.0f,    1.5f,    0.8f};    // different speeds per layer
GLubyte nightWaveCol[3][3] = {
    {20,  20,  160},
    {0,   0,   139},
    {10,  10,  110}
};

for(int w = 0; w < 3; w++) {
    glColor3ub(nightWaveCol[w][0], nightWaveCol[w][1], nightWaveCol[w][2]);
    glBegin(GL_LINE_STRIP);
    for(float x = -100; x <= 100; x += 0.5f) {
        float y = nightWaveY[w]
                + sin((x * nightWaveFreq[w]) + (waveOffset * nightWaveSpeed[w])) * nightWaveAmp[w]
                + sin((x * nightWaveFreq[w] * 1.7f) + (waveOffset * nightWaveSpeed[w] * 0.6f)) * 0.7f;
        glVertex2f(x, y);
    }
    glEnd();
}

//boat-reactive wave
glColor3ub(60, 60, 150);
for(int i = 1; i <= 4; i++) {
    glBegin(GL_LINE_STRIP);
    for(float x = -100; x <= 100; x += 0.5f) {
        float dist = x - (boatx - 10.0f);
        float amp  = (4.0f - i * 0.5f) / (1.0f + 0.006f * dist * dist);
        float y    = -30.0f - (i * 4.0f)          // i*4 spreads each wake line 4 units apart
                   + sin(dist * 0.45f + waveOffset * 2.0f) * amp;
        glVertex2f(x, y);
    }
    glEnd();
}

// Moonlight shimmer
glColor3ub(180, 180, 255);
glPointSize(1.5f);
glBegin(GL_POINTS);
for(float x = -100; x <= 100; x += 5.0f) {
    float y = -10.0f + sin((x + waveOffset) * 0.4f) * 2.0f;
    glVertex2f(x, y + 1.0f);
}
glEnd();
glPointSize(1.0f);
    //sky line
    glColor3ub(0, 0, 0);
    line(-100, 0, 100, 0);
    //river line
    glColor3ub(0, 0, 0);
    line(-100, -50, 100, -50);



    //ponyo boat
    //body
    glPushMatrix();
    glTranslatef(boatx, boaty, 0.0f);
    glColor3ub(255, 255, 0);
    polygon(-30, -25, 10, -25, 10, -27.5, -30, -27.5);
    polygon(-30, -27.5, 10, -27.5, 10, -30, -29, -30);
    glColor3ub(0, 255, 0);
    polygon(-29, -30, 10, -30,10, -32.5, -28, -32.5);
    //pipe
    glColor3ub(0, 0, 0);
    polygon(10, -30, 14, -30, 14, -27.5, 10, -27.5);
    //upper pipe
    glColor3ub(135, 135, 135);
    polygon(0, -17.5, 2, -17.5, 2, -20, 0, -20);
    polygon(0, -20, 0, -22, 8, -22, 8, -20);
    polygon(8, -20, 8, -25, 10, -25, 10, -22.5);
    //upper part
    glColor3ub(205, 102, 0);
    triangle(-30, -25, -24, -25, -24, -22.5);
    //outline
    glColor3ub(0, 0, 0);
    polygon(-24, -25, -24, -22.5, -21, -22.5, -22, -25);
    polygon(-24, -22.5, -21, -22.5, -19, -17.5, -20, -15);
    polygon(-20, -15, -4, -15, -4, -17.5, -19, -17.5);
    polygon(-8, -17.5, -6, -17.5, -4, -25, -6, -25);
    //inner part
    glColor3ub(0, 0,0);
    polygon(-20, -25, -18, -20, -16, -20, -18, -25);
    line(-18, -20, -10, -20);
    //fire
    glColor3ub(238, 64, 0);
    semiCircle(-13, -25, 3);
    glColor3ub(255, 153, 0);
    circle(-14, -22.5, 1.75);
    glColor3ub(255, 204, 0);
    circle(-12, -22.5, 1.75);
    glPopMatrix();

//vector house
    //boundary
    glColor3ub(205, 201, 201);
    polygon(-72, 0, -8, 0, -8, 5, -72, 5);
    //triangle
    glColor3ub(16, 78, 139);
    triangle(-68, 5, -12, 5, -40, 50);
    //house circle
    glColor3ub(205, 201, 201);
    semiCircle(-45, 22.5, 13);
    polygon(-58, 22.5, -58, 12.5, -32, 12.5, -32, 22.5);
    //house wall
    glColor3ub(139, 136, 120);
    polygon(-54, 5, -36, 5, -36, 12.5, -54, 12.5);
    //gate
    glColor3ub(205, 201, 201);
    semiCircle(-45, 5, 5);
    glColor3ub(205, 102, 29);
    polygon(-52, 0, -50, 0, -50, 10, -52, 10);
     polygon(-38, 0, -40, 0, -40, 10, -38, 10);
     //lower v
     polygon(-42, 7.5, -44, 7.5, -45, 2.5, -44, 0);
     polygon(-46, 7.5, -48, 7.5, -46, 0, -45, 2.5);
     triangle(-44, 0, -46, 0, -45, 2.5);
     //upper v
     polygon(-40, 40, -42, 40, -45, 32.5, -44, 30);
     polygon(-48, 40, -50, 40, -46, 30, -45, 32.5);
     triangle(-44, 30, -46, 30, -45, 32.5);


    //angry bird
     //tail
     glPushMatrix();
     glTranslatef(birdtx, birdty, 0.0f);
     glRotatef(birdangle, 0.0f, 0.0f, 1.0f);
     glTranslatef(-18.0f, -65.0f, 0.0f);//to spin on spot central points
     glScalef(0.90, 0.90, 1.0);
     glColor3ub(0, 0, 0);
     triangle(-6, 55, 4.5, 62.5, 2, 55);
     triangle(-3, 57.5, 0, 58, -4, 62.5);
     //body
     glColor3ub(255, 225, 0);
     polygon(2, 52.5, 34, 52.5, 34, 55, 2, 55);
     triangle(2, 55, 34, 55, 20, 77.5);
     //stomach
     glColor3ub(255, 225, 255);
     semiCircle(23, 52.5, 4);
     //eye
     glColor3ub(0, 0, 0);
     circle(15, 58.75, 2.5);//left
     circle(29, 58.75, 2.5);//right
     //eye ball
     glColor3ub(250, 250, 250);
     circle(15, 58.75, 1);//left
     circle(29, 58.75, 1);//right
     //brows
     glColor3ub(238, 44, 44);
     polygon(12, 62.5, 20, 57.5, 20, 60, 14, 64);//left
     polygon(26, 57.5, 32, 65, 30, 66.25, 24, 60);//right
     //mouth
     glColor3ub(255, 127, 36);
     triangle(21, 55, 23, 53.75, 25, 55);
     //lips
     glColor3ub(255, 127, 36);
     triangle(20, 53.75, 24.5, 57.5, 22, 57.5);//left
     triangle(21, 55, 30, 55, 24, 57.5);//right
     //hair
     glColor3ub(0, 0, 0);
     polygon(20, 77.5, 21, 87.5, 23, 77.5, 22, 75);
     triangle(18, 75, 14, 77.5, 20, 77.5);
     polygon(17, 77.5, 16, 82.5, 21, 80, 20, 77.5);
     triangle(22, 80, 24, 82.5, 22, 75);
     glPopMatrix();


    //up house
    //left house
    //window wall
    glColor3ub(255, 140, 0);
    polygon(26, -40, 40, -40, 40, 0, 26, 0);
    //window wall side
    glColor3ub(255, 215, 0);
    polygon(24, -40, 26, -40, 26, 0, 24, 0);
    //door wall
    glColor3ub(255, 140, 0);
    polygon(40, -40, 62, -40, 62, 0, 40, 0);
    //left side upper wall
    glColor3ub(191, 239, 255);
    polygon(26, -7.5, 62, -7.5, 62, 0, 26, 0);
    //upper wall lines
    glColor3ub(0, 0, 0);
    line(26, -2.5, 62, -2.5);
    line(26, -5, 62, -5);

    //upper railing back side
    glColor3ub(205, 102, 0);
    polygon(26, -7.5, 62, -7.5, 62, -12.5, 26, -12.5);
    //upper railing (left to right)
    glColor3ub(255, 215, 0);
    polygon(28, -12.5, 30, -12.5, 30, -7.5, 28, -7.5);
    polygon(32, -12.5, 34, -12.5, 34, -7.5, 32, -7.5);
    polygon(36, -12.5, 38, -12.5, 38, -7.5, 36, -7.5);
    polygon(42, -12.5, 44, -12.5, 44, -7.5, 42, -7.5);
    polygon(46, -12.5, 48, -12.5, 48, -7.5, 46, -7.5);
    polygon(50, -12.5, 52, -12.5, 52, -7.5, 50, -7.5);
    polygon(54, -12.5, 56, -12.5, 56, -7.5, 54, -7.5);
    //upper railing up-line
    glColor3ub(255, 245, 10);
    line(26, -7.5, 62, -7.5);
    //upper railing lower-line
    line(26, -12.5, 62, -12.5);
    //lower railing
    glColor3ub(255, 215, 0);
    polygon(28, -40, 30, -40, 30, -35, 28, -35);
    polygon(32, -40, 34, -40, 34, -35, 32, -35);
    polygon(36, -40, 38, -40, 38, -35, 36, -35);
    //lower railing line
    glColor3ub(255, 245, 10);
    line(26, -35, 40, -35);

    //window
    //outer window
    glColor3ub(210, 105, 30);
    polygon(28, -32.5, 38, -32.5, 38, -15, 28, -15);
    //inner window
    glColor3ub(255, 246, 143);
    polygon(30, -30, 36, -30, 36, -17.5, 30, -17.5);
    //inner window bar
    glColor3ub(210, 105, 30);
    polygon(30, -25, 36, -25, 36, -22.5, 30, -22.5);
    //window bar
    glColor3ub(238,118, 33);
    polygon(26, -35, 40, -35, 40, -32.5, 26, -32.5);

    //door
    //outer door
    glColor3ub(210, 105, 30);
    polygon(44, -40, 56, -40, 56, -17.5, 44, -17.5);
    //inner door
    glColor3ub(205,38, 38);
    polygon(46, -40, 54, -40, 54, -20, 46, -20);

    //stairs bar
    glColor3ub(210, 105, 30);
    polygon(20, -42.5, 60, -42.5, 60, -40, 20, -40);
    //outer stairs
    glColor3ub(255, 110, 180);
    polygon(24, -50, 60, -50, 60, -42.5, 24, -42.5);

    //middle stairs bar
    glColor3ub(255, 215, 0);
    polygon(38, -50, 40, -50, 40, 0, 38, 0);



    //right house
    //wall
    glColor3ub(162, 205, 90);
    polygon(60, -50, 70, -50, 70, -12.5, 60, -12.5);//left
    glColor3ub(188, 238, 104);
    polygon(70, -50, 80, -50, 80, -12.5, 70, -12.5);//middle
    glColor3ub(162, 205, 90);
    polygon(80, -50, 90, -50, 90, -12.5, 80, -12.5);//right
    //wall lines
    glColor3ub(255, 246, 143);
    line(70, -50, 70, -12.5);
    line(80, -50, 80, -12.5);

    //left window
    //outer
    glColor3ub(210, 105, 30);
    polygon(61, -35, 69, -35, 69, -20, 61, -20);
    //inner
    glColor3ub(0, 0, 0);
    polygon(62, -32.5, 68, -32.5, 68, -22.5, 62, -22.5);
    //inner bar
    glColor3ub(210, 105, 30);
    polygon(62, -28.5, 68, -28.5, 68, -26.5, 62, -26.5);
    //outer left bar
    glColor3ub(210, 105, 30);
    polygon(61, -37.5, 62, -37.5, 62, -35, 61, -35);
    //outer right bar
    glColor3ub(210, 105, 30);
    polygon(68, -37.5, 69, -37.5, 69, -35, 68, -35);

    //middle window
    //outer
    glColor3ub(210, 105, 30);
    polygon(71, -35, 79, -35, 79, -20, 71, -20);
    //inner
    glColor3ub(0, 0, 0);
    polygon(72, -32.5, 78, -32.5, 78, -22.5, 72, -22.5);
    //inner bar
    glColor3ub(210, 105, 30);
    polygon(72, -28.5, 78, -28.5, 78, -26.5, 72, -26.5);
    //outer left bar
    glColor3ub(210, 105, 30);
    polygon(71, -37.5, 72, -37.5, 72, -35, 71, -35);
    //outer right bar
    glColor3ub(210, 105, 30);
    polygon(78, -37.5, 79, -37.5, 79, -35, 78, -35);

    //left roof
    glColor3ub(139, 69, 19);
    polygon(30, 0, 68, 0, 68, 25, 30, 25);
    //left roof triangle
    triangle(20, 0, 30, 0, 30, 25);


    //right window
    //outer
    glColor3ub(210, 105, 30);
    polygon(81, -35, 89, -35, 89, -20, 81, -20);
    //inner
    glColor3ub(0, 0, 0);
    polygon(82, -32.5, 88, -32.5, 88, -22.5, 82, -22.5);
    //inner bar
    glColor3ub(210, 105, 30);
    polygon(82, -28.5, 88, -28.5, 88, -26.5, 82, -26.5);
    //outer left bar
    glColor3ub(210, 105, 30);
    polygon(81, -37.5, 82, -37.5, 82, -35, 81, -35);
    //outer right bar
    glColor3ub(210, 105, 30);
    polygon(88, -37.5, 89, -37.5, 89, -35, 88, -35);

    //window line
    glColor3ub(85, 107, 47);
    line(60, -15, 90, -15);
    line(60, -17.5, 90, -17.5);
    line(60, -40, 90, -40);
    line(60, -42.5, 90, -42.5);

    //window bar
    glColor3ub(238, 180, 34);
    polygon(60, -12.5, 90, -12.5, 90, -7.5, 60, -7.5);
    triangle(60, -12.5, 60, -7.5, 59, -7.5);//left
    triangle(90, -12.5, 90, -7.5, 91, -7.5);//right

    //2nd floor
    //lower part
    glColor3ub(255, 215, 0);
    polygon(62, -7.5, 88, -7.5, 88, -2.5, 62, -2.5);
    triangle(58, -7.5, 62, -7.5, 62, -2.5);//left
    triangle(88, -7.5, 88, -2.5, 92, -7.5);//left
    //wall
    glColor3ub(255, 215, 0);
    polygon(62, -2.5, 88, -2.5, 88, 12.5, 62, 12.5);
    triangle(62, 12.5, 88, 12.5, 75, 37.5);
    //window
    //outer window
    glColor3ub(210, 105, 30);
    polygon(68, 0, 82, 0, 82, 17.5, 68, 17.5);
    //inner window
    glColor3ub(255, 246, 143);
    polygon(70, 2.5, 80, 2.5, 80, 15, 70, 15);
    //inner window bar
    glColor3ub(210, 105, 30);
    polygon(70, 7.5, 80, 7.5, 80, 10, 70, 10);
    //window bar
    glColor3ub(238,118, 33);
    polygon(66, -2.5, 84, -2.5, 84, 0, 66, 0);
    //outer bar
    glColor3ub(210, 105, 30);
    polygon(68, -5, 70, -5, 70, -2.5, 68, -2.5);//left
    polygon(80, -5, 82, -5, 82, -2.5, 80, -2.5);//right
    //roof left
    glColor3ub(255, 255, 255);
    polygon(56, 7.5, 60, 7.5, 75, 32.5, 75, 37.5);
    //roof right
    polygon(94, 7.5, 90, 7.5, 75, 32.5, 75, 37.5);
    //roof house
    //wall
    glColor3ub(255, 215, 0);
    polygon(34, 10, 46, 10, 46, 20, 34, 20);
    triangle(34, 20, 46, 20, 40, 34);
    //window
    //outer window
    glColor3ub(210, 105, 30);
    polygon(36, 13.75, 44, 13.75, 44, 22.5, 36, 22.5);
    //inner window
    glColor3ub(255, 246, 143);
    polygon(37, 15.25, 43, 15.25, 43, 21, 37, 21);
    glColor3ub(210, 105, 30);
    line(37, 18.125, 43, 18.125);
    //window bar
    glColor3ub(210, 105, 30);
    polygon(36, 12.5, 38, 12.5, 38, 13.75, 36, 13.75);
    polygon(42, 12.5, 44, 12.5, 44, 13.75, 42, 13.75);
    //left roof
    glColor3ub(255, 255, 255);
    polygon(32, 20, 34, 20, 40, 32.5, 40, 35);
    //right roof
    polygon(46, 20, 48, 20, 40, 35, 40, 32.5);


    //inner stairs
    glColor3ub(255, 255, 0);
    polygon(26, -49, 26, -43.5, 38, -43.5, 38, -49);
    glColor3ub(139, 69, 19);
    polygon(40, -44, 60, -44, 60, -50, 40, -50);
    glColor3ub(255, 255, 0);
    polygon(40, -44, 60, -44, 60, -45, 40, -45);
    polygon(40, -46, 60, -46, 60, -47, 40, -47);
    polygon(40, -48, 60, -48, 60, -49, 40, -49);

    //chimney
    glColor3ub(205, 91, 69);
    polygon(54, 25, 60, 25, 60, 32.5, 54, 32.5);
    glColor3ub(139, 62, 47);
    polygon(53, 32.5, 61, 32.5, 61, 33.75, 53, 33.75);


  //london street lamp
//light
glColor3ub(238,201,0);
circle(-95,5,5);
//body
glColor3ub(128,0,0);
polygon(-100,-50,-90,-50,-90,-47.5,-100,-47.5);
polygon(-99,-47.5,-99,-45,-91,-45,-91,-47.5);
polygon(-98,-45,-98,-42.5,-92,-42.5,-92,-45);
polygon(-97,-42.5,-93,-42.5,-94,-12.5,-96,-12.5);
circle(-95,-25,3);
polygon(-97,-12.5,-93,-12.5,-93,-10,-97,-10);
polygon(-96,-10,-96,-5,-94,-5,-94,-10);
circle(-95,-7.5,2);
polygon(-97,-5,-97,-2.5,-93,-2.5,-93,-5);
polygon(-98,-2.5,-98,0,-92,0,-92,-2.5);

     //minion
     //head
     glColor3ub(255, 255, 0);
     semiCircle(-60, -30, 5);
     polygon(-65, -30, -65, -45, -55, -45, -55, -30);
     //hand
     triangle(-65, -37.5, -67, -41.25, -65, -45);
     triangle(-55, -37.5, -53, -41.25, -55, -45);
     //eye frame
     glColor3ub(0, 0, 0);
     polygon(-65, -31, -63, -31, -63, -33.5, -65, -33.5);
     polygon(-57, -31, -55, -31, -55, -33.5, -57, -33.5);
      glColor3ub(133, 133, 133);
     circle(-60, -32.5, 3.5);
     glColor3ub(255, 255, 255);
     circle(-60, -32.5, 3);
     //eye
     glColor3ub(0, 0, 0);
     circle(-59, -32.5, 1.5);
     glColor3ub(255, 255, 0);
     semiCircle(-60, -32.5, 3);
     //body
     glColor3ub(54, 100, 139);
     polygon(-65, -35, -65, -37.5, -63, -40, -63, -37.5);
     polygon(-55, -35, -55, -37.5, -57, -40, -57, -37.5);
     polygon(-63, -37.5, -63, -42.5, -57, -42.5, -57, -37.5);
     polygon(-65, -42.5, -65, -45, -55, -45, -55, -42.5);
     glColor3ub(255, 204, 0);
     line(-65, -37.5, -65, -42.5);
     line(-55, -37.5, -55, -42.5);
     //leg
     glColor3ub(54, 100, 139);
     polygon(-63, -45, -63, -47.5, -61, -47.5, -61, -45);
     polygon(-59, -45, -59, -47.5, -57, -47.5, -57, -45);
     //shoe
     glColor3ub(10, 280, 0);
     polygon(-63, -47.5, -63, -50, -60, -50, -60, -47.5);
     polygon(-59, -47.5, -59, -50, -56, -50, -56, -47.5);




     //Gastly
     //outer
     glPushMatrix();
     glTranslatef(balltx, ballty, 0.0f);
     glColor3ub(110, 50, 160);
     circle(6, -37.5, 9);
     triangle(7, -29.5, 20, -20, 15, -38);
     circle(-1, -35, 3);
     circle(0, -32, 3);
     circle(4, -29, 2);
     circle(9, -28, 2);
     circle(15, -23, 2);
     circle(19, -21, 1);
     circle(19, -23, 2);
     circle(17, -32, 2);
     circle(15, -39, 1.5);
     circle(14, -42, 1.5);
     circle(10, -46, 1.5);
     circle(5, -46, 2);
     circle(-1, -44, 2);
     circle(-2, -43, 2);
     //inner face
     glColor3ub(80, 0, 170);
     circle(6, -37.5, 7);
     //mouth
     glColor3ub(205, 96, 144);
     PokemonSemiCircle(5, -40, 3.5);
     //teeth
     glColor3ub(255,255, 255);
     triangle(2, -40, 4, -40, 3, -42.5);
     triangle(6, -40, 8, -40, 7, -42.5);
     //eyes
     glColor3ub(255,255, 255);
     triangle(-1, -37.5, 3, -35, 0, -32.5);//left
     triangle(-1, -37.5, 3, -35, 3, -37.5);
     PokemonSemiCircle(1, -37.5, 2);
     PokemonSemiCircle(9, -37.5, 2);//right
     triangle(10, -32.5, 6, -35, 11, -35);
     polygon(6, -35, 11, -35, 11, -37.5, 7, -37.5);
     //eyeball
     glPointSize(5);
     glBegin(GL_POINTS);
     glColor3ub(0, 0, 0);
     glVertex2f(1.5, -36);
     glVertex2f(9, -36);
     glEnd();



     //togepi
     //face
     glColor3ub(240, 230, 140);
     polygon(-86, -37.5, -86, -30, -70, -30, -70, -37.5);
     triangle(-88, -25, -80, -23.5, -86, -30);
     triangle(-80, -23.5, -77, -17.5, -73, -23.5);
     triangle(-73, -23.5, -68, -20, -70, -30);
     polygon(-70, -30, -73, -23.5, -80, -23.5, -86, -30);
     //shell
     glColor3ub(255, 255, 255);
     PokemonSemiCircle(-78, -37.5, 8);
     triangle(-86, -32.5, -86, -37.5, -83, -37.5);
     triangle(-83, -37.5, -79, -37.5, -80, -32.5);
     triangle(-79, -37.5, -75, -37.5, -76, -35);
     triangle(-75, -37.5, -70, -37.5, -73, -30);
     //hand
     //left
     glColor3ub(205, 198, 115);
     circle(-86, -35, 2);
     triangle(-86, -37, -86, -33, -91, -35);
     //right
     circle(-70, -32.5, 2);
     triangle(-70, -30.5, -68, -32.5, -66, -27.5);
     //left leg
     PokemonSemiCircle(-83, - 48, 2);
     polygon(-85, -48, -81, -48, -79, -45, -83, -44);
     //right leg
     PokemonSemiCircle(-73, - 48, 2);
     polygon(-75, -48, -71, -48, -74, -44, -77, -45);
     //eyeball
     glBegin(GL_POINTS);
     glColor3ub(0, 0, 0);
     glVertex2f(-80, -26.75);
     glVertex2f(-76, -26.75);
     glEnd();
     //mouth
     line(-80, -28.75, -76, -28.75);
     glColor3ub(188, 143, 143);
     polygon(-79, -28.75, -77, -28.75, -77, -32.5, -79, -32.5);
     glColor3ub(255, 193, 193);
     semiCircle(-78, -32.5, 1);
     //shell design
     glColor3ub(193, 0, 0);
     triangle(-83, -37.5, -84, -40, -82, -40);
     polygon(-74, -37.5, -76, -37.5, -76, -40, -74, -40);
     glColor3ub(255, 255, 255);
     polygon(-74.5, -38, -75.5, -38, -75.5, -39.5, -74.5, -39.5);
     glColor3ub(135, 206, 250);
     triangle(-80, -42.5, -80, -40, -78, -41.25);
     glPopMatrix();



     simpsonsCar();
//rain
glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glTranslatef(rainDriftOffset, rainFallOffset, 0.0f);

    // close heavy rain
    glColor4ub(200, 230, 255, 255);
    glLineWidth(1.8f);
    glBegin(GL_LINES);
    for(int i = 0; i < 80; i++)
    {
        glVertex2f(rainX[i],         rainY[i]);
        glVertex2f(rainX[i] - 1.2f, rainY[i] - 5.0f);
    }
    glEnd();

    glPopMatrix();

    //mid rain
    glPushMatrix();
    glTranslatef(rainDriftOffset * 0.7f, rainFallOffset * 0.7f, 0.0f);

    glColor4ub(180, 215, 255, 220);    // slightly dimmer
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    for(int i = 80; i < 150; i++)
    {
        glVertex2f(rainX[i],         rainY[i]);
        glVertex2f(rainX[i] - 0.8f, rainY[i] - 3.5f);
    }
    glEnd();

    glPopMatrix();

    //distant faint rain
    glPushMatrix();
    glTranslatef(rainDriftOffset * 0.4f, rainFallOffset * 0.4f, 0.0f);

    glColor4ub(160, 200, 245, 170);    // softer
    glLineWidth(0.8f);
    glBegin(GL_LINES);
    for(int i = 150; i < 200; i++)
    {
        glVertex2f(rainX[i],         rainY[i]);
        glVertex2f(rainX[i] - 0.4f, rainY[i] - 2.0f);
    }
    glEnd();

    glPopMatrix();

    glLineWidth(1.0f);
    glDisable(GL_BLEND);
}

void scene2()
{
    //sky
    glColor3ub(0, 191, 255);
    polygon(-100, 0, 100, 0, 100, 100, -100, 100);

    //sun
    glColor3ub(255, 255, 0);
    circle(-75, 81.25, 7);


     glPushMatrix();
glTranslatef(cloudx, cloudy, 0.0f);

// cloud 1 - left small
glColor3ub(210, 210, 210);
circle(-64, 87.5, 5);
circle(-60, 87.5, 6);
circle(-56, 87.5, 5);
glColor3ub(235, 235, 235);
circle(-62, 90, 4);
circle(-58, 90, 4);
circle(-60, 92, 3);
glColor3ub(255, 255, 255);
circle(-60, 91.5, 2.5);
circle(-61, 89, 2);

// cloud 2 - center big fluffy
glColor3ub(205, 205, 205);
circle(-28, 75, 7);
circle(-20, 75, 10);
circle(-12, 75, 7);
glColor3ub(230, 230, 230);
circle(-24, 80, 6);
circle(-16, 80, 6);
circle(-20, 83, 5);
glColor3ub(248, 248, 248);
circle(-26, 79, 4);
circle(-14, 79, 4);
circle(-20, 82, 4);
// bright white top
glColor3ub(255, 255, 255);
circle(-20, 83, 3);
circle(-24, 80, 2.5);
circle(-16, 80, 2.5);

// cloud 3 - right
glColor3ub(210, 210, 210);
circle(34, 80, 6);
circle(40, 80, 7);
circle(46, 80, 6);
glColor3ub(235, 235, 235);
circle(37, 83.5, 4);
circle(43, 83.5, 4);
circle(40, 86, 3.5);
glColor3ub(255, 255, 255);
circle(40, 85.5, 2.5);

// cloud 4 - far left
glColor3ub(215, 215, 215);
circle(-120, 75, 8);
circle(-128, 75, 6);
circle(-112, 75, 6);
glColor3ub(240, 240, 240);
circle(-125, 79, 5);
circle(-115, 79, 5);
circle(-120, 82, 4);
glColor3ub(255, 255, 255);
circle(-120, 82, 2.5);

glPopMatrix();


    //road
    glColor3ub(150,150,150);
    polygon(-100, -100, 100, -100, 100, -50, -100, -50);

    //road divider
     glColor3ub(255,255,255);
    polygon(-100,-75,-80,-75,-80,-70,-100,-70);
    polygon(-60,-75,-40,-75,-40,-70,-60,-70);
    polygon(-20,-75,0,-75,0,-70,-20,-70);
    polygon(20,-75,40,-75,40,-70,20,-70);
    polygon(60,-75,80,-75,80,-70,60,-70);


    //forest
    // forest 1st layer — dark forest green (day)
glColor3ub(0, 80, 0);
circle(-85, 16.5, 8);
circle(-65, 16.5, 8);
circle(-45, 16.5, 8);
circle(-25, 16.5, 8);
circle(-5,  16.5, 8);
circle(20,  16.5, 8);
circle(40,  16.5, 8);
circle(60,  16.5, 8);
circle(80,  16.5, 8);

// forest 2nd layer — medium green
glColor3ub(34, 139, 34);
circle(-95, 10, 8);
circle(-80, 10, 8);
circle(-65, 10, 8);
circle(-50, 10, 8);
circle(-35, 10, 8);
circle(-20, 10, 8);
circle(-5,  10, 8);
circle(10,  10, 8);
circle(25,  10, 8);
circle(40,  10, 8);
circle(55,  10, 8);
circle(70,  10, 8);
circle(85,  10, 8);
circle(100, 10, 8);

// forest 3rd layer — bright sunlit green
glColor3ub(80, 200, 80);
circle(-100, 5, 6.5);
circle(-90,  5, 6.5);
circle(-80,  5, 6.5);
circle(-70,  5, 6.5);
circle(-60,  5, 6.5);
circle(-50,  5, 6.5);
circle(-40,  5, 6.5);
circle(-30,  5, 6.5);
circle(-20,  5, 6.5);
circle(-10,  5, 6.5);
circle(0,    5, 6.5);
circle(10,   5, 6.5);
circle(20,   5, 6.5);
circle(30,   5, 6.5);
circle(40,   5, 6.5);
circle(50,   5, 6.5);
circle(60,   5, 6.5);
circle(70,   5, 6.5);
circle(80,   5, 6.5);
circle(90,   5, 6.5);
circle(100,  5, 6.5);
    //river
    glColor3ub(0, 191, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-100, -50);
    glVertex2f(100, -50);
    glColor3ub(16, 78, 139);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glEnd();
//wave


//filled wave band
glColor3ub(0, 160, 210);
glBegin(GL_TRIANGLE_STRIP);
for(float x = -100; x <= 100; x += 0.5f) {
    float y = -10.0f + sin((x + waveOffset) * 0.4f) * 2.0f
                     + sin((x + waveOffset * 1.3f) * 0.7f) * 0.8f;
    glVertex2f(x, y);
    glVertex2f(x, y - 4.0f);
}
glEnd();

//layered wave lines
float dayWaveY[3]    = {-10.0f,  -25.0f,  -40.0f};   // top, mid, bottom
float dayWaveAmp[3]  = { 1.5f,    2.0f,    1.2f};
float dayWaveFreq[3] = { 0.3f,    0.45f,   0.6f};
float dayWaveSpeed[3]= { 1.0f,    1.5f,    0.8f};     // different speeds per layer
GLubyte dayWaveCol[3][3] = {
    {0,  191, 255},
    {30, 144, 255},
    {0,  105, 180}
};

for(int w = 0; w < 3; w++) {
    glColor3ub(dayWaveCol[w][0], dayWaveCol[w][1], dayWaveCol[w][2]);
    glBegin(GL_LINE_STRIP);
    for(float x = -100; x <= 100; x += 0.5f) {
        float y = dayWaveY[w]
                + sin((x * dayWaveFreq[w]) + (waveOffset * dayWaveSpeed[w])) * dayWaveAmp[w]
                + sin((x * dayWaveFreq[w] * 1.7f) + (waveOffset * dayWaveSpeed[w] * 0.6f)) * 0.7f;
        glVertex2f(x, y);
    }
    glEnd();
}

//boat-reactive wave
glColor3ub(180, 230, 255);
for(int i = 1; i <= 4; i++) {
    glBegin(GL_LINE_STRIP);
    for(float x = -100; x <= 100; x += 0.5f) {
        float dist = x - (boatx - 10.0f);
        float amp  = (4.0f - i * 0.5f) / (1.0f + 0.006f * dist * dist);
        float y    = -30.0f - (i * 4.0f)          // i*4 spreads each wake line 4 units apart
                   + sin(dist * 0.45f + waveOffset * 2.0f) * amp;
        glVertex2f(x, y);
    }
    glEnd();
}

// Sunlight glint
glColor3ub(255, 255, 255);
glPointSize(2.0f);
glBegin(GL_POINTS);
for(float x = -100; x <= 100; x += 5.0f) {
    float y = -10.0f + sin((x + waveOffset) * 0.4f) * 2.0f;
    glVertex2f(x, y + 1.0f);
}
glEnd();
glPointSize(1.0f);

    //sky line
    glColor3ub(0, 0, 0);
    line(-100, 0, 100, 0);
    //river line
    glColor3ub(0, 0, 0);
    line(-100, -50, 100, -50);



    //ponyo boat
    //body
    glPushMatrix();
    glTranslatef(boatx, boaty, 0.0f);
    glColor3ub(255, 255, 255);
    polygon(-30, -25, 10, -25, 10, -27.5, -30, -27.5);
    polygon(-30, -27.5, 10, -27.5, 10, -30, -29, -30);
    glColor3ub(205, 38, 38);
    polygon(-29, -30, 10, -30,10, -32.5, -28, -32.5);
    //pipe
    glColor3ub(205, 38, 38);
    polygon(10, -30, 14, -30, 14, -27.5, 10, -27.5);
    //upper pipe
    glColor3ub(135, 135, 135);
    polygon(0, -17.5, 2, -17.5, 2, -20, 0, -20);
    polygon(0, -20, 0, -22, 8, -22, 8, -20);
    polygon(8, -20, 8, -25, 10, -25, 10, -22.5);
    //upper part
    glColor3ub(255, 193, 37);
    triangle(-30, -25, -24, -25, -24, -22.5);
    //outline
    glColor3ub(16, 78, 139);
    polygon(-24, -25, -24, -22.5, -21, -22.5, -22, -25);
    polygon(-24, -22.5, -21, -22.5, -19, -17.5, -20, -15);
    polygon(-20, -15, -4, -15, -4, -17.5, -19, -17.5);
    polygon(-8, -17.5, -6, -17.5, -4, -25, -6, -25);
    //inner part
    glColor3ub(102, 102, 102);
    polygon(-20, -25, -18, -20, -16, -20, -18, -25);
    line(-18, -20, -10, -20);
    //fire
    glColor3ub(238, 64, 0);
    semiCircle(-13, -25, 3);
    glColor3ub(255, 153, 0);
    circle(-14, -22.5, 1.75);
    glColor3ub(255, 204, 0);
    circle(-12, -22.5, 1.75);
    glPopMatrix();



    //vector house
    //boundary
    glColor3ub(240, 255, 240);
    polygon(-72, 0, -8, 0, -8, 5, -72, 5);
    //triangle
    glColor3ub(24, 116, 205);
    triangle(-68, 5, -12, 5, -40, 50);
    //house circle
    glColor3ub(255, 255, 255);
    semiCircle(-45, 22.5, 13);
    polygon(-58, 22.5, -58, 12.5, -32, 12.5, -32, 22.5);
    //house wall
    glColor3ub(205, 201, 201);
    polygon(-54, 5, -36, 5, -36, 12.5, -54, 12.5);
    //gate
    glColor3ub(240, 255, 240);
    semiCircle(-45, 5, 5);
    glColor3ub(255, 127, 36);
    polygon(-52, 0, -50, 0, -50, 10, -52, 10);
     polygon(-38, 0, -40, 0, -40, 10, -38, 10);
     //lower v
     polygon(-42, 7.5, -44, 7.5, -45, 2.5, -44, 0);
     polygon(-46, 7.5, -48, 7.5, -46, 0, -45, 2.5);
     triangle(-44, 0, -46, 0, -45, 2.5);
     //upper v
     polygon(-40, 40, -42, 40, -45, 32.5, -44, 30);
     polygon(-48, 40, -50, 40, -46, 30, -45, 32.5);
     triangle(-44, 30, -46, 30, -45, 32.5);





    //up house
    glPushMatrix();
    glTranslatef(housetx, housety, 0.0f);
    glScalef(housescale, housescale, 1.0f);
    //left house
    //window wall
    glColor3ub(255, 140, 0);
    polygon(26, -40, 40, -40, 40, 0, 26, 0);
    //window wall side
    glColor3ub(255, 215, 0);
    polygon(24, -40, 26, -40, 26, 0, 24, 0);
    //door wall
    glColor3ub(255, 140, 0);
    polygon(40, -40, 62, -40, 62, 0, 40, 0);
    //left side upper wall
    glColor3ub(191, 239, 255);
    polygon(26, -7.5, 62, -7.5, 62, 0, 26, 0);
    //upper wall lines
    glColor3ub(0, 0, 0);
    line(26, -2.5, 62, -2.5);
    line(26, -5, 62, -5);

    //upper railing back side
    glColor3ub(205, 102, 0);
    polygon(26, -7.5, 62, -7.5, 62, -12.5, 26, -12.5);
    //upper railing (left to right)
    glColor3ub(255, 215, 0);
    polygon(28, -12.5, 30, -12.5, 30, -7.5, 28, -7.5);
    polygon(32, -12.5, 34, -12.5, 34, -7.5, 32, -7.5);
    polygon(36, -12.5, 38, -12.5, 38, -7.5, 36, -7.5);
    polygon(42, -12.5, 44, -12.5, 44, -7.5, 42, -7.5);
    polygon(46, -12.5, 48, -12.5, 48, -7.5, 46, -7.5);
    polygon(50, -12.5, 52, -12.5, 52, -7.5, 50, -7.5);
    polygon(54, -12.5, 56, -12.5, 56, -7.5, 54, -7.5);
    //upper railing up-line
    glColor3ub(255, 245, 10);
    line(26, -7.5, 62, -7.5);
    //upper railing lower-line
    line(26, -12.5, 62, -12.5);
    //lower railing
    glColor3ub(255, 215, 0);
    polygon(28, -40, 30, -40, 30, -35, 28, -35);
    polygon(32, -40, 34, -40, 34, -35, 32, -35);
    polygon(36, -40, 38, -40, 38, -35, 36, -35);
    //lower railing line
    glColor3ub(255, 245, 10);
    line(26, -35, 40, -35);

    //window
    //outer window
    glColor3ub(210, 105, 30);
    polygon(28, -32.5, 38, -32.5, 38, -15, 28, -15);
    //inner window
    glColor3ub(255, 246, 143);
    polygon(30, -30, 36, -30, 36, -17.5, 30, -17.5);
    //inner window bar
    glColor3ub(210, 105, 30);
    polygon(30, -25, 36, -25, 36, -22.5, 30, -22.5);
    //window bar
    glColor3ub(238,118, 33);
    polygon(26, -35, 40, -35, 40, -32.5, 26, -32.5);

    //door
    //outer door
    glColor3ub(210, 105, 30);
    polygon(44, -40, 56, -40, 56, -17.5, 44, -17.5);
    //inner door
    glColor3ub(205,38, 38);
    polygon(46, -40, 54, -40, 54, -20, 46, -20);

    //stairs bar
    glColor3ub(210, 105, 30);
    polygon(20, -42.5, 60, -42.5, 60, -40, 20, -40);
    //outer stairs
    glColor3ub(255, 110, 180);
    polygon(24, -50, 60, -50, 60, -42.5, 24, -42.5);

    //middle stairs bar
    glColor3ub(255, 215, 0);
    polygon(38, -50, 40, -50, 40, 0, 38, 0);



    //right house
    //wall
    glColor3ub(162, 205, 90);
    polygon(60, -50, 70, -50, 70, -12.5, 60, -12.5);//left
    glColor3ub(188, 238, 104);
    polygon(70, -50, 80, -50, 80, -12.5, 70, -12.5);//middle
    glColor3ub(162, 205, 90);
    polygon(80, -50, 90, -50, 90, -12.5, 80, -12.5);//right
    //wall lines
    glColor3ub(255, 246, 143);
    line(70, -50, 70, -12.5);
    line(80, -50, 80, -12.5);

    //left window
    //outer
    glColor3ub(210, 105, 30);
    polygon(61, -35, 69, -35, 69, -20, 61, -20);
    //inner
    glColor3ub(0, 0, 0);
    polygon(62, -32.5, 68, -32.5, 68, -22.5, 62, -22.5);
    //inner bar
    glColor3ub(210, 105, 30);
    polygon(62, -28.5, 68, -28.5, 68, -26.5, 62, -26.5);
    //outer left bar
    glColor3ub(210, 105, 30);
    polygon(61, -37.5, 62, -37.5, 62, -35, 61, -35);
    //outer right bar
    glColor3ub(210, 105, 30);
    polygon(68, -37.5, 69, -37.5, 69, -35, 68, -35);

    //middle window
    //outer
    glColor3ub(210, 105, 30);
    polygon(71, -35, 79, -35, 79, -20, 71, -20);
    //inner
    glColor3ub(0, 0, 0);
    polygon(72, -32.5, 78, -32.5, 78, -22.5, 72, -22.5);
    //inner bar
    glColor3ub(210, 105, 30);
    polygon(72, -28.5, 78, -28.5, 78, -26.5, 72, -26.5);
    //outer left bar
    glColor3ub(210, 105, 30);
    polygon(71, -37.5, 72, -37.5, 72, -35, 71, -35);
    //outer right bar
    glColor3ub(210, 105, 30);
    polygon(78, -37.5, 79, -37.5, 79, -35, 78, -35);

    //left roof
    glColor3ub(139, 69, 19);
    polygon(30, 0, 68, 0, 68, 25, 30, 25);
    //left roof triangle
    triangle(20, 0, 30, 0, 30, 25);


    //right window
    //outer
    glColor3ub(210, 105, 30);
    polygon(81, -35, 89, -35, 89, -20, 81, -20);
    //inner
    glColor3ub(0, 0, 0);
    polygon(82, -32.5, 88, -32.5, 88, -22.5, 82, -22.5);
    //inner bar
    glColor3ub(210, 105, 30);
    polygon(82, -28.5, 88, -28.5, 88, -26.5, 82, -26.5);
    //outer left bar
    glColor3ub(210, 105, 30);
    polygon(81, -37.5, 82, -37.5, 82, -35, 81, -35);
    //outer right bar
    glColor3ub(210, 105, 30);
    polygon(88, -37.5, 89, -37.5, 89, -35, 88, -35);

    //window line
    glColor3ub(85, 107, 47);
    line(60, -15, 90, -15);
    line(60, -17.5, 90, -17.5);
    line(60, -40, 90, -40);
    line(60, -42.5, 90, -42.5);

    //window bar
    glColor3ub(238, 180, 34);
    polygon(60, -12.5, 90, -12.5, 90, -7.5, 60, -7.5);
    triangle(60, -12.5, 60, -7.5, 59, -7.5);//left
    triangle(90, -12.5, 90, -7.5, 91, -7.5);//right

    //2nd floor
    //lower part
    glColor3ub(255, 215, 0);
    polygon(62, -7.5, 88, -7.5, 88, -2.5, 62, -2.5);
    triangle(58, -7.5, 62, -7.5, 62, -2.5);//left
    triangle(88, -7.5, 88, -2.5, 92, -7.5);//left
    //wall
    glColor3ub(255, 215, 0);
    polygon(62, -2.5, 88, -2.5, 88, 12.5, 62, 12.5);
    triangle(62, 12.5, 88, 12.5, 75, 37.5);
    //window
    //outer window
    glColor3ub(210, 105, 30);
    polygon(68, 0, 82, 0, 82, 17.5, 68, 17.5);
    //inner window
    glColor3ub(255, 246, 143);
    polygon(70, 2.5, 80, 2.5, 80, 15, 70, 15);
    //inner window bar
    glColor3ub(210, 105, 30);
    polygon(70, 7.5, 80, 7.5, 80, 10, 70, 10);
    //window bar
    glColor3ub(238,118, 33);
    polygon(66, -2.5, 84, -2.5, 84, 0, 66, 0);
    //outer bar
    glColor3ub(210, 105, 30);
    polygon(68, -5, 70, -5, 70, -2.5, 68, -2.5);//left
    polygon(80, -5, 82, -5, 82, -2.5, 80, -2.5);//right
    //roof left
    glColor3ub(255, 255, 255);
    polygon(56, 7.5, 60, 7.5, 75, 32.5, 75, 37.5);
    //roof right
    polygon(94, 7.5, 90, 7.5, 75, 32.5, 75, 37.5);
    //roof house
    //wall
    glColor3ub(255, 215, 0);
    polygon(34, 10, 46, 10, 46, 20, 34, 20);
    triangle(34, 20, 46, 20, 40, 34);
    //window
    //outer window
    glColor3ub(210, 105, 30);
    polygon(36, 13.75, 44, 13.75, 44, 22.5, 36, 22.5);
    //inner window
    glColor3ub(255, 246, 143);
    polygon(37, 15.25, 43, 15.25, 43, 21, 37, 21);
    glColor3ub(210, 105, 30);
    line(37, 18.125, 43, 18.125);
    //window bar
    glColor3ub(210, 105, 30);
    polygon(36, 12.5, 38, 12.5, 38, 13.75, 36, 13.75);
    polygon(42, 12.5, 44, 12.5, 44, 13.75, 42, 13.75);
    //left roof
    glColor3ub(255, 255, 255);
    polygon(32, 20, 34, 20, 40, 32.5, 40, 35);
    //right roof
    polygon(46, 20, 48, 20, 40, 35, 40, 32.5);


    //inner stairs
    glColor3ub(255, 255, 0);
    polygon(26, -49, 26, -43.5, 38, -43.5, 38, -49);
    glColor3ub(139, 69, 19);
    polygon(40, -44, 60, -44, 60, -50, 40, -50);
    glColor3ub(255, 255, 0);
    polygon(40, -44, 60, -44, 60, -45, 40, -45);
    polygon(40, -46, 60, -46, 60, -47, 40, -47);
    polygon(40, -48, 60, -48, 60, -49, 40, -49);

    //chimney
    glColor3ub(205, 91, 69);
    polygon(54, 25, 60, 25, 60, 32.5, 54, 32.5);
    glColor3ub(139, 62, 47);
    polygon(53, 32.5, 61, 32.5, 61, 33.75, 53, 33.75);


    //balloon
     //string
     glColor3ub(0, 0, 0);
     line(56, 40, 56, 33.75);
     line(58, 40, 58, 33.75);
     line(62, 40, 60, 33.75);
     line(52, 40, 54, 33.75);
     line(51, 40, 53.5, 33.75);
     line(60, 40, 58, 33.75);
     //inner balloons
     //4th
     glColor3ub(0, 0, 139);
     circle(42, 67, 5);
     glColor3ub(104, 34, 139);
     circle(52, 67, 5);
     glColor3ub(139, 0, 0);
     circle(62, 67, 5);
     glColor3ub(47, 79, 79);
     circle(72, 67, 5);
     //5th
     glColor3ub(0, 0, 0);
     circle(67, 77, 5);
     glColor3ub(85, 26, 139);
     circle(57, 77, 5);
     glColor3ub(139, 101, 8);
     circle(47, 77, 5);
     //6th
     glColor3ub(0, 100, 0);
     circle(62, 88, 5);
     glColor3ub(0, 0, 139);
     circle(52, 88, 5);
     //1st
     glColor3ub(139, 0, 0);
     circle(67, 47, 5);
     glColor3ub(0, 100, 0);
     circle(57, 47, 5);
     glColor3ub(139, 71, 38);
     circle(47, 47, 5);
     //2nd
     glColor3ub(155, 20, 50);
     circle(42, 57, 5);
     glColor3ub(255, 120, 50);
     circle(52, 57, 5);
     glColor3ub(0, 0, 255);
     circle(62, 57, 5);
     glColor3ub(250, 0, 255);
     circle(72, 57, 5);

     //balloon
     //1st
     glColor3ub(118, 238, 198);
     circle(67, 42, 5);
     glColor3ub(255, 185, 15);
     circle(57, 42, 5);
     glColor3ub(162, 205, 90);
     circle(47, 42, 5);
     //2nd
     glColor3ub(255, 106, 167);
     circle(42, 52, 5);
     glColor3ub(191, 239, 255);
     circle(52, 52, 5);
     glColor3ub(171, 130, 255);
     circle(62, 52, 5);
     glColor3ub(205, 79, 57);
     circle(72, 52, 5);

     //3rd
     glColor3ub(238, 174, 238);
     circle(37, 62, 5);
     glColor3ub(32, 178, 170);
     circle(47, 62, 5);
     glColor3ub(255, 215, 0);
     circle(57, 62, 5);
     glColor3ub(110, 123, 139);
     circle(67, 62, 5);
     glColor3ub(250, 80, 0);
     circle(77, 62, 5);
     //4th
     glColor3ub(152, 251, 152);
     circle(42, 72, 5);
     glColor3ub(208, 32, 144);
     circle(52, 72, 5);
     glColor3ub(108, 166, 205);
     circle(62, 72, 5);
     glColor3ub(244, 164, 96);
     circle(72, 72, 5);
     //5th
     glColor3ub(69, 139, 116);
     circle(67, 82, 5);
     glColor3ub(255, 255, 0);
     circle(57, 82, 5);
     glColor3ub(238, 118, 0);
     circle(47, 82, 5);
    glPopMatrix();



   //london street lamp
//light
glColor3ub(238,201,0);
circle(-95,5,5);
//body
glColor3ub(0,0,0);
polygon(-100,-50,-90,-50,-90,-47.5,-100,-47.5);
polygon(-99,-47.5,-99,-45,-91,-45,-91,-47.5);
polygon(-98,-45,-98,-42.5,-92,-42.5,-92,-45);
polygon(-97,-42.5,-93,-42.5,-94,-12.5,-96,-12.5);
circle(-95,-25,3);
polygon(-97,-12.5,-93,-12.5,-93,-10,-97,-10);
polygon(-96,-10,-96,-5,-94,-5,-94,-10);
circle(-95,-7.5,2);
polygon(-97,-5,-97,-2.5,-93,-2.5,-93,-5);
polygon(-98,-2.5,-98,0,-92,0,-92,-2.5);




      //minion
     //head
     glColor3ub(255, 255, 0);
     semiCircle(-75, -30, 5);
     polygon(-80, -30, -80, -45, -70, -45, -70, -30);
     //hand
     triangle(-80, -37.5, -82, -41.25, -80, -45);
     triangle(-70, -37.5, -68, -41.25, -70, -45);
     //eye frame
     glColor3ub(0, 0, 0);
     polygon(-80, -31, -78, -31, -78, -33.5, -80, -33.5);
     polygon(-72, -31, -70, -31, -70, -33.5, -72, -33.5);
      glColor3ub(133, 133, 133);
     circle(-75, -32.5, 3.5);
     glColor3ub(255, 255, 255);
     circle(-75, -32.5, 3);
     //eye
     glColor3ub(0, 0, 0);
     circle(-74, -32.5, 1.5);
     glColor3ub(255, 255, 0);
     semiCircle(-75, -32.5, 3);
     //body
     glColor3ub(54, 100, 139);
     polygon(-80, -35, -80, -37.5, -78, -40, -78, -37.5);
     polygon(-70, -35, -70, -37.5, -72, -40, -72, -37.5);
     polygon(-78, -37.5, -78, -42.5, -72, -42.5, -72, -37.5);
     polygon(-80, -42.5, -80, -45, -70, -45, -70, -42.5);
     glColor3ub(255, 204, 0);
     line(-80, -37.5, -80, -42.5);
     line(-70, -37.5, -70, -42.5);
     //leg
     glColor3ub(54, 100, 139);
     polygon(-78, -45, -78, -47.5, -76, -47.5, -76, -45);
     polygon(-74, -45, -74, -47.5, -72, -47.5, -72, -45);
     //shoe
     glColor3ub(10, 280, 0);
     polygon(-78, -47.5, -78, -50, -75, -50, -75, -47.5);
     polygon(-74, -47.5, -74, -50, -71, -50, -71, -47.5);



     //imposter
     glPushMatrix();
     glTranslatef(impostertx, imposterty, 0.0f);
     //body
     glColor3ub(25, 185, 25);
     polygon(-60, -45, -46, -45, -46, -25, -60, -25);
     semiCircle(-53, -25, 7);
     //leg
     polygon(-60, -50, -56, -50, -56, -45, -60, -45);//left
     polygon(-50, -50, -46, -50, -46, -45, -50, -45);//right
     //bag
     glColor3ub(18, 140, 18);
     polygon(-64, -42.5, -60, -42.5, -60, -27.5, -64, -27.5);
     //glass
     glColor3ub(220, 220, 220);
     polygon(-51, -35, -46, -35, -46, -27.5, -51, -27.5);
     circle(-50, -31.25, 3.75);
     //hand
     glColor3ub(0, 100, 0);
     circle(-43, -40, 2);
     //balloon
     glColor3ub(0, 0, 0);
     line(-43, -38, -43, -20);
     glColor3ub(205, 0, 0);
     circle(-43, -15, 6);
     glPopMatrix();



     //pokemon ball
     glPushMatrix();
     glTranslatef(balltx, ballty, 0.0f);
     if(bounce < 4){

     glColor3ub(255, 255, 255);
     circle(13, -44.25, 5.5);//outer part
     glColor3ub(255, 0, 0);
     semiCircle(13, -44.25, 5.5);//outer part
     glColor3ub(0, 0, 0);
     polygon(7.5, -45.5, 18.5, -45.5, 18.5, -43.5, 7.5, -43.5);//bar
glColor3ub(0, 0, 0);
     circle(13, -44.25, 3);//outer part boundary
     glColor3ub(255, 255, 255);
     circle(13, -44.25, 2.5);//outer part
     glColor3ub(0, 0, 0);
     circle(13, -44.25, 1);//outer part

     }

     else if(bounce >= 4)
     {
     //Gastly
     //outer
     glColor3ub(110, 50, 160);
     circle(6, -37.5, 9);
     triangle(7, -29.5, 20, -20, 15, -38);
     circle(-1, -35, 3);
     circle(0, -32, 3);
     circle(4, -29, 2);
     circle(9, -28, 2);
     circle(15, -23, 2);
     circle(19, -21, 1);
     circle(19, -23, 2);
     circle(17, -32, 2);
     circle(15, -39, 1.5);
     circle(14, -42, 1.5);
     circle(10, -46, 1.5);
     circle(5, -46, 2);
     circle(-1, -44, 2);
     circle(-2, -43, 2);
     //inner face
     glColor3ub(80, 0, 170);
     circle(6, -37.5, 7);
     //mouth
     glColor3ub(205, 96, 144);
     PokemonSemiCircle(5, -40, 3.5);
     //teeth
     glColor3ub(255,255, 255);
     triangle(2, -40, 4, -40, 3, -42.5);
     triangle(6, -40, 8, -40, 7, -42.5);
     //eyes
     glColor3ub(255,255, 255);
     triangle(-1, -37.5, 3, -35, 0, -32.5);//left
     triangle(-1, -37.5, 3, -35, 3, -37.5);
     PokemonSemiCircle(1, -37.5, 2);
     PokemonSemiCircle(9, -37.5, 2);//right
     triangle(10, -32.5, 6, -35, 11, -35);
     polygon(6, -35, 11, -35, 11, -37.5, 7, -37.5);
     //eyeball
     glPointSize(5);
     glBegin(GL_POINTS);
     glColor3ub(0, 0, 0);
     glVertex2f(1.5, -36);
     glVertex2f(9, -36);
     glEnd();
     }
     glPopMatrix();

simpsonsCar();
}
void scene3(){


    //sky


    glBegin(GL_POLYGON);

glColor3f(0.96f, 0.82f, 0.48f);
    glVertex2f(-100,100);
    glColor3f(0.55f, 0.28f, 0.15f);
      glVertex2f(100,100);
      glColor3f(0.78f, 0.48f, 0.18f);
        glVertex2f(100,0);
        glColor3f(0.92f, 0.68f, 0.28f);
          glVertex2f(-100,0);
    glEnd();

    glPushMatrix();
    glTranslatef(cloudtx,cloudty,0);

//cloud
//out
    glColor3f(0.78f, 0.72f, 0.65f);
    circle(-60,87.5,4);
    circle(-64,87.5,3);
    circle(-56,87.5,3);

    circle(-20,75,8);
    circle(-28,75,5);
    circle(-12,75,5);

    circle(40,80,6);
    circle(46,80,4);
    circle(34,80,4);

    //mid
    glColor3f(0.88f, 0.84f, 0.78f);
        circle(-63,89.5,2);
    circle(-57,89.5,2);
      circle(-60,89.5,3);

 circle(-27,77,4);
    circle(-13,77,4);
      circle(-20,77,5);

     circle(45,82,3);
    circle(35,82,3);
     circle(40,82,4);
     //up
     glColor3f(0.88f, 0.84f, 0.78f);
        circle(-61,92.5,2);
    circle(-59,92.5,2);
      circle(-60,92.5,3);

 circle(-25,80,4);
    circle(-15,80,4);
      circle(-20,80,5);

     circle(43,85,3);
    circle(37,85,3);
     circle(40,85,4);
//inner
 glColor3f(0.96f, 0.93f, 0.88f);
 circle(41,85,2);
 circle(39,85,2);

   circle(-22,80,3);
 circle(-18,80,3);

         circle(-60.5,92.5,1);
           circle(-59.5,92.5,1);
glPopMatrix();


glPushMatrix();
glTranslatef(loontx,loonty,0);
glScalef(loonsx,loonsy,0);

    //airloon
    glColor3ub(255,0,0);
    circle(10,87.5,10);
    polygon(0,87.5,20,87.5,15,70,5,70);
    glColor3ub(0,0,0);
     glColor3ub(255,102,0);
    circle(7,87.5,5);
 glColor3ub(255,204,0);
    circle(13,87.5,5);
    glColor3ub(255,153,0);
    circle(10,82.5,5);
        glColor3ub(0,0,0);
         polygon(15,70,5,70,5,67.5,15,67.5);
    polygon(13,62.5,7,62.5,7,60,13,60);
    line(13,62.5,13,67.5);
     line(7,62.5,7,67.5);
glPopMatrix();

//HILL
glColor3ub(180, 220, 100);
glBegin(GL_POLYGON);
for(int i = 0; i <= 180; i++)
{
    float angle = i * 3.1416f / 180.0f;
    glVertex2f(-40 + 38 * cos(angle), 0 + 12 * sin(angle));
}
glEnd();
// platform highlight
glColor3ub(200, 235, 120);
glBegin(GL_POLYGON);
for(int i = 0; i <= 180; i++)
{
    float angle = i * 3.1416f / 180.0f;
    glVertex2f(-40 + 36 * cos(angle), 0 + 10 * sin(angle));
}
glEnd();
    //mickey clubhouse

    glColor3f(0,0,0);
    circle(-50,50,9);
    circle(-30,50,9);
    circle(-40,32.5,13);

    //joint
    glColor3ub(0,0,0);
    polygon(-24,2.5,-24,7.5,-12,7.5,-12,2.5);
     //leg
    glColor3ub(255,204,0);
    mickeyLeg(-10,6.25,6.25);
     mickeyLeg(-10,18.75,6.25);
     //body
       glColor3f(1,0,0);
    semiCircle(-40,0,20);
    //window
      glColor3ub(51,204,204);
    circle(-46,7.5,4);
    circle(-34,7.5,4);

    //doofenshmirtz

    glColor3ub(102,0,102);
    polygon(-90,62.5,-80,62.5,-80,60,-88,60);
    polygon(-70,50,-60,50,-62,47.5,-70,47.5);

    glColor3ub(102,102,153);
    polygon( -90,20,-90,50,-70,50,-70,20);
    polygon(-90,62.5,-90,75,-66,75,-70,62.5);
    polygon(-80,62.5,-58,62.5,-60,50,-80,50);

    glColor3ub(153,153,255);
    semiCircle(-78,75,12);
    glColor3ub(128,0,128);
    semiCircle(-78,75,4);

    //background grass
   glColor3ub(100, 160, 40);
polygon(-100,0,100,0,100,-50,-100,-50);



    //footpath
 glColor3ub(0,0,0);
    polygon(-100,-95,100,-95,100,-100,-100,-100);

//far city
glColor3ub(130, 140, 155);
polygon(30, 20,30, 37.5,40, 37.5,40,20);
polygon(40,20,40,50,50,50,50,20);
polygon(50,20,50,30,60,30,60,20);
polygon(60,20,60,62.5,70,62.5,70,20);
polygon(70,20,70,37.5,80,37.5,80,20);
polygon(80,20,80,50,90,50,90,20);
polygon(90,20,90,62.5,100,62.5,100,20);

//back trees
glColor3ub(20, 110, 20);
circle(-90,12.5,12.5);
circle(-70,12.5,12.5);
circle(10,12.5,12.5);
circle(30,12.5,12.5);
circle(50,12.5,12.5);
circle(70,12.5,12.5);
circle(90,12.5,12.5);

glColor3ub(100, 175, 40);

circle(-80,16,10);
circle(20,16,10);
circle(40,16,10);
circle(60,16,10);
circle(80,16,10);

glColor3ub(50, 140, 30);

circle(-100,9,10);
circle(-90,9,10);
circle(-80,9,10);
circle(-70,9,10);
circle(20,9,10);
circle(30,9,10);
circle(40,9,10);
circle(50,9,10);
circle(60,9,10);
circle(70,9,10);
circle(80,9,10);
circle(90,9,10);

//lines
glColor3f(0,0,0);
dda(-100,100,0,0);

glColor3ub(0,0,0);
polygon(-100,-52.5,-100,-50,100,-50,100,-52.5);

//london street lamp
//light
glColor3ub(238,201,0);
circle(-95,5,5);
//body
glColor3ub(0,0,0);
polygon(-100,-50,-90,-50,-90,-47.5,-100,-47.5);
polygon(-99,-47.5,-99,-45,-91,-45,-91,-47.5);
polygon(-98,-45,-98,-42.5,-92,-42.5,-92,-45);
polygon(-97,-42.5,-93,-42.5,-94,-12.5,-96,-12.5);
circle(-95,-25,3);
polygon(-97,-12.5,-93,-12.5,-93,-10,-97,-10);
polygon(-96,-10,-96,-5,-94,-5,-94,-10);
circle(-95,-7.5,2);
polygon(-97,-5,-97,-2.5,-93,-2.5,-93,-5);
polygon(-98,-2.5,-98,0,-92,0,-92,-2.5);




//powerpuff house
glColor3ub(192,192,192);
polygon(-10,-50,-10,-25,0,-12.5,0,-50);
polygon(20,-12.5,20,0,30,12.5,30,-12.5);

glColor3ub(245, 245, 255);
polygon(0,-50,0,-12.5,30,-12.5,30,-50);
polygon(30,-50,30,12.5,70,12.5,70,-50);
polygon(70,-50,70,-12.5,100,-12.5,100,-50);


//door
glColor3ub(255, 60, 120);
polygon(32,-50,32,-30,40,-30,40,-50);

//window
glColor3ub(128,128,128);
polygon(2,-37.5,2,-25,14,-25,14,-37.5);
polygon(16,-37.5,16,-25,28,-25,28,-37.5);

glColor3ub(0,0,0);
circle(64,0,6);
circle(50,0,6);
circle(36,0,6);

//inner window
glColor3ub(255,255,255);
circle(64,0,5.5);
circle(50,0,5.5);
circle(36,0,5.5);
glColor3ub(128,128,128);
circle(64,0,4.5);
circle(50,0,4.5);
circle(36,0,4.5);


polygon(50,-20,70,-20,70,-37.5,50,-37.5);

glColor3ub(192,192,192);
polygon(70,-50,70,-20,98,-20,98,-50);

glColor3ub(128,128,128);
line(30,-50,30,12.5);
line(70,-50,70,-12.5);
line(74,-30,94,-30);
line(74,-40,94,-40);


glPushMatrix();
glTranslatef(jumptx,jumpty,0.0f);


  //simpson
//head
glColor3ub(255,204,0);
polygon(-80,-22.5,-80,-5,-70,-5,-70,-22.5);
polygon(-80,-17.5,-82,-17.5,-82,-15,-80,-15);
triangle(-80,-20,-82,-20,-80,-17.5);
triangle(-80,-5,-80,-2.5,-79,-5);
triangle(-79,-5,-78,-2.5,-77,-5);
triangle(-77,-5,-76,-2.5,-75,-5);
triangle(-75,-5,-74,-2.5,-73,-5);
triangle(-73,-5,-72,-2.5,-71,-5);
triangle(-71,-5,-70,-2.5,-70,-5);
circle(-69,-18.75,1);
polygon(-78,-25,-78,-22.5,-70,-22.5,-70,-25);
glColor3ub(255,255,255);
circle(-80,-12.5,2);
circle(-76,-12.5,2);
glColor3ub(0,0,0);
circle(-80,-12.5,.5);
circle(-76,-12.5,.5);
glColor3ub(255,153,0);
line(-82,-20,-76,-20);


//body
glColor3ub(255,69,0);
polygon(-78,-30,-80,-37.5,-68,-37.5,-69,-30);
polygon(-78,-25,-78,-30,-70,-30,-70,-25);
triangle(-78,-25,-80,-30,-78,-30);
triangle(-69,-30,-70,-27.5,-70,-30);
glColor3ub(0,0,0);
line(-73, -30,-72, -27.5);
line(-69, -30,-73, -30);
line(-69, -30,-70, -27.5);
glColor3ub(255,204,0);
triangle(-80, -37.5,-80, -30,-78,-30);
polygon(-72, -30,-72, -37.5,-70,-37.5,-70,-30);
//pant
glColor3ub(0,154,205);
polygon(-80,-37.5,-68,-37.5,-70,-45,-80,-45);
glColor3ub(16,78,139);
line(-80,-37.5,-74,-42.5);
line(-74,-42.5,-74,-45);
glColor3ub(255,204,0);
polygon(-78, -45,-78, -50,-76, -50,-76, -45);
polygon(-72, -45,-72, -50,-70, -50,-70, -45);
glColor3ub(0,154,205);
polygon(-80, -47.5,-80, -50,-76, -50,-76,-47.5);
polygon(-74,-47.5,-74,-50,-70,-50,-70,-47.5);


//professor

//shoe
glColor3ub(0,0,0);
polygon(-50,-50,-47,-47.5,-46,-47.5,-48,-50);
polygon(-46,-50,-46,-47.5,-44,-47.5,-44,-50);
polygon(-42,-50,-44,-47.5,-43,-47.5,-40,-50);
//leg
polygon(-48,-40,-48,-47.5,-42,-47.5,-42,-40);
//apron
glColor3ub(255,255,255);
polygon(-50,-40,-50,-20,-40,-20,-40,-40);
polygon(-50,-20,-52,-20,-54,-27.5,-50,-27.5);
polygon(-54,-27.5,-50,-27.5,-50,-32.5,-54,-27.5);
polygon(-40,-20,-38,-20,-34,-27.5,-40,-25);
triangle(-40,-25,-38,-27.5,-34,-27.5);
polygon(-40,-30,-38,-27.5,-34,-27.5,-38,-32.5);
glColor3ub(0,0,0);
line(-50, -40,-50, -22.5);
//hand
glColor3ub(255,204,153);
triangle(-38, -32.5,-40, -32.5,-40, -30);
//shirt
glColor3ub(255,255,255);
triangle(-48,-17.5,-46,-20,-48,-20);
triangle(-42,-17.5,-46,-20,-42,-20);
glColor3ub(0,0,0);
polygon(-47,-22.5,-46,-20,-45,-22.5,-46,-25);
line(-48,-20,-46,-25);
line(-42,-20,-46,-25);
//head
glColor3ub(255,204,153);
polygon(-50,-17.5,-42,-17.5,-42,-5,-50,-5);
polygon(-42,-12.5,-40,-12.5,-40,-5,-42,-5);
triangle(-48,-17.5,-46,-20,-42,-17.5);

//hair
glColor3ub(0,0,0);
polygon(-50,-5,-40,-5,-46,-8.75,-50,-7.5);
triangle(-52,-5,-50,-7.5,-50,-5);
triangle(-42,-8.75,-40,-5,-40,-10);
//face
glColor3ub(0,0,0);
line(-47,-17.5,-44,-15);
line(-47,-17.5,-47,-15);
line(-48, -15,-47, -15);
line(-48, -15,-48, -10);
line(-50, -12.5,-48, -10);
line(-46, -10,-44, -12.5);
line(-49.5, -12.5,-48.5, -12.5);
line(-46, -12.5,-45, -12.5);

//tongue
glColor3ub(255,0,0);
triangle(-44,-17.5,-46,-17.5,-44,-15);
glPopMatrix();
  //road
    glColor3ub(150,150,150);
    polygon(-100,-50,100,-50,100,-95,-100,-95);

    //road divider
     glColor3ub(255,255,255);
    polygon(-100,-75,-80,-75,-80,-70,-100,-70);
    polygon(-60,-75,-40,-75,-40,-70,-60,-70);
    polygon(-20,-75,0,-75,0,-70,-20,-70);
    polygon(20,-75,40,-75,40,-70,20,-70);
    polygon(60,-75,80,-75,80,-70,60,-70);

    //3D
glMatrixMode(GL_PROJECTION);
glPushMatrix();
glLoadIdentity();
glOrtho(-100, 100, -100, 100, -100, 100);

glMatrixMode(GL_MODELVIEW);
glPushMatrix();
glLoadIdentity();

glTranslatef(5, -4, 0);
glRotatef(50, .5, .5, 0);

brick3D();

glPopMatrix();
glMatrixMode(GL_PROJECTION);
glPopMatrix();
glMatrixMode(GL_MODELVIEW);

glColor3ub(0,0,0);
dda(-100,100,-50,-50);
   //simpsons car
     glPushMatrix();
     glTranslatef(scartx, 0.0f, 0.0f);
     //body
     glColor3ub(255, 110, 180);
     polygon(32, -67.5, 96, -67.5, 96, -55, 32, -55);
     //side part
     glColor3ub(191, 239, 255);
     polygon(30, -67.5, 32, -67.5, 32, -55, 30, -55);
     polygon(96, -67.5, 98, -67.5, 98, -55, 96, -55);
     //upper body
     glColor3ub(255, 110, 180);
     polygon(44, -55, 86, -55, 80, -42.5, 54, -42.5);
     //left window
     glColor3ub(224, 255, 255);
     polygon(46, -55, 64, -55, 64, -45, 54, -45);
     //right window
     polygon(68, -55, 84, -55, 78, -45, 68, -45);
     //left door
     glColor3ub(238, 106, 167);
     polygon(46, -65, 84, -65, 84, -55, 46, -55);
     glColor3ub(255, 110, 180);
     semiCircle(43, -67.5, 8);//left
     semiCircle(87, -67.5, 8);//right
     //door divider
     glColor3ub(50, 10, 50);
     line(66, -42.5, 66, -65);
     //door handle
     glColor3ub(130, 130, 130);
     polygon(60, -58.75, 64, -58.75, 64, -56.25, 60, -56.25);
     polygon(78, -58.75, 82, -58.75, 82, -56.25, 78, -56.25);
     //headlight
     glColor3ub(173, 216, 230);
     polygon(28, -67.5, 34, -67.5, 34, -62.5, 28, -62.5);
     //left tire
     //shade
     glColor3ub(64, 64, 64);
     semiCircle(43, -67.5, 7);
     glColor3ub(99, 99, 99);
     circle(43, -67.5, 5);
     glColor3ub(191, 239, 255);
     circle(43, -67.5, 2.5);
     //right tire
     //shade
     glColor3ub(64, 64, 64);
     semiCircle(87, -67.5, 7);
     glColor3ub(99, 99, 99);
     circle(87, -67.5, 5);
     glColor3ub(191, 239, 255);
     circle(87, -67.5, 2.5);
     //door line
     glColor3ub(250, 220, 250);
     line(34, -57.5, 42, -57.5);
     glPopMatrix();

    glPushMatrix();
glTranslatef(cartx,carty,0);
//hotwheels
//body
glColor3ub(51,51,51);
polygon(-80,-80,-70,-80,-70,-92.5,-80,-92.5);
polygon(-42,-90,-42,-77.5,-32,-77.5,-32,-90);
glColor3ub(0,0,0);
polygon(-50, -70,-46, -70,-46, -75,-50, -75);
polygon(-44, -70,-40, -70,-40, -77.5,-44, -77.5);
polygon(-38, -70,-34, -70, -34, -77.5, -38, -77.5);

glColor3ub(0,204,255);
glBegin(GL_POLYGON);
glVertex2f(-70,-95);
glVertex2f(-46,-95);
glVertex2f(-46,-92.5);
glVertex2f(-44,-92.5);
glVertex2f(-44,-90);
glVertex2f(-42,-90);
glVertex2f(-42,-87.5);
glVertex2f(-40,-87.5);
glVertex2f(-40,-77.5);
glVertex2f(-46,-77.5);
glVertex2f(-46,-75);
glVertex2f(-52,-75);
glVertex2f(-52,-70);
glVertex2f(-58,-70);
glVertex2f(-58,-67.5);
glVertex2f(-62,-67.5);
glVertex2f(-62,-65);
glVertex2f(-66,-65);
glVertex2f(-66,-62.5);
glVertex2f(-70,-62.5);
glEnd();
glColor3ub(0,102,204);
polygon(-84,-80,-70,-80,-70,-70,-84,-70);
glColor3ub(51,102,255);
polygon(-74,-62.5,-74,-80,-70,-80,-70,-62.5);
polygon(-68,-75,-68, -70,-66,-70,-66,-75);
polygon(-62,-77.5,-66,-77.5,-66,-72.5,-62, -72.5);
polygon(-58,-80,-62,-80,-62,-75,-58,-75);


glColor3ub(0,204,255);
glBegin(GL_POLYGON);
glVertex2f(-84,-72.5);
glVertex2f(-76,-72.5);
glVertex2f(-76,-67.5);
glVertex2f(-78,-67.5);
glVertex2f(-78,-65);
glVertex2f(-80,-65);
glVertex2f(-80,-62.5);
glVertex2f(-84,-62.5);
glEnd();
polygon(-76,-75,-80,-75,-80,-72.5,-76,-72.5);
polygon(-86,-70,-86,-65,-84,-65,-84,-70);

//wheels
//right
glColor3ub(0,0,0);
circle(-32,-87.5,7.5);
glColor3ub(255,255,255);
circle(-32,-87.5,6);
glColor3ub(0,0,0);
circle(-32,-87.5,5);
glColor3ub(255,255,255);
circle(-32,-87.5,4);
glColor3ub(0,0,0);
circle(-32,-87.5,2);
//left
glColor3ub(0,0,0);
circle(-80,-87.5,7.7);
glColor3ub(255,255,255);
circle(-80,-87.5,6);
glColor3ub(0,0,0);
circle(-80,-87.5,5);
glColor3ub(255,255,255);
circle(-80,-87.5,4);
glColor3ub(0,0,0);
circle(-80,-87.5,2);

glColor3ub(255,0,0);
polygon(-64,-95,-64,-92.5,-62,-92.5,-62,-95);
polygon(-58,-95,-58,-92.5,-56,-92.5,-56,-95);
polygon(-52,-95,-52,-92.5,-50,-92.5,-50,-95);

glColor3ub(255,255,0);
polygon(-62,-92.5,-62,-90,-60,-90,-60,-92.5);
polygon(-56,-92.5,-56,-90,-54,-90,-54,-92.5);
polygon(-50,-92.5,-50,-90,-48,-90,-48,-92.5);

glColor3ub(255,255,255);
polygon(-60,-90,-60,-87.5,-58,-87.5,-58,-90);
polygon(-54,-90,-54,-87.5,-52,-87.5,-52,-90);
polygon(-48,-90,-48,-87.5,-46,-87.5,-46,-90);
glPopMatrix();


}

void scene4()
{
    //sky

  glColor3ub(0,0,128);
    polygon(-100,100,100,100,100,0,-100,0);

    //mickey clubhouse

    glColor3f(0,0,0);
    circle(-50,50,9);
    circle(-30,50,9);
    circle(-40,32.5,13);

    //joint
    glColor3ub(0,0,0);
    polygon(-24,2.5,-24,7.5,-12,7.5,-12,2.5);
     //leg
    glColor3ub(255,204,0);
    mickeyLeg(-10,6.25,6.25);
     mickeyLeg(-10,18.75,6.25);
     //body
       glColor3f(1,0,0);
    semiCircle(-40,0,20);
    //window
      glColor3ub(51,204,204);
    circle(-46,7.5,4);
    circle(-34,7.5,4);

    //doofenshmirtz

    glColor3ub(102,0,102);
    polygon(-90,62.5,-80,62.5,-80,60,-88,60);
    polygon(-70,50,-60,50,-62,47.5,-70,47.5);

    glColor3ub(102,102,153);
    polygon( -90,20,-90,50,-70,50,-70,20);
    polygon(-90,62.5,-90,75,-66,75,-70,62.5);
    polygon(-80,62.5,-58,62.5,-60,50,-80,50);

    glColor3ub(153,153,255);
    semiCircle(-78,75,12);
    glColor3ub(128,0,128);
    semiCircle(-78,75,4);

    //background grass
glColor3ub(30, 110, 65);
    polygon(-100,0,100,0,100,-50,-100,-50);



    //footpath
 glColor3ub(0,0,0);
    polygon(-100,-95,100,-95,100,-100,-100,-100);

//far city
glColor3ub(0,0,0);
polygon(30, 20,30, 37.5,40, 37.5,40,20);
polygon(40,20,40,50,50,50,50,20);
polygon(50,20,50,30,60,30,60,20);
polygon(60,20,60,62.5,70,62.5,70,20);
polygon(70,20,70,37.5,80,37.5,80,20);
polygon(80,20,80,50,90,50,90,20);
polygon(90,20,90,62.5,100,62.5,100,20);

//back trees
glColor3ub(30, 110, 65);

circle(-90,12.5,12.5);
circle(-70,12.5,12.5);
circle(10,12.5,12.5);
circle(30,12.5,12.5);
circle(50,12.5,12.5);
circle(70,12.5,12.5);
circle(90,12.5,12.5);

glColor3ub(50, 170, 100);

circle(-80,16,10);
circle(20,16,10);
circle(40,16,10);
circle(60,16,10);
circle(80,16,10);

glColor3ub(60, 200, 120);

circle(-100,9,10);
circle(-90,9,10);
circle(-80,9,10);
circle(-70,9,10);
circle(20,9,10);
circle(30,9,10);
circle(40,9,10);
circle(50,9,10);
circle(60,9,10);
circle(70,9,10);
circle(80,9,10);
circle(90,9,10);

//lines
glColor3f(0,0,0);
dda(-100,100,0,0);
glColor3ub(0,0,0);
polygon(-100,-52.5,-100,-50,100,-50,100,-52.5);

//london street lamp
//light
glColor3ub(238,201,0);
circle(-95,5,5);
//body
glColor3ub(0,0,0);
polygon(-100,-50,-90,-50,-90,-47.5,-100,-47.5);
polygon(-99,-47.5,-99,-45,-91,-45,-91,-47.5);
polygon(-98,-45,-98,-42.5,-92,-42.5,-92,-45);
polygon(-97,-42.5,-93,-42.5,-94,-12.5,-96,-12.5);
circle(-95,-25,3);
polygon(-97,-12.5,-93,-12.5,-93,-10,-97,-10);
polygon(-96,-10,-96,-5,-94,-5,-94,-10);
circle(-95,-7.5,2);
polygon(-97,-5,-97,-2.5,-93,-2.5,-93,-5);
polygon(-98,-2.5,-98,0,-92,0,-92,-2.5);


    //squidward house
    glColor3ub(150,150,150);
    polygon(30,-50,30,-5,68,-5,68,-50);
    polygon(32,-5,32,17.5,68,17.5,68,-5);
    glColor3ub(128,128,128);
    polygon(50,-5,52,-22.5,42,-22.5,44,-5);
      polygon(24,-12.5,30,-12.5,30,-25,24,-25);
    polygon(66,-25,70,-25,70,-12.5,66, -12.5);
    polygon(28,2.5,58,2.5,58,-5,28,-5);
    glColor3ub(102,102,153);
    polygon(42,-22.5,46,-25,54,-25,52,-22.5);
    polygon(54,-25,52,-22.5,50,-5,52,-5);
    polygon(30, -25, 24, -25, 26, -30, 30, -30);
    polygon(66, -25, 70, -25, 72, -27.5, 68, -30);
    polygon(70, -25, 72, -27.5, 72, -12.5, 70, -12.5);
    polygon(62,1.25,58,2.5,58,-5,62,-5);

    glColor3ub(153,153,255);
    circle(36,-12.5,6);
     circle(58,-12.5,6);

      glColor3ub(204,204,255);
    circle(36,-12.5,4);
     circle(58,-12.5,4);

     glColor3ub(139,115,85);
     polygon(44,-50,44,-37.5,56,-37.5,56,-50);
     semiCircle(50,-37.5,6);

      //road

    glBegin(GL_POLYGON);
   glColor3ub(40, 40, 120);
    glVertex2f(-100,-52.5);
    glVertex2f(100,-52.5);

glColor3ub(0,  0,  90);
      glVertex2f(100,-95);
    glVertex2f(-100,-95);

glEnd();
//ferb

//head
glColor3ub(255,204,153);
polygon(-78,-30,-70,-30,-70,-5,-78,-5);
triangle(-80,-25,-78,-22.5,-78,-25);
polygon(-78,-20,-82,-20,-82,-15,-78,-15);
circle(-69,-13.75,1);
glColor3ub(205,179,139);
line(-82,-20,-76,-20);
line(-76,-20,-75,-18.75);

//eye
glColor3ub(255,255,255);
circle(-76,-12.5,2);
glColor3ub(0,0,0);
circle(-76,-12.5,.75);

//hair
glColor3ub(50,205,50);
polygon(-68,-5,-82,-5,-78,-2.5,-70,-2.5);
polygon(-70,-2.5,-68,0,-70,0,-74,-2.5);
polygon(-74,-2.5,-78,0,-82,0,-78,-2.5);
triangle(-78, -5, -80, -7.5,-76,-5);
triangle(-76, -5,-74, -7.5,-72,-5);
triangle(-72, -5,-72, -7.5,-70,-5);

//shirt
glColor3ub(228,232,170);
polygon(-82,-35,-80,-30,-70,-30,-68,-35);
triangle(-76, -35,-75, -37.5,-74,-35);
glColor3ub(255,255,255);
polygon(-80,-30,-78,-32.5,-75,-31.25,-75,-30);
polygon(-75,-31.25,-75,-30,-70,-30,-72,-32.5);
glColor3ub(228,232,170);
triangle(-82,-35,-80,-30,-80,-35);
triangle(-70,-35,-68,-35, -70,-30);

//pants
glColor3ub(125,38,205);
polygon(-75, -37.5 ,-76, -35,-80,-35,-80,-37.5);
polygon(-74,-35,-70,-35,-70,-37.5,-75,-37.5);
polygon(-80,-37.5,-70,-37.5,-70,-45,-80,-45);
polygon(-78,-45,-76,-45,-76,-50,-78,-50);
polygon(-72,-45,-70,-45,-70,-50,-72,-50);

//shoe
glColor3ub(0,0,0);
polygon(-80,-47.5,-76,-47.5,-76,-50,-80,-50);
polygon(-74,-47.5,-70,-47.5,-70,-50,-74,-50);

//hand
glColor3ub(255,204,153);
triangle(-82,-35,-80,-35,-80,-40);
triangle(-70,-35,-68,-35, -70,-40);

glPushMatrix();
glTranslatef(submarinetx,submarinety-2.5, 0.0f);
    //submarine
     glColor3ub(255,153,0);
polygon(60,-65,70,-65,70,-70,60,-75);
polygon(70,-75,72,-75,72,-80,70,-80);
polygon(60,-85,30,-85,30,-87.5,60,-87.5);
polygon(30,-67.5,30,-87.5,25,-87.5,22,-67.5);

    glColor3ub(255,204,0);
polygon(46,-52.5,46,-60,44,-60,44,-52.5);
polygon(40,-55,40,-52.5,44,-52.5,44,-55);
polygon(40,-67.5,40,-60,50,-60,54,-67.5);
polygon(60,-85,30,-85,30,-67.5,60,-67.5);
polygon(74, -73.75,75,-70,76,-73.75,75,-77.5);
polygon(74,-83.75,75,-80,76,-83.75,75,-87.5);

glColor3ub(255,204,0);
polygon(70,-75,60,-67.5,60,-80,70,-80);
    glColor3ub(0,128,128);
polygon(40,-62.5,46,-62.5,46,-67.5,40,-67.5);
 glColor3ub(255,102,0);
polygon(72,-80,76,-80,76,-77.5,72,-77.5);
midpointCircle(36,-75,4);
midpointCircle(46,-75,4);
midpointCircle(56,-75,4);
triangle(62,-80,64,-87.5,64,-80);
polygon(70,-82.5,64,-82.5,64,-87.5,70,-87.5);
glColor3ub(0,128,128);
circle(36,-75,3.5);
circle(46,-75,3.5);
circle(56,-75,3.5);
glColor3ub(255,153,0);
circle(32,-82.5,1);
circle(36,-82.5,1);
circle(40,-82.5,1);
circle(44,-82.5,1);
circle(48,-82.5,1);
circle(52,-82.5,1);
circle(56,-82.5,1);
glPopMatrix();

//patrick house
glColor3ub(180, 50, 30);
semiCircle(0,-50,20);
glColor3ub(255,215,0);
polygon(8,-25,-6,-25,-6,-22.5,8,-22.5);
triangle(-10,-25,-6,-25,-6,-22.5);
triangle(-10,-25,-4,-20,-6,-22.5);
triangle(-10,-25,-4,-27.5,-6,-25);
line(0,-30,0,-25);

//phineas

//body
glColor3ub(255,204,0);
polygon(-56,-30,-52,-25,-48,-25,-44,-30);
glColor3ub(255,153,0);
polygon(-46,-35,-46,-30,-52,-30,-54,-35);
glColor3ub(255,204,0);
polygon(-54,-35,-56,-37.5,-46,-37.5,-46,-35);
//neck
glColor3ub(255,153,0);
circle(-50,-25,2);



//head
glColor3ub(255,204,153);
triangle(-60,-20,-50,-12.5,-50,-25);
//hair
glColor3ub(255,102,0);
glBegin(GL_POLYGON);
glVertex2f(-50,-12.5);
glVertex2f(-52,-10);
glVertex2f(-50,-10);
glVertex2f(-50,-7.5);
glVertex2f(-48,-10);
glVertex2f(-46,-10);
glVertex2f(-48,-12.5);
glEnd();
triangle(-48,-12.5,-50,-12.5,-48,-15);

//eyes
glColor3ub(255,255,255);
circle(-54,-15,2);
glColor3ub(0,0,0);
circle(-54,-15,1);


//hand
glColor3ub(255,204,153);
triangle(-46,-30,-44,-30,-46,-35);
polygon(-56,-30,-56,-37.5,-54,-35,-54,-30);
//pants
glColor3ub(51,51,153);
polygon(-56,-42.5,-56,-37.5,-46,-37.5,-46,-42.5);
glColor3ub(0,0,0);
line(-50,-40,-50,-42.5);
//legs
glColor3ub(255,204,153);
polygon(-54,-42.5,-54,-50,-52,-50,-52,-42.5);
polygon(-48,-42.5,-48,-50,-46,-50,-46,-42.5);
//shoes
glColor3ub(0,102,204);
polygon(-52,-50,-52,-47.5,-56,-47.5,-56,-50);
polygon(-46,-50,-46,-47.5,-50,-47.5,-50,-50);



glPushMatrix();
glTranslatef(spongebobtx, spongebobty, 0.0f);
//spongebob

//head
glColor3ub(255,204,0);
polygon(10,87.5,50,87.5,50,50,10,50);

//eye
glColor3ub(255,225,255);
circle(24,75,5);
glColor3ub(135,206,250);
circle(24,75,3);
glColor3ub(0,0,0);
circle(24,75,1);

glColor3ub(255,225,255);
circle(36,75,5);
glColor3ub(135,206,250);
circle(36,75,3);
glColor3ub(0,0,0);
circle(36,75,1);

//blush
glColor3ub(255,69,0);
semiCircle(20,67.5,2);
semiCircle(40,67.5,2);

glColor3ub(0,0,0);
//smile
line(40, 67.5,36, 62.5);
line(20, 67.5, 24, 62.5);

//nose
line(28, 66.25, 28, 70);
line(32, 70, 28, 70);
line(32, 66.25, 32, 70);

//teeth
glColor3ub(255,255,255);
polygon(24,62.5,28,62.5,28,57.5,24,57.5);
polygon(32,62.5,36,62.5,36,57.5,32,57.5);
glColor3b(0,0,0);
line(24,62.5,36,62.5);

//Body
glColor3ub(255,255,255);
polygon(10,50,50,50,50,42.5,10,42.5);
glColor3ub(0,0,0);
midLine(10,50,42.5,42.5);
midLine(10,50,50,50);
//pant
glColor3ub(101, 55, 0);
polygon(10,42.5,50,42.5,50,37.5,10,37.5);

//tie
glColor3ub(255,255,255);
triangle(20,50,24,46.125 ,28,50);
triangle(32,50,36,46.125,40,50);
glColor3ub(255,0,0);
polygon(28,50,32,50,32,47.5,28,47.5);
polygon(28,47.5,32,47.5,33,42.5,27,42.5);
triangle(27,42.5,33,42.5,30,37.5);
glColor3ub(0,0,0);
line(20, 50,24, 46.125);
line(24, 46.125,28, 50);
line(32, 50,36, 46.125);
line(36, 46.125,40, 50);
line(28,47.5,32,47.5);

glPopMatrix();

//bubbles
glPushMatrix();
glTranslatef(bubbletx,bubblety,0.0f);
glColor3ub(191,239,255);

circle(-90,-130,2);
circle(-70,-150,2);
circle(-70,50,2);
circle(100,-120,2);
circle(50,-10,2);
circle(30,60,2);
circle(-10,-10,2);
circle(-30,30,2);
circle(0,50,2);
circle(-30,-160,2);
circle(-90,0,2);
circle(-60,10,2);
circle(20,-50,2);
circle(70,0,2);
circle(80,75,2);
circle(-50,60,2);
circle(80,-70,2);
circle(0,-90,2);
circle(-90,-50,2);
circle(-70,-70,2);
circle(-90,90,2);
circle(-30,90,2);
circle(70,-130,2);
circle(50,-150,2);
glPopMatrix();
}
void rain()
{
    srand(42);
    for(int i = 0; i < 200; i++)
    {
        rainX[i] = -120.0f + (rand() % 240);   // spread wider than screen
        rainY[i] = -100.0f + (rand() % 200);   // spread full height
    }
    rainInitialized = true;
}




void snow()
{
    srand(123);
    for(int i = 0; i < 300; i++)
    {
        snowX[i] = -120.0f + (rand() % 260);
        snowY[i] = -100.0f + (rand() % 220);
    }
    snowInitialized = true;
}

void drawSnow()
{
    if(!snowInitialized) snow();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //big close flakes
    glPushMatrix();
    glTranslatef(snowDriftOffset * 0.3f, snowOffset, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glPointSize(4.5f);
    glBegin(GL_POINTS);
    for(int i = 0; i < 80; i++)
        glVertex2f(snowX[i], snowY[i]);
    glEnd();
    glPopMatrix();

    // medium flakes
    glPushMatrix();
    glTranslatef(snowDriftOffset * 0.5f, snowOffset * 0.75f, 0.0f);
    glColor4ub(240, 248, 255, 230);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for(int i = 80; i < 180; i++)
        glVertex2f(snowX[i], snowY[i]);
    glEnd();
    glPopMatrix();

    // small distant flake
    glPushMatrix();
    glTranslatef(snowDriftOffset * 0.8f, snowOffset * 0.5f, 0.0f);
    glColor4ub(220, 235, 255, 180);
    glPointSize(1.8f);
    glBegin(GL_POINTS);
    for(int i = 180; i < 300; i++)
        glVertex2f(snowX[i], snowY[i]);
    glEnd();
    glPopMatrix();

    glPointSize(1.0f);
    glDisable(GL_BLEND);
}


void scene5()
{

   //sky
    // upper sky
    glBegin(GL_POLYGON);
    glColor3ub(80, 90, 105);
    glVertex2f(-100, 100);
    glVertex2f(100, 100);
    glColor3ub(110, 120, 135);
    glVertex2f(100, 50);
    glVertex2f(-100, 50);
    glEnd();

    // lower sky
    glBegin(GL_POLYGON);
    glColor3ub(110, 120, 135);
    glVertex2f(-100, 50);
    glVertex2f(100, 50);
    glColor3ub(160, 165, 170);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glEnd();

    //sun

    // outer glow
    glColor3ub(190, 185, 165);
    circle(65, 78, 10);
    // mid glow
    glColor3ub(205, 198, 175);
    circle(65, 78, 7);
    // inner pale disc
    glColor3ub(220, 212, 190);
    circle(65, 78, 4.5);



    //clouds
   glPushMatrix();
glTranslatef(cloudx, cloudy, 0.0f);


 glColor3ub(40, 40, 50);
    circle(-110, 85, 8);
    circle(-118, 85, 6);
    circle(-102, 85, 6);
    circle(-115, 90, 5);
    circle(-107, 90, 5);
    circle(-110, 93, 4);
    // highlight
    glColor3ub(65, 65, 75);
    circle(-110, 90, 2);


    glColor3ub(45, 45, 58);
    circle(-95, 78, 7);
    circle(-103, 78, 5);
    circle(-87,  78, 5);
    circle(-100, 82, 4);
    circle(-92,  82, 4);
    circle(-95,  85, 3);
    // highlight
    glColor3ub(70, 70, 80);
    circle(-95, 82, 2);


    glColor3ub(50, 50, 60);
    circle(-60, 87.5, 6);
    circle(-66, 87.5, 5);
    circle(-54, 87.5, 5);
    circle(-63, 91.0, 4);
    circle(-57, 91.0, 4);
    circle(-60, 93.5, 3);
    // highlight
    glColor3ub(75, 75, 85);
    circle(-60, 90, 2);


    glColor3ub(42, 42, 54);
    circle(-38, 82, 8);
    circle(-46, 82, 5);
    circle(-30, 82, 5);
    circle(-42, 87, 4);
    circle(-34, 87, 4);
    circle(-38, 90, 3);
    // highlight
    glColor3ub(68, 68, 78);
    circle(-38, 87, 2);


    glColor3ub(45, 45, 55);
    circle(-20, 78,  10);
    circle(-30, 78,   7);
    circle(-10, 78,   7);
    circle(-26, 83,   6);
    circle(-14, 83,   6);
    circle(-20, 87,   5);
    // highlight
    glColor3ub(72, 72, 82);
    circle(-20, 84, 3);


    glColor3ub(48, 48, 60);
    circle(12, 84, 7);
    circle( 5, 84, 5);
    circle(19, 84, 5);
    circle( 8, 88, 4);
    circle(16, 88, 4);
    circle(12, 91, 3);
    // highlight
    glColor3ub(73, 73, 83);
    circle(12, 88, 2);


    glColor3ub(55, 55, 65);
    circle(40, 83,  8);
    circle(48, 83,  5);
    circle(32, 83,  5);
    circle(44, 87,  4);
    circle(36, 87,  4);
    circle(40, 90,  3);
    // highlight
    glColor3ub(78, 78, 88);
    circle(40, 87, 2);


    glColor3ub(43, 43, 55);
    circle(85, 80, 9);
    circle(76, 80, 6);
    circle(94, 80, 6);
    circle(80, 85, 5);
    circle(90, 85, 5);
    circle(85, 88, 4);
    // highlight
    glColor3ub(68, 68, 78);
    circle(85, 85, 2);


    glColor3ub(40, 40, 52);
    circle(108,  83, 8);
    circle(100,  83, 5);
    circle(116,  83, 5);
    circle(104,  87, 4);
    circle(112,  87, 4);
    circle(108,  90, 3);
    // highlight
    glColor3ub(65, 65, 75);
    circle(108, 87, 2);


    glColor4ub(174, 214, 241, 140);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.0f);
    glBegin(GL_LINES);

    // under cloud 1 (off screen left)
    glVertex2f(-114, 80.0f);  glVertex2f(-114.8f, 76.5f);
    glVertex2f(-110, 79.0f);  glVertex2f(-110.8f, 75.5f);
    glVertex2f(-106, 80.0f);  glVertex2f(-106.8f, 76.5f);

    // under cloud 2
    glVertex2f(-99,  73.5f);  glVertex2f(-99.8f,  70.0f);
    glVertex2f(-95,  72.5f);  glVertex2f(-95.8f,  69.0f);
    glVertex2f(-91,  73.5f);  glVertex2f(-91.8f,  70.0f);

    // under cloud 3
    glVertex2f(-64,  83.5f);  glVertex2f(-64.8f,  80.0f);
    glVertex2f(-60,  82.5f);  glVertex2f(-60.8f,  79.0f);
    glVertex2f(-56,  83.5f);  glVertex2f(-56.8f,  80.0f);

    // under cloud 4
    glVertex2f(-42,  77.5f);  glVertex2f(-42.8f,  74.0f);
    glVertex2f(-38,  76.5f);  glVertex2f(-38.8f,  73.0f);
    glVertex2f(-34,  77.5f);  glVertex2f(-34.8f,  74.0f);

    // under cloud 5
    glVertex2f(-28,  72.0f);  glVertex2f(-28.8f,  68.5f);
    glVertex2f(-22,  71.0f);  glVertex2f(-22.8f,  67.5f);
    glVertex2f(-16,  71.5f);  glVertex2f(-16.8f,  68.0f);
    glVertex2f(-12,  72.0f);  glVertex2f(-12.8f,  68.5f);

    // under cloud 6
    glVertex2f(  8,  79.5f);  glVertex2f(  7.2f,  76.0f);
    glVertex2f( 12,  78.5f);  glVertex2f( 11.2f,  75.0f);
    glVertex2f( 16,  79.5f);  glVertex2f( 15.2f,  76.0f);

    // under cloud 7
    glVertex2f( 34,  78.5f);  glVertex2f( 33.2f,  75.0f);
    glVertex2f( 40,  77.5f);  glVertex2f( 39.2f,  74.0f);
    glVertex2f( 46,  78.5f);  glVertex2f( 45.2f,  75.0f);

    // under cloud 8
    glVertex2f( 80,  75.5f);  glVertex2f( 79.2f,  72.0f);
    glVertex2f( 85,  74.5f);  glVertex2f( 84.2f,  71.0f);
    glVertex2f( 90,  75.5f);  glVertex2f( 89.2f,  72.0f);

    // under cloud 9 (off screen right)
    glVertex2f(104,  78.5f);  glVertex2f(103.2f,  75.0f);
    glVertex2f(108,  77.5f);  glVertex2f(107.2f,  74.0f);
    glVertex2f(112,  78.5f);  glVertex2f(111.2f,  75.0f);

    glEnd();
    glDisable(GL_BLEND);



glPopMatrix();


//london eye
// LONDON EYE


    float cx = -30.0f;   // wheel center x
    float cy = 20.0f;    // wheel center y
    float r  = 30.0f;    // outer radius

    // bottom frame
    glColor3ub(160, 158, 150);
    // left leg
    glBegin(GL_POLYGON);
    glVertex2f(cx - 3,  cy - r + 5);
    glVertex2f(cx - 18, cy - r - 18);
    glVertex2f(cx - 16, cy - r - 18);
    glVertex2f(cx - 1,  cy - r + 5);
    glEnd();
    // right leg
    glBegin(GL_POLYGON);
    glVertex2f(cx + 1,  cy - r + 5);
    glVertex2f(cx + 16, cy - r - 18);
    glVertex2f(cx + 18, cy - r - 18);
    glVertex2f(cx + 3,  cy - r + 5);
    glEnd();
    // leg base bar
    glColor3ub(140, 138, 130);
    polygon(cx - 19, cy - r - 18,
            cx + 19, cy - r - 18,
            cx + 19, cy - r - 20,
            cx - 19, cy - r - 20);

    // hub shaft
    glColor3ub(150, 148, 140);
    polygon(cx - 2, cy - r + 5,
            cx + 2, cy - r + 5,
            cx + 2, cy - r - 2,
            cx - 2, cy - r - 2);

    //outer rim
    glColor3ub(180, 178, 165);

    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
    // cut inner hole
    glColor3ub(110, 120, 135);  // sky color to cutout
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        glVertex2f(cx + (r - 2.5f) * cos(angle), cy + (r - 2.5f) * sin(angle));
    }
    glEnd();

    // rotating)
    glPushMatrix();
    glTranslatef(cx, cy, 0.0f);
    glRotatef(londonEyeAngle, 0.0f, 0.0f, 1.0f);

    glColor3ub(165, 163, 150);
    glLineWidth(1.2f);
    // 16 spokes
    for(int i = 0; i < 16; i++)
    {
        float angle = i * 3.1416f / 8.0f;
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f((r - 1.5f) * cos(angle), (r - 1.5f) * sin(angle));
        glEnd();
    }
    glLineWidth(1.0f);


    // 16 capsules on the rim, rotate with wheel
    for(int i = 0; i < 16; i++)
    {
        float angle = i * 3.1416f / 8.0f;
        float gx = (r - 1.5f) * cos(angle);
        float gy = (r - 1.5f) * sin(angle);

        // capsule stays upright — counter-rotate
        glPushMatrix();
        glTranslatef(gx, gy, 0.0f);
        glRotatef(-londonEyeAngle, 0.0f, 0.0f, 1.0f);

        // capsule body
        glColor3ub(210, 230, 245);
        glBegin(GL_POLYGON);
        for(int j = 0; j < 360; j++)
        {
            float a = j * 3.1416f / 180.0f;
            glVertex2f(2.2f * cos(a), 1.2f * sin(a));
        }
        glEnd();
        // capsule outline
        glColor3ub(160, 158, 150);
        glBegin(GL_LINE_LOOP);
        for(int j = 0; j < 360; j++)
        {
            float a = j * 3.1416f / 180.0f;
            glVertex2f(2.2f * cos(a), 1.2f * sin(a));
        }
        glEnd();
        // capsule window
        glColor3ub(180, 210, 235);
        glBegin(GL_POLYGON);
        for(int j = 0; j < 360; j++)
        {
            float a = j * 3.1416f / 180.0f;
            glVertex2f(1.4f * cos(a), 0.7f * sin(a));
        }
        glEnd();

        glPopMatrix();
    }

    glPopMatrix(); // end rotating group


    glColor3ub(180, 178, 165);
    circle(cx, cy, 3.5f);
    glColor3ub(160, 158, 150);
    circle(cx, cy, 2.5f);
    glColor3ub(200, 198, 185);
    circle(cx, cy, 1.5f);

//grass ,fence and stone footpath
    // stone embankment wall (replaces river)
    glColor3ub(150, 143, 128);
    polygon(-100, -50, 100, -50, 100, -43, -100, -43);
    // embankment highlight top edge
    glColor3ub(170, 163, 148);
    polygon(-100, -43, 100, -43, 100, -42, -100, -42);
    // embankment shadow bottom edge
    glColor3ub(120, 113, 98);
    polygon(-100, -50, 100, -50, 100, -49, -100, -49);
    // embankment stone lines (vertical joints)
    glColor3ub(130, 123, 108);
    line(-80, -50, -80, -43);
    line(-60, -50, -60, -43);
    line(-40, -50, -40, -43);
    line(-20, -50, -20, -43);
    line(0, -50, 0, -43);
    line(20, -50, 20, -43);
    line(40, -50, 40, -43);
    line(60, -50, 60, -43);
    line(80, -50, 80, -43);

    // main grass field
    glColor3ub(34, 85, 45);
    polygon(-100, -43, 100, -43, 100, 0, -100, 0);

    // grass colour variation strips (gives depth)
    glColor3ub(40, 95, 50);
    polygon(-100, -43, 100, -43, 100, -38, -100, -38);
    glColor3ub(45, 100, 55);
    polygon(-100, -38, 100, -38, 100, -30, -100, -30);
    glColor3ub(38, 90, 48);
    polygon(-100, -30, 100, -30, 100, -20, -100, -20);
    glColor3ub(42, 95, 52);
    polygon(-100, -20, 100, -20, 100, -10, -100, -10);
    glColor3ub(36, 88, 46);
    polygon(-100, -10, 100, -10, 100, 0, -100, 0);

    // grass highlight along top edge of embankment
    glColor3ub(55, 115, 60);
    polygon(-100, -43, 100, -43, 100, -41, -100, -41);

    // FOOTPATH
    glColor3ub(170, 163, 148);
    polygon(-100, -43, 100, -43, 100, -36, -100, -36);
    // path stone joints horizontal
    glColor3ub(150, 143, 128);
    line(-100, -40, 100, -40);
    // path stone joints vertical
    glColor3ub(150, 143, 128);
    line(-90, -43, -90, -36);
    line(-70, -43, -70, -36);
    line(-50, -43, -50, -36);
    line(-30, -43, -30, -36);
    line(-10, -43, -10, -36);
    line(10, -43, 10, -36);
    line(30, -43, 30, -36);
    line(50, -43, 50, -36);
    line(70, -43, 70, -36);
    line(90, -43, 90, -36);


    // GRASS PATCHES

    glColor3ub(30, 78, 40);
    glPointSize(1.5f);
    glBegin(GL_POINTS);
    // scattered darker grass dots
    float gx[] = {-95,-85,-75,-65,-55,-45,-35,-25,-15,-5,
                   5,  15, 25, 35, 45, 55, 65, 75, 85, 95,
                  -90,-70,-50,-30,-10, 10, 30, 50, 70, 90,
                  -88,-68,-48,-28, -8, 12, 32, 52, 72, 92};
    float gy[] = {-28,-22,-18,-32,-25,-15,-20,-28,-16,-24,
                  -20,-26,-14,-22,-30,-18,-24,-12,-28,-20,
                  -10,-16,-22,-12,-18,-14,-20,-10,-16,-22,
                   -8,-14,-10,-18, -8,-12,-16, -8,-14,-10};
    for(int i = 0; i < 40; i++)
        glVertex2f(gx[i], gy[i]);
    glEnd();
    glPointSize(1.0f);


    // fence base bar
    glColor3ub(30, 30, 30);
    polygon(-100, -36, 100, -36, 100, -35, -100, -35);
    // fence top bar
    polygon(-100, -28, 100, -28, 100, -27, -100, -27);
    // fence posts (vertical spikes)
    for(float fx = -98; fx <= 98; fx += 4.0f)
    {
        glColor3ub(30, 30, 30);
        polygon(fx, -36, fx+1, -36, fx+1, -27, fx, -27);
        // spike tip
        triangle(fx, -27, fx+1, -27, fx+0.5f, -25);
    }


//big ben tower
    //lower bar
    glColor3ub(140, 130, 110);
    polygon(74, -25, 98, -25, 98, -22.5, 74, -22.5);
    //level 1
    glColor3ub(180, 170, 150);
    polygon(76, -22.5, 96, -22.5, 96, -5, 76, -5);
    //window
    glColor3ub(30, 50, 80);
    polygon(78, -20, 80, -20, 80, -15, 78, -15);//lower
    polygon(82, -20, 84, -20, 84, -15, 82, -15);
    polygon(88, -20, 90, -20, 90, -15, 88, -15);
    polygon(92, -20, 94, -20, 94, -15, 92, -15);
    glColor3ub(255, 240, 180);
    polygon(78.5, -19.5, 79.5, -19.5, 79.5, -15.5, 78.5, -15.5);
    polygon(82.5, -19.5, 83.5, -19.5, 83.5, -15.5, 82.5, -15.5);
    polygon(88.5, -19.5, 89.5, -19.5, 89.5, -15.5, 88.5, -15.5);
    polygon(92.5, -19.5, 93.5, -19.5, 93.5, -15.5, 92.5, -15.5);
    glColor3ub(30, 50, 80);
    polygon(78, -12.5, 80, -12.5, 80, -7.5, 78, -7.5);//upper
    polygon(82, -12.5, 84, -12.5, 84, -7.5, 82, -7.5);
    polygon(88, -12.5, 90, -12.5, 90, -7.5, 88, -7.5);
    polygon(92, -12.5, 94, -12.5, 94, -7.5, 92, -7.5);
    glColor3ub(255, 240, 180);
    polygon(78.5, -12, 79.5, -12, 79.5, -8, 78.5, -8);
    polygon(82.5, -12, 83.5, -12, 83.5, -8, 82.5, -8);
    polygon(88.5, -12, 89.5, -12, 89.5, -8, 88.5, -8);
    polygon(92.5, -12, 93.5, -12, 93.5, -8, 92.5, -8);
    //middle bar
    glColor3ub(120, 110, 90);
    polygon(74, -5, 98, -5, 98, -2.5, 74, -2.5);
    //level 2
    glColor3ub(180, 170, 150);
    polygon(76, -2.5, 96, -2.5, 96, 15, 76, 15);
    //window
    glColor3ub(30, 50, 80);
    polygon(78, 0, 80, 0, 80, 5, 78, 5);//lower
    polygon(82, 0, 84, 0, 84, 5, 82, 5);
    polygon(88, 0, 90, 0, 90, 5, 88, 5);
    polygon(92, 0, 94, 0, 94, 5, 92, 5);
    glColor3ub(255, 240, 180);
    polygon(78.5, 0.5, 79.5, 0.5, 79.5, 4.5, 78.5, 4.5);
    polygon(82.5, 0.5, 83.5, 0.5, 83.5, 4.5, 82.5, 4.5);
    polygon(88.5, 0.5, 89.5, 0.5, 89.5, 4.5, 88.5, 4.5);
    polygon(92.5, 0.5, 93.5, 0.5, 93.5, 4.5, 92.5, 4.5);
    glColor3ub(30, 50, 80);
    polygon(78, 7.5, 80, 7.5, 80, 12.5, 78, 12.5);//upper
    polygon(82, 7.5, 84, 7.5, 84, 12.5, 82, 12.5);
    polygon(88, 7.5, 90, 7.5, 90, 12.5, 88, 12.5);
    polygon(92, 7.5, 94, 7.5, 94, 12.5, 92, 12.5);
    glColor3ub(255, 240, 180);
    polygon(78.5, 8, 79.5, 8, 79.5, 12, 78.5, 12);
    polygon(82.5, 8, 83.5, 8, 83.5, 12, 82.5, 12);
    polygon(88.5, 8, 89.5, 8, 89.5, 12, 88.5, 12);
    polygon(92.5, 8, 93.5, 8, 93.5, 12, 92.5, 12);
    //upper bar
    glColor3ub(120, 110, 90);
    polygon(74, 15, 98, 15, 98, 17.5, 74, 17.5);
    //level 3
    glColor3ub(180, 170, 150);
    polygon(76, 17.5, 96, 17.5, 96, 35, 76, 35);
    //window
    glColor3ub(30, 50, 80);
    polygon(78, 20, 80, 20, 80, 25, 78, 25);//lower
    polygon(82, 20, 84, 20, 84, 25, 82, 25);
    polygon(88, 20, 90, 20, 90, 25, 88, 25);
    polygon(92, 20, 94, 20, 94, 25, 92, 25);
    glColor3ub(255, 240, 180);
    polygon(78.5, 20.5, 79.5, 20.5, 79.5, 24.5, 78.5, 24.5);
    polygon(82.5, 20.5, 83.5, 20.5, 83.5, 24.5, 82.5, 24.5);
    polygon(88.5, 20.5, 89.5, 20.5, 89.5, 24.5, 88.5, 24.5);
    polygon(92.5, 20.5, 93.5, 20.5, 93.5, 24.5, 92.5, 24.5);
    glColor3ub(30, 50, 80);
    polygon(78, 27.5, 80, 27.5, 80, 32.5, 78, 32.5);//upper
    polygon(82, 27.5, 84, 27.5, 84, 32.5, 82, 32.5);
    polygon(88, 27.5, 90, 27.5, 90, 32.5, 88, 32.5);
    polygon(92, 27.5, 94, 27.5, 94, 32.5, 92, 32.5);
    glColor3ub(255, 240, 180);
    polygon(78.5, 28, 79.5, 28, 79.5, 32, 78.5, 32);
    polygon(82.5, 28, 83.5, 28, 83.5, 32, 82.5, 32);
    polygon(88.5, 28, 89.5, 28, 89.5, 32, 88.5, 32);
    polygon(92.5, 28, 93.5, 28, 93.5, 32, 92.5, 32);
    //clock lower bar
    glColor3ub(120, 110, 90);
    polygon(74, 35, 98, 35, 98, 40, 74, 40);
    //clock level
    glColor3ub(160, 150, 130);
    polygon(76, 40, 96, 40, 96, 52.5, 76, 52.5);

   // clock
// outer stone frame
glColor3ub(120, 110, 90);
circle(86, 46.25, 6.5);
// gold ring
glColor3ub(180, 150, 50);
circle(86, 46.25, 6.0);
// inner gold ring
glColor3ub(140, 115, 35);
circle(86, 46.25, 5.5);
// cream face
glColor3ub(240, 235, 210);
circle(86, 46.25, 5.0);
// inner detail ring
glColor3ub(180, 150, 50);
circle(86, 46.25, 4.6);
glColor3ub(240, 235, 210);
circle(86, 46.25, 4.2);
// 12 hour marker dots
glColor3ub(20, 20, 20);
glPointSize(2.0f);
glBegin(GL_POINTS);
for(int i = 0; i < 12; i++)
{
    float angle = i * 3.1416f / 6.0f - 3.1416f / 2.0f;
    glVertex2f(86 + 3.6f * cos(angle), 46.25f + 3.6f * sin(angle));
}
glEnd();
glPointSize(1.0f);

// ROTATING HANDS
glPushMatrix();
glTranslatef(86, 46.25, 0.0f);
glRotatef(-bigBenClockAngle, 0.0f, 0.0f, 1.0f);  // minute hand spins
glColor3ub(20, 20, 20);
glLineWidth(1.8f);
// minute hand points up
glBegin(GL_LINES);
glVertex2f(0, 0);
glVertex2f(0, 4.5f);
glEnd();
glPopMatrix();

glPushMatrix();
glTranslatef(86, 46.25, 0.0f);
glRotatef(-bigBenClockAngle * 0.0833f, 0.0f, 0.0f, 1.0f);
glColor3ub(20, 20, 20);
glLineWidth(2.2f);
// hour hand shorter
glBegin(GL_LINES);
glVertex2f(0, 0);
glVertex2f(0, 3.2f);
glEnd();
glPopMatrix();

glLineWidth(1.0f);
// center pin
glColor3ub(180, 150, 50);
circle(86, 46.25, 0.7f);
glColor3ub(20, 20, 20);
circle(86, 46.25, 0.4f);

    //clock upper bar
    glColor3ub(120, 110, 90);
    polygon(74, 52.5, 98, 52.5, 98, 57.5, 74, 57.5);
    //level 4
    glColor3ub(180, 170, 150);
    polygon(76, 57.5, 96, 57.5, 96, 62.5, 76, 62.5);
    //window
    glColor3ub(30, 50, 80);
    polygon(78, 58.5, 80, 58.5, 80, 61.5, 78, 61.5);
    polygon(82, 58.5, 84, 58.5, 84, 61.5, 82, 61.5);
    polygon(88, 58.5, 90, 58.5, 90, 61.5, 88, 61.5);
    polygon(92, 58.5, 94, 58.5, 94, 61.5, 92, 61.5);
    glColor3ub(255, 240, 180);
    polygon(78.5, 59, 79.5, 59, 79.5, 61, 78.5, 61);
    polygon(82.5, 59, 83.5, 59, 83.5, 61, 82.5, 61);
    polygon(88.5, 59, 89.5, 59, 89.5, 61, 88.5, 61);
    polygon(92.5, 59, 93.5, 59, 93.5, 61, 92.5, 61);
    //bar
    glColor3ub(120, 110, 90);
    polygon(74, 62.5, 98, 62.5, 98, 65, 74, 65);
    //level 5
    glColor3ub(180, 170, 150);
    polygon(76, 65, 96, 65, 92, 71, 80, 71);
    //window
    glColor3ub(30, 50, 80);
    polygon(78, 67, 80, 67, 80, 68.5, 78, 68.5);
    polygon(82, 67, 84, 67, 84, 68.5, 82, 68.5);
    polygon(88, 67, 90, 67, 90, 68.5, 88, 68.5);
    polygon(92, 67, 94, 67, 94, 68.5, 92, 68.5);
    //bar
    glColor3ub(120, 110, 90);
    polygon(80, 71, 92, 71, 92, 73.5, 80, 73.5);
    //level 6
    glColor3ub(180, 170, 150);
    polygon(82, 73.5, 90, 73.5, 90, 78.5, 82, 78.5);
    //window
    glColor3ub(30, 50, 80);
    polygon(85, 73.5, 87, 73.5, 87, 76, 85, 76);
    glColor3ub(255, 240, 180);
    polygon(85.3, 73.8, 86.7, 73.8, 86.7, 75.7, 85.3, 75.7);
    //bar
    glColor3ub(120, 110, 90);
    polygon(80, 78.5, 92, 78.5, 92, 81, 80, 81);
    //roof level
    glColor3ub(100, 95, 80);
    polygon(80, 81, 92, 81, 88, 88.5, 84, 88.5);
    // roof highlight
    glColor3ub(120, 115, 95);
    triangle(80, 81, 84, 88.5, 82, 85);
    //stand
    glColor3ub(120, 110, 90);
    polygon(85, 91, 87, 91, 87, 88.5, 85, 88.5);
    // ball replaced with weathervane tip
    glColor3ub(180, 150, 50);
    circle(86, 92.25, 1.5);
    glColor3ub(140, 115, 35);
    circle(86, 92.25, 1.0);


    //westminster palace

    //part 1
    //level 1
    glColor3ub(160, 150, 130);
    polygon(20, -25, 74, -25, 74, -22.5, 20, -22.5);
    polygon(20, -22.5, 76, -22.5, 76, -15, 20, -15);
    //bar
    glColor3ub(120, 110, 90);
    polygon(20, -15, 76, -15, 76, -10, 20, -10);
    //level 2
    glColor3ub(180, 170, 150);
    polygon(20, -5, 76, -5, 76, -10, 20, -10);
    polygon(20, -5, 74, -5, 74, -2.5, 20, -2.5);
    //bar
    glColor3ub(120, 110, 90);
    polygon(20, -2.5, 76, -2.5, 76, 2.5, 20, 2.5);
    //pillar
    glColor3ub(100, 95, 80);
    polygon(26, -25, 30, -25, 30, 7.5, 26, 7.5);//1
    triangle(26, 7.5, 30, 7.5, 28, 10);
    polygon(34, -25, 38, -25, 38, 7.5, 34, 7.5);//2
    triangle(34, 7.5, 38, 7.5, 36, 10);
    polygon(42, -25, 46, -25, 46, 7.5, 42, 7.5);//3
    triangle(42, 7.5, 46, 7.5, 44, 10);
    polygon(50, -25, 54, -25, 54, 7.5, 50, 7.5);//4
    triangle(50, 7.5, 54, 7.5, 52, 10);
    polygon(58, -25, 62, -25, 62, 7.5, 58, 7.5);//5
    triangle(58, 7.5, 62, 7.5, 60, 10);
    polygon(66, -25, 70, -25, 70, 7.5, 66, 7.5);//6
    triangle(66, 7.5, 70, 7.5, 68, 10);

    //part 2
    //left side wall
    glColor3ub(140, 130, 110);
    polygon(-4, -25, 0, -25, 0, 20, -4, 20);
    glColor3ub(160, 150, 130);
    polygon(-3, 20, -1, 20, -1, 22.5, -3, 22.5);
    glColor3ub(120, 110, 90);
    triangle(-4, 22.5, 0, 22.5, -2, 25);
    //right side wall
    glColor3ub(140, 130, 110);
    polygon(16, -25, 20, -25, 20, 20, 16, 20);
    glColor3ub(160, 150, 130);
    polygon(17, 20, 19, 20, 19, 22.5, 17, 22.5);
    glColor3ub(120, 110, 90);
    triangle(16, 22.5, 20, 22.5, 18, 25);
    //middle wall
    glColor3ub(200, 190, 170);
    polygon(0, -25, 16, -25, 16, 12.5, 0, 12.5);
    //level lines
    glColor3ub(140, 130, 110);
    line(0, -25, 16, -25);
    line(0, -12.5, 16, -12.5);
    line(0, 0, 16, 0);
    //bar middle
    glColor3ub(160, 150, 130);
    polygon(7, -25, 9, -25, 9, 12.5, 7, 12.5);
    //windows
    glColor3ub(30, 50, 80);
    polygon(1, -25, 5, -25, 5, -20, 1, -20);//1(left)
    triangle(1, -20, 5, -20, 3, -17.5);
    polygon(11, -25, 15, -25, 15, -20, 11, -20);//1(right)
    triangle(11, -20, 15, -20, 13, -17.5);
    polygon(1, -12.5, 5, -12.5, 5, -7.5, 1, -7.5);//2(left)
    triangle(1, -7.5, 5, -7.5, 3, -5);
    polygon(11, -12.5, 15, -12.5, 15, -7.5, 11, -7.5);//2(right)
    triangle(11, -7.5, 15, -7.5, 13, -5);
    polygon(1, 0, 5, 0, 5, 5, 1, 5);//3(left)
    triangle(1, 5, 5, 5, 3, 7.5);
    polygon(11, 0, 15, 0, 15, 5, 11, 5);//3(right)
    triangle(11, 5, 15, 5, 13, 7.5);
    // window glow
    glColor3ub(255, 240, 180);
    polygon(1.5, -24.5, 4.5, -24.5, 4.5, -20.5, 1.5, -20.5);
    polygon(11.5, -24.5, 14.5, -24.5, 14.5, -20.5, 11.5, -20.5);
    polygon(1.5, -12, 4.5, -12, 4.5, -8, 1.5, -8);
    polygon(11.5, -12, 14.5, -12, 14.5, -8, 11.5, -8);
    polygon(1.5, 0.5, 4.5, 0.5, 4.5, 4.5, 1.5, 4.5);
    polygon(11.5, 0.5, 14.5, 0.5, 14.5, 4.5, 11.5, 4.5);
    //roof
    glColor3ub(100, 95, 80);
    polygon(0, 12.5, 16, 12.5, 14, 17.5, 2, 17.5);
    glColor3ub(140, 130, 110);
    triangle(2, 22.5, 2, 17.5, 4, 17.5);
    triangle(14, 22.5, 14, 17.5, 12, 17.5);

    //part 3
    //left side wall
    glColor3ub(160, 150, 130);
    polygon(-40, -25, -34, -25, -34, 5, -40, 5);
    polygon(-40, 5, -38, 5, -38, 10, -40, 10);
    polygon(-36, 5, -34, 5, -34, 10, -36, 10);
    //inner
    glColor3ub(140, 130, 110);
    polygon(-40, -25, -34, -25, -34, 2.5, -40, 2.5);
    triangle(-38, 2.5, -36, 2.5, -37, 5);
    //middle
    glColor3ub(180, 170, 150);
    polygon(-39, -25, -35, -25, -35, 0, -39, 0);
    //window
    glColor3ub(30, 50, 80);
    polygon(-38, -22.5, -36, -22.5, -36, -17.5, -38, -17.5);//1
    polygon(-38, -15, -36, -15, -36, -10, -38, -10);//2
    polygon(-38, -7.5, -36, -7.5, -36, -2.5, -38, -2.5);//3
    glColor3ub(255, 240, 180);
    polygon(-37.7, -22.2, -36.3, -22.2, -36.3, -17.8, -37.7, -17.8);
    polygon(-37.7, -14.7, -36.3, -14.7, -36.3, -10.3, -37.7, -10.3);
    polygon(-37.7, -7.2, -36.3, -7.2, -36.3, -2.8, -37.7, -2.8);
    //middle wall
    //bar
    glColor3ub(120, 110, 90);
    polygon(-34, -25, -4, -25, -4, -22.5, -34, -22.5);
    //level 1
    glColor3ub(180, 170, 150);
    polygon(-4, -22.5, -34, -22.5, -34, -12.5, -4, -12.5);
    //window
    glColor3ub(30, 50, 80);
    polygon(-32, -20, -30, -20, -30, -15, -32, -15);//1
    polygon(-28, -20, -26, -20, -26, -15, -28, -15);//2
    polygon(-24, -20, -22, -20, -22, -15, -24, -15);//3
    polygon(-20, -20, -18, -20, -18, -15, -20, -15);//4
    polygon(-16, -20, -14, -20, -14, -15, -16, -15);//5
    polygon(-12, -20, -10, -20, -10, -15, -12, -15);//6
    polygon(-8, -20, -6, -20, -6, -15, -8, -15);//7
    glColor3ub(255, 240, 180);
    polygon(-31.7, -19.7, -30.3, -19.7, -30.3, -15.3, -31.7, -15.3);
    polygon(-27.7, -19.7, -26.3, -19.7, -26.3, -15.3, -27.7, -15.3);
    polygon(-23.7, -19.7, -22.3, -19.7, -22.3, -15.3, -23.7, -15.3);
    polygon(-19.7, -19.7, -18.3, -19.7, -18.3, -15.3, -19.7, -15.3);
    polygon(-15.7, -19.7, -14.3, -19.7, -14.3, -15.3, -15.7, -15.3);
    polygon(-11.7, -19.7, -10.3, -19.7, -10.3, -15.3, -11.7, -15.3);
    polygon(-7.7, -19.7, -6.3, -19.7, -6.3, -15.3, -7.7, -15.3);
    //level 2
    glColor3ub(180, 170, 150);
    polygon(-4, -12.5, -34, -12.5, -34, -2.5, -4, -2.5);
    //window
    glColor3ub(30, 50, 80);
    polygon(-32, -10, -30, -10, -30, -5, -32, -5);//1
    polygon(-28, -10, -26, -10, -26, -5, -28, -5);//2
    polygon(-24, -10, -22, -10, -22, -5, -24, -5);//3
    polygon(-20, -10, -18, -10, -18, -5, -20, -5);//4
    polygon(-16, -10, -14, -10, -14, -5, -16, -5);//5
    polygon(-12, -10, -10, -10, -10, -5, -12, -5);//6
    polygon(-8, -10, -6, -10, -6, -5, -8, -5);//7
    glColor3ub(255, 240, 180);
    polygon(-31.7, -9.7, -30.3, -9.7, -30.3, -5.3, -31.7, -5.3);
    polygon(-27.7, -9.7, -26.3, -9.7, -26.3, -5.3, -27.7, -5.3);
    polygon(-23.7, -9.7, -22.3, -9.7, -22.3, -5.3, -23.7, -5.3);
    polygon(-19.7, -9.7, -18.3, -9.7, -18.3, -5.3, -19.7, -5.3);
    polygon(-15.7, -9.7, -14.3, -9.7, -14.3, -5.3, -15.7, -5.3);
    polygon(-11.7, -9.7, -10.3, -9.7, -10.3, -5.3, -11.7, -5.3);
    polygon(-7.7, -9.7, -6.3, -9.7, -6.3, -5.3, -7.7, -5.3);
    //level 3
    glColor3ub(160, 150, 130);
    polygon(-4, -2.5, -34, -2.5, -34, 2.5, -4, 2.5);
    //level 2 upper square
    glColor3ub(140, 130, 110);
    polygon(-32, 0, -30, 0, -30, -2.5, -32, -2.5);//1
    polygon(-28, 0, -26, 0, -26, -2.5, -28, -2.5);//2
    polygon(-24, 0, -22, 0, -22, -2.5, -24, -2.5);//3
    polygon(-20, 0, -18, 0, -18, -2.5, -20, -2.5);//4
    polygon(-16, 0, -14, 0, -14, -2.5, -16, -2.5);//5
    polygon(-12, 0, -10, 0, -10, -2.5, -12, -2.5);//6
    polygon(-8, 0, -6, 0, -6, -2.5, -8, -2.5);//7
    //middle level line
    glColor3ub(120, 110, 90);
    line(-4, -12.5, -34, -12.5);
    //roof
    //level 1
    glColor3ub(140, 130, 110);
    polygon(-26, 2.5, -12, 2.5, -12, 17.5, -26, 17.5);
    //windows
    glColor3ub(30, 50, 80);
    polygon(-24, 2.5, -22, 2.5, -22, 5, -24, 5);//1
    polygon(-20, 2.5, -18, 2.5, -18, 5, -20, 5);
    polygon(-16, 2.5, -14, 2.5, -14, 5, -16, 5);
    polygon(-24, 7.5, -22, 7.5, -22, 10, -24, 10);//2
    polygon(-20, 7.5, -18, 7.5, -18, 10, -20, 10);
    polygon(-16, 7.5, -14, 7.5, -14, 10, -16, 10);
    polygon(-24, 12.5, -22, 12.5, -22, 15, -24, 15);//3
    polygon(-20, 12.5, -18, 12.5, -18, 15, -20, 15);
    polygon(-16, 12.5, -14, 12.5, -14, 15, -16, 15);
    glColor3ub(255, 240, 180);
    polygon(-23.7, 2.8, -22.3, 2.8, -22.3, 4.7, -23.7, 4.7);
    polygon(-19.7, 2.8, -18.3, 2.8, -18.3, 4.7, -19.7, 4.7);
    polygon(-15.7, 2.8, -14.3, 2.8, -14.3, 4.7, -15.7, 4.7);
    //level 2
    glColor3ub(160, 150, 130);
    polygon(-26, 17.5, -12, 17.5, -14, 20, -24, 20);
    polygon(-14, 20, -24, 20, -24, 30, -14, 30);
    //window
    glColor3ub(30, 50, 80);
    polygon(-22, 20, -20, 20, -20, 22.5, -22, 22.5);//1
    polygon(-18, 20, -16, 20, -16, 22.5, -18, 22.5);
    polygon(-22, 25, -20, 25, -20, 27.5, -22, 27.5);//2
    polygon(-18, 25, -16, 25, -16, 27.5, -18, 27.5);
    glColor3ub(255, 240, 180);
    polygon(-21.7, 20.3, -20.3, 20.3, -20.3, 22.2, -21.7, 22.2);
    polygon(-17.7, 20.3, -16.3, 20.3, -16.3, 22.2, -17.7, 22.2);
    //upper roof
    glColor3ub(100, 95, 80);
    triangle(-24, 30, -14, 30, -19, 40);
    // roof highlight
    glColor3ub(120, 115, 95);
    triangle(-24, 30, -19, 40, -21, 35);

    //part 4
    //bar
    glColor3ub(120, 110, 90);
    polygon(-54, -25, -40, -25, -40, -22.5, -54, -22.5);
    //level 1
    glColor3ub(180, 170, 150);
    polygon(-54, -22.5, -40, -22.5, -40, -12.5, -54, -12.5);
    //windows
    glColor3ub(30, 50, 80);
    polygon(-52, -20, -50, -20, -50, -15, -52, -15);
    polygon(-48, -20, -46, -20, -46, -15, -48, -15);
    polygon(-44, -20, -42, -20, -42, -15, -44, -15);
    glColor3ub(255, 240, 180);
    polygon(-51.7, -19.7, -50.3, -19.7, -50.3, -15.3, -51.7, -15.3);
    polygon(-47.7, -19.7, -46.3, -19.7, -46.3, -15.3, -47.7, -15.3);
    polygon(-43.7, -19.7, -42.3, -19.7, -42.3, -15.3, -43.7, -15.3);
    //level 2
    glColor3ub(180, 170, 150);
    polygon(-54, -12.5, -40, -12.5, -40, -2.5, -54, -2.5);
    //windows
    glColor3ub(30, 50, 80);
    polygon(-52, -10, -50, -10, -50, -5, -52, -5);
    polygon(-48, -10, -46, -10, -46, -5, -48, -5);
    polygon(-44, -10, -42, -10, -42, -5, -44, -5);
    glColor3ub(255, 240, 180);
    polygon(-51.7, -9.7, -50.3, -9.7, -50.3, -5.3, -51.7, -5.3);
    polygon(-47.7, -9.7, -46.3, -9.7, -46.3, -5.3, -47.7, -5.3);
    polygon(-43.7, -9.7, -42.3, -9.7, -42.3, -5.3, -43.7, -5.3);
    //middle level line
    glColor3ub(120, 110, 90);
    line(-54, -12.5, -40, -12.5);
    //upper level
    glColor3ub(140, 130, 110);
    polygon(-54, -2.5, -40, -2.5, -40, 2.5, -54, 2.5);
    //upper squares
    glColor3ub(160, 150, 130);
    polygon(-52, -2.5, -50, -2.5, -50, 0, -52, 0);
    polygon(-48, -2.5, -46, -2.5, -46, 0, -48, 0);
    polygon(-44, -2.5, -42, -2.5, -42, 0, -44, 0);

    //part 5
    glColor3ub(160, 150, 130);
    polygon(-100, -25, -54, -25, -54, -17.5, -100, -17.5);
    //left wall
    polygon(-100, -25, -90, -25, -90, 7.5, -100, 7.5);
    polygon(-100, 7.5, -90, 7.5, -90, 10, -98, 10);
    polygon(-98, 10, -90, 10, -90, 12.5, -98, 12.5);
    polygon(-98, 12.5, -96, 12.5, -96, 15, -98, 15);
    triangle(-98, 15, -96, 15, -97, 17.5);
    polygon(-94, 12.5, -90, 12.5, -90, 15, -94, 15);
    //windows
    glColor3ub(30, 50, 80);
    polygon(-98, -15, -96, -15, -96, -7.5, -98, -7.5);
    polygon(-94, -15, -92, -15, -92, -7.5, -94, -7.5);
    polygon(-98, -2.5, -96, -2.5, -96, 5, -98, 5);
    polygon(-94, -2.5, -92, -2.5, -92, 5, -94, 5);
    glColor3ub(255, 240, 180);
    polygon(-97.7, -14.7, -96.3, -14.7, -96.3, -7.8, -97.7, -7.8);
    polygon(-93.7, -14.7, -92.3, -14.7, -92.3, -7.8, -93.7, -7.8);
    polygon(-97.7, -2.2, -96.3, -2.2, -96.3, 4.7, -97.7, 4.7);
    polygon(-93.7, -2.2, -92.3, -2.2, -92.3, 4.7, -93.7, 4.7);
    //left pillar
    glColor3ub(180, 170, 150);
    polygon(-94, 15, -88, 15, -88, 75, -94, 75);
    // pillar highlight
    glColor3ub(200, 190, 170);
    polygon(-93, 15, -92, 15, -92, 75, -93, 75);
    glColor3ub(140, 130, 110);
    polygon(-92, 75, -90, 75, -90, 77.5, -92, 77.5);
    glColor3ub(100, 95, 80);
    triangle(-94, 77.5, -88, 77.5, -91, 82.5);
    //right pillar
    glColor3ub(180, 170, 150);
    polygon(-62, 10, -56, 10, -56, 75, -62, 75);
    // pillar highlight
    glColor3ub(200, 190, 170);
    polygon(-61, 10, -60, 10, -60, 75, -61, 75);
    glColor3ub(140, 130, 110);
    polygon(-60, 75, -58, 75, -58, 77.5, -60, 77.5);
    glColor3ub(100, 95, 80);
    triangle(-62, 77.5, -56, 77.5, -59, 82.5);
    //middle wall
    //bar
    glColor3ub(140, 130, 110);
    polygon(-90, -17.5, -62, -17.5, -62, -12.5, -90, -12.5);
    //outer wall
    glColor3ub(180, 170, 150);
    polygon(-90, -12.5, -60, -12.5, -60, 57.5, -90, 57.5);
    // outer wall highlight strip
    glColor3ub(200, 190, 170);
    polygon(-90, -12.5, -88, -12.5, -88, 57.5, -90, 57.5);
    //window
    glColor3ub(30, 50, 80);
    polygon(-88, 40, -84, 40, -84, 45, -88, 45);//1
    polygon(-82, 40, -78, 40, -78, 45, -82, 45);
    polygon(-72, 40, -68, 40, -68, 45, -72, 45);
    polygon(-66, 40, -62, 40, -62, 45, -66, 45);
    polygon(-88, 50, -84, 50, -84, 55, -88, 55);//2
    polygon(-82, 50, -78, 50, -78, 55, -82, 55);
    polygon(-72, 50, -68, 50, -68, 55, -72, 55);
    polygon(-66, 50, -62, 50, -62, 55, -66, 55);
    glColor3ub(255, 240, 180);
    polygon(-87.7, 40.3, -84.3, 40.3, -84.3, 44.7, -87.7, 44.7);
    polygon(-81.7, 40.3, -78.3, 40.3, -78.3, 44.7, -81.7, 44.7);
    polygon(-71.7, 40.3, -68.3, 40.3, -68.3, 44.7, -71.7, 44.7);
    polygon(-65.7, 40.3, -62.3, 40.3, -62.3, 44.7, -65.7, 44.7);
    polygon(-87.7, 50.3, -84.3, 50.3, -84.3, 54.7, -87.7, 54.7);
    polygon(-81.7, 50.3, -78.3, 50.3, -78.3, 54.7, -81.7, 54.7);
    polygon(-71.7, 50.3, -68.3, 50.3, -68.3, 54.7, -71.7, 54.7);
    polygon(-65.7, 50.3, -62.3, 50.3, -62.3, 54.7, -65.7, 54.7);
    //inner wall
    glColor3ub(160, 150, 130);
    polygon(-86, -12.5, -64, -12.5, -64, 37.5, -86, 37.5);
    //level 1 windows
    glColor3ub(30, 50, 80);
    polygon(-84, -12.5, -81, -12.5, -81, -7.5, -84, -7.5);//1
    polygon(-80, -12.5, -77, -12.5, -77, -7.5, -80, -7.5);
    polygon(-73, -12.5, -70, -12.5, -70, -7.5, -73, -7.5);
    polygon(-69, -12.5, -66, -12.5, -66, -7.5, -69, -7.5);
    polygon(-84, -2.5, -81, -2.5, -81, -5, -84, -5);//2
    semiCircle(-82.5, -2.5, 1.5);
    polygon(-80, -2.5, -77, -2.5, -77, -5, -80, -5);
    semiCircle(-78.5, -2.5, 1.5);
    polygon(-73, -2.5, -70, -2.5, -70, -5, -73, -5);
    semiCircle(-71.5, -2.5, 1.5);
    polygon(-69, -2.5, -66, -2.5, -66, -5, -69, -5);
    semiCircle(-67.5, -2.5, 1.5);
    glColor3ub(255, 240, 180);
    polygon(-83.7, -12.2, -81.3, -12.2, -81.3, -7.8, -83.7, -7.8);
    polygon(-79.7, -12.2, -77.3, -12.2, -77.3, -7.8, -79.7, -7.8);
    polygon(-72.7, -12.2, -70.3, -12.2, -70.3, -7.8, -72.7, -7.8);
    polygon(-68.7, -12.2, -66.3, -12.2, -66.3, -7.8, -68.7, -7.8);
    //bar
    glColor3ub(140, 130, 110);
    polygon(-86, 0, -64, 0, -64, 5, -86, 5);
    //level 2
    glColor3ub(180, 170, 150);
    polygon(-86, 5, -64, 5, -64, 15, -86, 15);
    //windows
    glColor3ub(30, 50, 80);
    polygon(-84, 5, -81, 5, -81, 7.5, -84, 7.5);//1
    polygon(-77, 5, -74, 5, -74, 7.5, -77, 7.5);
    polygon(-70, 5, -67, 5, -67, 7.5, -70, 7.5);
    polygon(-84, 12.5, -81, 12.5, -81, 10, -84, 10);//2
    polygon(-77, 12.5, -74, 12.5, -74, 10, -77, 10);
    polygon(-70, 12.5, -67, 12.5, -67, 10, -70, 10);
    glColor3ub(255, 240, 180);
    polygon(-83.7, 5.3, -81.3, 5.3, -81.3, 7.2, -83.7, 7.2);
    polygon(-76.7, 5.3, -74.3, 5.3, -74.3, 7.2, -76.7, 7.2);
    polygon(-69.7, 5.3, -67.3, 5.3, -67.3, 7.2, -69.7, 7.2);
    //roof
    glColor3ub(120, 110, 90);
    polygon(-90, 57.5, -60, 57.5, -64, 65, -86, 65);
    // roof highlight
    glColor3ub(140, 130, 110);
    polygon(-90, 57.5, -88, 57.5, -86, 65, -90, 65);
    //roof pillar
    glColor3ub(160, 150, 130);
    polygon(-78, 65, -72, 65, -72, 75, -78, 75);
    glColor3ub(100, 95, 80);
    triangle(-78, 75, -72, 75, -75, 82.5);

    //flag stand (pole)
glColor3ub(80, 75, 60);
line(-75, 65, -75, 95);

// UNION JACK FLAG

glColor3ub(0, 36, 125);
polygon(-75, 87.5, -55, 87.5, -55, 97.5, -75, 97.5);


// diagonal top-left to bottom-right (red)
glColor3ub(207, 20, 43);
// upper-left half
glBegin(GL_POLYGON);
glVertex2f(-75, 97.5);
glVertex2f(-72, 97.5);
glVertex2f(-55, 88.5);
glVertex2f(-55, 87.5);
glVertex2f(-58, 87.5);
glVertex2f(-75, 96.5);
glEnd();
// lower-right half
glBegin(GL_POLYGON);
glVertex2f(-75, 97.5);
glVertex2f(-75, 96.0);
glVertex2f(-57, 87.5);
glVertex2f(-55, 87.5);
glVertex2f(-55, 89.0);
glVertex2f(-73, 97.5);
glEnd();

glBegin(GL_POLYGON);
glVertex2f(-55, 97.5);
glVertex2f(-52, 97.5); // off edge clamp
glVertex2f(-75, 87.5);
glVertex2f(-75, 88.5);
glVertex2f(-57, 97.5);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(-75, 87.5);
glVertex2f(-73, 87.5);
glVertex2f(-55, 96.5);
glVertex2f(-55, 97.5);
glVertex2f(-57, 97.5);
glVertex2f(-75, 88.5);
glEnd();



glColor3ub(255, 255, 255);
glBegin(GL_POLYGON);
glVertex2f(-75, 97.5);
glVertex2f(-73, 97.5);
glVertex2f(-55, 88.2);
glVertex2f(-55, 87.5);
glVertex2f(-57, 87.5);
glVertex2f(-75, 96.8);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(-75, 96.5);
glVertex2f(-75, 97.5);
glVertex2f(-73.5, 97.5);
glVertex2f(-55, 88.0);
glVertex2f(-55, 87.5);
glVertex2f(-56.5, 87.5);
glEnd();


glBegin(GL_POLYGON);
glVertex2f(-55, 97.5);
glVertex2f(-57, 97.5);
glVertex2f(-75, 88.2);
glVertex2f(-75, 87.5);
glVertex2f(-73, 87.5);
glVertex2f(-55, 96.8);
glEnd();
glBegin(GL_POLYGON);
glVertex2f(-75, 87.5);
glVertex2f(-75, 88.5);
glVertex2f(-57.5, 97.5);
glVertex2f(-55, 97.5);
glVertex2f(-55, 96.5);
glVertex2f(-73.5, 87.5);
glEnd();



glColor3ub(255, 255, 255);
polygon(-75, 91.5, -55, 91.5, -55, 93.5, -75, 93.5);
// white vertical bar
polygon(-66, 87.5, -64, 87.5, -64, 97.5, -66, 97.5);


glColor3ub(207, 20, 43);
polygon(-75, 91.8, -55, 91.8, -55, 93.2, -75, 93.2);

polygon(-65.6, 87.5, -64.4, 87.5, -64.4, 97.5, -65.6, 97.5);


glColor3ub(180, 150, 50);
line(-75, 87.5, -75, 97.5);  // pole edge
line(-75, 97.5, -55, 97.5);  // top edge
line(-75, 87.5, -55, 87.5);  // bottom edge

    //right wall
    glColor3ub(160, 150, 130);
    polygon(-62, -25, -54, -25, -54, 7.5, -62, 7.5);
    polygon(-62, 7.5, -54, 7.5, -54, 10, -60, 10);
    polygon(-60, 10, -58, 10, -58, 15, -60, 15);
    polygon(-56, 10, -54, 10, -54, 15, -56, 15);
    //windows
    glColor3ub(30, 50, 80);
    polygon(-61, -15, -59, -15, -59, -7.5, -61, -7.5);
    polygon(-57, -15, -55, -15, -55, -7.5, -57, -7.5);
    polygon(-57, -2.5, -55, -2.5, -55, 5, -57, 5);
    polygon(-61, -2.5, -59, -2.5, -59, 5, -61, 5);
    glColor3ub(255, 240, 180);
    polygon(-60.7, -14.7, -59.3, -14.7, -59.3, -7.8, -60.7, -7.8);
    polygon(-56.7, -14.7, -55.3, -14.7, -55.3, -7.8, -56.7, -7.8);
    polygon(-56.7, -2.2, -55.3, -2.2, -55.3, 4.7, -56.7, 4.7);
    polygon(-60.7, -2.2, -59.3, -2.2, -59.3, 4.7, -60.7, 4.7);


    //road
    glColor3ub(150,150,150);
    polygon(-100, -100, 100, -100, 100, -50, -100, -50);

    //road divider
     glColor3ub(255,255,255);
    polygon(-100,-75,-80,-75,-80,-70,-100,-70);
    polygon(-60,-75,-40,-75,-40,-70,-60,-70);
    polygon(-20,-75,0,-75,0,-70,-20,-70);
    polygon(20,-75,40,-75,40,-70,20,-70);
    polygon(60,-75,80,-75,80,-70,60,-70);


 //snowman
   // snow bumps on ground
    glColor3ub(235, 245, 255);

    glBegin(GL_POLYGON);
    for(int i = 0; i <= 180; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        glVertex2f(-20 + 25 * cos(angle), -38 + 4 * sin(angle));
    }
    glEnd();
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 180; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        glVertex2f(60 + 35 * cos(angle), -38 + 6 * sin(angle));
    }
    glEnd();

    // snow on fence spikes
    glColor3ub(240, 248, 255);
    for(float fx = -98; fx <= 98; fx += 4.0f)
    {
        triangle(fx,      -27,
                 fx + 1,  -27,
                 fx + 0.5f, -24);
    }

 //body
    // bottom ball shadow
    glColor3ub(200, 215, 230);
    circle(30, -29, 9.5f);
    // bottom ball
    glColor3ub(240, 248, 255);
    circle(30, -29, 9.0f);
    // bottom ball shading
    glColor3ub(220, 235, 248);
    circle(32, -31, 5.0f);

    // middle ball shadow
    glColor3ub(200, 215, 230);
    circle(30, -16, 7.5f);
    // middle ball
    glColor3ub(245, 250, 255);
    circle(30, -16, 7.0f);
    // middle ball shading
    glColor3ub(225, 238, 250);
    circle(32, -17.5, 4.0f);

    // top ball (head) shadow
    glColor3ub(200, 215, 230);
    circle(30, -5.5, 5.5f);
    // top ball head
    glColor3ub(248, 252, 255);
    circle(30, -5.5, 5.0f);

  //face
    // eyes
    glColor3ub(20, 20, 20);
    circle(27.5, -4.0, 0.8f);
    circle(32.5, -4.0, 0.8f);

    // carrot nose
    glColor3ub(255, 120, 0);
    triangle(28.5, -5.8,
             31.5, -5.8,
             35.5, -5.5);
    // nose highlight
    glColor3ub(255, 160, 50);
    triangle(29.0, -5.5,
             31.0, -5.5,
             34.5, -5.4);

    // smile (5 coal dots)
    glColor3ub(20, 20, 20);
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    glVertex2f(26.5, -7.5);
    glVertex2f(28.0, -8.5);
    glVertex2f(30.0, -9.0);
    glVertex2f(32.0, -8.5);
    glVertex2f(33.5, -7.5);
    glEnd();
    glPointSize(1.0f);

    // eyebrows (twig style)
    glColor3ub(60, 35, 10);
    glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(26.5, -2.5); glVertex2f(29.5, -2.0);  // left brow
    glVertex2f(30.5, -2.0); glVertex2f(33.5, -2.5);  // right brow
    glEnd();
    glLineWidth(1.0f);


    // hat brim
    glColor3ub(20, 20, 20);
    polygon(23.5, -1.5,
            36.5, -1.5,
            36.5, -0.5,
            23.5, -0.5);
    // hat body
    polygon(25.5, -0.5,
            34.5, -0.5,
            34.5,  6.5,
            25.5,  6.5);
    // hat highlight
    glColor3ub(45, 45, 45);
    polygon(25.5, -0.5,
            27.0, -0.5,
            27.0,  6.5,
            25.5,  6.5);
    // hat band
    glColor3ub(180, 30, 30);
    polygon(25.5, 1.5,
            34.5, 1.5,
            34.5, 3.0,
            25.5, 3.0);
    // hat band buckle
    glColor3ub(220, 180, 0);
    polygon(29.0, 1.6,
            31.0, 1.6,
            31.0, 2.9,
            29.0, 2.9);
    glColor3ub(180, 140, 0);
    polygon(29.4, 2.0,
            30.6, 2.0,
            30.6, 2.5,
            29.4, 2.5);


    // main scarf wrap
    glColor3ub(200, 40, 40);
    polygon(23.5, -13.5,
            36.5, -13.5,
            36.5, -11.0,
            23.5, -11.0);
    // scarf stripes
    glColor3ub(240, 60, 60);
    polygon(23.5, -12.5,
            36.5, -12.5,
            36.5, -12.0,
            23.5, -12.0);
    polygon(23.5, -11.8,
            36.5, -11.8,
            36.5, -11.4,
            23.5, -11.4);
    // scarf tail hanging down left
    glColor3ub(200, 40, 40);
    polygon(23.5, -13.5,
            25.5, -13.5,
            25.5, -19.0,
            23.5, -19.0);
    // scarf tail stripe
    glColor3ub(240, 60, 60);
    polygon(23.5, -15.0,
            25.5, -15.0,
            25.5, -14.5,
            23.5, -14.5);
    polygon(23.5, -17.0,
            25.5, -17.0,
            25.5, -16.5,
            23.5, -16.5);
    // scarf tail fringe
    glColor3ub(200, 40, 40);
    glLineWidth(1.2f);
    glBegin(GL_LINES);
    glVertex2f(23.5, -19.0); glVertex2f(23.5, -20.5);
    glVertex2f(24.2, -19.0); glVertex2f(24.0, -20.8);
    glVertex2f(24.8, -19.0); glVertex2f(24.6, -20.5);
    glVertex2f(25.4, -19.0); glVertex2f(25.5, -20.8);
    glEnd();
    glLineWidth(1.0f);


    //buttons

    glColor3ub(20, 20, 20);
    circle(30, -13.5, 1.0f);
    circle(30, -16.5, 1.0f);
    circle(30, -19.5, 1.0f);

//arms
    glColor3ub(60, 35, 10);
    glLineWidth(2.0f);
    // left arm main branch
    glBegin(GL_LINES);
    glVertex2f(23.0, -14.0);
    glVertex2f(13.0, -10.0);
    glEnd();
    // left arm branch 1
    glBegin(GL_LINES);
    glVertex2f(16.0, -11.5);
    glVertex2f(13.5, -8.0);
    glEnd();
    // left arm branch 2
    glBegin(GL_LINES);
    glVertex2f(14.5, -10.5);
    glVertex2f(12.0, -13.0);
    glEnd();

    // right arm main branch
    glBegin(GL_LINES);
    glVertex2f(37.0, -14.0);
    glVertex2f(47.0, -10.0);
    glEnd();
    // right arm branch 1
    glBegin(GL_LINES);
    glVertex2f(44.0, -11.5);
    glVertex2f(46.5, -8.0);
    glEnd();
    // right arm branch 2
    glBegin(GL_LINES);
    glVertex2f(45.5, -10.5);
    glVertex2f(48.0, -13.0);
    glEnd();
    glLineWidth(1.0f);


    // snow on hat

    glColor3ub(240, 248, 255);
    glBegin(GL_POLYGON);
    for(int i = 0; i <= 180; i++)
    {
        float angle = i * 3.1416f / 180.0f;
        glVertex2f(30.5f + 4.5f * cos(angle),
                   6.5f  + 1.5f * sin(angle));
    }
    glEnd();


    //snow on arm
 glColor3ub(235, 245, 255);
    circle(13.5, -10.0, 1.5f);
    circle(46.5, -10.0, 1.5f);


    //snoball next to snowman

    glColor3ub(200, 215, 230);
    circle(48, -33, 4.5f);
    glColor3ub(235, 245, 255);
    circle(48, -33, 4.0f);
    glColor3ub(220, 235, 248);
    circle(49.5, -34, 2.5f);



//london street lamp
//light
glColor3ub(238,201,0);
circle(-95,18,5);
//body
glColor3ub(0,0,0);
polygon(-100,-37,-90,-37,-90,-34.5,-100,-34.5);
polygon(-99,-34.5,-99,-32,-91,-32,-91,-34.5);
polygon(-98,-32,-98,-29.5,-92,-29.5,-92,-32);
polygon(-97,-29.5,-93,-29.5,-94,0.5,-96,0.5);
circle(-95,-12,3);
polygon(-97,0.5,-93,0.5,-93,3,-97,3);
polygon(-96,3,-96,8,-94,8,-94,3);
circle(-95,5.5,2);
polygon(-97,8,-97,10.5,-93,10.5,-93,8);
polygon(-98,10.5,-98,13,-92,13,-92,10.5);

//telephone booth
glColor3ub(0,0,0);
polygon(-82,-37,-82,-34.5,-58,-34.5,-58,-37);
glColor3ub(205,38,38);
polygon(-80,-34.5,-80,8,-60,8,-60,-34.5);
polygon(-80,8,-75,13,-65,13,-60,8);
glColor3ub(178,34,34);
triangle(-80,8,-75,13,-78.5,12);
triangle(-60,8,-65,13,-61.5,12);
//text
glColor3ub(220,220,220);
polygon(-79,1,-79,5,-61,5,-61,1);
glColor3ub(0,0,0);
    drawText(-78,2, "TELEPHONE");
glColor3ub(178,34,34);
line(-80,0.5,-60,0.5);
line(-80,5.5,-60,5.5);
line(-80,5.5,-80,0.5);
line(-60,5.5,-60,0.5);
line(-78,-2,-78,-34.5);
line(-62,-2,-62,-34.5);
line(-62,-2,-78,-2);
polygon(-77,-3.25,-63,-3.25,-63,-27,-77,-27);
polygon(-77,-32,-63,-32,-63,-28.25,-77,-28.25);
//glass
glColor3ub(0,0,0);
polygon(-75.5,-4.5,-72.5,-4.5,-72.5,-8.5,-75.5,-8.5);
polygon(-71.5,-4.5,-68.5,-4.5,-68.5,-8.5,-71.5,-8.5);
polygon(-67.5,-4.5,-64.5,-4.5,-64.5,-8.5,-67.5,-8.5);
polygon(-75.5,-9.75,-72.5,-9.75,-72.5,-13.75,-75.5,-13.75);
polygon(-71.5,-9.75,-68.5,-9.75,-68.5,-13.75,-71.5,-13.75);
polygon(-67.5,-9.75,-64.5,-9.75,-64.5,-13.75,-67.5,-13.75);
polygon(-75.5,-15,-72.5,-15,-72.5,-19,-75.5,-19);
polygon(-71.5,-15,-68.5,-15,-68.5,-19,-71.5,-19);
polygon(-67.5,-15,-64.5,-15,-64.5,-19,-67.5,-19);
polygon(-75.5,-20.25,-72.5,-20.25,-72.5,-24.25,-75.5,-24.25);
polygon(-71.5,-20.25,-68.5,-20.25,-68.5,-24.25,-71.5,-24.25);
polygon(-67.5,-20.25,-64.5,-20.25,-64.5,-24.25,-67.5,-24.25);
glColor3ub(238,44,44);
//image
polygon(-80,8,-75,13,-65,13,-60,8);
polygon(-80,8,-80,5.5,-60,5.5,-60,8);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, logoTexture);


    glColor3ub(255, 255, 255);


    glBegin(GL_QUADS);
        // Bottom-Left corner
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-74.0f, 7.75f);
        // Bottom-Right corner
        glTexCoord2f(1.0f, 0.0f); glVertex2f(-66.0f, 7.75f);
        // Top-Right corner
        glTexCoord2f(1.0f, 1.0f); glVertex2f(-66.0f, 13.0f);
        // Top-Left corner
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-74.0f, 13.0f);
    glEnd();


    glDisable(GL_TEXTURE_2D);


glColor3ub(178,34,34);
//detail lines
line(-80,0.25,-60,0.25);
line(-80,5.75,-60,5.75);
line(-80,0,-60,0);
line(-80,6,-60,6);
line(-80,-0.25,-60,-0.25);
line(-80,6.25,-60,6.25);

//royal guard
//hair
glColor3ub(0,0,0);
semiCircle(-50,8,4);                    // +13
polygon(-54,8,-46,8,-46,0.5,-54,0.5);
//neck
glColor3ub(255,228,181);
polygon(-52,-4.5,-48,-4.5,-48,-2,-52,-2);
//head
glColor3ub(205,133,0);
PokemonSemiCircle(-50,0.5,4);
glColor3ub(255,228,181);
PokemonSemiCircle(-50,0.5,3.75);
//hand
circle(-55,-19.5,1);
circle(-45,-19.5,1);
//body
glColor3ub(205,0,0);
polygon(-55,-4.5,-45,-4.5,-44,-5.75,-56,-5.75);
polygon(-44,-5.75,-56,-5.75,-56,-19.5,-44,-19.5);
polygon(-54,-19.5,-54,-22,-46,-22,-46,-19.5);
glColor3ub(248,248,255);
polygon(-54,-19.5,-54,-17,-46,-17,-46,-19.5);
glColor3ub(139,0,0);
line(-54,-9.5,-54,-22);
line(-46,-9.5,-46,-22);
glColor3ub(0,0,0);
polygon(-56,-19.5,-56,-19,-54,-19,-54,-19.5);
polygon(-46,-19.5,-46,-19,-44,-19,-44,-19.5);
//collar
glColor3ub(0,0,0);
polygon(-52,-4.5,-48,-4.5,-48,-5.75,-52,-5.75);
polygon(-48,-5.75,-52,-5.75,-51,-7,-49,-7);
//pants
glColor3ub(0,0,0);
triangle(-51,-22,-49,-22,-50,-19.5);
polygon(-54,-22,-51,-22,-51,-37,-54,-37);
polygon(-49,-22,-46,-22,-46,-37,-49,-37);
polygon(-54,-22,-46,-22,-46,-24.5,-54,-24.5);
//button
glColor3ub(255,193,37);
circle(-50,-9,1);
circle(-50,-12,1);
circle(-50,-15,1);
circle(-50,-18,1);


glPushMatrix();
glTranslatef(bustx,busty,0.0f);
//london bus

glColor3ub(238,44,44);
polygon(22,-60,90,-60,90,-42.5,22,-42.5);
circle(80,-10,10);
polygon(26,-42.5,90,-42.5,90,-25,26,-25);
polygon(24,-22.5,26,-2.5,90,-12.5,90,-22.5);
polygon(26,-2.5,28,0,80,0,90,-21.5);
glColor3ub(0,0,0);
polygon(20,-60,24,-60,24,-57.5,20,-57.5);
//inner
glColor3ub(178,34,34);
polygon(26,-42.5,26,-25,40,-25,40,-42.5);
polygon(83,-25,90,-25,90,-55,83,-55);
polygon(75,-58.75,90,-58.75,90,-60,75,-60);
//outer inner
glColor3ub(205,38,38);
polygon(22,-50,22,-42.5,26,-42.5,26,-45);
polygon(26,-42.5,26,-45,40,-45,40,-42.5);
polygon(78,-25,78,-58.75,83,-58.75,83,-25);
polygon(24,-25,24,-22.5,90,-22.5,90,-25);

//outline
glColor3ub(139,26,26);
polygon(89.5,-58.75,90,-58.75,90,-25,89.5,-25);
semiCircle(32,-60,8);
semiCircle(67,-60,8);
line(24,-25,90,-25);
line(24,-22.5,90,-22.5);
line(24,-22.5,24,-25);
line(90,-22.5,90,-25);
line(26,-25,26,-42.5);
line(40,-25,40,-45);
line(22,-42.5,40,-42.5);
line(26,-45,40,-45);
line(22,-42.5,22,-57.5);
line(22,-50,26,-45);
line(78,-25,78,-58.75);
line(83,-25,83,-58.75);

glColor3ub(205,38,38);
line(42,-45,76,-45);
line(26,-5,86,-5);
line(25,-15,89,-15);
line(40,0,40,-22.5);
line(52,0,52,-15);
line(66,0,66,-15);
line(52,-25,52,-45);
line(66,-25,66,-45);
//head light
glColor3ub(175,175,175);
polygon(23,-47.5,23,-52.5,24,-52.5,24,-47.5);

//wheels
glColor3ub(178,34,34);
semiCircle(32,-60,8);
semiCircle(67,-60,8);

glColor3ub(139,26,26);
semiCircle(32,-60,7.25);
semiCircle(67,-60,7.25);

glColor3ub(0,0,0);
circle(32,-60,6);
circle(67,-60,6);

glColor3ub(48,48,48);
circle(32,-60,5.5);
circle(67,-60,5.5);

glColor3ub(0,0,0);
circle(32,-60,4);
circle(67,-60,4);

glColor3ub(127,127,127);
circle(32,-60,3.5);
circle(67,-60,3.5);

glColor3ub(0,0,0);
circle(32,-60,3.25);
circle(67,-60,3.25);

glColor3ub(189,189,189);
circle(32,-60,3);
circle(67,-60,3);

glColor3ub(0,0,0);
circle(32,-60,2.5);
circle(67,-60,2.5);

glColor3ub(235,235,235);
circle(32,-60,2.25);
circle(67,-60,2.25);

//stairs
glColor3ub(200,200,200);//1
polygon(83,-58.75,89.5,-58.75,89.5,-55,83,-55);
glColor3ub(175,175,175);//2
polygon(83,-55,88.75,-55,88.75,-52.5,83,-52.5);
glColor3ub(135,135,135);//3
polygon(83,-50,88,-50,88,-52.5,83,-52.5);
glColor3ub(95,95,95);//4
polygon(83,-50,87,-50,87,-47.5,83,-47.5);
glColor3ub(55,55,55);//5
polygon(83,-45,86,-45,86,-47.5,83,-47.5);
glColor3ub(35,35,35);//6
polygon(83,-45,85,-45,85,-42.5,83,-42.5);
glColor3ub(0,0,0);//7
polygon(83,-40,84,-40,84,-42.5,83,-42.5);

//handle and bar
glColor3ub(255,204,0);
line(85,-25,85,-58.75);
line(80,-40,80,-55);
line(78,-40,80,-40);
line(78,-55,80,-55);

//window
//inner window
glColor3ub(0,0,0);
polygon(27,-28.75,39,-28.75,39,-38.75,27,-38.75);


glColor3ub(128,128,128);
polygon(27.25,-29,38.75,-29,38.75,-38.5,27.25,-38.5);

//bottom floor window

glColor3ub(0,0,0);
polygon(41,-40,51,-40,51,-32.5,41,-32.5);


glColor3ub(150,150,150);
polygon(41.25,-39.75,50.75,-39.75,50.75,-32.75,41.25,-32.75);

glColor3ub(0,0,0);
polygon(54,-40,64,-40,64,-32.5,54,-32.5);


glColor3ub(150,150,150);
polygon(54.25,-39.75,63.75,-39.75,63.75,-32.75,54.25,-32.75);

glColor3ub(0,0,0);
polygon(67,-40,77,-40,77,-32.5,67,-32.5);


glColor3ub(150,150,150);
polygon(67.25,-39.75,76.75,-39.75,76.75,-32.75,67.25,-32.75);

//up floor window
glColor3ub(0,0,0);
polygon(28,-13.75,38,-13.75,38,-6.25,28,-6.25);


glColor3ub(192,192,192);
polygon(28.25,-13.5,37.75,-13.5,37.75,-6.5,28.25,-6.5);

glColor3ub(0,0,0);
polygon(41,-13.75,51,-13.75,51,-6.25,41,-6.25);


glColor3ub(192,192,192);
polygon(41.25,-13.5,50.75,-13.5,50.75,-6.5,41.25,-6.5);

glColor3ub(0,0,0);
polygon(54,-13.75,64,-13.75,64,-6.25,54,-6.25);


glColor3ub(192,192,192);
polygon(54.25,-13.5,63.75,-13.5,63.75,-6.5,54.25,-6.5);

glColor3ub(0,0,0);
polygon(67,-13.75,77,-13.75,77,-6.25,67,-6.25);


glColor3ub(192,192,192);
polygon(67.25,-13.5,76.75,-13.5,76.75,-6.5,67.25,-6.5);

//text
glColor3ub(0,0,0);
polygon(28,-16.25,36,-16.25,36,-21.25,28,-21.25);
glColor3ub(255,255,255);
 drawTextBus(29,-20, " 15 ");

glColor3ub(0,0,0);
polygon(42,-16.25,88,-16.25,88,-21.25,42,-21.25);
glColor3ub(255,153,0);
 drawTextBus(46,-20, "Round London Sightseeing Tour");
 glPopMatrix();




//mr bean car
 glPushMatrix();
 glTranslatef(beancartx,beancarty,0.0f);
 glScalef(1.10,1.10,0.0f);


//back light
glColor3ub(255,255,255);
circle(-90, -77.5, 1.5);

//front light
circle(-41, -78.75, 1.75);
glColor3ub(139,0,0);
polygon(-40, -87.5, -38, -87.5, -38, -85, -40, -85);

//body
glColor3ub(179,238,58);
polygon(-90, -87.5, -40, -87.5, -40, -75, -90, -75);
polygon(-88, -75, -50, -75, -56, -65, -83, -65);
polygon(-56, -65, -83, -65,-81,-62.5,-58,-62.5);
//front light holder
glColor3ub(224, 255, 255);
polygon(-41, -80, -40, -80, -40, -77.5, -41, -77.5);
polygon(-41, -82, -40, -82, -40, -84.5, -41, -84.5);
glColor3ub(224, 255, 0);
triangle(-40, -82, -40, -84.5, -38, -83.25);

//left window
//outer
glColor3ub(154,205,50);
polygon(-86, -75, -72, -75, -72, -65, -82, -65);

//glass
glColor3ub(224, 255, 255);
polygon(-84.5, -73.5, -73, -73.5,-73, -66.75, -81.5, -66.75);
//right window
//outer
glColor3ub(154,205,50);
polygon(-68, -75, -54, -75, -58, -65, -68, -65);
//glass
glColor3ub(224, 255, 255);
polygon(-66.75, -73.5, -56, -73.5, -58.5, -66.75, -66.75, -66.75);

//front window
glColor3ub(224, 255, 255);
polygon(-51,-73.75,-53,-73.75,-57,-65,-56,-65);

//lower bar
glColor3ub(179,238,58);
polygon(-74, -88.75, -53, -88.75, -52, -87.5, -75, -87.5);

//body lines
glColor3ub(69,139,0);
line(-88, -87.5, -86, -75);
line(-69, -76.25, -69, -86.25);
line(-69, -76.25, -68, -75);
line(-69, -86.25, -68, -87.5);
line( -52, -87.5, -75, -87.5);
line(-54,-75,-86,-75);
line(-58, -65, -54, -75);
line( -54, -75,-50,-85);
line(-54, -87.5, -54, -75);
line(-83,-65,-56,-65);
line(-68,-65,-68,-75);
line(-82,-65,-86,-75);
line(-51,-73.75,-53,-73.75);
line(-53,-73.75,-57,-65);
line(-40,-75,-50,-75);
line(-88,-75,-90,-75);
line(-88,-75,-83,-65);
//backside
glColor3ub(139, 0, 0);
polygon(-92, -85, -90, -85, -90, -80, -92, -80);
//left tire
     //shade
     glColor3ub(80, 80, 80);
     semiCircle(-81, -87.5, 6);

     glColor3ub(0, 0, 0);
     circle(-81, -87.5, 5);

     glColor3ub(80, 80, 80);
     circle(-81, -87.5, 4);

     glColor3ub(130, 130, 130);
     circle(-81, -87.5, 3);

     glColor3ub(220, 220, 220);
     circle(-81, -87.5, 2);

          glColor3ub(248, 248, 255);
     circle(-81, -87.5, 1);
//right tire
     //shade
     glColor3ub(80, 80, 80);
     semiCircle(-46, -87.5, 6);

     glColor3ub(0, 0, 0);
     circle(-46, -87.5, 5);

     glColor3ub(80, 80, 80);
     circle(-46, -87.5, 4);

     glColor3ub(130, 130, 130);
     circle(-46, -87.5, 3);

      glColor3ub(220, 220, 220);
     circle(-46, -87.5, 2);

      glColor3ub(248, 248, 255);
     circle(-46, -87.5, 1);
//car handle
glColor3ub(255, 255, 255);
polygon(-68, -78, -64, -78, -64, -77, -68, -77);


 // rack base rail (sits exactly on roof)
    glColor3ub(170, 165, 155);
    polygon(-80, -62.5, -58, -62.5, -58, -61.5, -80, -61.5);
    // rack raised side rails
    polygon(-80, -61.5, -79, -61.5, -79, -59.5, -80, -59.5);
    polygon(-59, -61.5, -58, -61.5, -58, -59.5, -59, -59.5);
    // rack top rail
    polygon(-80, -59.5, -58, -59.5, -58, -58.8, -80, -58.8);
    // rack cross bars
    glColor3ub(155, 150, 140);
    polygon(-78, -61.5, -76, -61.5, -76, -58.8, -78, -58.8);
    polygon(-71, -61.5, -69, -61.5, -69, -58.8, -71, -58.8);
    polygon(-64, -61.5, -62, -61.5, -62, -58.8, -64, -58.8);


    // suitcase main body
    glColor3ub(120, 82, 45);
    polygon(-79, -58.8, -59, -58.8, -59, -54.5, -79, -54.5);
    // suitcase top highlight
    glColor3ub(148, 102, 60);
    polygon(-79, -54.5, -59, -54.5, -59, -54.0, -79, -54.0);
    // suitcase shadow left side
    glColor3ub(95, 65, 32);
    polygon(-79, -58.8, -77, -58.8, -77, -54.5, -79, -54.5);
    // suitcase edge trim
    glColor3ub(80, 55, 25);
    line(-79, -58.8, -59, -58.8);
    line(-79, -54.5, -59, -54.5);
    line(-79, -58.8, -79, -54.5);
    line(-59, -58.8, -59, -54.5);
    // suitcase center clasp
    glColor3ub(185, 150, 75);
    polygon(-71.5, -54.5, -68.5, -54.5, -68.5, -56.0, -71.5, -56.0);
    glColor3ub(210, 175, 95);
    polygon(-71.2, -54.7, -68.8, -54.7, -68.8, -55.8, -71.2, -55.8);
    // suitcase handle
    glColor3ub(80, 55, 25);
    line(-71.0, -54.5, -71.0, -53.5);
    line(-71.0, -53.5, -69.0, -53.5);
    line(-69.0, -53.5, -69.0, -54.5);
    // suitcase horizontal strap
    glColor3ub(85, 58, 28);
    line(-79, -56.5, -59, -56.5);
    // suitcase corner bolts
    glColor3ub(160, 130, 65);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    glVertex2f(-78.0, -58.5);
    glVertex2f(-60.0, -58.5);
    glVertex2f(-78.0, -54.8);
    glVertex2f(-60.0, -54.8);
    glEnd();
    glPointSize(1.0f);


    //  teddy

    glColor3ub(165, 120, 75);
    circle(-45, -72.2, 2.8f);
    // teddy head — above body
    circle(-45, -68.2, 2.2f);
    // teddy ears
    glColor3ub(150, 105, 62);
    circle(-46.8, -66.5, 1.1f);
    circle(-43.2, -66.5, 1.1f);
    // ear inner
    glColor3ub(195, 155, 110);
    circle(-46.8, -66.5, 0.6f);
    circle(-43.2, -66.5, 0.6f);
    // teddy face patch
    glColor3ub(185, 140, 90);
    circle(-45, -68.5, 1.4f);
    // teddy eyes
    glColor3ub(20, 20, 20);
    circle(-45.8, -68.0, 0.4f);
    circle(-44.2, -68.0, 0.4f);
    // eye shine
    glColor3ub(255, 255, 255);
    glPointSize(1.2f);
    glBegin(GL_POINTS);
    glVertex2f(-45.6, -67.8);
    glVertex2f(-44.0, -67.8);
    glEnd();
    glPointSize(1.0f);
    // teddy nose
    glColor3ub(80, 40, 20);
    circle(-45, -68.8, 0.5f);
    // teddy mouth
    glColor3ub(60, 30, 10);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-45.5, -69.2);
    glVertex2f(-45.0, -69.5);
    glVertex2f(-44.5, -69.2);
    glEnd();
    // teddy tummy patch
    glColor3ub(195, 155, 110);
    circle(-45, -72.5, 1.5f);


    // teddy legs dangling down from body
    // sit at y:-75 edge
    glColor3ub(165, 120, 75);
    circle(-46.5, -74.8, 1.5f);
    circle(-43.5, -74.8, 1.5f);
    // leg bottom (feet)
    glColor3ub(150, 105, 62);
    circle(-46.5, -76.2, 1.0f);
    circle(-43.5, -76.2, 1.0f);
    // teddy bow tie
    glColor3ub(200, 30, 30);
    triangle(-46.2, -70.5, -43.8, -70.5, -45.0, -69.8);
    triangle(-46.2, -70.5, -43.8, -70.5, -45.0, -71.2);
    // bow tie center knot
    glColor3ub(230, 50, 50);
    circle(-45, -70.5, 0.4f);


glPopMatrix();
    //snow
    drawSnow();
//rain
//drawRain();
}
void display() {

     glClearColor(0.4f,0.8f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

if(playScene1==1)
{
    scene1();
}
else if(playScene2==1)
{
    scene2();
}
else if(playScene3==1)
{
    scene3();
}
else if(playScene4==1)
{
    scene4();
}
else if(playScene5==1)
{
    scene5();
}
    glFlush();
}


void stopMusic()
{
    PlaySound(NULL, 0, 0);
}

void playMusic()
{
      switch(currentScene)
    {
        case 1:
            PlaySound(
                TEXT("D:\\pdf\\sem-8\\Computer Graphics\\final\\lab\\Toonverse\\rain.wav"),
                NULL, SND_FILENAME | SND_ASYNC | SND_LOOP
            );
            break;
        case 2:
            PlaySound(
                TEXT("D:\\pdf\\sem-8\\Computer Graphics\\final\\lab\\Toonverse\\up.wav"),
                NULL, SND_FILENAME | SND_ASYNC | SND_LOOP
            );
            break;
        case 3:
            PlaySound(
                TEXT("D:\\pdf\\sem-8\\Computer Graphics\\final\\lab\\Toonverse\\Simpsons.wav"),
                NULL, SND_FILENAME | SND_ASYNC | SND_LOOP
            );
            break;
        case 4:

              PlaySound(TEXT("D:\\pdf\\sem-8\\Computer Graphics\\final\\lab\\Toonverse\\SpongeBob.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;
        case 5:
            PlaySound(TEXT("D:\\pdf\\sem-8\\Computer Graphics\\final\\lab\\Toonverse\\Mr.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;

    }

}



void update(int value) {

//scene 1 and 2sa
waveOffset += 0.05f;
    //car right to left
    scartx = scartx-1.0f;

    //car limit
    if(scartx < -200){
        scartx = 100;
    }

    //boat right to left
    boatx = boatx-1.25f;
    //boat up down
    if(boat == true)
    {
        boaty = boaty + 0.5;
        if(boaty == 1.5)
        {
            boat = false;
        }
    }
    if(boat == false)
    {
        boaty = boaty - 0.5;
        if(boaty == -1.5)
        {
            boat = true;
        }
    }
    //boat limit

    if(boatx < -150)
    {
        boatx = 200;
    }
//cloud left to right
    cloudx = cloudx + 0.1f;
    //cloud limit
    if(cloudx > 120)
    {
        cloudx = 0;
    }
//bird left to right
    birdtx = birdtx + 1.0f;
    birdangle = birdangle - 1;//clockwise rotation -1
//bird limit
    if(birdtx > 120){
        birdtx = -120;
    }

    if(bounceflag){
        balljump = balljump - 0.01f;
        ballty = ballty + balljump;
        if(ballty <= 0.0f)
        {
            ballty = 0.0f;
            balljump = 0;
            bounceflag = false;
        }
    }
//house bottom to top
    housety = housety+0.1f;
    housescale = housescale - 0.001f;
    // house limit
    if(housety > 100)
    {
        housety = 0;
        housescale = 1;
    }


//scene 3
 cartx +=1.0f;
     cloudtx +=.1f;
     loontx+=.1f;
     loonsx -= 0.001f;
     loonsy -= 0.001f;

        if(cartx>200.0f){
            cartx= -130.0f;

        }
        if(cloudtx>50.0f){
            cloudtx= 0.0f;

        }
        if(loontx>60)
        {

            loontx=0.0f;
             loonsx = 1.0f;
     loonsy = 1.0f;
        }
         if (jumpflag) {
        jump -= 0.1f;
        jumpty += jump;


        if (jumpty <= 0.0f) {
            jumpty= 0.0f;
            jump = 0.0f;
            jumpflag = false;
        }
    }



//scene 4

     submarinetx -=1.0f;
    bubblety +=.1f;

        if(submarinetx<-180.0f){
            submarinetx = 80.0f;

        }

        if(bubblety>100.0f){
            bubblety = -50.0f;

        }
//scene 5

beancartx += .75;
if(beancartx>200)
{
    beancartx=-100;
}
londonEyeAngle += 0.15f;
if(londonEyeAngle > 360.0f) londonEyeAngle -= 360.0f;

bigBenClockAngle += 0.3f;
if(bigBenClockAngle > 360.0f) bigBenClockAngle -= 360.0f;

//rain

if(!rainInitialized) rain();

    rainFallOffset -= 2.5f;
    rainDriftOffset -= 0.4f;

    if(rainFallOffset < -200.0f)
        rainFallOffset += 200.0f;

    if(rainDriftOffset < -200.0f)
        rainDriftOffset += 200.0f;


 //bus right to left
    bustx = bustx-.5f;

    //bus limit
    if(bustx < -200){
        bustx = 100;
    }
// snow
snowOffset -= 0.8f;
snowDriftOffset += 0.2f;
if(snowOffset < -200.0f) snowOffset += 200.0f;
if(snowDriftOffset > 200.0f) snowDriftOffset -= 200.0f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
    case '1':
        playScene1 = 1;
        playScene2 = 0;
         playScene3 = 0;
          playScene4 = 0;
            currentScene = 1;
 stopMusic();
    playMusic();
        break;
    case '2':
         playScene1 = 0;
        playScene2 = 1;
         playScene3 = 0;
          playScene4 = 0;
            currentScene = 2;
 stopMusic();
    playMusic();

        break;

    case '3':
         playScene1 = 0;
        playScene2 = 0;
         playScene3 = 1;
          playScene4 = 0;
            currentScene = 3;
 stopMusic();
    playMusic();
        break;

    case '4':
        playScene1 = 0;
        playScene2 = 0;
         playScene3 = 0;
          playScene4 = 1;
          runSubmarine=1;
            currentScene = 4;
 stopMusic();
    playMusic();
        break;
        case '5':
        playScene1 = 0;
        playScene2 = 0;
         playScene3 = 0;
          playScene4 = 0;
         playScene5 = 1;
           currentScene = 5;
 stopMusic();
    playMusic();
        break;
        case 'w':
if(playScene1==1 || playScene2==1){
             if(scarty < 25){
            scarty = scarty+2.0f;
        }
}

            if(playScene4==1) {
            if(spongebobty<15) {spongebobty += 7.5f;}
            }
            break;
        case 's':
            if(playScene1==1 || playScene2==1){
            if(scarty > -7){
            scarty = scarty - 2.0f;
        }
            }
            if(playScene4==1){
              if(spongebobty>-135) {spongebobty -= 7.5f;}
            }
            break;
        case 'a': if(playScene4==1){
        if(spongebobtx>-112.5) {spongebobtx -= 7.5f;}
            }
            if(playScene2==1){
       if(impostertx > -36){
            impostertx = impostertx - 1;

        }
            }
            break;
        case 'd':
            if(playScene2==1){
      if(impostertx < 140){
            impostertx = impostertx + 1;
        }
            }

            if(playScene4==1){
            if(spongebobtx<52.5) {spongebobtx += 7.5f;}
            }
            break;
            case ' ':
                if(bounceflag == false)
        {
            bounceflag = true;
            if(playScene2==1){bounce++;}
            balljump = 0.5;
        }

                if (!jumpflag) {
            jumpflag = true;
            jump= 1 ;
        };
         break;
         case 'o':
              if(musicOn == false)
    {
        musicOn = true;
        playMusic();
    }
         break;
         case 'f':
   if(musicOn == true)
    {
        musicOn = false;
        stopMusic();
    }
    break;
         case 'x':  exit(0);
         break;

    }
    glutPostRedisplay();
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gluOrtho2D(-100, 100, -100, 100);

    glGenTextures(1, &logoTexture);
    glBindTexture(GL_TEXTURE_2D, logoTexture);

    // Set texture wrapping/filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image data
    int width, height, nrChannels;

    unsigned char *data = stbi_load( "D:\\pdf\\sem-8\\Computer Graphics\\final\\lab\\Toonverse\\crown.jpg",&width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        printf("Failed to load texture\n");
    }
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);

    glutInitWindowSize(1000, 768);
    glutInitWindowPosition(250,0);

    glutCreateWindow("Toonverse");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

currentScene = 5;
musicOn = true;
playMusic();
    glutMainLoop();

    return 0;
}
