/*
 * Eigen - an OCaml interface to C++ Eigen library
 * Copyright (c) 2016-2020 Liang Wang <liang.wang@cl.cam.ac.uk>
 */

#include "sparse_solver.h"

/******************** pointer conversion  ********************/

typedef SparseMatrix<spmat_z_elt, Eigen::RowMajor, INDEX> spmat_z;
typedef SparseMatrix<spmat_z_elt, Eigen::ColMajor,   int> col_major_spmat_z;


inline spmat_z& c_to_eigen(c_spmat_z* ptr)
{
  return *reinterpret_cast<spmat_z*>(ptr);
}

inline c_spmat_z* eigen_to_c(spmat_z& ref)
{
  return reinterpret_cast<c_spmat_z*>(&ref);
}

inline c_spmat_z_elt eigen_to_c(spmat_z_elt& ref)
{
  return *reinterpret_cast<c_spmat_z_elt*>(&ref);
}

inline spmat_z_elt c_to_eigen(c_spmat_z_elt c)
{
  return spmat_z_elt(c.r, c.i);
}

inline c_spmat_z_elt* eigen_to_c_ptr(spmat_z_elt* ref)
{
  return reinterpret_cast<c_spmat_z_elt*>(ref);
}

/***************** c stubs for c++ functions *****************/

c_spmat_z* c_eigen_spmat_z_new(INDEX size, INDEX rows, INDEX cols)
{
  spmat_z* x = new spmat_z(rows, cols);
  (*x).reserve(size);
  return eigen_to_c(*x);
}

void c_eigen_spmat_z_delete(c_spmat_z *m)
{
  delete &c_to_eigen(m);
}

c_spmat_z* c_eigen_spmat_z_eye(INDEX m)
{
  spmat_z* x = new spmat_z(m, m);
  (*x).setIdentity();
  return eigen_to_c(*x);
}

INDEX c_eigen_spmat_z_rows(c_spmat_z *m)
{
  return c_to_eigen(m).rows();
}

INDEX c_eigen_spmat_z_cols(c_spmat_z *m)
{
  return c_to_eigen(m).cols();
}

INDEX c_eigen_spmat_z_nnz(c_spmat_z *m)
{
  return (c_to_eigen(m)).nonZeros();
}

c_spmat_z_elt c_eigen_spmat_z_get(c_spmat_z *m, INDEX i, INDEX j)
{
  spmat_z_elt a = (c_to_eigen(m)).coeff(i,j);
  return eigen_to_c(a);
}

void c_eigen_spmat_z_set(c_spmat_z *m, INDEX i, INDEX j, c_spmat_z_elt x)
{
  (c_to_eigen(m)).coeffRef(i,j) = c_to_eigen(x);
}

void c_eigen_spmat_z_insert(c_spmat_z *m, INDEX i, INDEX j, c_spmat_z_elt x)
{
  (c_to_eigen(m)).insert(i,j) = c_to_eigen(x);
}

void c_eigen_spmat_z_reset(c_spmat_z *m)
{
  (c_to_eigen(m)).setZero();
}

int c_eigen_spmat_z_is_compressed(c_spmat_z *m)
{
  return (c_to_eigen(m)).isCompressed();
}

void c_eigen_spmat_z_compress(c_spmat_z *m)
{
  (c_to_eigen(m)).makeCompressed();
}

void c_eigen_spmat_z_uncompress(c_spmat_z *m)
{
  (c_to_eigen(m)).uncompress();
}

void c_eigen_spmat_z_reshape(c_spmat_z *m, INDEX rows, INDEX cols)
{
  // FIXME: keep old data
  (c_to_eigen(m)).resize(rows, cols);
}

void c_eigen_spmat_z_prune(c_spmat_z *m, c_spmat_z_elt ref, double eps)
{
  spmat_z_elt a = c_to_eigen(ref);
  (c_to_eigen(m)).prune(a, eps);
}

c_spmat_z_elt* c_eigen_spmat_z_valueptr(c_spmat_z *m, INDEX *l)
{
  spmat_z& x = c_to_eigen(m);
  x.makeCompressed();
  *l = x.data().size();
  return eigen_to_c_ptr(x.valuePtr());
}

INDEX* c_eigen_spmat_z_innerindexptr(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  x.makeCompressed();
  return x.innerIndexPtr();
}

INDEX* c_eigen_spmat_z_outerindexptr(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  x.makeCompressed();
  return x.outerIndexPtr();
}

c_spmat_z* c_eigen_spmat_z_clone(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_z(x));
}

c_spmat_z* c_eigen_spmat_z_row(c_spmat_z *m, INDEX i)
{
  spmat_z* x = new spmat_z((c_to_eigen(m)).row(i));
  return eigen_to_c(*x);
}

c_spmat_z* c_eigen_spmat_z_col(c_spmat_z *m, INDEX i)
{
  spmat_z* x = new spmat_z((c_to_eigen(m)).col(i));
  return eigen_to_c(*x);
}

