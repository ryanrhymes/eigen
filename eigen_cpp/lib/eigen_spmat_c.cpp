/*
 * Eigen - an OCaml interface to C++ Eigen library
 * Copyright (c) 2016-2020 Liang Wang <liang.wang@cl.cam.ac.uk>
 */

#include "sparse_solver.h"

/******************** pointer conversion  ********************/

typedef SparseMatrix<spmat_c_elt, Eigen::RowMajor, INDEX> spmat_c;
typedef SparseMatrix<spmat_c_elt, Eigen::ColMajor,   int> col_major_spmat_c;


inline spmat_c& c_to_eigen(c_spmat_c* ptr)
{
  return *reinterpret_cast<spmat_c*>(ptr);
}

inline c_spmat_c* eigen_to_c(spmat_c& ref)
{
  return reinterpret_cast<c_spmat_c*>(&ref);
}

inline c_spmat_c_elt eigen_to_c(spmat_c_elt& ref)
{
  return *reinterpret_cast<c_spmat_c_elt*>(&ref);
}

inline spmat_c_elt c_to_eigen(c_spmat_c_elt c)
{
  return spmat_c_elt(c.r, c.i);
}

inline c_spmat_c_elt* eigen_to_c_ptr(spmat_c_elt* ref)
{
  return reinterpret_cast<c_spmat_c_elt*>(ref);
}


/***************** SparseMatrix_C: c stubs for c++ functions *****************/

c_spmat_c* c_eigen_spmat_c_new(INDEX size, INDEX rows, INDEX cols)
{
  spmat_c* x = new spmat_c(rows, cols);
  (*x).reserve(size);
  return eigen_to_c(*x);
}

void c_eigen_spmat_c_delete(c_spmat_c *m)
{
  delete &c_to_eigen(m);
}

c_spmat_c* c_eigen_spmat_c_eye(INDEX m)
{
  spmat_c* x = new spmat_c(m, m);
  (*x).setIdentity();
  return eigen_to_c(*x);
}

INDEX c_eigen_spmat_c_rows(c_spmat_c *m)
{
  return c_to_eigen(m).rows();
}

INDEX c_eigen_spmat_c_cols(c_spmat_c *m)
{
  return c_to_eigen(m).cols();
}

INDEX c_eigen_spmat_c_nnz(c_spmat_c *m)
{
  return (c_to_eigen(m)).nonZeros();
}

c_spmat_c_elt c_eigen_spmat_c_get(c_spmat_c *m, INDEX i, INDEX j)
{
  spmat_c_elt a = (c_to_eigen(m)).coeff(i,j);
  return eigen_to_c(a);
}

void c_eigen_spmat_c_set(c_spmat_c *m, INDEX i, INDEX j, c_spmat_c_elt x)
{
  (c_to_eigen(m)).coeffRef(i,j) = c_to_eigen(x);
}

void c_eigen_spmat_c_insert(c_spmat_c *m, INDEX i, INDEX j, c_spmat_c_elt x)
{
  (c_to_eigen(m)).insert(i,j) = c_to_eigen(x);
}

void c_eigen_spmat_c_reset(c_spmat_c *m)
{
  (c_to_eigen(m)).setZero();
}

int c_eigen_spmat_c_is_compressed(c_spmat_c *m)
{
  return (c_to_eigen(m)).isCompressed();
}

void c_eigen_spmat_c_compress(c_spmat_c *m)
{
  (c_to_eigen(m)).makeCompressed();
}

void c_eigen_spmat_c_uncompress(c_spmat_c *m)
{
  (c_to_eigen(m)).uncompress();
}

void c_eigen_spmat_c_reshape(c_spmat_c *m, INDEX rows, INDEX cols)
{
  // FIXME: keep old data
  (c_to_eigen(m)).resize(rows, cols);
}

void c_eigen_spmat_c_prune(c_spmat_c *m, c_spmat_c_elt ref, float eps)
{
  spmat_c_elt a = c_to_eigen(ref);
  (c_to_eigen(m)).prune(a, eps);
}

c_spmat_c_elt* c_eigen_spmat_c_valueptr(c_spmat_c *m, INDEX *l)
{
  spmat_c& x = c_to_eigen(m);
  x.makeCompressed();
  *l = x.data().size();
  return eigen_to_c_ptr(x.valuePtr());
}

INDEX* c_eigen_spmat_c_innerindexptr(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  x.makeCompressed();
  return x.innerIndexPtr();
}

INDEX* c_eigen_spmat_c_outerindexptr(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  x.makeCompressed();
  return x.outerIndexPtr();
}

c_spmat_c* c_eigen_spmat_c_clone(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_c(x));
}

c_spmat_c* c_eigen_spmat_c_row(c_spmat_c *m, INDEX i)
{
  spmat_c* x = new spmat_c((c_to_eigen(m)).row(i));
  return eigen_to_c(*x);
}

