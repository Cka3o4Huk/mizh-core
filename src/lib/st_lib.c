#include <stdarg.h>
#include "errno.h"
#include "st_lib.h"

char cmp(char* str1,char* str2){
	int i=0;
	
	while((str1[i]!='\0')&&(str2[i]!='\0')){
		if(str1[i]!=str2[i])return 0;
		i++;
	};
	if(str1[i]==str2[i])return 1;
	return 0;
};

void perror(char* str){
	printf("%s",str);
};

char isdigit(char s){
	if((s>='0')&&(s<='9'))return 1;
	return 0;
};

char h_byte(char a){
	if((a>='0')&&(a<='9'))return a-'0';
	if((a>='a')&&(a<='f'))return a-'a'+10;
	if((a>='A')&&(a<='F'))return a-'A'+10;
	return -1;
};                     

int min(int a,int b){
	if(a>b)return a;
	return b;
};

unsigned short h_short(char* str,int size){
        int i,len;
        short ret=0;
        len = min(4,size);
        for(i=0;i<len;i++){
                if((str[i]==' ')||(str[i]=='\0'))return ret;
                if(h_byte(str[i])<0) return -1;
                ret*=16;
                ret+=h_byte(str[i]);
        };
        return ret;
};

unsigned char h_char(char* str,int size){
        int i,len;
        char ret=0;
        len = min(2,size);
        for(i=0;i<len;i++){
                if((str[i]==' ')||(str[i]=='\0'))return ret;
		if(h_byte(str[i])<0) return -1;
                ret*=16;
                ret+=h_byte(str[i]);
        };
        return ret;
};

unsigned int h_int(char* str,int size){
	int i,len;
	int ret=0;
	len = min(8,size);
	for(i=0;i<len;i++){
                if((str[i]==' ')||(str[i]=='\0'))return ret;
		if(h_byte(str[i])<0) return -1;
		ret=ret<<4;
		ret+=h_byte(str[i]);
	};
	return ret;
};

//доделать обработку переполнения
unsigned int n_int(char* str,int size){
	int i=0;
	int ret=0;
	while(i<size){
		if(str[i]==' ') break;
		if(!isdigit(str[i]))break;
		ret*=10;
		ret+=str[i]-'0';
		i++;
	};
	return ret;
};

unsigned int n_short(char* str,int size){
	int i_ret=0;
	short ret;
	i_ret=n_int(str,size);
	if(i_ret<=0xffffffff){
		ret=i_ret;
		return ret;
	};
	return 0;
};

unsigned char n_char(char* str,int size){
	int i_ret=0;
	char ret;
	i_ret=n_int(str,size);
	if(i_ret>255) return 0;
	ret=i_ret;	
	return ret;
};	

void putdec(unsigned int num){

	unsigned int w;
	unsigned char z[30];
	char i,j;

	w=num;

	for(i=0;i<30;i++){
		z[i]=w%10;
		w=w/10;
	}

	i=29;

	while((z[i]==0)&&(i>0))i--;
	while(i>=0)putchar(digit[z[i--]]);

}

void puthex(unsigned int num){

	unsigned int w;
	unsigned char b[8];
	char i;

	w=num;

	for(i=0;i<8;i++)b[i]=(unsigned char)((w>>i*4) & 0x0000000f);

	i=7;

	while(i>=0)putchar(hex[b[i--]]);
}

void vprintf(const char* fmt,va_list args);

void printf(const char* fmt, ...){
	va_list args;
	va_start(args,fmt);

	textcolor(7);

	vprintf(fmt,args);

	va_end(args);
}

void puthexb(unsigned char byte){
	unsigned  char lb, rb;
	lb=byte >> 4;
  	rb=byte & 0x0F;
	putchar(hex[lb]);
	putchar(hex[rb]);
}

void vprintf(const char* fmt,va_list args){
	char* ch;
	int size;
	
	while(*fmt){
		switch(*fmt){
		case '%':
			fmt++;
			switch(*fmt){
				case 's':
					puts(va_arg(args,char *));
					break;
				case 'S':
				    ch = va_arg(args,char *);
				    size = va_arg(args,unsigned int);
					puts_size(ch,size);
					break;					
				case 'c':
					putchar(va_arg(args,unsigned int));
					break;
				case 'i':
					putdec(va_arg(args,unsigned int));
					break;
				case 'x':
					puthex(va_arg(args,unsigned int));
					break;
				case 'z':
					textcolor(va_arg(args,unsigned int));
					break;
				case '\0':
					errno=1;
					perror("Error>End of string\n");
					break;
				default:
					errno=2;
				        perror("Error>Undefined format string in printf\n");
			}
			break;
		case '\0':
			return;
		
		default:
			putchar(*fmt);
			break;
		}
		fmt++;
	}
}

