
//Dan Miller and The funky Bunch
//Project 3

/*
 * References:
 * Simple House Program, code modified from that framework
 * https://users.cs.jmu.edu/bernstdh/web/common/lectures/slides_opengl-text.php - Text Drawing
 * 
 */


#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <unistd.h>   //sleep
#include <stdio.h>
#include <math.h>
#include <time.h>
#include<stdlib.h>
#define MAPSIZE 20

typedef GLfloat point3[3];

void initMap(short int[MAPSIZE][MAPSIZE]);
void createMainPath(short int[MAPSIZE][MAPSIZE]);
void printMap(short int[MAPSIZE][MAPSIZE]);
void walk(int c_row, int c_col, int e_row, int e_col,short int[MAPSIZE][MAPSIZE]);
void branch(int, int, short int[MAPSIZE][MAPSIZE]);
void createBranches(short int [MAPSIZE][MAPSIZE], int);
void myinit(void);
void drawCards(void);
void display(void);
void reshape(int, int);
void axis(void);
void drawLegs(void);
float eyeX = 0.0;
float eyeY = 0.0;
float eyeZ = 0.0;
float centerY=0.0;
float centerX=9.0;
float centerZ=0.0;
int currentAngle = 0;
int lastX = 0;
int lastY = 0;
float xPoints[500];
float zPoints[500];
int num_points=500;

void myinit(void)
{
	glEnable (GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);

}

//draw cards
void drawCards (void)
{

}



void display( void )
{


}

