/*
 * Eigen - an OCaml interface to C++ Eigen library
 * Copyright (c) 2016-2020 Liang Wang <liang.wang@cl.cam.ac.uk>
 */

#include "sparse_solver.h"

/******************** pointer conversion  ********************/

typedef SparseMatrix<spmat_d_elt, Eigen::RowMajor, INDEX> spmat_d;
typedef SparseMatrix<spmat_d_elt, Eigen::ColMajor,   int> col_major_spmat_d;


inline spmat_d& c_to_eigen(c_spmat_d* ptr)
{
  return *reinterpret_cast<spmat_d*>(ptr);
}

inline c_spmat_d* eigen_to_c(spmat_d& ref)
{
  return reinterpret_cast<c_spmat_d*>(&ref);
}


/***************** c stubs for c++ functions *****************/

c_spmat_d* c_eigen_spmat_d_new(INDEX size, INDEX rows, INDEX cols)
{
  spmat_d* x = new spmat_d(rows, cols);
  (*x).reserve(size);
  return eigen_to_c(*x);
}

void c_eigen_spmat_d_delete(c_spmat_d *m)
{
  delete &c_to_eigen(m);
}

c_spmat_d* c_eigen_spmat_d_eye(INDEX m)
{
  spmat_d* x = new spmat_d(m, m);
  (*x).setIdentity();
  return eigen_to_c(*x);
}

INDEX c_eigen_spmat_d_rows(c_spmat_d *m)
{
  return c_to_eigen(m).rows();
}

INDEX c_eigen_spmat_d_cols(c_spmat_d *m)
{
  return c_to_eigen(m).cols();
}

INDEX c_eigen_spmat_d_nnz(c_spmat_d *m)
{
  return (c_to_eigen(m)).nonZeros();
}

spmat_d_elt c_eigen_spmat_d_get(c_spmat_d *m, INDEX i, INDEX j)
{
  return (c_to_eigen(m)).coeff(i,j);
}

void c_eigen_spmat_d_set(c_spmat_d *m, INDEX i, INDEX j, spmat_d_elt x)
{
  (c_to_eigen(m)).coeffRef(i,j) = x;
}

void c_eigen_spmat_d_insert(c_spmat_d *m, INDEX i, INDEX j, spmat_d_elt x)
{
  (c_to_eigen(m)).insert(i,j) = x;
}

void c_eigen_spmat_d_reset(c_spmat_d *m)
{
  (c_to_eigen(m)).setZero();
}

int c_eigen_spmat_d_is_compressed(c_spmat_d *m)
{
  return (c_to_eigen(m)).isCompressed();
}

void c_eigen_spmat_d_compress(c_spmat_d *m)
{
  (c_to_eigen(m)).makeCompressed();
}

void c_eigen_spmat_d_uncompress(c_spmat_d *m)
{
  (c_to_eigen(m)).uncompress();
}

void c_eigen_spmat_d_reshape(c_spmat_d *m, INDEX rows, INDEX cols)
{
  // FIXME: keep old data
  (c_to_eigen(m)).resize(rows, cols);
}

void c_eigen_spmat_d_prune(c_spmat_d *m, spmat_d_elt ref, spmat_d_elt eps)
{
  (c_to_eigen(m)).prune(ref, eps);
}

spmat_d_elt* c_eigen_spmat_d_valueptr(c_spmat_d *m, INDEX *l)
{
  spmat_d& x = c_to_eigen(m);
  x.makeCompressed();
  *l = x.data().size();
  return x.valuePtr();
}

INDEX* c_eigen_spmat_d_innerindexptr(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  x.makeCompressed();
  return x.innerIndexPtr();
}

INDEX* c_eigen_spmat_d_outerindexptr(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  x.makeCompressed();
  return x.outerIndexPtr();
}

c_spmat_d* c_eigen_spmat_d_clone(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_d(x));
}

