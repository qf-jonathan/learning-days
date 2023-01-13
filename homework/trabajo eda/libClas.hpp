#include "lib13h.h"
#include "mouse.h"

class JBoton{
  jWord jx0,jy0;
  jWord jx1,jy1;
  jByte jNombre[40];
  void (*jPtrFuncion)(void);
public:
  void jSetBoton(jByte *,void (*)(void));
  void jDibujar(jWord, jWord, jWord, jWord);
  void jFuncMouse(void);
};
class JArrayBotones{
  JBoton **jPtrArray;
  jWord jTamanioArray;
  void jLimpiarArray(void);
public:
  JArrayBotones(jWord);
  void jAsignarArray(jWord,JBoton *);
  void jRecorrerArray(void);
  ~JArrayBotones();
};

#include "libclas.cpp"