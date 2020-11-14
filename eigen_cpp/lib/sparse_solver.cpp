#include "sparse_solver.h"

bool report_error(Eigen::ComputationInfo info) {
    switch(info) {
    case NumericalIssue:
      std::cerr << "Solver Failed: Numerical Issue (prerequisites not met)" << std::endl;
      return true;
    case NoConvergence:
      std::cerr << "Solver Failed: Did not converge" << std::endl;
      return true;
    case InvalidInput:
      std::cerr << "Solver Failed: Invalid input" << std::endl;
      return true;
    case Success:
    default:
      return false;
    }
  }

template <class Solver,
          typename spmat,
          typename spmat_elt,
          typename c_spmat>
spmat& SparseSolver<Solver, spmat, spmat_elt, c_spmat>
::c_to_eigen(c_spmat* ptr)
{
  return *reinterpret_cast<spmat*>(ptr);
}

template <class Solver,
          typename spmat,
          typename spmat_elt,
          typename c_spmat>
c_spmat* SparseSolver<Solver, spmat, spmat_elt, c_spmat>
::eigen_to_c(spmat& ref)
{
  return reinterpret_cast<c_spmat*>(&ref);
}

template <class Solver,
          typename spmat,
          typename spmat_elt,
          typename c_spmat>
SparseSolver<Solver, spmat, spmat_elt, c_spmat>
::SparseSolver(c_spmat *c_coefficients, c_spmat *c_observations)
{
  spmat row_major_coeffs = c_to_eigen(c_coefficients).pruned();
  spmat row_major_observ = c_to_eigen(c_observations).pruned();

  coefficients = new col_major_spmat(row_major_coeffs);
  observations = new col_major_spmat(row_major_observ);

  coefficients->makeCompressed();
  observations->makeCompressed();

  solver.compute(*coefficients);
}

template <class Solver,
          typename spmat,
          typename spmat_elt,
          typename c_spmat>
SparseSolver<Solver, spmat, spmat_elt, c_spmat>
::~SparseSolver()
{
  delete coefficients;
  delete observations;
}

template <class Solver,
          typename spmat,
          typename spmat_elt,
          typename c_spmat>
c_spmat* SparseSolver<Solver, spmat, spmat_elt, c_spmat>::solve()
{
  col_major_spmat col_major_solution;
  spmat*          row_major_solution;
  c_spmat*        c_solution;

  if(report_error(SparseSolver::solver.info())) { return NULL; }
  col_major_solution = SparseSolver::solver.solve(*observations);
  row_major_solution = new spmat(col_major_solution);
  if(report_error(SparseSolver::solver.info())) { return NULL; }
  c_solution = eigen_to_c(*row_major_solution);
  return c_solution;
}
