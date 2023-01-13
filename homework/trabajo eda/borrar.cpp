#include <dos.h>

void Modo13h(void) {
    union REGS r;

    r.h.ah = 0;
    r.h.al = 0x13;
    int86(0x10, & r, & r);
}