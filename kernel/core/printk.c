#include <sys/types.h>
#include <sys/stdarg.h>
#include <asm/asm_work.h>
#include <kernel/printk.h>
#include <kernel/kernel.h>

#define abs(x) __builtin_abs(x)
 
void initialize_serial(uint16_t device)
{
	outb(device + 1 ,0x00);
	outb(device + 3 ,0x80);
	outb(device, 0x03);
	outb(device + 1, 0x00);
	outb(device + 3, 0x03);
	outb(device + 2, 0xC7);
	outb(device + 4, 0x0B);
}

uint8_t is_serial_empty(uint16_t device)
{
	return inb(device + 5) & 0x20;
}

inline void putch(uint16_t device, char c)
{
	while(is_serial_empty(device) == 0);
	outb(device, c);
}

inline void putstr(uint16_t device, const char *str)
{
	while(*str){
		putch(device, *str);
		str++;
	}
	return;
}

void putoct(uint16_t device, uint32_t val, uint16_t width, uint8_t zeropad )
{
	if ( !width ){
		char c[11];
		uint32_t i = 0;
		do
		{
			c[i++] ='0'+(val&0x07);
			val >>= 3;
		}
		while ( val != 0 );
		while ( i > 0 )
			putch(device,c[--i]);
	}else{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] ='0'+(val&0x07);
			val >>= 3;
		}
		while ( (val != 0) && (i < width) );
		while ( i < width )
			c[i++] = (zeropad)?'0':' ';
		while ( i > 0 )
			putch(device,c[--i]);
	}
	return;
}

void putdec(uint16_t device, int val, uint16_t width, uint8_t zeropad)
{
	uint8_t isneg = (val < 0);
	val = abs(val);
	if ( !width ){
		char c[10];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while ( val != 0 );
		if ( isneg )
			putch(device,'-');
		while ( i > 0 )
			putch(device,c[--i]);
	}
	else
	{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while ( (val != 0) && (i < width) );
		if ( isneg )
			putch(device,'-');
		while ( i < width )
			c[i++] = (zeropad)?'0':' ';
		while ( i > 0 )
			putch(device,c[--i]);
	}
}

void puthex(uint16_t device, uint32_t val, uint16_t width, uint8_t zeropad )
{
	if(!width){
		char c[8];
		uint32_t i = 0;
		do{
			c[i++] = ((val&0x0F)>0x09)?('A'+(val&0x0F)-0x0A)
				:('0'+(val&0x0F));
			val >>= 4;
		}
		while ( val != 0 );
		while ( i > 0 )
			putch(device,c[--i]);
	}else{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] = ((val&0x0F)>0x09)?('A'+(val&0x0F)-0x0A)
				:('0'+(val&0x0F));
			val >>= 4;
		}
		while ( (val != 0) && (i < width) );
		while ( i < width )
			c[i++] = (zeropad)?'0':' ';
		while ( i > 0 )
			putch(device,c[--i]);
	}
}

void putuns(uint16_t device, uint32_t val, uint16_t width, uint8_t zeropad )
{
	if(!width){
		char c[10];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while ( val != 0 );
		while ( i > 0 )
			putch(device,c[--i]);
	}else{
		char c[width];
		uint32_t i = 0;
		do{
			c[i++] = '0'+val%10;
			val /= 10;
		}
		while ( (val != 0) && (i < width) );
		while ( i < width )
			c[i++] = (zeropad)?'0':' ';
		while ( i > 0 )
			putch(device,c[--i]);
	}
}

void vaprintk(uint16_t device, char *s, va_list args )
{
	uint8_t alt;
	uint8_t zp;
	uint16_t wide;
	int i;

	for(i = 0; s[i] != 0x00; i++)
		;

	while ( *s ){
		alt = 0;
		zp = 0;
		wide = 0;

		if(*s != '%'){
			putch(device,*(s++));
			continue;
		}
		s++;
		if(*s == '%'){
			putch(device,*(s++));
			continue;
		}
		if(*s == 's'){
			putstr(device, (char*)va_arg(args, char *));
			s++;
			continue;
		}
		if(*s == 'c'){
			putch(device,va_arg(args, int));
			s++;
			continue;
		}
		if(*s == '#'){
			alt = 1;
			s++;
		}
		if(*s == '0'){
			zp = 1;
			s++;
		}
		while ( (*s >= '0') && (*s <= '9') ) /* field width */
			wide = wide*10+(*(s++)-'0');
		if(*s == 'd'){
			putdec(device,(uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		if(*s == 'u'){
			putuns(device,(uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		if(*s == 'x'){
			if(alt)
				putstr(device,"0x");
			puthex(device,(uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		if(*s == 'o' ){
			if(alt)
				putch(device,'0');
			putoct(device,(uint32_t)va_arg(args,uint32_t),wide,zp);
			s++;
			continue;
		}
		putch(device,*(s++));
	}
}

void printk(char *str, ...)
{
	va_list args;
	va_start(args, str);
	vaprintk(COM1, str, args);
	va_end(args);
	return;
}
