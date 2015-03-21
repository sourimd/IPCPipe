//pipes are only for related process,, i.e. between parent and child
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	int exitStatus;
	// file descriptor array. the first one will contain read type
	// and the 2nd one will contain write type
	int fds[2];

	pid_t childProcessID;

	// create pipe
	pipe( fds );

	childProcessID = fork();
	// child process will be used as reader
	if( childProcessID == 0 ){
		void * buf;
		// close the writer file descriptor 
		// as child process will be used only as reader
		close( fds[1] );
		//create read stream with the read file descriptor
		sleep(1);
		read( fds[0], buf, 12 );

		puts( (char *)buf );
		//close the read file descriptor once reading is done
		close( fds[0] );
	}
	else{
		// close the reader file descriptor 
		// as parent process will be used only as writer
		close( fds[0] );
		//create write stream with the read file descriptor
		char * buf = "hello world";
		write( fds[1], buf, strlen(buf) );
		//close the write file descriptor once writing is done
		close( fds[1] );
		waitpid(-1, &exitStatus, 0);
	}
}
