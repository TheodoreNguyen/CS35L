#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>


int rot13cmp(void const *a, void const*b)
{
   const char *a2 = *((const char**) a);
   const char *b2 = *((const char**) b);
   int i;
   int comparer = 0;
   for(i = 0; comparer == 0; i++)
   {
	if(a2[i] >= 'A' && a2[i] <= 'Z' || b2[i] >= 'A' && b2[i] <= 'Z')
	{
	   comparer = a2[i] - b2[i];
	}
	if(a2[i] >= 'a' && a2[i] <= 'z' || b2[i] >= 'a' && b2[i] <= 'z')
	{
	   comparer = a2[i] - b2[i]; 
	}
	if(a2[i] == '\n' && b2[i] != '\n')
	{
	   return -1;
	}
	if(a2[i] != '\n' && b2[i] == '\n')
	{
	   return 1;	
	}
	if((a2[i] == '\n' && b2[i] == '\n') && comparer == 0)
	{
	   return comparer; 
	}
	comparer = a2[i] - b2[i];	
	if( (a2[i]>='a' && a2[i]<='z') && (b2[i]>='a' && b2[i]<='z') )
	{
	    if( ((a2[i]<='m' && b2[i]<='m') || (a2[i]>='n' && b2[i]>='n')) )
		comparer *= 1;
	    else
		comparer *= -1;
	}
	if( (a2[i]>='A' && a2[i]<='Z') && (b2[i]>='A' && b2[i]<='Z') )
	{
	    if( ((a2[i]<='M' && b2[i]<='M') || (a2[i]>='N' && b2[i]>='N')) )
	    	comparer *= 1;
	    else
		comparer *= -1;
	}

   }

   return comparer; 
}

int main(void)
{
   int buf = 2147483647; 
   int mem = 1000000000; 
   int NumChars = 0;
   int NumWords = 0;
   int c;
   char* charArray = (char*) malloc(sizeof(char) * buf);
   char** wordArray = (char**) malloc(sizeof(char*) * mem);
   if(charArray != NULL && wordArray != NULL)
   {
	wordArray[NumWords] = charArray;
	do
	{
		c = getchar();
		if(c == EOF) 
	        {
                  charArray[NumChars] = '\n'; 
                  NumWords++;     
                  NumChars++; 
                  break;
                }	
		if(NumChars >= buf)  
                {
                        buf += 10;
                        charArray = (char*) realloc(charArray, (buf) * sizeof(char)); 
			if(!charArray)
			{
			   fprintf(stderr, "realloc space allocation failed");
			   exit(1);
			}
                }
		charArray[NumChars] = (char)c;
		NumChars++;
		if(charArray[NumChars-1] == '\n') 
		{
		   if(NumWords >= mem)
		   {	
			mem += 10;
			wordArray = (char**) realloc(wordArray, (mem) * sizeof(char*)); 
			if(!wordArray)
			{
			   fprintf(stderr, "realloc space allocation failed");
			   exit(1);
			}
		   }
		   NumWords++;
		   wordArray[NumWords] = (charArray+NumChars);
		}	 
	} while (c != EOF);
   }
   else
   {
	fprintf(stderr, "cannot allocate space");
	exit(1);
   }
   qsort(wordArray, NumWords, sizeof(char*), rot13cmp);
   int k;
   for(k = 0; k < NumWords; k++) 
   {
	int i;
	for(i = 0; i < mem; i++)
	{
	   char d = wordArray[k][i];
	   int error = putc(d, stdout);
	   if(error == EOF)
	   {
		fprintf(stderr, "writing error");
		exit(1);
	   }
	   if ( d =='\n')
   	   {
		break;
	   }
	}
   }
   return 0;
}
