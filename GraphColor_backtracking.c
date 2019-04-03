#include <GL/glut.h>
#include <GL/gl.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#include<time.h>
int matrix[10][10]={
                   {0,1,1,1,1,1,0,0,0,0},
                   {1,0,0,1,1,0,0,0,0,0},
                   {1,0,0,0,0,0,1,0,1,0},
                   {1,1,0,0,0,0,1,0,0,0},
                   {1,1,0,0,0,0,0,1,0,0},
                   {1,0,0,0,0,0,0,0,1,0},
                   {0,0,1,1,0,0,0,0,0,0},
                   {0,0,0,0,1,0,0,0,0,0},
                   {0,0,1,0,0,1,0,0,0,1},
                   {0,0,0,0,0,0,0,0,1,0}
                   };
int colormat[10]={0,0,0,0,0,0,0,0,0,0};
char cities[11][50] ={"Dehradun","Haridwar","Mussorie","Rishikesh","Roorkee","Vikasnagar","Chamba","Delhi","Chakrata","Shimla",""};
int boxindex[10][10]={{250,250},{310,220},{310,290},{310,250},{190,220},{190,290},{370,290},{130,190},{250,320},{190,360}};
void delay(int number_of_seconds) { 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
    // Stroing start time 
    clock_t start_time = clock(); 
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
} 
void *font = GLUT_BITMAP_TIMES_ROMAN_10;
void *fonts[] = {
      GLUT_BITMAP_9_BY_15,
      GLUT_BITMAP_TIMES_ROMAN_10,
      GLUT_BITMAP_TIMES_ROMAN_24
};
int mouseX=0;
int mouseY=0;
void drawLine(int x1,int y1,int x2,int y2){
    glBegin(GL_LINES);
        glVertex2f(x1 ,y1);
        glVertex2f(x2 ,y2);        
    glEnd();
}
void drawRectangle(int x,int y){
    glBegin(GL_LINES);
        glVertex2f(x ,y);
        glVertex2f(x ,y+10);

        glVertex2f(x ,y+10);
        glVertex2f(x+50 ,y+10);

        glVertex2f(x+50 ,y+10);
        glVertex2f(x+50 ,y);

        glVertex2f(x+50 ,y);
        glVertex2f(x ,y);
        
    glEnd();
}
void writeName(int x,int y,char name[]){
    int len, i;
      glRasterPos2f(x, y);
      len = (int) strlen(name);
      for (i = 0; i < len; i++)
            glutBitmapCharacter(font, name[i]);
}
void fillColor(int x, int y){
    delay(200);
    glBegin(GL_POLYGON);
        glVertex2f(x ,y);
        glVertex2f(x ,y+10);
        glVertex2f(x+50 ,y+10);
        glVertex2f(x+50 ,y);               
    glEnd();
    glFlush();
    glColor3f(0.0,0.0,0.0);

}
void startFillinColor(int color,int pos){
    int j=color;
    int count=0;
    int k=pos;
    while(count<10){
    for(k;k<10;k++)
        {   bool canColor=false;
            while(!canColor&&j<4)
            {
                canColor=true;
                for(int i=0;i<10;i++){
                    if(matrix[k][i]==1)
                    {
                        if(j==colormat[i])
                        {
                        j++;
                        canColor=false;
                        break;
                        }
                    }
                }
            }
            if(canColor&&j<4)
                {
                    switch (j) {
                    case 1:
                            glColor3f( 1.0,0.0,0.0);
                            break;
                    case 2:
                            glColor3f( 0.0,1.0,0.0);
                            break;
                    case 3:
                            glColor3f( 0.0,0.0,1.0);
                            break;
                    }
                    fillColor(boxindex[k][0],boxindex[k][1]);  
                    glColor3f( 0.0,0.0,0.0);
                    writeName(boxindex[k][0]+5,boxindex[k][1]+3,cities[k]);
                    colormat[k]=j;
                    j=1;
                    count++;
                }
            else{
                    k--;
            }
        }
        k=0;
    }
    
}
void renderFunction(){
    glClearColor(1.0,1.0,1.0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,0.0);
    for(int i=0;i<10;i++)
    {
        drawRectangle(boxindex[i][0],boxindex[i][1]);
        writeName(boxindex[i][0]+5,boxindex[i][1]+3,cities[i]);
    } 
    drawLine(280,250,310,220);
    drawLine(280,260,310,290);
    drawLine(300,255,310,255);
    drawLine(250,250,220,230);
    drawLine(250,260,220,290);
    drawLine(360,295,370,295);
    drawLine(340,260,400,290);
    drawLine(325,230,325,250);
    drawLine(310,220,220,220);
    drawLine(190,220,160,200);
    drawLine(220,300,250,320);
    drawLine(280,320,310,300);
    drawLine(250,330,220,360);
    glFlush();
    
}
void processMenuEvents(int option) {
    
    for(int i=0;i<10;i++)
        {
            colormat[i]=0;
        }
    renderFunction();
    for(int j=0;j<10;j++)
    {
    if(mouseX>=boxindex[j][0]&&mouseX<=boxindex[j][0]+50&&mouseY>=boxindex[j][1]&&mouseY<=boxindex[j][1]+10){
       startFillinColor(option,j); 
       }
    }
    //checkSelectedCity(mouseX,mouseY,option);
    glFlush();
   
}
void createGLUTMenus() {
	int menu;
	menu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAttachMenu(GLUT_LEFT_BUTTON);
}
void mouse(int state, int x, int y) 
    {   
        y=500-y;
        if(state == GLUT_MENU_IN_USE){ 
            mouseX=x;
            mouseY=y;
        }
}
void init() {  
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Constraint Satisfaction Problem");
  glClearColor(1.0,1.0,1.0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(0,500,0,500); 
  
}
int main(int argc, char **argv) {
  
  glutInit(&argc, argv);
  init();
  glutDisplayFunc(renderFunction);
   createGLUTMenus();
  glutMenuStatusFunc(mouse);
  glutMainLoop();
  return 0;
}