c_spmat_d* c_eigen_spmat_d_row(c_spmat_d *m, INDEX i)
{
  spmat_d* x = new spmat_d((c_to_eigen(m)).row(i));
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_col(c_spmat_d *m, INDEX i)
{
  spmat_d* x = new spmat_d((c_to_eigen(m)).col(i));
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_transpose(c_spmat_d *m)
{
  spmat_d* x = new spmat_d((c_to_eigen(m)).transpose());
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_adjoint(c_spmat_d *m)
{
  spmat_d* x = new spmat_d((c_to_eigen(m)).adjoint());
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_diagonal(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_d(x.diagonal().sparseView()));
}

spmat_d_elt c_eigen_spmat_d_trace(c_spmat_d *m)
{
  return c_to_eigen(m).diagonal().sparseView().sum();
}

int c_eigen_spmat_d_is_zero(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  if (x.nonZeros() == 0)
    return 1;

  spmat_d_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k] != spmat_d_zero) {
      b = 0;
      break;
    }
  }
  return b;
}

int c_eigen_spmat_d_is_positive(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  x.makeCompressed();
  if (x.nonZeros() < (x.rows() * x.cols()))
    return 0;

  spmat_d_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k] <= 0) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_d_is_negative(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  x.makeCompressed();
  if (x.nonZeros() < (x.rows() * x.cols()))
    return 0;

  spmat_d_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k] >= 0) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_d_is_nonpositive(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  x.makeCompressed();
  spmat_d_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k] > 0) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_d_is_nonnegative(c_spmat_d *m)
{
  spmat_d& x = c_to_eigen(m);
  x.makeCompressed();
  spmat_d_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k] < 0) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_d_is_equal(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d x = c_to_eigen(m0) - c_to_eigen(m1);
  x.prune(spmat_d_zero, 0.);
  return (x.nonZeros() == 0);
}

int c_eigen_spmat_d_is_unequal(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d x = c_to_eigen(m0) - c_to_eigen(m1);
  x.prune(spmat_d_zero, 0.);
  return (x.nonZeros() != 0);
}

int c_eigen_spmat_d_is_greater(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_d_is_positive(eigen_to_c(x));
}

int c_eigen_spmat_d_is_smaller(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_d_is_negative(eigen_to_c(x));
}

int c_eigen_spmat_d_equal_or_greater(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_d_is_nonnegative(eigen_to_c(x));
}

int c_eigen_spmat_d_equal_or_smaller(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_d_is_nonpositive(eigen_to_c(x));
}

c_spmat_d* c_eigen_spmat_d_add(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d& x0 = c_to_eigen(m0);
  spmat_d& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_d(x0 + x1));
}

c_spmat_d* c_eigen_spmat_d_sub(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d& x0 = c_to_eigen(m0);
  spmat_d& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_d(x0 - x1));
}

c_spmat_d* c_eigen_spmat_d_mul(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d& x0 = c_to_eigen(m0);
  spmat_d& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_d(x0.cwiseProduct(x1)));
}

c_spmat_d* c_eigen_spmat_d_div(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d& x0 = c_to_eigen(m0);
  spmat_d& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_d(x0.cwiseQuotient(x1)));
}

c_spmat_d* c_eigen_spmat_d_gemm(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d& x0 = c_to_eigen(m0);
  spmat_d& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_d(x0 * x1));
}

c_spmat_d* c_eigen_spmat_d_add_scalar(c_spmat_d *m, spmat_d_elt a)
{
  spmat_d* x = new spmat_d(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_d::InnerIterator it(*x,k); it; ++it)
      it.valueRef() += a;
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_sub_scalar(c_spmat_d *m, spmat_d_elt a)
{
  spmat_d* x = new spmat_d(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_d::InnerIterator it(*x,k); it; ++it)
      it.valueRef() -= a;
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_mul_scalar(c_spmat_d *m, spmat_d_elt a)
{
  spmat_d& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_d(x * a));
}

c_spmat_d* c_eigen_spmat_d_div_scalar(c_spmat_d *m, spmat_d_elt a)
{
  spmat_d* x = new spmat_d(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_d::InnerIterator it(*x,k); it; ++it)
      it.valueRef() /= a;
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_min2(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d& x0 = c_to_eigen(m0);
  spmat_d& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_d(x0.cwiseMin(x1)));
}

c_spmat_d* c_eigen_spmat_d_max2(c_spmat_d *m0, c_spmat_d *m1)
{
  spmat_d& x0 = c_to_eigen(m0);
  spmat_d& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_d(x0.cwiseMax(x1)));
}

