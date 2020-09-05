#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

char mn[25],rep[20][25],tstr[999];
int hist[542][21]={0};

// For Calculating LevenshteinDistance
int ReturnDistance(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);
}

//For reading messages and removing special characters, numbers & less then three letter word
char* msg(char s[])
{
	char ch;
        char wrd[25];
	FILE *fout=NULL,*fin=NULL;
	fin=fopen("temp1.txt","w+");
	fout=fopen("temp2.txt","w+");
	fputs(s,fin);
	fseek(fin,0,SEEK_SET);
	while(!feof(fin))
	{   
		ch=fgetc(fin);
		if(!(ch>=65&&ch<=90||ch>=97&&ch<=122))
		  ch=' ';				
		if(ch!=' ')
		  fputc(tolower(ch),fout);
		else
		 fputc(' ',fout);
	}
     fclose(fin);
     fclose(fout);
     fin=fopen("temp2.txt","r");
     fout=fopen("temp1.txt","w+");
     while(!feof(fin))
     {   
	fscanf(fin,"%s ",wrd);
	if(!(strlen(wrd)<3))
         fprintf(fout,"%s ",wrd);
     }
     fseek(fout,0,SEEK_SET);
     fgets(tstr,999,fout);
     fclose(fin);
     fclose(fout);
     remove("temp1.txt");
     remove("temp2.txt");
  return tstr;
}

//For dividing text file into test and train data file
void divide_file()
{
 char cArray[1000];
 int s_count=0,h_count=0;
 FILE *fin=NULL,*fout1=NULL,*fout2=NULL;
 fin=fopen("english.txt","r");
 fout1=fopen("train_msg.txt","w");
 fout2=fopen("test_msg.txt","w");
 if(fin==NULL)
  printf("Cannot open file");
 else
 {
  while(fgets(cArray,999,fin))
  {
   if(cArray[strlen(cArray)-5]=='p')
   {
    strcpy(cArray,msg(cArray));
    if(s_count<=41)
    {
     fputs(cArray,fout1);
     fputc('\n',fout1);
     s_count++;
    }
    else
    {
     fputs(cArray,fout2);
     fputc('\n',fout2);
     s_count++;
    }
   }
   else
   {
    strcpy(cArray,msg(cArray));
    if(h_count<=501)
    {
     fputs(cArray,fout1);
     h_count++;
     fputc('\n',fout1);
    }
    else
    {
     fputs(cArray,fout2);
     h_count++;
     fputc('\n',fout2);
    }
   }
  }
  printf("\nEnglish.txt file reading succesfull !\n");
  printf("Spams = %d & Hams = %d\n",s_count,--h_count);
 }
fclose(fin);
fclose(fout1);
fclose(fout2);
}

//Finding Centroid of a ComputeKMeans
char* mean(FILE *fin)
{
   char c1[25],c2[25];
   int ld=0,min=1000000;
   FILE *fout=NULL;
   fout=fopen("temp.txt","w+");
   fseek(fin,0,SEEK_SET);
   while(!feof(fin))
   {
     fscanf(fin,"%s ",c1);
     fprintf(fout,"%s ",c1);
   }
   fseek(fin,0,SEEK_SET);
   while(!(feof(fin)))
   {
     ld=0;
     fscanf(fin,"%s ",c1);
     fseek(fout,0,SEEK_SET);
     while(!(feof(fout)))
     {
       	fscanf(fout,"%s ",c2);
        ld+=ReturnDistance(c1,c2);
     }
     if(ld<min)
     {
       strcpy(mn,c1);
       min=ld;
     }
   }
  remove("temp.txt");
 return mn;
}

//Arranging words for ComputeKMeansing   
void divide_word()
{
  char ch1;
  char wrd[25];
  FILE *fin=NULL,*fout=NULL;
  fout=fopen("train_word.txt","w");
  fin=fopen("train_msg.txt","r");
  if(fin==NULL)
    printf("Cannot open file");
  else
  {
	while(!feof(fin))
	{   
		fscanf(fin,"%s ",wrd);
		if(!((strcmp(wrd,"spam")==0)||(strcmp(wrd,"ham")==0)))
                    fprintf(fout,"%s ",wrd);
	}
  }
 fclose(fin);
 fclose(fout); 
}