c_spmat_z* c_eigen_spmat_z_transpose(c_spmat_z *m)
{
  spmat_z* x = new spmat_z((c_to_eigen(m)).transpose());
  return eigen_to_c(*x);
}

c_spmat_z* c_eigen_spmat_z_adjoint(c_spmat_z *m)
{
  spmat_z* x = new spmat_z((c_to_eigen(m)).adjoint());
  return eigen_to_c(*x);
}

c_spmat_z* c_eigen_spmat_z_diagonal(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_z(x.diagonal().sparseView()));
}

c_spmat_z_elt c_eigen_spmat_z_trace(c_spmat_z *m)
{
  spmat_z_elt a = c_to_eigen(m).diagonal().sparseView().sum();
  return eigen_to_c(a);
}

int c_eigen_spmat_z_is_zero(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  if (x.nonZeros() == 0)
    return 1;

  spmat_z_elt* a = x.valuePtr();
  int b = 1;
  for (INDEX k = 0; k < x.data().size(); ++k)
  {
    if (a[k] != spmat_z_zero) {
      b = 0;
      break;
    }
  }
  return b;
}

int c_eigen_spmat_z_is_positive(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  x.makeCompressed();
  if (x.nonZeros() < (x.rows() * x.cols()))
    return 0;

  spmat_z_elt* a = x.valuePtr();
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

int c_eigen_spmat_z_is_negative(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  x.makeCompressed();
  if (x.nonZeros() < (x.rows() * x.cols()))
    return 0;

  spmat_z_elt* a = x.valuePtr();
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

int c_eigen_spmat_z_is_nonpositive(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  x.makeCompressed();
  spmat_z_elt* a = x.valuePtr();
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

int c_eigen_spmat_z_is_nonnegative(c_spmat_z *m)
{
  spmat_z& x = c_to_eigen(m);
  x.makeCompressed();
  spmat_z_elt* a = x.valuePtr();
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

int c_eigen_spmat_z_is_equal(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z x = c_to_eigen(m0) - c_to_eigen(m1);
  x.prune(spmat_z_zero, 0.);
  return (x.nonZeros() == 0);
}

int c_eigen_spmat_z_is_unequal(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z x = c_to_eigen(m0) - c_to_eigen(m1);
  x.prune(spmat_z_zero, 0.);
  return (x.nonZeros() != 0);
}

int c_eigen_spmat_z_is_greater(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_z_is_positive(eigen_to_c(x));
}

int c_eigen_spmat_z_is_smaller(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_z_is_negative(eigen_to_c(x));
}

int c_eigen_spmat_z_equal_or_greater(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_z_is_nonnegative(eigen_to_c(x));
}

int c_eigen_spmat_z_equal_or_smaller(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z x = c_to_eigen(m0) - c_to_eigen(m1);
  return c_eigen_spmat_z_is_nonpositive(eigen_to_c(x));
}

c_spmat_z* c_eigen_spmat_z_add(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z& x0 = c_to_eigen(m0);
  spmat_z& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_z(x0 + x1));
}

c_spmat_z* c_eigen_spmat_z_sub(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z& x0 = c_to_eigen(m0);
  spmat_z& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_z(x0 - x1));
}

c_spmat_z* c_eigen_spmat_z_mul(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z& x0 = c_to_eigen(m0);
  spmat_z& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_z(x0.cwiseProduct(x1)));
}

c_spmat_z* c_eigen_spmat_z_div(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z& x0 = c_to_eigen(m0);
  spmat_z& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_z(x0.cwiseQuotient(x1)));
}

c_spmat_z* c_eigen_spmat_z_gemm(c_spmat_z *m0, c_spmat_z *m1)
{
  spmat_z& x0 = c_to_eigen(m0);
  spmat_z& x1 = c_to_eigen(m1);
  return eigen_to_c(*new spmat_z(x0 * x1));
}

c_spmat_z* c_eigen_spmat_z_add_scalar(c_spmat_z *m, c_spmat_z_elt a)
{
  spmat_z_elt b = c_to_eigen(a);
  spmat_z* x = new spmat_z(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_z::InnerIterator it(*x,k); it; ++it)
      it.valueRef() += b;
  return eigen_to_c(*x);
}

c_spmat_z* c_eigen_spmat_z_sub_scalar(c_spmat_z *m, c_spmat_z_elt a)
{
  spmat_z_elt b = c_to_eigen(a);
  spmat_z* x = new spmat_z(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_z::InnerIterator it(*x,k); it; ++it)
      it.valueRef() -= b;
  return eigen_to_c(*x);
}

c_spmat_z* c_eigen_spmat_z_mul_scalar(c_spmat_z *m, c_spmat_z_elt a)
{
  spmat_z_elt b = c_to_eigen(a);
  spmat_z& x = c_to_eigen(m);
  return eigen_to_c(*new spmat_z(x * b));
}

