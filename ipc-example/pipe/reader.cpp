#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MSG_SIZE 1024

using namespace std;

int main() {
   cout << "Reader started..." << endl << flush;

   const char * pipe_pathname = "./pipe";
   
   int fd = open(pipe_pathname, O_RDONLY); // oflag for read-only access
   if (fd == -1) {
      cout << "Pipe open failed" << endl << flush;
      exit(1);
   }
   cout << "Named pipe opened for reading..." << endl << flush;

   char line[MSG_SIZE] = {0};

   int bytes_read;
   /* reads up to MSG_SIZE bytes from fd into the buffer */
   bytes_read = read(fd, line, MSG_SIZE);
   cout << bytes_read << " bytes are read from the pipe: " << line <<  endl;
   bytes_read = read(fd, line, MSG_SIZE);
   cout << bytes_read << " bytes are read from the pipe: " << line <<  endl;
   cout << "Finished reading bytes from the pipe..." << endl << flush;

   /* writes up to MSG_SIZE bytes from the buffer to fd */
   // write(fd, first, MSG_SIZE);   	
   // write(fd, second, MSG_SIZE);

   // close pipe from the write end
   close(fd);
   
   return 0;
}