//Clustering of words and finding representative words
void ComputeKMeans(int t)
{

 if(t==0)
 	return;
 char str[25];
 int ld[20];
 int i,j,min;
 FILE *fin=NULL;
 FILE *fout[20];
 fin=fopen("train_word.txt","r");
 fout[0]=fopen("ComputeKMeans1.txt","w+");
 fout[1]=fopen("ComputeKMeans2.txt","w+");
 fout[2]=fopen("ComputeKMeans3.txt","w+");
 fout[3]=fopen("ComputeKMeans4.txt","w+");
 fout[4]=fopen("ComputeKMeans5.txt","w+");
 fout[5]=fopen("ComputeKMeans6.txt","w+");
 fout[6]=fopen("ComputeKMeans7.txt","w+");
 fout[7]=fopen("ComputeKMeans8.txt","w+");
 fout[8]=fopen("ComputeKMeans9.txt","w+");
 fout[9]=fopen("ComputeKMeans10.txt","w+");
 fout[10]=fopen("ComputeKMeans11.txt","w+");
 fout[11]=fopen("ComputeKMeans12.txt","w+");
 fout[12]=fopen("ComputeKMeans13.txt","w+");
 fout[13]=fopen("ComputeKMeans14.txt","w+");
 fout[14]=fopen("ComputeKMeans15.txt","w+");
 fout[15]=fopen("ComputeKMeans16.txt","w+");
 fout[16]=fopen("ComputeKMeans17.txt","w+");
 fout[17]=fopen("ComputeKMeans18.txt","w+");
 fout[18]=fopen("ComputeKMeans19.txt","w+");
 fout[19]=fopen("ComputeKMeans20.txt","w+");

 while(!feof(fin))
 {
  fscanf(fin,"%s ",str);
  for(i=0;i<20;i++)
   	ld[i]=ReturnDistance(str,rep[i]);
  min=ld[0];
  j=0;
  for(i=1;i<20;i++)
  {
  	if(ld[i]<min)
  	{
  		min=ld[i];
  		j=i;
  	}
  }
  fprintf(fout[j],"%s ",str);
 }
 for(i=0;i<20;i++)
 	fseek(fout[i],0,SEEK_SET);
 for(i=0;i<20;i++)
   strcpy(rep[i],mean(fout[i]));
  ComputeKMeans(t-1);
  fclose(fin);
 for(i=0;i<20;i++)
 	fclose(fout[i]);
 remove("ComputeKMeans1.txt");
 remove("ComputeKMeans2.txt");
 remove("ComputeKMeans3.txt");
 remove("ComputeKMeans4.txt");
 remove("ComputeKMeans5.txt");
 remove("ComputeKMeans6.txt");
 remove("ComputeKMeans7.txt");
 remove("ComputeKMeans8.txt");
 remove("ComputeKMeans9.txt");
 remove("ComputeKMeans10.txt");
 remove("ComputeKMeans11.txt");
 remove("ComputeKMeans12.txt");
 remove("ComputeKMeans13.txt");
 remove("ComputeKMeans14.txt");
 remove("ComputeKMeans15.txt");
 remove("ComputeKMeans16.txt");
 remove("ComputeKMeans17.txt");
 remove("ComputeKMeans18.txt");
 remove("ComputeKMeans19.txt");
 remove("ComputeKMeans20.txt");
}

