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

char handle_prefix(long int size, long int * ret) {
    long int s = size;
    while (s >= 1000) {
        s /= 1000;
    }
    *ret = s;
    if (size < 1e6) return 'k';
    if (size < 1e9) return 'M';
    if (size < 1e12) return 'G';
    if (size < 1e15) return 'T';
    if (size < 1e18) return 'P';
    if (size < 1e21) return 'E';
    if (size < 1e24) return 'Z';
    if (size < 1e27) return 'Y';
    return '!';
}

void fmt_SI(long int size, char unit_char, char* buf) {
    if (size < 1000) {
        sprintf(buf, "%li B\0", size);
    } else if (size < 1e27) {
        long int displayval;
        char prefix = handle_prefix(size, &displayval);
        sprintf(buf, "%li %c%c\0", displayval, prefix, unit_char);
    } else {
        sprintf(buf, "%li Y%c\0", size / (long int) 1e24, unit_char);
    }
}

void printStat( char * file ){
    if( file == NULL ) {
        printf( "No filename entered!" );
        return;
    }

    struct stat filestat;

    if ( stat( file, &filestat ) == 0 ) {
        // name:
        printf( "File: %s\n", file );
        // size:
        char p[256];
        fmt_SI(filestat.st_size, 'B', p);
        printf("File Size: %s\n", p);
        // permissions:
        printf("Access Permissions of file: %o\n", filestat.st_mode);
        // time last accessed:
        printf("Time last accessed: %s\n", ctime( &(filestat.st_atime) ));
    } else {
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
