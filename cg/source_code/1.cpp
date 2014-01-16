//3D SIERPINSKI GASKET

#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
typedef float point[3];
point v[]={{0.0,0.0,1.0},{0.0,1.0,0.0},
           {-1.0,-0.5,0.0}, {1.0,-0.5,0.0}};
int n;

void triangle(point a,point b,point c)
{
	glBegin(GL_POLYGON);
	  glVertex3fv(a);
	  glVertex3fv(b);
	  glVertex3fv(c);
	glEnd();
}

void divide_triangle(point a,point b,point c,int m)
{
	point v1,v2,v3;
	int j;
	if(m>0)
	{
		for(j=0;j<3;j++)
			v1[j]=(a[j]+b[j])/2;
		for(j=0;j<3;j++)
			v2[j]=(a[j]+c[j])/2;
		for(j=0;j<3;j++)
			v3[j]=(c[j]+b[j])/2;
		divide_triangle(a,v1,v2,m-1);
		divide_triangle(c,v2,v3,m-1);
		divide_triangle(b,v3,v1,m-1);
	}
	else(triangle(a,b,c));
}

void tetrahedron(int m)
{
	glColor3f(1.0,0.0,0.0);
	divide_triangle(v[0],v[1],v[2],m);
	glColor3f(0.0,1.0,0.0);
	divide_triangle(v[3],v[2],v[1],m);
	glColor3f(0.0,0.0,1.0);
	divide_triangle(v[0],v[3],v[1],m);
	glColor3f(0.0,0.0,0.0);
	divide_triangle(v[0],v[2],v[3],m);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	tetrahedron(n);
	glFlush();
}

void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w, 
2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
glOrtho(-2.0*(GLfloat)w/(GLfloat)h,    
 2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void main(int argc,char ** argv)
{
 	printf("No of Division?: ");
scanf("%d",&n);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH;
glutCreateWindow("3D gasket");
glutReshapeFunc(myReshape);
glutDisplayFunc(display);
glEnable(GL_DEPTH_TEST);
glClearColor(1.0,1.0,1.0,0.0);
glutMainLoop();
}






LIANG-BARSKY LINE CLIPPING ALGORITHM

#include<stdio.h>
#include<GL/glut.h>
double xmin=50,ymin=50,xmax=100,ymax=100;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;
double x0,y0,x1,y1;

int cliptest(double p,double q,double *t1,double *t2)
{
	double t=q/p;
	if(p<0.0)
	{
		if(t> *t1) *t1=t;
		if(t> *t2) return(false);
	}
	else if(p>0.0)
	{
			if(t< *t2) *t2=t;
			if(t< *t1) return(false);
	}
	else if(p==0.0)
	{
				if(q<0.0) return(false);
	}
	return(true);
}

void LiangBarsky(double x0,double y0,double x1,double y1)
{
	double dx=x1-x0,dy=y1-y0,te=0.0,tl=1.0;
	if(cliptest(-dx,x0-xmin,&te,&tl))
	if(cliptest(dx,xmax-x0,&te,&tl))
	if(cliptest(-dy,y0-ymin,&te,&tl))
	if(cliptest(dy,ymax-y0,&te,&tl))
	{
		if(tl<1.0)
		{
			x1=x0+tl*dx;
			y1=y0+tl*dy;
		}
		if(te>0.0)
		{
			x0=x0+te*dx;
			y0=y0+te*dy;
		}
		
		double sx=(xvmax-xvmin)/(xmax-xmin);
		double sy=(yvmax-yvmin)/(ymax-ymin);
		double vx0=xvmin+(x0-xmin)*sx;
		double vy0=yvmin+(y0-ymin)*sy;
		double vx1=xvmin+(x1-xmin)*sx;
		double vy1=yvmin+(y1-ymin)*sy;
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINE_LOOP);
			glVertex2f(xvmin,yvmin);
			glVertex2f(xvmax,yvmin);
			glVertex2f(xvmax,yvmax);
			glVertex2f(xvmin,yvmax);
		glEnd();
		glColor3f(0.0,0.0,1.0);
		glBegin(GL_LINES);
			glVertex2d(vx0,vy0);
			glVertex2d(vx1,vy1);
		glEnd();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex2d(x0,y0);
		glVertex2d(x1,y1);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin,ymin);
		glVertex2f(xmax,ymin);
		glVertex2f(xmax,ymax);
		glVertex2f(xmin,ymax);
	glEnd();
	LiangBarsky(x0,y0,x1,y1);
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,499.0,0.0,499.0);
}
void main(int argc,char ** argv)
{
	printf("Enter the end points of the line: ");
	scanf("%lf%lf%lf%lf", &x0,&y0,&x1,&y1);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("2nd program");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}