//Computing Histogram
void ComputeHistogram()
{
 char cArray[1000],cWord[25];
 int sum=0,j=0,k=0;
 FILE *fin=NULL,*fout=NULL;
 fin=fopen("train_msg.txt","r"); 
 if(fin==NULL)
  printf("Cannot open file");
 else
 {
  while(!feof(fin))
  {
  	fout=fopen("temp.txt","w+");
  	fgets(cArray,999,fin);
  	fputs(cArray,fout);
        if(cArray[strlen(cArray)-5]=='p')
   	    hist[j][20]=1;     
        else
   	   hist[j][20]=0;
        for(k=0;k<20;k++)
        { 
          sum=0;
          fseek(fout,0,SEEK_SET);
      	  while(!feof(fout))
   	  {
   	    fscanf(fout,"%s ",cWord); 
            sum+=ReturnDistance(rep[k],cWord);
          } 
          hist[j][k]=200-sum;        
        }
    j++;
  }
 } 
 fclose(fin);
 fclose(fout);
 remove("temp.txt");
}

//Finding similarity between test and train data and judging test message
void ComputeL1distance()
{
 char cArray[1000],cWord[25];
 int i=0,j=0,t=0,incorrect=0,correct=0,min=0,sum=0,pos=0,sc=0,si=0,hc=0,hi=0; 
 int test_hist[21]={0};
 FILE *fin=NULL,*fout=NULL;
 fin=fopen("test_msg.txt","r"); 
  while(!feof(fin))
  {  j++;
  	fout=fopen("temp.txt","w+");
  	fgets(cArray,999,fin);
  	fputs(cArray,fout);
        if(cArray[strlen(cArray)-5]=='p')
   	       test_hist[20]=1;
        else
   	      test_hist[20]=0;
   	for(i=0;i<20;i++)
          { 
            sum=0;
            fseek(fout,0,SEEK_SET);
      	    while(!feof(fout))
   	    {
   	      fscanf(fout,"%s ",cWord); 
              sum+=ReturnDistance(rep[i],cWord);
            } 
           test_hist[i]=200-sum;        
         }
     fclose(fout); 
   min=1000;
   for(j=0;j<510;j++)
   {
   	sum=0;
  	for(t=0;t<20;t++)
  	   sum+=((hist[j][t]-test_hist[t])*(hist[j][t]-test_hist[t]));	 
        if(sum<=min)
           {
           	min=sum;
           	pos=j;
           }
    }
    if(hist[pos][20]==test_hist[20])
  	{
        	correct++;
  		if(test_hist[20]==1)
  	        	sc++;
  	 	else
                    hc++;
         }
  	 else
  	 {
  	   incorrect++;
  	   if(test_hist[20]==1)
  	     si++;
  	   else
             hi++;
  	 }
   }
   printf("\n******* Report *********\n");
   printf("Total Messages read = %d\n",correct+incorrect);
   printf("correctly read = %d\nincorrectly read= %d\n",correct,incorrect);
   printf("Percentage= %d  (approx)\n\n\n",(correct*100)/(incorrect+correct));
   printf("correctly read spam messeages= %d\nincorrectly read spam messages= %d\n",sc,si);
   printf("correctly read ham messages= %d\nincorrectly read ham messages= %d\n",hc,hi);
 fclose(fin);
 remove("temp.txt");
}

//Selecting first random 20 words for clustering
void GenarateRandom()
{
 char str[25];
 int j;
 FILE *fin=NULL;
 fin=fopen("train_word.txt","r");
 for(j=0;j<20;j++)
  {
 	fseek(fin,((rand()*247)%1000),SEEK_SET);
 	fscanf(fin,"%s ",str);
 	fscanf(fin,"%s ",str);
 	strcpy(rep[j],str);
  }
  fclose(fin); 
}

void main()
{
  int j;
  
  divide_file(); 
  divide_word(); 
  GenarateRandom();

  printf("\nClustering.......Please wait !\n");
  
  ComputeKMeans(4);

  printf("\nClustering successful !\n"); 
  printf("\nReprsentative words are :\n"); 
  
  for(j=0;j<20;j++)
  	printf("%d) %s\n",j+1,rep[j]);
  
  printf("\nReading test data .......please wait\n");
  
  ComputeHistogram(); 
  
  printf("\nTest data reading succesful!\n");
  ComputeL1distance(); 
 
 remove("test_msg.txt");
 remove("train_word.txt");
 remove("train_msg.txt");
}

