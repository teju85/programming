// FUNCTION:
//          showHelp.c
// COMMENTS:
//          Displays the help information of the stand-alone C-files and shell scripts.
// USAGE:
//          ./showHelp <fileName> <comments>           (for proper usage)
//          ./showHelp -h (--help)                     (for help and exit)
//
// <fileName>
//           Name of the file whose help needs to be displayed.
// <comments>
//           The character or string which is used to represent the comments. In case of C it
// is '//' and in case of shell it is '#'.
//
// NOTE:
//           The help information will be displayed till the first line which doesn't start
// with the <comments>.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define MAXLEN 50
#define MAX 200
#define NO_ERR 0
#define ERR 1



// print the help
void help(char *file,char *type)
{
  int i,len;
  char data[MAX];
  FILE *fp;

  // initialization
  fp = fopen(file,"r");
  if(fp == NULL)
    {
      printf("The input file (%s) doesn't exist\n",file);
      exit(ERR);
    }
  len = strlen(type);
  // check
  while(!feof(fp))
    {
      fgets(data,MAX,fp);
      for(i=0;i<len;i++)
	if(data[i] != type[i])
	  break;
      if(i != len)
	return;
      printf("%s",data+i);
    }
  fclose(fp);
  return;
}


// main function
int main(int argc,char  *argv[])
{
  char file[MAXLEN],type[MAXLEN];

  // error
  if((argc != 3) && (argc != 1))
    {
      printf("Type '%s -h (--help)' for proper usage\n",argv[0]);
      exit(ERR);
    }
  // help and exit
  if(!strcmp(argv[1],"-h") ||!strcmp(argv[1],"--help"))
    {
      strcpy(file,"./showHelp ");
      strcat(file,argv[0]);
      strcat(file,".c //");
      system(file);
      exit(NO_ERR);
    }
  // arguments
  strcpy(file,argv[1]);
  strcpy(type,argv[2]);
  // print
  help(file,type);
  return NO_ERR;
}
