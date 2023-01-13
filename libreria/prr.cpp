#include <stdio.h>
#include <conio.h>

#define MK_FP( seg,ofs )( (void _seg * )( seg ) +( void near * )( ofs ))
#define FP_SEG( fp )( (unsigned )( void _seg * )( void far * )( fp ))
#define FP_OFF( fp )( (unsigned )( fp ))

#define mainscreen (byte*)0xA0000000
#ifndef null
    #define NULL 0L
#endif
#ifndef byte
    #define byte unsigned char
#endif
#ifndef word
    #define word unsigned char
#endif
#ifndef uint
    #define uint unsigned char
#endif
#ifndef uchar
    #define uchar unsigned char
#endif

uint hip(void* __dir){
    asm{
        mov ax,SEG [__dir];
    }
    return _AX;
}    
uint lowp(void* __dir){
    asm{
        mov ax,OFFSET [__dir];
    }
    return _AX;
}

int main(){
    uchar *VGA=(uchar *)MK_FP(0xA000,0);
    int segmento=(uint)FP_SEG(VGA);
    
    asm mov ax,0x13
    asm int 0x10
    
    int dir=(uint)FP_OFF(VGA);
    dir+=100*320+160;
    
    asm{
        mov ax,[segmento]
        mov es,ax
        mov di,[dir]
        mov al,15
        mov es:[di],al
    }
    
    printf("%u:%u",hip(VGA),lowp(VGA));
    printf("\n%u:%u",FP_SEG(VGA),FP_OFF(VGA));
    getch();
    return 0;
}