c_spmat_c* c_eigen_spmat_c_col(c_spmat_c *m, INDEX i)
{
  spmat_c* x = new spmat_c((c_to_eigen(m)).col(i));
  return eigen_to_c(*x);
}

c_spmat_c* c_eigen_spmat_c_transpose(c_spmat_c *m)
{
  spmat_c* x = new spmat_c((c_to_eigen(m)).transpose());
  return eigen_to_c(*x);
}

c_spmat_c* c_eigen_spmat_c_adjoint(c_spmat_c *m)
{
  spmat_c* x = new spmat_c((c_to_eigen(m)).adjoint());
  return eigen_to_c(*x);
}

c_spmat_c* c_eigen_spmat_c_diagonal(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_c(x.diagonal().sparseView()));
}

c_spmat_c_elt c_eigen_spmat_c_trace(c_spmat_c *m)
{
  spmat_c_elt a = c_to_eigen(m).diagonal().sparseView().sum();
  return eigen_to_c(a);
}

int c_eigen_spmat_c_is_zero(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  if (x.nonZeros() == 0)
    return 1;

  spmat_c_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k] != spmat_c_zero) {
      b = 0;
      break;
    }
  }
  return b;
}

int c_eigen_spmat_c_is_positive(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  x.makeCompressed();
  if (x.nonZeros() < (x.rows() * x.cols()))
    return 0;

  spmat_c_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k].real() <= 0. || a[k].imag() <= 0.) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_c_is_negative(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  x.makeCompressed();
  if (x.nonZeros() < (x.rows() * x.cols()))
    return 0;

  spmat_c_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k].real() >= 0. || a[k].imag() >= 0.) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_c_is_nonpositive(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  x.makeCompressed();
  spmat_c_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k].real() > 0. || a[k].imag() > 0.) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_c_is_nonnegative(c_spmat_c *m)
{
  spmat_c& x = c_to_eigen(m);
  x.makeCompressed();
  spmat_c_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k].real() < 0. || a[k].imag() < 0.) {
      b = 0;
      break;
    }
  }

  return b;
}

int c_eigen_spmat_c_is_equal(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c x = c_to_eigen(m0) - c_to_eigen(m1);
  x.prune(spmat_c_zero, 0.);
  return (x.nonZeros() == 0);
}

int c_eigen_spmat_c_is_unequal(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c x = c_to_eigen(m0) - c_to_eigen(m1);
  x.prune(spmat_c_zero, 0.);
  return (x.nonZeros() != 0);
}

int c_eigen_spmat_c_is_greater(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_c_is_positive(eigen_to_c(x));
}

int c_eigen_spmat_c_is_smaller(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_c_is_negative(eigen_to_c(x));
}

int c_eigen_spmat_c_equal_or_greater(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_c_is_nonnegative(eigen_to_c(x));
}

int c_eigen_spmat_c_equal_or_smaller(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_c_is_nonpositive(eigen_to_c(x));
}

c_spmat_c* c_eigen_spmat_c_add(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c& x0 = c_to_eigen(m0);
  spmat_c& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_c(x0 + x1));
}

c_spmat_c* c_eigen_spmat_c_sub(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c& x0 = c_to_eigen(m0);
  spmat_c& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_c(x0 - x1));
}

c_spmat_c* c_eigen_spmat_c_mul(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c& x0 = c_to_eigen(m0);
  spmat_c& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_c(x0.cwiseProduct(x1)));
}

c_spmat_c* c_eigen_spmat_c_div(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c& x0 = c_to_eigen(m0);
  spmat_c& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_c(x0.cwiseQuotient(x1)));
}

c_spmat_c* c_eigen_spmat_c_gemm(c_spmat_c *m0, c_spmat_c *m1)
{
  spmat_c& x0 = c_to_eigen(m0);
  spmat_c& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_c(x0 * x1));
}

c_spmat_c* c_eigen_spmat_c_add_scalar(c_spmat_c *m, c_spmat_c_elt a)
{
  spmat_c_elt b = c_to_eigen(a);
  spmat_c* x = new spmat_c(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_c::InnerIterator it(*x,k); it; ++it)
      it.valueRef() += b;
  return eigen_to_c(*x);
}

c_spmat_c* c_eigen_spmat_c_sub_scalar(c_spmat_c *m, c_spmat_c_elt a)
{
  spmat_c_elt b = c_to_eigen(a);
  spmat_c* x = new spmat_c(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_c::InnerIterator it(*x,k); it; ++it)
      it.valueRef() -= b;
  return eigen_to_c(*x);
}

c_spmat_c* c_eigen_spmat_c_mul_scalar(c_spmat_c *m, c_spmat_c_elt a)
{
  spmat_c_elt b = c_to_eigen(a);
  spmat_c& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_c(x * b));
}

