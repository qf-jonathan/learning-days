#include "lib13h.hpp"
#include "conio.h"
#include "stdlib.h"

int main(){
	randomize();
    begin13h();
	Screen VGA(SCREEN,random(256));
    Screen p1(VIRTUAL);
	Screen p2(VIRTUAL,15);
	Screen p3(VIRTUAL,12);
	for(int i=0;i<200;i++)
		for(int j=0;j<320;j++)
			p1.setPixel(j,i,i+j);
	for(i=0;i<1000;i++){
		p2.setHLine(random(320),random(200),random(320),random(256));
		p2.setVLine(random(320),random(200),random(320),random(256));
	}
	for(i=0;i<1000;i++){
		p3.setBox(random(160),random(100),random(160)+160,random(100)+100,random(256));
		p3.setFillBox(random(160),random(100),random(160)+160,random(100)+100,random(256));
		p3.setFilledBox(random(160),random(100),random(160)+160,random(100)+100,random(256),random(256));
	}
    getch();
	p1.flipScreen();
	getch();
    p2.flipScreen();
	getch();
	p3.flipScreen();
	getch();
	p1.clear();
	while(!kbhit()){
		p1.setBox(random(160),random(100),random(160)+160,random(100)+100,random(256));
		p1.setFillBox(random(160),random(100),random(160)+160,random(100)+100,random(256));
		p1.setFilledBox(random(160),random(100),random(160)+160,random(100)+100,random(256),random(256));
		p1.setHLine(random(320),random(200),random(320),random(256));
		p1.setVLine(random(320),random(200),random(320),random(256));
		p1.setPixel(random(320),random(200),random(256));
		p1.flipScreen();
	}
    end13h();
    return 0;
}