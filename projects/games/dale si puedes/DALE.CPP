#include<prolib\modo13h.h>
#include<stdlib.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<prolib\mouses.h>

#define P1 "img\\pre1.img"
#define P2 "img\\pre2.img"
#define P3 "img\\pre3.img"
#define PANEL "img\\prin.img"
#define JUEGO "img\\jueg.img"
#define GANADOR "img\\gan.img"
#define OPCIONES "img\\opc.img"
#define SPRITE "img\\mano.spr"

typedef enum boolean{FALSO,VERDADERO};
class sector
{ int x0,y0;
  int x1,y1;
  public:
  sector(int a,int b,int c,int d);
  int verificar(void);
  int verificar2(void);
};
sector::sector(int a,int b,int c,int d)
{   x0=a;
    y0=b;
    x1=c;
    y1=d;
}
int sector::verificar(void)
{   int x,y,est;
    leermouse(&x,&y,&est);
    if(est==Bizquierdo)
    {   if((x>x0)&&(x<x1)&&(y>y0)&&(y<y1))
	{  do{
	     leermouse(&x,&y,&est);
	   }while(x>x0&&x<x1&&y>y0&&y<y1&&est!=0);
	}

    if(est==0)
       return VERDADERO;
    }
    return FALSO;
}
int sector::verificar2(void)
{  int x,y,est;
   leermouse(&x,&y,&est);
   if((x>x0)&&(x<x1)&&(y>y0)&&(y<y1))
     return 1;
   return 0;
}
int jugador1;
int jugador2;
char dificultad;
_pvirtual fondo;
_pvirtual trab;
_paleta paletaprin;
//mini graficos
char flechaab[]=
	{1,1,1,1,1,1,1,1,1,1,1,
	 0,1,1,1,1,1,1,1,1,1,0,
	 0,0,1,1,1,1,1,1,1,0,0,
	 0,0,0,1,1,1,1,1,0,0,0,
	 0,0,0,0,1,1,1,0,0,0,0,
	 0,0,0,0,0,1,0,0,0,0,0};
char flechaar[]=
	{0,0,0,0,0,1,0,0,0,0,0,
	 0,0,0,0,1,1,1,0,0,0,0,
	 0,0,0,1,1,1,1,1,0,0,0,
	 0,0,1,1,1,1,1,1,1,0,0,
	 0,1,1,1,1,1,1,1,1,1,0,
	 1,1,1,1,1,1,1,1,1,1,1};
char senyal[]=
	{0,0,0,0,0,0,0,0,0,0,1,
	 0,0,0,0,0,0,0,0,0,1,1,
	 0,0,0,0,0,0,0,0,1,1,0,
	 0,0,0,0,0,0,0,1,1,0,0,
	 1,1,0,0,0,0,1,1,0,0,0,
	 1,1,1,0,0,1,1,0,0,0,0,
	 0,1,1,1,1,1,0,0,0,0,0,
	 0,0,1,1,1,0,0,0,0,0,0};
char apuntador[]=
	{0,0,0,0,0,1,1,1,0,0,0,0,0,
	 0,0,0,0,0,1,0,1,0,0,0,0,0,
	 0,0,0,1,0,0,1,0,0,1,0,0,0,
	 0,0,0,0,0,0,1,0,0,0,0,0,0,
	 1,1,1,0,0,0,0,0,0,0,1,1,1,
	 1,1,0,1,1,0,0,0,1,1,0,1,1,
	 1,1,1,0,0,0,0,0,0,0,1,1,1,
	 0,0,0,0,0,0,1,0,0,0,0,0,0,
	 0,0,0,1,0,0,1,0,0,1,0,0,0,
	 0,0,0,0,0,1,0,1,0,0,0,0,0,
	 0,0,0,0,0,1,1,1,0,0,0,0,0};
char mouse[]=
	{1,0,0,0,0,0,0,0,
	 1,1,0,0,0,0,0,0,
	 1,1,1,0,0,0,0,0,
	 1,1,1,1,0,0,0,0,
	 1,1,1,1,1,0,0,0,
	 1,1,1,1,1,1,0,0,
	 1,1,1,1,1,1,1,0,
	 1,1,1,1,1,1,1,1,
	 1,1,1,0,0,0,0,0,
	 1,1,0,0,0,0,0,0,
	 1,0,0,0,0,0,0,0};