c_spmat_c* c_eigen_spmat_c_div_scalar(c_spmat_c *m, c_spmat_c_elt a)
{
  spmat_c_elt b = c_to_eigen(a);
  spmat_c* x = new spmat_c(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_c::InnerIterator it(*x,k); it; ++it)
      it.valueRef() /= b;
  return eigen_to_c(*x);
}

c_spmat_c_elt c_eigen_spmat_c_sum(c_spmat_c *m)
{
  spmat_c_elt a = (c_to_eigen(m)).sum();
  return eigen_to_c(a);
}
/*
spmat_c_elt c_eigen_spmat_c_min(c_spmat_c *m)
{
  spmat_c_elt a = std::numeric_limits<spmat_c_elt>::infinity();
  spmat_c& x = c_to_eigen(m);
  for (INDEX k = 0; k < x.outerSize(); ++k)
    for (spmat_c::InnerIterator it(x,k); it; ++it)
    {
      if (it.value() < a)
        a = it.value();
    }
  if ((x.nonZeros() < (x.rows() * x.cols())) && (a > 0))
    a = 0;
  return a;
}

spmat_c_elt c_eigen_spmat_c_max(c_spmat_c *m)
{
  spmat_c_elt a = -std::numeric_limits<spmat_c_elt>::infinity();
  spmat_c& x = c_to_eigen(m);
  for (INDEX k = 0; k < x.outerSize(); ++k)
    for (spmat_c::InnerIterator it(x,k); it; ++it)
    {
      if (it.value() > a)
        a = it.value();
    }
  if ((x.nonZeros() < (x.rows() * x.cols())) && (a < 0))
    a = 0;
  return a;
}

c_spmat_c* c_eigen_spmat_c_abs(c_spmat_c *m)
{
  spmat_c* x = new spmat_c((c_to_eigen(m)).cwiseAbs());
  return eigen_to_c(*x);
}
*/
c_spmat_c* c_eigen_spmat_c_neg(c_spmat_c *m)
{
  spmat_c* x = new spmat_c(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_c::InnerIterator it(*x,k); it; ++it)
      it.valueRef() = -it.value();
  return eigen_to_c(*x);
}

c_spmat_c* c_eigen_spmat_c_sqrt(c_spmat_c *m)
{
  spmat_c* x = new spmat_c((c_to_eigen(m)).cwiseSqrt());
  return eigen_to_c(*x);
}

void c_eigen_spmat_c_print(c_spmat_c *m)
{
  std::cout << c_to_eigen(m) << std::endl;
}

c_spmat_c* c_eigen_spmat_c_sparse_LU(c_spmat_c *c_coefficients, c_spmat_c *c_observations)
{
  SparseSolver<SparseLU<col_major_spmat_c>,
               spmat_c,
               spmat_c_elt,
               c_spmat_c> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_c* c_eigen_spmat_c_sparse_QR(c_spmat_c *c_coefficients, c_spmat_c *c_observations)
{
  SparseSolver<SparseQR<col_major_spmat_c, COLAMDOrdering<int> >,
               spmat_c,
               spmat_c_elt,
               c_spmat_c> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_c* c_eigen_spmat_c_simplicial_LLT(c_spmat_c *c_coefficients,
                                          c_spmat_c *c_observations)
{
  SparseSolver<SimplicialLLT<col_major_spmat_c>,
               spmat_c,
               spmat_c_elt,
               c_spmat_c> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_c* c_eigen_spmat_c_simplicial_LDLT(c_spmat_c *c_coefficients,
                                           c_spmat_c *c_observations)
{
  SparseSolver<SimplicialLDLT<col_major_spmat_c>,
               spmat_c,
               spmat_c_elt,
               c_spmat_c> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_c* c_eigen_spmat_c_conjugate_gradient(c_spmat_c *c_coefficients,
                                              c_spmat_c *c_observations)
{
  SparseSolver<ConjugateGradient<col_major_spmat_c>,
               spmat_c,
               spmat_c_elt,
               c_spmat_c> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_c* c_eigen_spmat_c_least_squares_conjugate_gradient(c_spmat_c *c_coefficients,
                                                            c_spmat_c *c_observations)
{
  SparseSolver<LeastSquaresConjugateGradient<col_major_spmat_c>,
               spmat_c,
               spmat_c_elt,
               c_spmat_c> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_c* c_eigen_spmat_c_BiCGSTAB(c_spmat_c *c_coefficients,
                                              c_spmat_c *c_observations)
{
  SparseSolver<BiCGSTAB<col_major_spmat_c>,
               spmat_c,
               spmat_c_elt,
               c_spmat_c> ss(c_coefficients, c_observations);
  return ss.solve();
}