c_spmat_z* c_eigen_spmat_z_div_scalar(c_spmat_z *m, c_spmat_z_elt a)
{
  spmat_z_elt b = c_to_eigen(a);
  spmat_z* x = new spmat_z(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_z::InnerIterator it(*x,k); it; ++it)
      it.valueRef() /= b;
  return eigen_to_c(*x);
}

c_spmat_z_elt c_eigen_spmat_z_sum(c_spmat_z *m)
{
  spmat_z_elt a = (c_to_eigen(m)).sum();
  return eigen_to_c(a);
}
/*
spmat_z_elt c_eigen_spmat_z_min(c_spmat_z *m)
{
  spmat_z_elt a = std::numeric_limits<spmat_z_elt>::infinity();
  spmat_z& x = c_to_eigen(m);
  for (INDEX k = 0; k < x.outerSize(); ++k)
    for (spmat_z::InnerIterator it(x,k); it; ++it)
    {
      if (it.value() < a)
        a = it.value();
    }
  if ((x.nonZeros() < (x.rows() * x.cols())) && (a > 0))
    a = 0;
  return a;
}

spmat_z_elt c_eigen_spmat_z_max(c_spmat_z *m)
{
  spmat_z_elt a = -std::numeric_limits<spmat_z_elt>::infinity();
  spmat_z& x = c_to_eigen(m);
  for (INDEX k = 0; k < x.outerSize(); ++k)
    for (spmat_z::InnerIterator it(x,k); it; ++it)
    {
      if (it.value() > a)
        a = it.value();
    }
  if ((x.nonZeros() < (x.rows() * x.cols())) && (a < 0))
    a = 0;
  return a;
}

c_spmat_z* c_eigen_spmat_z_abs(c_spmat_z *m)
{
  spmat_z* x = new spmat_z((c_to_eigen(m)).cwiseAbs());
  return eigen_to_c(*x);
}
*/
c_spmat_z* c_eigen_spmat_z_neg(c_spmat_z *m)
{
  spmat_z* x = new spmat_z(c_to_eigen(m));
  for (INDEX k = 0; k < (*x).outerSize(); ++k)
    for (spmat_z::InnerIterator it(*x,k); it; ++it)
      it.valueRef() = -it.value();
  return eigen_to_c(*x);
}

c_spmat_z* c_eigen_spmat_z_sqrt(c_spmat_z *m)
{
  spmat_z* x = new spmat_z((c_to_eigen(m)).cwiseSqrt());
  return eigen_to_c(*x);
}

void c_eigen_spmat_z_print(c_spmat_z *m)
{
  std::cout << c_to_eigen(m) << std::endl;
}

c_spmat_z* c_eigen_spmat_z_sparse_LU(c_spmat_z *c_coefficients, c_spmat_z *c_observations)
{
  SparseSolver<SparseLU<col_major_spmat_z>,
               spmat_z,
               spmat_z_elt,
               c_spmat_z> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_z* c_eigen_spmat_z_sparse_QR(c_spmat_z *c_coefficients, c_spmat_z *c_observations)
{
  SparseSolver<SparseQR<col_major_spmat_z, COLAMDOrdering<int> >,
               spmat_z,
               spmat_z_elt,
               c_spmat_z> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_z* c_eigen_spmat_z_simplicial_LLT(c_spmat_z *c_coefficients,
                                          c_spmat_z *c_observations)
{
  SparseSolver<SimplicialLLT<col_major_spmat_z>,
               spmat_z,
               spmat_z_elt,
               c_spmat_z> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_z* c_eigen_spmat_z_simplicial_LDLT(c_spmat_z *c_coefficients,
                                           c_spmat_z *c_observations)
{
  SparseSolver<SimplicialLDLT<col_major_spmat_z>,
               spmat_z,
               spmat_z_elt,
               c_spmat_z> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_z* c_eigen_spmat_z_conjugate_gradient(c_spmat_z *c_coefficients,
                                              c_spmat_z *c_observations)
{
  SparseSolver<ConjugateGradient<col_major_spmat_z>,
               spmat_z,
               spmat_z_elt,
               c_spmat_z> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_z* c_eigen_spmat_z_least_squares_conjugate_gradient(c_spmat_z *c_coefficients,
                                                            c_spmat_z *c_observations)
{
  SparseSolver<LeastSquaresConjugateGradient<col_major_spmat_z>,
               spmat_z,
               spmat_z_elt,
               c_spmat_z> ss(c_coefficients, c_observations);
  return ss.solve();
}

c_spmat_z* c_eigen_spmat_z_BiCGSTAB(c_spmat_z *c_coefficients,
                                              c_spmat_z *c_observations)
{
  SparseSolver<BiCGSTAB<col_major_spmat_z>,
               spmat_z,
               spmat_z_elt,
               c_spmat_z> ss(c_coefficients, c_observations);
  return ss.solve();
}