spmat_d_elt c_eigen_spmat_d_sum(c_spmat_d *m)
{
  return (c_to_eigen(m)).sum();
}

spmat_d_elt c_eigen_spmat_d_min(c_spmat_d *m)
{
  spmat_d_elt a = std::numeric_limits<spmat_d_elt>::infinity();
  spmat_d& x = c_to_eigen(m);
  for (INDEX k = 0; k < x.outerSize(); ++k)
    for (spmat_d::InnerIterator it(x,k); it; ++it)
    {
      if (it.value() < a)
        a = it.value();
    }
  if ((x.nonZeros() < (x.rows() * x.cols())) && (a > 0))
    a = 0;
  return a;
}

spmat_d_elt c_eigen_spmat_d_max(c_spmat_d *m)
{
  spmat_d_elt a = -std::numeric_limits<spmat_d_elt>::infinity();
  spmat_d& x = c_to_eigen(m);
  for (INDEX k = 0; k < x.outerSize(); ++k)
    for (spmat_d::InnerIterator it(x,k); it; ++it)
    {
      if (it.value() > a)
        a = it.value();
    }
  if ((x.nonZeros() < (x.rows() * x.cols())) && (a < 0))
    a = 0;
  return a;
}

c_spmat_d* c_eigen_spmat_d_abs(c_spmat_d *m)
{
  spmat_d* x = new spmat_d((c_to_eigen(m)).cwiseAbs());
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_neg(c_spmat_d *m)
{
  spmat_d* x = new spmat_d(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_d::InnerIterator it(*x,k); it; ++it)
      it.valueRef() = -it.value();
  return eigen_to_c(*x);
}

c_spmat_d* c_eigen_spmat_d_sqrt(c_spmat_d *m)
{
  spmat_d* x = new spmat_d((c_to_eigen(m)).cwiseSqrt());
  return eigen_to_c(*x);
}

void c_eigen_spmat_d_print(c_spmat_d *m)
{
  std::cout << c_to_eigen(m) << std::endl;
}

c_spmat_d* c_eigen_spmat_d_sparse_LU(c_spmat_d *c_coefficients, c_spmat_d *c_observations)
{
  SparseSolver<SparseLU<col_major_spmat_d>,
               spmat_d,
               spmat_d_elt,
               c_spmat_d> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_d* c_eigen_spmat_d_sparse_QR(c_spmat_d *c_coefficients, c_spmat_d *c_observations)
{
  SparseSolver<SparseQR<col_major_spmat_d, COLAMDOrdering<int> >,
               spmat_d,
               spmat_d_elt,
               c_spmat_d> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_d* c_eigen_spmat_d_simplicial_LLT(c_spmat_d *c_coefficients,
                                          c_spmat_d *c_observations)
{
  SparseSolver<SimplicialLLT<col_major_spmat_d>,
               spmat_d,
               spmat_d_elt,
               c_spmat_d> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_d* c_eigen_spmat_d_simplicial_LDLT(c_spmat_d *c_coefficients,
                                           c_spmat_d *c_observations)
{
  SparseSolver<SimplicialLDLT<col_major_spmat_d>,
               spmat_d,
               spmat_d_elt,
               c_spmat_d> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_d* c_eigen_spmat_d_conjugate_gradient(c_spmat_d *c_coefficients,
                                              c_spmat_d *c_observations)
{
  SparseSolver<ConjugateGradient<col_major_spmat_d>,
               spmat_d,
               spmat_d_elt,
               c_spmat_d> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_d* c_eigen_spmat_d_least_squares_conjugate_gradient(c_spmat_d *c_coefficients,
                                                            c_spmat_d *c_observations)
{
  SparseSolver<LeastSquaresConjugateGradient<col_major_spmat_d>,
               spmat_d,
               spmat_d_elt,
               c_spmat_d> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_d* c_eigen_spmat_d_BiCGSTAB(c_spmat_d *c_coefficients,
                                              c_spmat_d *c_observations)
{
  SparseSolver<BiCGSTAB<col_major_spmat_d>,
               spmat_d,
               spmat_d_elt,
               c_spmat_d> ss(c_coefficients, c_observations);
  return ss.solve();
}