char tiro[]=
	{0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,1,0,1,0,1,1,0,0,0,
	 0,0,1,1,1,1,1,1,1,1,0,0,
	 0,1,1,1,1,1,1,1,1,0,1,0,
	 0,0,1,1,1,1,1,1,1,1,0,0,
	 0,1,0,1,1,1,1,1,1,1,0,0,
	 0,0,1,0,1,1,1,1,1,0,1,0,
	 0,1,0,1,1,1,1,1,1,0,1,0,
	 0,0,1,0,1,0,1,0,0,1,0,0,
	 0,0,0,0,0,0,0,0,1,0,0,0};
//funciones principales
void flech(int x,int y,boolean flecha);
void sen(int x,int y);
void apunt(int x,int y);
void pmouse(int x,int y);
void sen(int x,int y);
void tir(int x,int y);
void tiemblamouse();
void presentacion(void);
int panel(void);
void opciones(void);
void juego(void);
void ganador(void);
void dibujasprite(int x,int y,int altura,unsigned char *spr);
int puntaje(int num);
void main()
{ int dato;
  if(!separarpvirtual(&fondo))
  {   printf("falta meria para el fondo!");
      borrarseparado(&fondo);
      exit(1);}
  if(!separarpvirtual(&trab))
  {   printf("falta meria para la pantalla de trabajo!");
      borrarseparado(&trab);
      exit(1);}
  if(!insmouse())
   {   ponermodo(_03h);
       printf("no hay driver de mouse!");
       exit(1);}
  dificultad=2;
  jugador1=0;
  jugador2=0;
  ponermodo(_13h);
  presentacion();
  do{
  dato=panel();
  if(dato==0)
  juego();
  if(dato==1)
  opciones();
  if(dato==2)
  break;
  }while(VERDADERO);
  ponermodo(_03h);
  printf("Programado por: Jonathan Alberth Quispe Fuentes (J.A.Q.F.)\n");
  printf("\tgracias por jugar \"Dale si puedes!!\"");
  borrarseparado(&fondo);
  borrarseparado(&trab);
}
void flech(int x,int y,boolean flecha)
{  int i,j,indice=0;
   for(j=0;j<6;j++)
      for(i=0;i<11;i++)
	 if (flecha==1)
	 {  if(flechaab[indice++]==1)
	       punto(i+x,j+y,34,trab);}
	 else
	 {  if(flechaar[indice++]==1)
	       punto(i+x,j+y,34,trab);}
}
void sen(int x,int y)
{  int i,j;
   for(i=0;i<11;i++)
   {  for(j=0;j<8;j++)
      {	 if(senyal[j*11+i]==1)
	    punto(i+x,j+y,34,VGA);}
	 retrazos(3);
   }
}
void apunt(int x,int y)
{  int i,j;
   int indice=0;
   for(j=0;j<11;j++)
      for(i=0;i<13;i++)
	 if(apuntador[indice++]==1)
	    punto(i+x,j+y,34,trab);
}
void pmouse(int x,int y)
{  int i,j;
   int indice=0;
   for(j=0;j<11;j++)
      for(i=0;i<8;i++)
	 if(mouse[indice++]==1)
	    punto(i+x,j+y,34,trab);
}
void tir(int x,int y)
{  int i,j;
   int indice=0;
   for(j=0;j<12;j++)
      for(i=0;i<10;i++)
	 if(tiro[indice++]==1)
	    punto(i+x,j+y,34,trab);
}
void tiemblamouse()
{  int px,py,est;
   leermouse(&px,&py,&est);
   int x;
   int y;
   char longitud;
   x=random(2);
   y=random(2);
   longitud=random(dificultad)+1;
   if(x==1)
     px+=longitud;
   else
     px-=longitud;
   if(y==1)
     py+=longitud;
   else
     py-=longitud;
   situarmouse(px,py);
}
void presentacion(void)
{  FILE *A;
   FILE *B;
   FILE *C;
   _paleta pal;
   for(int i=0;i<768;i++)
      pal[i]=0;
   ponerpaleta(pal);
   if(!(A=fopen(P1,"rb")))
   {  ponermodo(_03h);fclose(A);
      printf("no se encuentra archivo %s!\n",P1);
      exit(1);}
   if(!(B=fopen(P2,"rb")))
   {  ponermodo(_03h);fclose(B);
      printf("no se encuentra archivo %s!\n",P2);
      exit(1);}
   if(!(C=fopen(P3,"rb")))
   {  ponermodo(_03h);fclose(C);
      printf("no se encuentra archivo %s!\n",P3);
      exit(1);}
   fread(pal,sizeof(unsigned char),768,A);
   fread(VGA,sizeof(unsigned char),64000,A);
   fundidoen(pal,1);
   retrazos(60);
   fundidonegro(1);
   fread(pal,sizeof(unsigned char),768,B);
   fread(VGA,sizeof(unsigned char),64000,B);
   fundidoen(pal,1);
   retrazos(50);
   fundidonegro(1);
   fread(pal,sizeof(unsigned char),768,C);
   fread(VGA,sizeof(unsigned char),64000,C);
   fundidoen(pal,1);
   retrazos(50);
   fundidonegro(1);
   fclose(A);fclose(B);fclose(C);
}
int panel(void)
{  FILE *p;
   int x,y,est;
   int opcion=5;
   sector jugar(113,69,200,97);
   sector opciones(95,108,226,136);
   sector salir(117,145,198,175);
   if(!(p=fopen(PANEL,"rb")))
   {   ponermodo(_03h);fclose(p);
       printf("no se encuentra el archivo %s!",PANEL);
       exit(1);}
   limitedemouse(1,1,313,190);
   fread(paletaprin,sizeof(unsigned char),768,p);
   fread(fondo,sizeof(unsigned char),64000,p);
   ponerpvirtual(fondo);
   fundidoen(paletaprin,1);
   do{
      ponerpvirtual_a(trab,fondo);
      leermouse(&x,&y,&est);
      pmouse(x-1,y-1);
      ponerpvirtual(trab);
      if(jugar.verificar())
      {opcion=0;break;}
      if(opciones.verificar())
      {opcion=1;break;}
      if(salir.verificar())
      {opcion=2;break;}
   }while(VERDADERO);
   if(opcion==0)
      sen(206,80);
   else if(opcion==1)
      sen(230,118);
   else
      sen(203,156);
   fundidonegro(1);
   fclose(p);
   return opcion;
}
void opciones(void)
{  FILE *f;
   int x,y,est;
   sector facil(68,103,131,115);
   sector medio(178,101,241,113);
   sector dificil(115,127,194,141);
   sector volver(108,161,199,184);
   limitedemouse(1,1,313,190);
   if(!(f=fopen(OPCIONES,"rb")))
   {  ponermodo(_03h);fclose(f);
      printf("no se encuentra el archivo %s!",OPCIONES);
      exit(1);
   }
   fread(paletaprin,sizeof(unsigned char),768,f);
   fread(fondo,sizeof(unsigned char),64000,f);
   fclose(f);
   ponerpvirtual(fondo);
   fundidoen(paletaprin,1);
   do{
      ponerpvirtual_a(trab,fondo);
      leermouse(&x,&y,&est);
      if(facil.verificar())
	 dificultad=1;
      if(medio.verificar())
	 dificultad=2;
      if(dificil.verificar())
	 dificultad=3;
      if(volver.verificar())
      {	 sen(200,174);break;}
      if(dificultad==1)
	 flech(88,126,FALSO);
      else if(dificultad==2)
	 flech(205,123,FALSO);
      else
	 flech(146,113,VERDADERO);
      pmouse(x-1,y-1);
      ponerpvirtual(trab);
      }while(VERDADERO);
      fundidonegro(1);
}
void juego(void)
{   FILE *f1;
    FILE *f2;
    unsigned char puntoxy;
    unsigned char basura[46];
    int balasde1=10;
    int balasde2=10;
    int i,j;
    int aux1,aux2;
    int px,py,est;
    int psx;
    char puntaje1[5];
    char puntaje2[5];
    char balas[3];
    unsigned char *mano1;
    unsigned char *mano2;
    sector juego(32,3,153,96);
    sector raton(2,2,182,158);
    sector salir(220,152,276,170);
    if(!(f1=fopen(JUEGO,"rb")))
    {   ponermodo(_03h),fclose(f1);
	printf("no se encuentra el archico %s!",JUEGO);
	exit(1);
    }
    if(!(f2=fopen(SPRITE,"rb")))
    {   ponermodo(_03h),fclose(f1);
	printf("no se encuentra el archico %s!",SPRITE);
	exit(1);
    }
    mano1=(unsigned char*)calloc(1886,sizeof(unsigned char));
    mano2=(unsigned char*)calloc(3036,sizeof(unsigned char));
    if(!mano1&&!mano2)
    {   ponermodo(_03h),free(mano1);free(mano2);
	printf("falta memoria para sprites!");
	exit(1);
    }
    fread(paletaprin,sizeof(unsigned char),768,f1);
    fread(fondo,sizeof(unsigned char),64000,f1);
    fread(mano1,sizeof(unsigned char),1886,f2);
    fread(basura,sizeof(unsigned char),46,f2);
    fread(mano2,sizeof(unsigned char),3036,f2);
    fclose(f1);
    fclose(f2);
    leermouse(&px,&py,&est);
    ponerpvirtual_a(trab,fondo);
    dibujasprite(64,118,41,mano1);
    apunt(px-6,py-5);
    ponerpvirtual(trab);
    fundidoen(paletaprin,1);
    do{
       ponerpvirtual_a(trab,fondo);
       leermouse(&px,&py,&est);
       sprintf(puntaje1,"%d",jugador1);
       sprintf(puntaje2,"%d",jugador2);
       if(balasde1>0)
       { sprintf(balas,"%d",balasde1);
	 escrivir(10,182,"jugador 1",34,trab);
       }
       else if(balasde2>0)
       { sprintf(balas,"%d",balasde2);
	 escrivir(10,182,"jugador 2",34,trab);
       }
       escrivir(121,182,balas,34,trab);
       escrivir(201,89,puntaje1,34,trab);
       escrivir(201,116,puntaje2,34,trab);
       psx=px-24;
       if(px<32)
	  psx=9;
       if(px>153)
	  psx=126;
       if(raton.verificar2())
       {  if(juego.verificar2())
	  {  tiemblamouse();
	     leermouse(&px,&py,&est);
	     if(est==Bizquierdo)
	     {  do{
		leermouse(&aux1,&aux2,&est);
		}while(est!=Bsoltados);
		dibujasprite(psx,93,66,mano2);
		puntoxy=puntaje(pedirpunto(px,py,fondo));
		if(puntoxy!=0)
		{  if(balasde1>0)
		     {jugador1+=puntaje(pedirpunto(px,py,fondo));balasde1--;}
		   else if(balasde2>0)
		     {jugador2+=puntaje(pedirpunto(px,py,fondo));balasde2--;}
		}
		tir(px-6,py-5);
		ponerpvirtual(trab);
		retrazos(10);
		situarmouse(182,158);
	     }
	  }
	dibujasprite(psx,118,41,mano1);
	apunt(px-6,py-5);
       }
       else
       {
       if(salir.verificar())
       {sen(280,160);break;}
       dibujasprite(psx,118,41,mano1);
       pmouse(px,py);
       }
       ponerpvirtual(trab);
       retrazo();
   }while(balasde1>0||balasde2>0);

   sprintf(puntaje2,"%d",jugador2);
   ponerpvirtual_a(trab,fondo);
   escrivir(201,89,puntaje1,34,trab);
   escrivir(201,116,puntaje2,34,trab);
   ponerpvirtual(trab);
   retrazos(5);
   fundidonegro(1);
   free(mano1);
   free(mano2);
   ganador();
}






