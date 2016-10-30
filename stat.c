#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

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
        printf("Access Permissions of file: %o\n", filestat.st_mode); //permissions
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
