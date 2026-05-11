#include<windows.h>
#include <GL/glut.h>
#define PI 3.1416
#include<math.h>

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

void scene1()
{
    //sky
    glColor3ub(69, 139, 122);
    polygon(-100, 0, 100, 0, 100, 100, -100, 100);


     //cloud
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


    //road
    glColor3ub(70, 122, 49);
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
    glColor3ub(70, 122, 49);
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
    glColor3ub(70, 129, 67);
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
    glColor3ub(90, 129, 47);
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
    glColor3ub(70, 120, 122);
    polygon(-100, -50, 100, -50, 100, 0, -100, 0);

    //sky line
    glColor3ub(0, 0, 0);
    line(-100, 0, 100, 0);
    //river line
    glColor3ub(0, 0, 0);
    line(-100, -50, 100, -50);


    //up house
    //left house-door
    //window wall
    glColor3ub(20, 40, 80);
    polygon(26, -40, 40, -40, 40, 0, 26, 0);
    //window wall side
    glColor3ub(70, 40, 80);
    polygon(24, -40, 26, -40, 26, 0, 24, 0);
    //door wall
    glColor3ub(70, 40, 210);
    polygon(40, -40, 62, -40, 62, 0, 40, 0);

    //upper railing (left to right)
    glColor3ub(170, 40, 210);
    polygon(28, -12.5, 30, -12.5, 30, -7.5, 28, -7.5);
    polygon(32, -12.5, 34, -12.5, 34, -7.5, 32, -7.5);
    polygon(36, -12.5, 38, -12.5, 38, -7.5, 36, -7.5);
    polygon(42, -12.5, 44, -12.5, 44, -7.5, 42, -7.5);
    polygon(46, -12.5, 48, -12.5, 48, -7.5, 46, -7.5);
    polygon(50, -12.5, 52, -12.5, 52, -7.5, 50, -7.5);
    polygon(54, -12.5, 56, -12.5, 56, -7.5, 54, -7.5);
    //upper railing up-line
    glColor3ub(170, 140, 210);
    line(26, -7.5, 62, -7.5);
    //upper railing lower-line
    line(26, -12.5, 62, -12.5);
    //lower railing
    glColor3ub(170, 40, 210);
    polygon(28, -40, 30, -40, 30, -35, 28, -35);
    polygon(32, -40, 34, -40, 34, -35, 32, -35);
    polygon(36, -40, 38, -40, 38, -35, 36, -35);
    //lower railing line
    glColor3ub(170, 140, 210);
    line(26, -35, 40, -35);

    //window
    //outer window
    glColor3ub(170, 40, 110);
    polygon(28, -32.5, 38, -32.5, 38, -15, 28, -15);
    //inner window
    glColor3ub(170, 210, 110);
    polygon(30, -30, 36, -30, 36, -17.5, 30, -17.5);
    //inner window bar
    glColor3ub(70, 210, 190);
    polygon(30, -25, 36, -25, 36, -22.5, 30, -22.5);
    //window bar
    glColor3ub(70, 170, 190);
    polygon(26, -35, 40, -35, 40, -32.5, 26, -32.5);

    //door
    //outer door
    glColor3ub(170, 170, 190);
    polygon(44, -40, 56, -40, 56, -17.5, 44, -17.5);
    //inner door
    glColor3ub(120, 20, 190);
    polygon(46, -40, 54, -40, 54, -20, 46, -20);

    //stairs bar
    glColor3ub(110, 190, 90);
    polygon(20, -42.5, 60, -42.5, 60, -40, 20, -40);
    //outer stairs
    glColor3ub(210, 190, 90);
    polygon(24, -50, 60, -50, 60, -42.5, 24, -42.5);
    //inner stairs
    glColor3ub(210, 90, 190);
    polygon(26, -47.5, 60, -47.5, 60, -45, 26, -45);
    //middle stairs bar
    glColor3ub(110, 90, 230);
    polygon(38, -50, 40, -50, 40, -40, 38, -40);



    //right house
    //wall
    glColor3ub(70, 70, 90);
    polygon(60, -50, 90, -50, 90, -12.5, 60, -12.5);
    //wall lines
    glColor3ub(50, 50, 50);
    line(70, -50, 70, -12.5);
    line(80, -50, 80, -12.5);

    //left window
    //outer
    glColor3ub(30, 80, 10);
    polygon(61, -35, 69, -35, 69, -20, 61, -20);
    //inner
    glColor3ub(30, 180, 10);
    polygon(62, -32.5, 68, -32.5, 68, -22.5, 62, -22.5);
    //inner bar
    glColor3ub(130, 180, 210);
    polygon(62, -28.5, 68, -28.5, 68, -26.5, 62, -26.5);
    //outer left bar
    glColor3ub(130, 180, 210);
    polygon(61, -37.5, 62, -37.5, 62, -35, 61, -35);
    //outer right bar
    glColor3ub(130, 180, 210);
    polygon(68, -37.5, 69, -37.5, 69, -35, 68, -35);

    //middle window
    //outer
    glColor3ub(30, 80, 10);
    polygon(71, -35, 79, -35, 79, -20, 71, -20);
    //inner
    glColor3ub(30, 180, 10);
    polygon(72, -32.5, 78, -32.5, 78, -22.5, 72, -22.5);
    //inner bar
    glColor3ub(130, 180, 210);
    polygon(72, -28.5, 78, -28.5, 78, -26.5, 72, -26.5);
    //outer left bar
    glColor3ub(130, 180, 210);
    polygon(71, -37.5, 72, -37.5, 72, -35, 71, -35);
    //outer right bar
    glColor3ub(130, 180, 210);
    polygon(78, -37.5, 79, -37.5, 79, -35, 78, -35);

    //left roof
    glColor3ub(50, 50, 50);
    polygon(30, 0, 68, 0, 68, 25, 30, 25);
    //left roof triangle
    triangle(20, 0, 30, 0, 30, 25);


    //right window
    //outer
    glColor3ub(30, 80, 10);
    polygon(81, -35, 89, -35, 89, -20, 81, -20);
    //inner
    glColor3ub(30, 180, 10);
    polygon(82, -32.5, 88, -32.5, 88, -22.5, 82, -22.5);
    //inner bar
    glColor3ub(130, 180, 210);
    polygon(82, -28.5, 88, -28.5, 88, -26.5, 82, -26.5);
    //outer left bar
    glColor3ub(130, 180, 210);
    polygon(81, -37.5, 82, -37.5, 82, -35, 81, -35);
    //outer right bar
    glColor3ub(130, 180, 210);
    polygon(88, -37.5, 89, -37.5, 89, -35, 88, -35);

    //window line
    glColor3ub(50, 50, 50);
    line(60, -15, 90, -15);
    line(60, -17.5, 90, -17.5);
    line(60, -40, 90, -40);
    line(60, -42.5, 90, -42.5);

    //window bar
    glColor3ub(150, 150, 150);
    polygon(60, -12.5, 90, -12.5, 90, -7.5, 60, -7.5);
    triangle(60, -12.5, 60, -7.5, 59, -7.5);//left
    triangle(90, -12.5, 90, -7.5, 91, -7.5);//right

    //2nd floor
    //lower part
    glColor3ub(250, 250, 250);
    polygon(62, -7.5, 88, -7.5, 88, -2.5, 62, -2.5);
    triangle(58, -7.5, 62, -7.5, 62, -2.5);//left
    triangle(88, -7.5, 88, -2.5, 92, -7.5);//left
    //wall
    glColor3ub(250, 250, 250);
    polygon(62, -2.5, 88, -2.5, 88, 12.5, 62, 12.5);
    triangle(62, 12.5, 88, 12.5, 75, 37.5);
    //window
    //outer window
    glColor3ub(50, 50, 50);
    polygon(68, 0, 82, 0, 82, 17.5, 68, 17.5);
    //inner window
    glColor3ub(250, 250, 250);
    polygon(70, 2.5, 80, 2.5, 80, 15, 70, 15);
    //inner window bar
    glColor3ub(50, 50, 50);
    polygon(70, 7.5, 80, 7.5, 80, 10, 70, 10);
    //window bar
    glColor3ub(150, 150, 150);
    polygon(66, -2.5, 84, -2.5, 84, 0, 66, 0);
    //outer bar
    glColor3ub(250, 50, 150);
    polygon(68, -5, 70, -5, 70, -2.5, 68, -2.5);//left
    polygon(80, -5, 82, -5, 82, -2.5, 80, -2.5);//right
    //roof left
    glColor3ub(250, 50, 150);
    polygon(56, 7.5, 60, 7.5, 75, 32.5, 75, 37.5);
    //roof right
    polygon(94, 7.5, 90, 7.5, 75, 32.5, 75, 37.5);
    //roof house
    //wall
    glColor3ub(250, 50, 150);
    polygon(34, 10, 46, 10, 46, 20, 34, 20);
    triangle(34, 20, 46, 20, 40, 34);
    //window
    //outer window
    glColor3ub(50, 50, 150);
    polygon(36, 13.75, 44, 13.75, 44, 22.5, 36, 22.5);
    //inner window
    glColor3ub(50, 50, 50);
    polygon(37, 15.25, 43, 15.25, 43, 21, 37, 21);
    glColor3ub(250, 250, 250);
    line(37, 18.125, 43, 18.125);
    //window bar
    glColor3ub(250, 250, 250);
    polygon(36, 12.5, 38, 12.5, 38, 13.75, 36, 13.75);
    polygon(42, 12.5, 44, 12.5, 44, 13.75, 42, 13.75);
    //left roof
    glColor3ub(50, 150, 250);
    polygon(32, 20, 34, 20, 40, 32.5, 40, 35);
    //right roof
    polygon(46, 20, 48, 20, 40, 35, 40, 32.5);



    //chimney
    glColor3ub(50, 50, 150);
    polygon(54, 25, 60, 25, 60, 32.5, 54, 32.5);
    glColor3ub(150, 150, 150);
    polygon(53, 32.5, 61, 32.5, 61, 33.75, 53, 33.75);




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




    //vector house
    //boundary
    glColor3ub(50, 50, 150);
    polygon(-72, 0, -8, 0, -8, 5, -72, 5);
    //triangle
    glColor3ub(250, 50, 150);
    triangle(-68, 5, -12, 5, -40, 50);
    //house circle
    glColor3ub(150, 150, 250);
    semiCircle(-45, 22.5, 13);
    polygon(-58, 22.5, -58, 12.5, -32, 12.5, -32, 22.5);
    //house wall
    glColor3ub(150, 150, 250);
    polygon(-54, 5, -36, 5, -36, 12.5, -54, 12.5);
    //gate
    glColor3ub(250, 150, 250);
    semiCircle(-45, 5, 5);
    glColor3ub(250, 150, 50);
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



     //simpsson car
     //body
     glColor3ub(250, 150, 250);
     polygon(32, -87.5, 96, -87.5, 96, -75, 32, -75);
     //side part
     glColor3ub(150, 150, 250);
     polygon(30, -87.5, 32, -87.5, 32, -75, 30, -75);
     polygon(96, -87.5, 98, -87.5, 98, -75, 96, -75);
     //upper body
     glColor3ub(150, 150, 250);
     polygon(44, -75, 86, -75, 80, -62.5, 54, -62.5);
     //left window
     glColor3ub(50, 150, 50);
     polygon(46, -75, 64, -75, 64, -65, 54, -65);
     //right window
     polygon(68, -75, 84, -75, 78, -65, 68, -65);
     //left door
     glColor3ub(250, 10, 50);
     polygon(46, -85, 84, -85, 84, -75, 46, -75);
     glColor3ub(250, 150, 250);
     semiCircle(43, -87.5, 8);//left
     semiCircle(87, -87.5, 8);//left
     //door divider
     glColor3ub(50, 10, 50);
     line(66, -62.5, 66, -85);
     //door handle
     glColor3ub(50, 10, 50);
     polygon(60, -78.75, 64, -78.75, 64, -76.25, 60, -76.25);
     polygon(78, -78.75, 82, -78.75, 82, -76.25, 78, -76.25);
     //headlight
     glColor3ub(250, 210, 250);
     polygon(28, -87.5, 34, -87.5, 34, -82.5, 28, -82.5);
     //left tire
     //shade
     glColor3ub(250, 20, 250);
     semiCircle(43, -87.5, 7);
     glColor3ub(150, 20, 250);
     circle(43, -87.5, 5);
     glColor3ub(250, 20, 250);
     circle(43, -87.5, 2.5);
     //right tire
     //shade
     glColor3ub(250, 20, 250);
     semiCircle(87, -87.5, 7);
     glColor3ub(150, 20, 250);
     circle(87, -87.5, 5);
     glColor3ub(250, 20, 250);
     circle(87, -87.5, 2.5);
     //door line
     glColor3ub(250, 220, 250);
     line(34, -77.5, 42, -77.5);

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    scene1();

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1000, 768);
    glutInitWindowPosition(250,0);
    glutCreateWindow("ToonLand");

    init();


    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
