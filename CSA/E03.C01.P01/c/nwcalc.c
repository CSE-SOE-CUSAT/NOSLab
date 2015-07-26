#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int* getIP(char* strIP){
	int i,j;
	int commaCount=0;
	static int pBytes[] ={0,0,0,0};
	for(i=0;i<sizeof(strIP);i++)
		if(strIP[i]==','){
			commaCount++;
		}
		if(commaCount==3)
			for(j=0;j<sizeof(strIP);j++){
				if(strIP[j]!=',')
					pBytes[3-commaCount] = pBytes[3-commaCount]*10 + (strIP[j]-'0');
				else
					commaCount--;
			}
	return pBytes;
}
char getClass(int byte){
	if( byte > 0 && byte < 127)
		return 'A';
	if( byte > 127 && byte < 192)
		return 'B';
	if( byte > 191 && byte < 224)
		return 'C';
	if( byte > 223 && byte < 240)
		return 'D';
	if( byte > 239 && byte < 255)
		return 'E';
}
int getMask(int byte){
	printf("%c\n", getClass(byte));
	return (getClass(byte)-'A')*8;
}
int main(int argc, char **argv) {
	int mask,bytes[4];
	if (argc<2){
		printf("Usage : %s <IP> [ Default Network Mask used ] \n\t%s <IP/Mask>\nEg : \t%s 52.5.25.103/09",argv[0],argv[0],argv[0]);
	}else{
		if(argv[1][sizeof(argv[1])-3]=='/')
			mask=((argv[1][sizeof(argv[1])-2]-'0')*10)+(argv[1][sizeof(argv[1])-1]-'0');
		else
			mask=getMask(bytes[0]);
		//bytes=getIP()
		printf("%d",mask);
	}

	return 0;
}