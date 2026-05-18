#include <iostream>
using namespace std;
#include<windows.h>
#include <GL/glut.h>
#define PI 3.1416
#include<math.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

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


int scene1 = 1;
int scene2 = 0;

void circle(float x, float y, float ra) {
	int i;
    GLfloat p1 = x; GLfloat q1 = y; GLfloat r1 = ra;
    int tringle2=40;
    GLfloat tp2 =2.0f * PI  ;
    glBegin (GL_TRIANGLE_FAN);

    glVertex2f (p1,q1);
    for(i= 0;i<=tringle2; i++)
    {
        glVertex2f (
                    p1+(r1*cos(i*tp2/tringle2)),
                    q1+(r1*sin(i*tp2/tringle2))
                    );
    }
    glEnd ();
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

void polygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3)
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
     glVertex2f(x1, y1);
     glVertex2f(x2, y2);
     glEnd();
}

void sceneDay()
{

    //sky
    glColor3ub(0, 191, 255);
    polygon(-100, 0, 100, 0, 100, 100, -100, 100);

    //sun
    glColor3ub(255, 255, 0);
    circle(-75, 81.25, 7);


     //cloud
     glPushMatrix();
     glTranslatef(cloudx, cloudy, 0.0f);
    glColor3ub(255,255,255);
    circle(-60,87.5,4);
    circle(-64,87.5,3);
    circle(-56,87.5,3);

     glColor3ub(255,255,255);
    circle(-20,75,8);
    circle(-28,75,5);
    circle(-12,75,5);

    glColor3ub(255,255,255);
    circle(40,80,6);
    circle(46,80,4);
    circle(34,80,4);

    glColor3ub(255,255,255);
    circle(-120,75,8);
    circle(-128,75,5);
    circle(-112,75,5);
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
    //forest 1st layer (left to right)
    glColor3ub(0, 100, 0);
    circle(-85, 16.5, 8); //1
    circle(-65, 16.5, 8); //2
    circle(-45, 16.5, 8); //3
    circle(-25, 16.5, 8); //4
    circle(-5, 16.5, 8); //5
    circle(20, 16.5, 8); //6
    circle(40, 16.5, 8); //7
    circle(60, 16.5, 8); //8
    circle(80, 16.5, 8); //9

    //forest 2nd layer (left to right)
    glColor3ub(0, 139, 0);
    circle(-95, 10, 8); //1
    circle(-80, 10, 8); //2
    circle(-65, 10, 8); //3
    circle(-50, 10, 8); //4
    circle(-35, 10, 8); //5
    circle(-20, 10, 8); //6
    circle(-5, 10, 8); //7
    circle(10, 10, 8); //8
    circle(25, 10, 8); //9
    circle(40, 10, 8); //10
    circle(55, 10, 8); //11
    circle(70, 10, 8); //12
    circle(85, 10, 8); //13
    circle(100, 10, 8); //14

    //forest 3rd layer (left to right)
    glColor3ub(50, 205, 50);
    circle(-100, 5, 6.5); //1
    circle(-90, 5, 6.5); //2
    circle(-80, 5, 6.5); //3
    circle(-70, 5, 6.5); //4
    circle(-60, 5, 6.5); //5
    circle(-50, 5, 6.5); //6
    circle(-40, 5, 6.5); //7
    circle(-30, 5, 6.5); //8
    circle(-20, 5, 6.5); //9
    circle(-10, 5, 6.5); //10
    circle(0, 5, 6.5); //11
    circle(10, 5, 6.5); //12
    circle(20, 5, 6.5); //13
    circle(30, 5, 6.5); //14
    circle(40, 5, 6.5); //15
    circle(50, 5, 6.5); //16
    circle(60, 5, 6.5); //17
    circle(70, 5, 6.5); //18
    circle(80, 5, 6.5); //19
    circle(90, 5, 6.5); //20
    circle(100, 5, 6.5); //21

    //river
    glColor3ub(0, 191, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-100, -50);
    glVertex2f(100, -50);
    glColor3ub(16, 78, 139);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glEnd();

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



    //street lamp
    //lower part
    glColor3ub(128,0,0);
    polygon(-98,-50,-98,-45,-92,-45,-92,-50);
    polygon(-98,-45,-96,-42.5,-94,-42.5,-92,-45);
    polygon(-96,-42.5,-96,0,-94,0,-94,-42.5);
    polygon(-96,0,-98,2.5,-92,2.5,-94,0);
    //light
    glColor3ub(255,255,153);
    polygon(-96,2.5,-98,7.5,-92,7.5,-94,2.5);
    //upper part
    glColor3ub(128,0,0);
    polygon(-97,7.5,-97,10,-93,10,-93,7.5);
    triangle(-96,10,-95,12.5,-94,10);




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
     glColor3ub(0, 135, 0);
     polygon(-60, -45, -46, -45, -46, -25, -60, -25);
     semiCircle(-53, -25, 7);
     //leg
     polygon(-60, -50, -56, -50, -56, -45, -60, -45);//left
     polygon(-50, -50, -46, -50, -46, -45, -50, -45);//right
     //bag
     glColor3ub(0, 100, 0);
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
     glColor3ub(139, 71, 137);
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
     glColor3ub(70, 0, 140);
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



     //simpsons car
     //body
     glPushMatrix();
     glTranslatef(scartx, scarty, 0.0f);
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



void sceneNight()
{

    //sky
    glColor3ub(0, 0, 128);
    polygon(-100, 0, 100, 0, 100, 100, -100, 100);


    //moon
    glColor3ub(255, 255, 255);
    circle(75, 81.25, 7);

     //cloud
     glPushMatrix();
     glTranslatef(cloudx, cloudy, 0.0f);
    glColor3ub(102,102,102);
    circle(-60,87.5,4);
    circle(-64,87.5,3);
    circle(-56,87.5,3);

    circle(-20,75,8);
    circle(-28,75,5);
    circle(-12,75,5);

    circle(40,80,6);
    circle(46,80,4);
    circle(34,80,4);

    circle(-120,75,8);
    circle(-128,75,5);
    circle(-112,75,5);
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
    glColor3ub(0, 0, 0);
    circle(-85, 16.5, 8); //1
    circle(-65, 16.5, 8); //2
    circle(-45, 16.5, 8); //3
    circle(-25, 16.5, 8); //4
    circle(-5, 16.5, 8); //5
    circle(20, 16.5, 8); //6
    circle(40, 16.5, 8); //7
    circle(60, 16.5, 8); //8
    circle(80, 16.5, 8); //9

    //forest 2nd layer (left to right)
    glColor3ub(0, 139, 0);
    circle(-95, 10, 8); //1
    circle(-80, 10, 8); //2
    circle(-65, 10, 8); //3
    circle(-50, 10, 8); //4
    circle(-35, 10, 8); //5
    circle(-20, 10, 8); //6
    circle(-5, 10, 8); //7
    circle(10, 10, 8); //8
    circle(25, 10, 8); //9
    circle(40, 10, 8); //10
    circle(55, 10, 8); //11
    circle(70, 10, 8); //12
    circle(85, 10, 8); //13
    circle(100, 10, 8); //14

    //forest 3rd layer (left to right)
    glColor3ub(50, 205, 50);
    circle(-100, 5, 6.5); //1
    circle(-90, 5, 6.5); //2
    circle(-80, 5, 6.5); //3
    circle(-70, 5, 6.5); //4
    circle(-60, 5, 6.5); //5
    circle(-50, 5, 6.5); //6
    circle(-40, 5, 6.5); //7
    circle(-30, 5, 6.5); //8
    circle(-20, 5, 6.5); //9
    circle(-10, 5, 6.5); //10
    circle(0, 5, 6.5); //11
    circle(10, 5, 6.5); //12
    circle(20, 5, 6.5); //13
    circle(30, 5, 6.5); //14
    circle(40, 5, 6.5); //15
    circle(50, 5, 6.5); //16
    circle(60, 5, 6.5); //17
    circle(70, 5, 6.5); //18
    circle(80, 5, 6.5); //19
    circle(90, 5, 6.5); //20
    circle(100, 5, 6.5); //21

    //river
    glColor3ub(0, 0, 205);
    glBegin(GL_POLYGON);
    glVertex2f(-100, -50);
    glVertex2f(100, -50);
    glColor3ub(0, 0, 139);
    glVertex2f(100, 0);
    glVertex2f(-100, 0);
    glEnd();

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
    glColor3ub(205, 201, 201);
    polygon(-30, -25, 10, -25, 10, -27.5, -30, -27.5);
    polygon(-30, -27.5, 10, -27.5, 10, -30, -29, -30);
    glColor3ub(0, 0, 0);
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



    //angry bird
     //tail
     glPushMatrix();
     glTranslatef(birdtx, birdty, 0.0f);
     glRotatef(birdangle, 0.0f, 0.0f, 1.0f);
     glTranslatef(-18.0f, -65.0f, 0.0f);
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




    //street lamp
    //lower part
    glColor3ub(128,0,0);
    polygon(-98,-50,-98,-45,-92,-45,-92,-50);
    polygon(-98,-45,-96,-42.5,-94,-42.5,-92,-45);
    polygon(-96,-42.5,-96,0,-94,0,-94,-42.5);
    polygon(-96,0,-98,2.5,-92,2.5,-94,0);
    //light
    glColor3ub(255,193,37);
    polygon(-96,2.5,-98,7.5,-92,7.5,-94,2.5);
    //upper part
    glColor3ub(128,0,0);
    polygon(-97,7.5,-97,10,-93,10,-93,7.5);
    triangle(-96,10,-95,12.5,-94,10);




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
     glColor3ub(139, 71, 137);
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
     glColor3ub(70, 0, 140);
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
     glColor3ub(237, 230, 133);//light
     //polygon(0, -75, 0, -82.5, 30, -82.5, 30, -75);
     //triangle(0, -70, 0, -75,30, -75);//up
     //triangle(0, -82.5, 0, -87.5, 30, -82.5);//low
     polygon(-20, -90, 10, -90, 28, -82.5, 30, -75);
     triangle(28, -82.5, 30, -82.5, 30, -75);
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


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    if(scene1 == 1)
    {
        sceneDay();
    }
    if(scene2 == 1)
    {
        sceneNight();
    }



    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{

    switch(key)
    {
    case 'w':
        if(scarty < 25){
            scarty = scarty+2.0f;
        }
        break;

    case 's':
        if(scarty > -7){
            scarty = scarty - 2.0f;
        }

        break;

    case ' ':
        if(bounceflag == false)
        {
            bounceflag = true;
            bounce++;
            balljump = 0.5;
        }
        break;

    case 'a':
        if(impostertx > -36){
            impostertx = impostertx - 1;

        }
         break;


    case 'd':
        if(impostertx < 140){
            impostertx = impostertx + 1;
        }

        break;

    case '1':
         scene1 = 1;
         scene2 = 0;
         break;

    case '2':
         scene1 = 0;
         scene2 = 1;
    }

    glutPostRedisplay();
}

void update(int value)
{
    scartx = scartx-1.0f;

    if(scartx < -200){
        scartx = 100;
    }

    boatx = boatx-1.25f;
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

    if(boatx < -150)
    {
        boatx = 200;
    }

    cloudx = cloudx + 0.1f;
    if(cloudx > 120)
    {
        cloudx = 0;
    }

    birdtx = birdtx + 1.0f;
    birdangle = birdangle - 1;

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

    housety = housety+0.1f;
    housescale = housescale - 0.001f;
    if(housety > 100)
    {
        housety = 0;
        housescale = 1;
    }


    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 768);
    glutInitWindowPosition(250,0);
    glutCreateWindow("ToonLand");

    init();


    PlaySound(TEXT("D:\\pdf\\sem-8\\Computer Graphics\\final\\lab\\s1\\backgroundMusic.wav"),
          NULL,
          SND_FILENAME | SND_ASYNC | SND_LOOP);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);
    cout<< "Press '1' for scene 1." << endl;
    cout << "Press '2' for scene 2." << endl;
    cout << "Press SPACE to jump." << endl;
    cout << endl;
    cout << "To move Imposter:" << endl;
    cout << "Press 'a' for LEFT." << endl;
    cout << "Press 'd' for RIGHT." << endl;
    cout << "To move Simpsons car:" << endl;
    cout << "Press 'w' for UP." << endl;
    cout << "Press 's' for DOWN." << endl;
    cout << endl;
    cout<< "To summon the Pokemon from Pokemon Ball."<<endl;
    cout<< "Press SPACE 4 time." << endl;
    glutMainLoop();
    return 0;
}