void ganador(void)
{   FILE *f;
    if(!(f=fopen(GANADOR,"rb")))
    {   ponermodo(_03h);fclose(f);
	printf("no se encuentra el archivo %s!",GANADOR);
	exit(1);
    }
    fread(paletaprin,sizeof(unsigned char),768,f);
    fread(VGA,sizeof(unsigned char),64000,f);
    fclose(f);
    if(jugador1>jugador2)
    {escrivir(109,120,"EL JUGADOR 1!",12,VGA);
    escrivir(108,119,"EL JUGADOR 1!",34,VGA);}
    else if(jugador2>jugador1)
    {escrivir(109,120,"EL JUGADOR 2!",12,VGA);
    escrivir(108,119,"EL JUGADOR 2!",34,VGA);}
    else
    {escrivir(120,120,"EMPATE!",12,VGA);
    escrivir(119,119,"EMPATE!",34,VGA);}
    jugador1=0;
    jugador2=0;
    fundidoen(paletaprin,1);
    getch();
    fundidonegro(1);
}
void dibujasprite(int x,int y,int altura,unsigned char *spr)
{  int num=0;
   int i,j;
   for(j=0;j<altura;j++)
       {  for(i=0;i<46;i++)
	  {   if(spr[num]!=219)
	      {punto(i+x,j+y,spr[num],trab);}
	       num++;
	  }
       }
}
int puntaje(int num)
{  switch(num)
   { case 159:return 1;
     case 30:return 3;
     case 254:return 6;
     case 227:return 10;
     case 31:return 15;
     case 28:return 21;
     case 252:return 50;
     default:return 0;
   }
}
