  #include <graphics.h>
  #include <stdlib.h>
  #include <stdio.h>
  #include <conio.h>

  int main(void)
  {
     /* request autodetection */
     int gdriver = DETECT, gmode, errorcode;

     /* initialize graphics and local variables */
     initgraph(&gdriver, &gmode, "bgi");

     /* read result of initialization */
     errorcode = graphresult();
     if (errorcode != grOk)      /* an error occurred */
     {
        printf("Graphics error: %s\n", grapherrormsg(errorcode));
        printf("Press any key to halt:");
        getch();
        exit(1);                 /* terminate with an error code */
     }

     viewporttype vp;
     getviewsettings(&vp);
     setfillstyle(SOLID_FILL,GREEN);
     bar(0,0,getmaxx(),getmaxy());
     setviewport(100,100,200,200,1);
     setfillstyle(SOLID_FILL,BLUE);
     bar(0,0,100,100);

     setcolor(15);
     line(0,0,100,100);
     getch();
     closegraph();
     return 0;
  }