#ifndef _SPARSE_SOLVER_H_
#define _SPARSE_SOLVER_H_

template <class Solver,
          typename spmat,
          typename spmat_elt,
          typename c_spmat>
class SparseSolver
{
  typedef SparseMatrix<spmat_elt, Eigen::ColMajor, int> col_major_spmat;

 private:
  col_major_spmat* coefficients;
  col_major_spmat* observations;
  spmat& c_to_eigen(c_spmat*);
  c_spmat* eigen_to_c(spmat&);

 public:
  Solver solver;
  SparseSolver(c_spmat *c_coefficients, c_spmat *c_observations);
  ~SparseSolver();
  c_spmat* solve();
};

#include "sparse_solver.cpp"

#endif
