#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void
head(int fd, char *name, int line)
{
    int i, n, l, c; 

    l = c = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0 )
  {
    for(i=0;i<=n ;i++)
    {				
      if(buf[i]!='\n'){			
      	printf(1,"%c",buf[i]);
      }	
				
      else if (l == (line-1)){
	printf(1,"\n");	
	exit();
      }
				
      else{
      	printf(1,"\n");
      	l++;
      } 
    }
  }

  if(n < 0){
    printf(1, "head: read error\n");
    exit();
  }
}



int main(int argc, char *argv[]) {
    
      int i,fd = 0,standard = 10;	
    
      char sv,*nm;

      nm = ""; 

      if (argc <= 1) {	
            head(0, "", 10);	
            exit();
      }

      else {
            for (i = 1; i < argc; i++) {
		sv = *argv[i];	
				
                  if (sv == '-') { 
			argv[i]++;
                        standard = atoi(argv[i]++);
                  }
				
                  else {	
			if ((fd = open(argv[i], 0)) < 0) {
                        printf(1, "head: cannot open %s\n", argv[i]);
                        exit();
                        }
                  }
            }
		 
            head(fd, nm, standard);
            close(fd);
            exit();    

      }
}
