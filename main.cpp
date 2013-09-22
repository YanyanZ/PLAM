# include "src/Interface.hpp"

int main(int argc, char* argv[])
{
  if (argc == 2)
  {
    Interface solver(argv[1]);

    solver.solve();

    return 0;
  }
  else
    return -1;
}
