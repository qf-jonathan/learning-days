//#include "mouse.h"
//#include "pantalla.h"
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INT_MOUSE 0x33
#define SERV_ACTIVA_MOUSE 0x00
#define SERV_MUESTRA_MOUSE 0x01
#define SERV_GET_MOUSE_STATUS 0x03
#define SERV_SET_MOUSE_XY 0x04

#define LX_MOUSE 640
#define LY_MOUSE 200
/*
int activa_mouse();
void muestra_mouse();
int get_x_mouse();
int get_y_mouse();
int pulsado_left();
int pulsado_right();
void pinta_mouse();
void carga_cursor (char *nombre_fichero);
void set_xy_mouse(int x,int y);
void borra_mouse();
int mouse_movido();
void libera_cursor();
void lee_fondo_mouse();

*/
char *fondo_mouse;
char *cursor_mouse;
int lx_mouse,ly_mouse;
int x_mouse,y_mouse;
int _mouse_cargado=0;
int _cursor_cargado=0;

int activa_mouse()
{
	union REGS r;


	r.x.ax=SERV_ACTIVA_MOUSE;

	int86(INT_MOUSE,&r,&r);
	if (r.x.ax){
		_mouse_cargado=1;
		return 1;
	}
	return 0;
}
void muestra_mouse()
{
	union REGS r;
	r.x.ax=SERV_MUESTRA_MOUSE;
	int86(INT_MOUSE,&r,&r);


}
int get_x_mouse()
{
	union REGS r;

	r.x.ax=SERV_GET_MOUSE_STATUS;
	int86(INT_MOUSE,&r,&r);
	return r.x.cx;
}
int get_y_mouse()
{
	union REGS r;

	r.x.ax=SERV_GET_MOUSE_STATUS;
	int86(INT_MOUSE,&r,&r);
	return r.x.dx;
}

int pulsado_left()
{
	union REGS r;

	r.x.ax=SERV_GET_MOUSE_STATUS;
	int86(INT_MOUSE,&r,&r);
	return r.x.bx&1;
}
int pulsado_right()
{
	union REGS r;

	r.x.ax=SERV_GET_MOUSE_STATUS;
	int86(INT_MOUSE,&r,&r);
	return r.x.bx&2;
}
/*
void carga_cursor (char *nombre_fichero)
{
	int i,j;
	FILE *fp;

	if ((fp=fopen(nombre_fichero,"rb"))==NULL){
		printf("Error al abrir el fichero %s",nombre_fichero);
		exit (EXIT_FAILURE);
	}



	if (!_mouse_cargado) return;
	if (_cursor_cargado) libera_cursor();

	fread(&lx_mouse,sizeof (char),1,fp);
	fread(&ly_mouse,sizeof (char),1,fp);
	x_mouse=LX/2;
	y_mouse=LY/2;

	if ((fondo_mouse=malloc(sizeof (char)*lx_mouse*ly_mouse))==NULL){
		printf("Error de memoria");
		exit(EXIT_FAILURE);
	}
	if ((cursor_mouse=malloc(sizeof (char)*lx_mouse*ly_mouse))==NULL){
		printf("Error de memoria");
		exit(EXIT_FAILURE);
	}

	fread(cursor_mouse,sizeof (char)*lx_mouse*ly_mouse,1,fp);
	fclose(fp);
	lee_sprite(x_mouse,y_mouse,lx_mouse,ly_mouse,fondo_mouse);
	_cursor_cargado=1;

}

void pinta_mouse()
{
	if (!_cursor_cargado) return;
	borra_mouse();
	if ( (x_mouse=get_x_mouse())>LX-lx_mouse){
		x_mouse=LX-lx_mouse;
		set_xy_mouse(x_mouse,y_mouse);
	}
	if ( (y_mouse=get_y_mouse())>LY-ly_mouse){
		y_mouse=LY-ly_mouse;
		set_xy_mouse(x_mouse,y_mouse);
	}
	lee_sprite(x_mouse,y_mouse,lx_mouse,ly_mouse,fondo_mouse);
	pon_sprite(x_mouse,y_mouse,lx_mouse,ly_mouse,cursor_mouse);

}
*/
void set_xy_mouse(int x,int y)
{
	union REGS r;

	r.x.ax=SERV_SET_MOUSE_XY;
	r.x.cx=x;
	r.x.dx=y;
	int86(INT_MOUSE,&r,&r);
}
/*
void borra_mouse()
{
	if (!_cursor_cargado) return;
	pon_sprite(x_mouse,y_mouse,lx_mouse,ly_mouse,fondo_mouse);
}

int mouse_movido()
{
	if (!_cursor_cargado) return 0;
	if (x_mouse!=get_x_mouse() || y_mouse!=get_y_mouse())
		return 1;
	return 0;
}
*/
void libera_cursor()
{
	free (cursor_mouse);
	free (fondo_mouse);
	_cursor_cargado=0;
}
/*
void lee_fondo_mouse()
{
	if ( (x_mouse=get_x_mouse())>LX-lx_mouse){
		x_mouse=LX-lx_mouse;
		set_xy_mouse(x_mouse,y_mouse);
	}
	if ( (y_mouse=get_y_mouse())>LY-ly_mouse){
		y_mouse=LY-ly_mouse;
		set_xy_mouse(x_mouse,y_mouse);
	}
	lee_sprite(x_mouse,y_mouse,lx_mouse,ly_mouse,fondo_mouse);

} */