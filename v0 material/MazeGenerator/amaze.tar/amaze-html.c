/* amaze-html: make random web mazes by walking around aimlessly

Copyright (C) 2008 Henry Kroll www.thenerdshow.com

    . You might find stuff like this in the Public Domain.
    . I made this as a fun exercise, without consulting them.
    . I am not a programmer. This could be an error trove!
    . You are free use, copy and modify this "software."

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.

*/

/*
>gcc -Wall -pedantic -O2 "amaze.c" -o "amaze"
>Exit code: 0

>./"amaze"
Usage: ./amaze ROWS<=39 COLS<=39 [color 1-8] [wall char]
Example: ./amaze 11 15 @
>Exit code: 1

>./amaze 6 35 3 @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@       @                     @         @     @             @         @
@ @@@ @ @ @@@@@@@ @@@@@ @@@@@ @ @@@@@@@@@ @ @@@ @ @@@ @@@@@@@ @@@@@ @@@
@   @ @ @ @     @ @   @     @   @         @     @   @ @       @   @   @
@ @@@ @ @@@ @@@ @ @ @ @@@@@ @@@@@ @@@@@@@@@@@@@@@ @ @ @ @@@@@@@@@ @@@ @
@ @   @     @   @ @ @       @             @     @ @ @ @   @     @   @ @
@@@ @@@@@@@@@ @@@@@ @@@@@@@@@ @@@@@@@@@@@@@ @@@ @ @ @@@@@ @@@ @ @ @ @ @
@ @       @ @ @     @       @   @   @       @ @ @ @           @   @ @ @
@ @@@@@@@ @ @ @@@ @@@ @@@@@ @@@ @ @ @ @@@@@@@ @ @@@@@@@ @@@@@@@@@@@@@ @
@       @ @ @   @         @     @ @   @   @     @     @ @     @   @   @
@@@@@@@ @ @ @@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@ @@@@@ @@@ @@@ @@@ @ @ @ @ @
@         @                       @               @       @     @   @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
>Exit code: 0

*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#define MAX 69 /* max rows and columns */

void usage(){
	printf(	"<!-- This is a compiled CGI script -->\n"
			"<html><head><title=\"usage\"></head><body>\n\n");
    printf(		"\tUsage: ?rows=[ROWS 2-%d]&amp;cols=[COLS 2-%d]&amp;color=[red]"
				"<br>\n",MAX,MAX);
    printf(		"\tExample: http://myserver.com/amaze-html"
				"?rows=11&amp;cols=15&amp;color=blue\n\n"
			"</body></html>\n");
    exit(0);
}
void parseqs(char **envpp,int *rows,int *cols,char *color){
	char *envp,*var,*val;
	printf("%s%c%c\n",
	"Content-Type:text/html;charset=iso-8859-1",13,10);
	if(!(envp=getenv("QUERY_STRING")))usage();
	for(var=strtok(envp,"&");var;var=strtok(NULL,"&")){
		if(!(val=strchr(var,'=')))usage();
		*val++=0;
		if(strstr(var,"rows"))*rows=atoi(val);
		if(strstr(var,"cols"))*cols=atoi(val);
		if(strstr(var,"color"))strncpy(color,val,15);
	}
	if(*rows>MAX||*cols>MAX||*rows<2||*cols<2)usage();
}
void initrand(){
    struct timeval tv; /* seed srand() */
    gettimeofday(&tv,0); /* with something... */
    srand((unsigned int)tv.tv_usec);
}
char **mazeinit(int rows,int cols, char wall){
    char **a=malloc((2*rows+1)*sizeof(char*)); /* 3x3 with overlap of 1 */
    int i,j;
    for(i=0;i<2*rows+1;i++){
        if(!(a[i]=malloc(2*cols+1))){
			fprintf(stderr,"Out of memory.\n"); /* something for the logs */
			exit(1);
		}
        for(j=0;j<2*cols+1;j++)
            a[i][j]=(wall)?wall:'*';
    }
    return a;
}
void mazestep(char **a,int *rows,int *cols,int r,int c){
    int i,vector[3][2];
    #define ROW vector[i][0]
    #define COL vector[i][1]
    while(1){
        i=0; /* look around */
        if(r>1          &&a[r-2][c] !=' '){ROW=r-2;COL=c;i++;}
        if(r<*rows*2-1  &&a[r+2][c] !=' '){ROW=r+2;COL=c;i++;}
        if(c>1          &&a[r][c-2] !=' '){ROW=r;COL=c-2;i++;}
        if(c<*cols*2-1  &&a[r][c+2] !=' '){ROW=r;COL=c+2;i++;}
        if(!i)break; /* check for dead end */
        i=(int)(i*(rand()/(RAND_MAX+1.0))); /* choose a path */
        a [(ROW+r)/2]   [(COL+c)/2]=' ';    /* knock out a wall */
        a [ROW]         [COL]=' ';          /* clear to it */
        mazestep(a,rows,cols,ROW,COL);      /* repeat */
    }
}
void mazewalk(char **a,int rows, int cols){
    /* this starts at one side but you can start anywhere */
    /* there is a way out no matter where your exits are */
    int i,r,c;
    c=cols|1;
    a[0][c]=' ';a[2*rows][c]=' ';
	i=(int)(2*(rand()/(RAND_MAX+1.0)));
	c=(i)?1:2*cols-1;r=rows|1;a[r][c]=' ';

    mazestep(a,&rows,&cols,r,c);
}
void mazeprint(char **a,int rows, int cols, char *color){
    int i,j;
	printf(
	"<html><head><title=\"Amaze\">\n"
	"<style>.maz{ color:%s; background-color:%s; }\n</style>\n"
	"</head><body><pre>\n",color,color); 
    for(i=0;i<2*rows+1;i++){
        for(j=0;j<2*cols+1;j++){
            if(color[0]&&a[i][j]!=' ')
				if(j==0||a[i][j-1]==' ') /* reduce control codes */
					printf("<span class=\"maz\">");
            if(color[0]&&a[i][j]==' '&&a[i][j-1]!=' ')printf("</span>");
            printf("%c",a[i][j]);
        }       
        if(color[0])printf("</span>");
		printf("\n");
    }printf("</pre>\n</body></html>");
}
void mazefree(char **a,int rows){
    int i;
    for(i=0;i<2*rows+1;i++)
        free(a[i]);
    free(a);
}

int main (int argc,char **argv, char **envp){
    int rows,cols;char **a,*color=malloc(sizeof color);color[0]=0;
	rows=10;cols=25;
    parseqs    (envp,&rows,&cols,color);
	//printf("%d %d %s\n",rows,cols,color);

    initrand();
a=  mazeinit    (rows,cols,'*');
    mazewalk    (a,rows,cols);
    mazeprint   (a,rows,cols,color);
    mazefree    (a,rows); 
    return 0;
}
