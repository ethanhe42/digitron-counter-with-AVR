//** 文件名：digitron.c
//** 功能：8位数码管依次循环显示
//** 说明：数码管共阳极连接
#include <avr/io.h>
#include <util/delay.h>
#define DIG_CS1 PG3
#define DIG_CS2 PG4
#define PB_MASK 0xFF

uint8_t code[16] = { 0xC0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0x88, 0x83, 0xc6, 0xa1, 0x86, 0x8e };

void DIG_Init() {
    PORTB = ~PB_MASK;
    DDRB = PB_MASK;
    PORTG &= 0x00;
    DDRG |= _BV(DIG_CS1) | _BV(DIG_CS2);
}

void showchar(int pos, int c){
	PORTG |= _BV(DIG_CS2);
	PORTG &= ~_BV(DIG_CS1);
    PORTB = code[c];

	PORTG |= _BV(DIG_CS1);
	PORTG &= ~_BV(DIG_CS2);
    PORTB = 1<<(7-pos);

	PORTG &= ~_BV(DIG_CS1);
	PORTG &= ~_BV(DIG_CS2);
    _delay_ms(1);
}

void orig(int sec) {

}

void print(int num) {
	int c[7];
	int i,rest,tmp, s;
	tmp = num;
	for (i=0; i <7; i++){

		rest = tmp % 10;
		showchar(i, rest);
		s = tmp / 10;
		if ( s == 0) {
			break;
		}
		tmp = s;
	}
}

int main() {
	DIG_Init();
	if (0) {//original;
		orig(500);
	}
	else if (1) {
		//stable
		int i =0;
		while(1){
			print(i);
			_delay_ms(1);
			i++;
		}
	}

    return 0;
}
