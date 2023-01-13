/* libreria pila */
#ifndef _PILA_HPP_
#define _PILA_HPP_

//definicion del NULL
#ifndef NULL
# if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#   define NULL    0 //punteros de 2 bytes
# else
#   define NULL    0L//puntetos de 4 bytes
# endif
#endif

#ifndef UINT
# define UINT unsigned int
#endif

//lista de errores
#define noExisteNodo 001
#define pilaVacia    002
#define noHayMemoria 003
#define noError      004

enum BOOL {false,true};

struct retError{
  BOOL _error;
  int _codigoError;
  int _numero;
};

// declaracion de clases
//clase nodo
class Nodo{
  int _dato;
  Nodo *_sig;
public:
  Nodo(int);
  void setDato(int);
  int getDato(void);
  Nodo *getSig(void);
  void setSig(Nodo *);
};
//clases pila
class Pila{
  Nodo *_inicio;
  UINT _numNodos;
public:
  Pila(void);
  retError insertar(int,UINT);      //dato,posicion_nodo
  retError eliminar(UINT);          //posicion_nodo
  retError retEliminar(UINT);       //posicion_nodo
  retError intercambiar(UINT,UINT); //posicion_nodo,posicion_nodo
  retError cambiarNodo(int,UINT);   //dato,posicion_nodo
  UINT tamanioPila(void);
};
//implementacion de la clase NODO
Nodo::Nodo(int _numero){
  _dato=_numero;
  _sig=NULL;
}
void Nodo::setDato(int _numero){
  _dato=_numero;
}
int Nodo::getDato(void){
  return _dato;
}
Nodo *Nodo::getSig(void){
  return _sig;
}
void Nodo::setSig(Nodo *_siguiente){
  _sig=_siguiente;
}
//implementacion de la clase PILA
Pila::Pila(){
  _inicio=NULL;
  _numNodos=false;
}
retError Pila::insertar(int _dato,UINT _posicion=0){
  retError _retornar;
  Nodo *_tmp;
  if(!_inicio){
    _inicio=new Nodo(_dato);
    if(!_inicio){
      _retornar._error=true;
      _retornar._codigoError=noHayMemoria;
      return _retornar;
    }
    _retornar._error=false;
    _numNodos++;
    return _retornar;
  }
  if(!_posicion){
    _tmp=_inicio->getSig();
    _inicio=new Nodo(_dato);
    _inicio->setSig(_tmp);
    _numNodos++;
    _retornar._error=false;
    return _retornar;
  }else{
    if(_posicion>_numNodos){

}
#endif