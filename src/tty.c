#include <stdarg.h>

#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25
#define VIDEO_RAM 0xb8000

int cursor;
char attr;

char* video_buf=(char*)VIDEO_RAM;

void init_tty(){
	video_buf=VIDEO_RAM; 
	cursor=0;
	attr=7;
}

void textcolor(char color){
	attr=color;
}

void clear(){
	int i;

	for(i=0;i<VIDEO_HEIGHT*VIDEO_WIDTH;i++){
		*(unsigned short*)(VIDEO_RAM+i*2)=0x0720;
	}
	cursor=0;
}

/*
 * TODO: support tabulation
 */

void putchar(char c){
	int i;
	switch(c){
		case 8:
			cursor--;
			*(video_buf+cursor*2)=' ';
			break;
		case '\n':
			cursor=cursor-cursor%VIDEO_WIDTH+VIDEO_WIDTH;
			break;
		default:
			*(video_buf+cursor*2)=c;
			*(video_buf+cursor*2+1)=attr;
			cursor++;
			break;
	}

	if(cursor>VIDEO_WIDTH*VIDEO_HEIGHT){
		for(i=VIDEO_WIDTH*2;i<=VIDEO_WIDTH*VIDEO_HEIGHT*2+VIDEO_WIDTH*2;i++){
			video_buf[i-VIDEO_WIDTH*2]=video_buf[i];
		}
		cursor-=VIDEO_WIDTH;
	}
}

void puts(const char *s){
	while(*s){
		putchar(*s);
		s++;
	}
}

void puts_size(const char *s, int size){
	int ind;
	ind = 0;
	ind = size;
	while((*s) && (ind > 0)){
		putchar(*s);
		s++;
		ind--;
	}
}
