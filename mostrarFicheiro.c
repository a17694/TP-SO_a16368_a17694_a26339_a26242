#include <fcntl.h>
#include <unistd.h>

/// @brief Mostra ficheiros
/// @param argc
/// @param argv
void showfile(int argc, char *argv[])
{
  char buffer[4096];
  int i, fo, nread, ntotalwritten, nwritten;

  // @details Loop files
  for (i = 1; i < argc; i++)
  {
    fo = open(argv[i], O_RDONLY);
    if (fo != -1)
    {
      // @detail Read file
      while ((nread = read(fo, buffer, sizeof(buffer))) > 0)
      {
        ntotalwritten = 0;
        // @details Run file
        while (ntotalwritten < nread)
        {
          nwritten = write(STDOUT_FILENO, buffer + ntotalwritten, nread - ntotalwritten);
          if (nwritten >= 1) {
            ntotalwritten += nwritten;
          }
        }
      }
      write(STDOUT_FILENO, "\n", 1);
      close(fo);
    }
    else
    {
      write(STDERR_FILENO, "O ficheiro nao existe\n\n", 23);
    }
  }
}