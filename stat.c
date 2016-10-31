#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

char* printPermissions( int n ) {
  char * c = (char*) malloc( 9 * sizeof(char) );
  int i = 8;

  while( n > 0 ) {
    int x = n % 8;

    printf( "%d", x );
    
    c[i--] = '-';
    c[i--] = '-';
    c[i--] = '-';

    if( i%2 == 1 ) {
       c[i+3] = 'x';
    }

    if( (i == 2) || (i == 3) || (i == 6) || (i == 7) ) {
      c[i+2] = 'w';
    }

    if( i >= 4 ) {
      c[i+1] = 'r';
    }

    n /= 8;
  }
    
  return c;
}


void printStat( char * file ){
    if( file == NULL ) {
        printf( "No filename entered!" );
        return;
    }

    struct stat filestat;

    if( stat( file, &filestat ) == 0 )
    {
        printf( "File: %s\n", file ); //name
        printf("File Size: %li bytes\n", filestat.st_size ); //size
        printf("Access Permissions of file: %s\n", printPermissions(filestat.st_mode)); //permissions
        printf("Time last accessed: %s\n", ctime( &(filestat.st_atime) )); //time last accessed
    }
    else {
        printf("File Error %d: %s\n", errno, strerror(errno));
    }
}

void main()
{
    //used to test other files
    /*
    // Get file name
    printf("Enter Filename....\n");
    scanf( "%s", file );
    */

    printStat( "file.txt" ); //print info on default file

}
