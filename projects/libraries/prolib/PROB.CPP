#include <prolib\mod13.h>
#include <stdlib.h>
#include <conio.h>
void main()
{  _pvirtual p1;
   _pvirtual p2;
   _pvirtual p3;
   if(pvirtual(&p1)==NULL)
   exit(1);
   if(pvirtual(&p2)==NULL)
   exit(1);
   if(pvirtual(&p3)==NULL)
   exit(1);
   randomize();
   for(int i=0;i<5000;i++)
     setpunto(random(320),random(200),random(255)+1,p1);
   for(i=0;i<5000;i++)
     setpunto(random(320),random(200),random(255)+1,p2);
   for(i=0;i<5000;i++)
     setpunto(random(320),random(200),random(255)+1,p3);
   pmodo(0x13);
   while(!kbhit())
   {  setpvirtual(p1);
      retrazo();
      setpvirtual(p2);
      retrazo();
      setpvirtual(p3);
      retrazo();
   }
   pmodo(0x03);
}