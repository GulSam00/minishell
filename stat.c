#include <errno.h> 
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h>


int main(int argc, char **argv)
{
    struct stat sb; 
    int a = stat(argv[1], &sb);
    
    printf ("++++ result : %d ++++++\n", a);
   

    return (0);
}