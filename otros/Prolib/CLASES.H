#include<prolib\busca.h>

class Boton
{   byte *cadena;
    int x,y;
    public:
    void Dato(byte *dat);
    void Posicion(int i,int j);
    byte Verificar();
};
void Boton::Dato(byte *dat)
{   strcpy(cadena,dat);
}
void Boton::Posicion(int i,int j)
{   x=i;
    y=j;
    botnp(x,y,cadena,letradelsistema);
}
byte Boton::Verificar()
{   int i,j,est;
    leermouse(&i,&j,&est);
    if(est==Bizquierdo)
    { if(i>=x&&i<=(x+110)&&j>=y&&j<=(y+30))
      {  quitarmouse();
	    botp(x,y,cadena,letradelsistema);
	 ponermouse();
	 do{
	   leermouse(&i,&j,&est);
	   }while(i>=x&&i<=(x+110)&&j>=y&&j<=(y+30)&&est!=Bsoltados);
	 quitarmouse();
	    botnp(x,y,cadena,letradelsistema);
	 ponermouse();
      }
      if(est==Bsoltados)
	 return 1;
     }
     return 0;
}
