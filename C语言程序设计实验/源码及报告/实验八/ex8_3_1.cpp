#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *copy(FILE *fp,FILE *tmpfp,char *s,int m);
FILE *insert(FILE *fp,FILE *tmpfp,char *s,int n);
int main(int argc,char *argv[]) {
	if(argc!=4) {
		printf("Argument error!\n");
		exit(-1);
	}

	FILE *fp,*tmpfp;
	if((fp=fopen(argv[1],"rb"))==NULL)
		exit(-1);
	if((tmpfp=fopen("tmp.txt","w"))==NULL)
		exit(-1);

	for(;;) {
		if(copy(fp,tmpfp,argv[3],strlen(argv[3]))==NULL)
			break;
		insert(fp,tmpfp,argv[2],strlen(argv[3]));
	}
	fclose(fp);
	fclose(tmpfp);
	remove(argv[1]);
	rename("tmp.txt",argv[1]);
	return 0;
}
FILE *copy(FILE *fp,FILE *tmpfp,char *s,int m) {
#ifdef DEBUG
	printf("copy\n");
#endif // DEBUG
	char ch[m+1];
	for(;;) {
#ifdef DEBUG
		printf("for\n");
#endif // DEBUG
		fpos_t pos,*ptr=&pos;
		fgetpos(fp,ptr);
		fread(ch,1,m,fp);
		ch[m]=0;
		fsetpos(fp,ptr);
		fgetpos(fp,ptr);
		if(fgetc(fp)==EOF)
			return NULL;
		fsetpos(fp,ptr);
		if(strcmp(ch,s)==0)
			return fp;
		else {
#ifdef DEBUG
			printf("fprintf\n");
#endif // DEBUG
			if(ch[0]!='\r')
				fprintf(tmpfp,"%c",ch[0]);
			fseek(fp,1L,SEEK_CUR);
		}
	}
}
FILE *insert(FILE *fp,FILE *tmpfp,char *s,int m) {
#ifdef DEBUG
	printf("insert\n");
#endif // DEBUG
	fputs(s,tmpfp);
	fseek(fp,m,SEEK_CUR);
	return fp;
}
