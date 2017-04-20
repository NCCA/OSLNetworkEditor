#include "ShaderParser.h"
#include <cstdlib>
int main(int argc, char **argv)
{
  ShaderParser s(argv[1]);
  s.print();
  return EXIT_SUCCESS;
}