void reshape(int w,int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w/(float)h, 1.0, 300.0);
}
void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if(button == GLUT_LEFT_BUTTON) {
		exit(0); 
	}
}
void myKey(unsigned char key,int x, int y){
 
     if(key == 'w' || key == 'W')
     {
            float radians = currentAngle*3.14 / 180;
            eyeX = eyeX + cos(radians);
            centerX = centerX + cos(radians);
 
            eyeZ = eyeZ + sin(radians);
            centerZ = centerZ + sin(radians);
     }
     else if(key == 's' || key == 'S')
          //have to add this soon
     else if(key == 'a' || key == 'A')
          {    
          if(currentAngle >=0 && currentAngle <= 90){
             centerX = centerX + 0.1;
             centerZ = centerZ - 0.1;
          }
          else if(currentAngle > 90 && currentAngle < 180){
            centerZ = centerZ + 0.1;
            centerX = centerX + 0.1;
          }
          else if(currentAngle > 180 && currentAngle <= 270)
          {
               centerZ = centerZ + 0.1;
               centerX = centerX - 0.1;
           }
           else if(currentAngle > 270 && currentAngle < 360)
           {
                centerX = centerX - 0.1;
                centerZ = centerZ - 0.1;
            }
          
           if(currentAngle == 0)
             currentAngle = 359;
           else
               currentAngle--;
               
     }
     else if(key == 'd' || key == 'D')
     {    
          if(currentAngle > 0 && currentAngle < 90){
             centerX = centerX - 0.1;
             centerZ = centerZ + 0.1;
          }
          else if(currentAngle >= 90 && currentAngle <= 180){
            centerZ = centerZ - 0.1;
            centerX = centerX - 0.1;
          }
          else if(currentAngle > 180 && currentAngle <= 270)
          {
               centerZ = centerZ - 0.1;
               centerX = centerX + 0.1;
           }
           else if(currentAngle > 270 && currentAngle < 359)
           {
                centerX = centerX + 0.1;
                centerZ = centerZ + 0.1;
            }
          
           if(currentAngle == 359)
             currentAngle = 0;
           else
               currentAngle++;   
     }
 
 
     display();  
}
void processMousePassiveMotion(int x,int y){
     //Nick may add something here later for funsies
}
int main(int argc, char** argv)
{        
	//Generate map foundation
	short int map[MAPSIZE][MAPSIZE];
	int branch_chance = 50;
	initMap(map);
	createMainPath(map);
	createBranches(map, branch_chance);
	printMap(map);
	system("pause");
	/* Standard GLUT initialization */
	//glutInit(&argc,argv);
	/*glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(50,50);
    glutCreateWindow("War Games Scene");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
	glutKeyboardFunc(myKey);*/






	//myinit();
	//glutMainLoop(); /* enter event loop */
}
void createBranches(short int in[MAPSIZE][MAPSIZE],int num) {
	//function creates random branches along the main path
	int i,j;
	srand(time(NULL));

	for (i = 0; i < MAPSIZE - 1; i++) {
		for (j = 0; j < MAPSIZE - 1; j++) {
			if ( in[i][j] == 5 && rand() %100 < num)
				branch(i,j,in);  
		}
	}          
}
void branch(int s_row, int s_col, short int in[MAPSIZE][MAPSIZE]) {
	//s_row and s_col refer to a grid in the array where there is a 5.  At this point the path will branch



	//branch in a random direction
	int direction = rand()% 7+1;
	int die_chance = 5;
	switch (direction) {
	case 1:
		if (in[s_row-1][s_col-1] != 0 && in[s_row-1][s_col-1] != 5) {
			if (rand()%100 > die_chance)
				branch(s_row-1,s_col-1,in);
			break;

		}

	case 2:
		if (in[s_row-1][s_col] != 0 && in[s_row-1][s_col] != 5) {
			in[s_row-1][s_col] = 6;
			if (rand()%100 > die_chance)
				branch(s_row-1,s_col,in);

			break;
		}

	case 3:
		if (in[s_row-1][s_col+1] != 0 && in[s_row-1][s_col+1] != 5) {
			in[s_row-1][s_col+1] = 6;
			if (rand()%100 > die_chance)
				branch(s_row-1,s_col+1,in);

			break;
		}

	case 4:
		if (in[s_row][s_col-1] != 0 && in[s_row][s_col-1] != 5) {
			in[s_row][s_col-1] = 6;
			if (rand()%100 > die_chance)
				branch(s_row,s_col-1,in);

			break;
		}

	case 5:
		if (in[s_row][s_col+1] != 0 && in[s_row][s_col+1] != 5) {
			in[s_row][s_col+1] = 6;
			if (rand()%100 > die_chance)
				branch(s_row,s_col+1,in);

			break;
		}

	case 6:
		if (in[s_row+1][s_col-1] != 0 && in[s_row+1][s_col-1] != 5) {
			in[s_row+1][s_col-1] = 6;
			if (rand()%100 > die_chance)
				branch(s_row+1,s_col-1,in);

			break;
		}

	case 7:
		if (in[s_row+1][s_col] != 0 && in[s_row+1][s_col] != 5) {
			in[s_row+1][s_col] = 6;
			if (rand()%100 > die_chance)
				branch(s_row+1,s_col,in);

			break;
		}

	case 8:
		if (in[s_row+1][s_col+1] != 0 && in[s_row+1][s_col+1] != 5) {
			in[s_row+1][s_col+11] = 6;
			if (rand()%100 > die_chance)
				branch(s_row+1,s_col+1,in);
			break;

		}

	default:
		break;
	}
}
void initMap(short int in[MAPSIZE][MAPSIZE]) {
	int i, j;
	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) {
			if ( i == 0 || j == 0 || i == (MAPSIZE - 1) || (j == MAPSIZE - 1))
				in[i][j] = 0;
			else
				in[i][j] = 1;
		}
	}
}
void createMainPath(short int in[MAPSIZE][MAPSIZE]){
	int i,j;                 //loop control variables
	int start, end;


	//first generate the random start and end rows along the main path
	srand(time(NULL));
	start = rand() % (MAPSIZE-3) + 1;
	end = rand() % (MAPSIZE-3) + 1;


	walk(start,1,end,MAPSIZE-2,in); 
	in[start][1] = 3;
	in[end][MAPSIZE-2] = 4;    
}
void walk(int c_row, int c_col, int e_row, int e_col,short int in[MAPSIZE][MAPSIZE]){
	if (c_row == e_row && c_col == e_col)
		return;
	else {
		int decider = rand()%100 + 1;
		if (decider <= 20) {
			//go right

			if (in[c_row][c_col+1] != 0) {
				in[c_row][c_col+1] = 5;
				walk( c_row, c_col+1, e_row, e_col, in);
			}
			else {
				walk(c_row,c_col,e_row,e_col,in);
			}                         
		}
		else if (decider <=40) {
			//go up right

			if (in[c_row-1][c_col+1] != 0) {
				in[c_row-1][c_col+1] = 5;
				walk( c_row-1, c_col+1, e_row, e_col, in);
			}
			else {
				walk(c_row,c_col,e_row,e_col,in);
			}

		}
		else if (decider <=60) {
			//go down right

			if (in[c_row+1][c_col+1] != 0) {
				in[c_row+1][c_col+1] = 5;
				walk( c_row+1, c_col+1, e_row, e_col, in);
			}
			else {
				walk(c_row,c_col,e_row,e_col,in);
			}

		}
		else if (decider <=80) {
			//go up

			if (in[c_row-1][c_col] != 0) {
				in[c_row-1][c_col] = 5;
				walk( c_row-1, c_col, e_row, e_col, in);
			}
			else {
				walk(c_row,c_col,e_row,e_col,in);
			}

		}
		else if (decider > 70) {

			//go down

			if (in[c_row+1][c_col] != 0) {

				in[c_row+1][c_col] = 5;
				walk( c_row+1, c_col, e_row, e_col, in);
			}
			else if (in[c_row][c_col-1] != 0) {

				in[c_row][c_col-1] = 5;
				walk( c_row, c_col-1, e_row, e_col, in);
			}
			else if (in[c_row][c_col+1] != 0) {

				in[c_row][c_col+1] = 5;
				walk( c_row, c_col+1, e_row, e_col, in);
			} 

			else if (in[c_row-1][c_col] != 0) {

				in[c_row-1][c_col] = 5;
				walk( c_row-1, c_col, e_row, e_col, in);
			}

		}
	}     
}
void printMap(short int out[MAPSIZE][MAPSIZE]) {
	int i, j;
	for (i = 0; i < MAPSIZE; i++) {
		for (j = 0; j < MAPSIZE; j++) {
			printf(" %i ", out[i][j]);
		}
		printf("\n");
	}
}

