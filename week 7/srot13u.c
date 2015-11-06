#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

int numrot = 0;

int rot13cmp(void const *a, void const*b)
{
   numrot++;
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
   int buf = 1; 
   int NumChar = 0;
   int NumWords = 0;
   int charptr = 0;
   int sizechange;
   
   char* charArray;

   bool inputfromstd = true;

   struct stat statfile;
   fstat(0, &statfile);
   if(S_ISREG(statfile.st_mode))
   {
      charArray = (char*) malloc(statfile.st_size);
   }
   else
   {
      inputfromstd = false;
      charArray = (char*) malloc(sizeof(char) * buf);
   }
   
   int sizefile = statfile.st_size;
 
   for( ; read(0, (charArray + NumChar), 1) > 0; NumChar++)
   {
      if((statfile.st_size == 0) && inputfromstd)
      {
         charArray = (char*)realloc(charArray, sizefile);
         sizefile++;
      }
      if (NumChar >= buf)
      {
          buf += 10;
          charArray = (char*) realloc(charArray, buf * sizeof(char));
      }
      NumChar++;
   }
   
   if(charArray[NumChar] != '\n')
   {
      charArray[NumChar] = '\n';
      NumChar++;
   }
   for( ; charptr < NumChar; charptr++)
      if(charArray[charptr] == '\n')
         NumWords++;

   char** wordArray = (char**) malloc(sizeof(char*) * NumWords);
   wordArray[0] = charArray;

   int addwords;
   int c;
   for(addwords = 0, c = 0; NumChar > addwords; addwords++)
      if(charArray[addwords] = '\n')
      { 
         c++;
         wordArray[c] = (charArray + addwords + 1);
      }
   
   qsort(wordArray, NumWords, sizeof(char*), rot13cmp);
   int k;
   for(k = 0; k < NumWords; k++) 
   {
	int i;
	for(i = 0; i < NumChar; i++)
	{
	   char d = wordArray[k][i];
	   write(1, &d, 1);
	   if ( d =='\n')
   	   {
		break;
	   }
	}
   }
   fprintf(stderr, "Number of Comparisons: %d \n", numrot);

//   int f;
//   free(charArray);
//   for(f = 0; f < NumWords; f++)
//      free(wordArray);
  
   return 0;

}


