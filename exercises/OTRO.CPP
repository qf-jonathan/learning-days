#include<prolib\md13h2.h>
#include<conio.h>
#include<stdlib.h>
void main()
{  pvirt p1,p2,p3,p4;
   asigmem(&p1);
   asigmem(&p2);
   asigmem(&p3);
   asigmem(&p4);

   if(!p1&&!p2&&!p3&&!p4)
   {	cprintf("error!");
	getch();
	exit(1);
   }
   setmodo(GRA);
   clsp(p1,15);
   clsp(p2,0);
   clsp(p3,12);
   clsp(p4,8);
   while(!kbhit())
   {	volcp(VGA,p1);
	retard();
	volcp(VGA,p2);
	retard();
	//volcp(VGA,p3);
	//retard();
	//volcp(VGA,p4);
	//retard();
   }
   getch();
   setmodo(TXT);
   libmem(&p1);
   libmem(&p2);
   libmem(&p3);
   libmem(&p4);
}