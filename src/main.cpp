# include "solver/Solver.hpp"

int main(int argc, char* argv[])
{
  if (argc == 4)
  {
    Solver *solver = new Solver(argv[1], argv[2]);

    solver->solve();
    //    solver->save_result();

    delete (solver);
  }
  else
  {
    std::cerr << "Bad usage: /Solver FILEPATH PROBLEM_NAME RESULT_FILE" << std::endl;
    return -1;
  }
}
