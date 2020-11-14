/*
 * Eigen - an OCaml interface to C++ Eigen library
 * Copyright (c) 2016-2020 Liang Wang <liang.wang@cl.cam.ac.uk>
 */

#ifdef __cplusplus
extern "C"
{
#endif

typedef int64_t INDEX;

#ifdef __cplusplus
  typedef float spmat_s_elt;
  typedef double spmat_d_elt;
  typedef std::complex<float> spmat_c_elt;
  typedef std::complex<double> spmat_z_elt;
  typedef struct { float r, i; } c_spmat_c_elt;
  typedef struct { double r, i; } c_spmat_z_elt;
  const spmat_s_elt spmat_s_zero = 0.;
  const spmat_d_elt spmat_d_zero = 0.;
  const spmat_c_elt spmat_c_zero = 0.;
  const spmat_z_elt spmat_z_zero = 0.;
#else
  typedef float spmat_s_elt;
  typedef double spmat_d_elt;
  typedef float _Complex c_spmat_c_elt;
  typedef double _Complex c_spmat_z_elt;
#endif


  /**************************** SparseMatrix_S ****************************/

  struct c_spmat_s {};

  struct c_spmat_s* c_eigen_spmat_s_new(INDEX size, INDEX rows, INDEX cols);
  void c_eigen_spmat_s_delete(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_eye(INDEX m);
  INDEX c_eigen_spmat_s_rows(struct c_spmat_s *m);
  INDEX c_eigen_spmat_s_cols(struct c_spmat_s *m);
  INDEX c_eigen_spmat_s_nnz(struct c_spmat_s *m);
  float c_eigen_spmat_s_get(struct c_spmat_s *m, INDEX i, INDEX j);
  void c_eigen_spmat_s_set(struct c_spmat_s *m, INDEX i, INDEX j, float x);
  void c_eigen_spmat_s_insert(struct c_spmat_s *m, INDEX i, INDEX j, float x);
  void c_eigen_spmat_s_reset(struct c_spmat_s *m);
  int c_eigen_spmat_s_is_compressed(struct c_spmat_s *m);
  void c_eigen_spmat_s_compress(struct c_spmat_s *m);
  void c_eigen_spmat_s_uncompress(struct c_spmat_s *m);
  void c_eigen_spmat_s_reshape(struct c_spmat_s *m, INDEX rows, INDEX cols);
  void c_eigen_spmat_s_prune(struct c_spmat_s *m, float ref, float eps);
  float* c_eigen_spmat_s_valueptr(struct c_spmat_s *m, INDEX *l);
  INDEX* c_eigen_spmat_s_innerindexptr(struct c_spmat_s *m);
  INDEX* c_eigen_spmat_s_outerindexptr(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_clone(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_row(struct c_spmat_s *m, INDEX i);
  struct c_spmat_s* c_eigen_spmat_s_col(struct c_spmat_s *m, INDEX i);
  struct c_spmat_s* c_eigen_spmat_s_transpose(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_adjoint(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_diagonal(struct c_spmat_s *m);
  float c_eigen_spmat_s_trace(struct c_spmat_s *m);
  int c_eigen_spmat_s_is_zero(struct c_spmat_s *m);
  int c_eigen_spmat_s_is_positive(struct c_spmat_s *m);
  int c_eigen_spmat_s_is_negative(struct c_spmat_s *m);
  int c_eigen_spmat_s_is_nonpositive(struct c_spmat_s *m);
  int c_eigen_spmat_s_is_nonnegative(struct c_spmat_s *m);
  int c_eigen_spmat_s_is_equal(struct c_spmat_s *m0, struct c_spmat_s *m1);
  int c_eigen_spmat_s_is_unequal(struct c_spmat_s *m0, struct c_spmat_s *m1);
  int c_eigen_spmat_s_is_greater(struct c_spmat_s *m0, struct c_spmat_s *m1);
  int c_eigen_spmat_s_is_smaller(struct c_spmat_s *m0, struct c_spmat_s *m1);
  int c_eigen_spmat_s_equal_or_greater(struct c_spmat_s *m0, struct c_spmat_s *m1);
  int c_eigen_spmat_s_equal_or_smaller(struct c_spmat_s *m0, struct c_spmat_s *m1);
  struct c_spmat_s* c_eigen_spmat_s_add(struct c_spmat_s *m0, struct c_spmat_s *m1);
  struct c_spmat_s* c_eigen_spmat_s_sub(struct c_spmat_s *m0, struct c_spmat_s *m1);
  struct c_spmat_s* c_eigen_spmat_s_mul(struct c_spmat_s *m0, struct c_spmat_s *m1);
  struct c_spmat_s* c_eigen_spmat_s_div(struct c_spmat_s *m0, struct c_spmat_s *m1);
  struct c_spmat_s* c_eigen_spmat_s_gemm(struct c_spmat_s *m0, struct c_spmat_s *m1);
  struct c_spmat_s* c_eigen_spmat_s_add_scalar(struct c_spmat_s *m, float a);
  struct c_spmat_s* c_eigen_spmat_s_sub_scalar(struct c_spmat_s *m, float a);
  struct c_spmat_s* c_eigen_spmat_s_mul_scalar(struct c_spmat_s *m, float a);
  struct c_spmat_s* c_eigen_spmat_s_div_scalar(struct c_spmat_s *m, float a);
  struct c_spmat_s* c_eigen_spmat_s_min2(struct c_spmat_s *m0, struct c_spmat_s *m1);
  struct c_spmat_s* c_eigen_spmat_s_max2(struct c_spmat_s *m0, struct c_spmat_s *m1);
  float c_eigen_spmat_s_sum(struct c_spmat_s *m);
  float c_eigen_spmat_s_min(struct c_spmat_s *m);
  float c_eigen_spmat_s_max(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_abs(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_neg(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_sqrt(struct c_spmat_s *m);
  void c_eigen_spmat_s_print(struct c_spmat_s *m);
  struct c_spmat_s* c_eigen_spmat_s_sparse_LU(struct c_spmat_s *a, struct c_spmat_s *b);
  struct c_spmat_s* c_eigen_spmat_s_sparse_QR(struct c_spmat_s *a, struct c_spmat_s *b);
  struct c_spmat_s* c_eigen_spmat_s_simplicial_LLT(struct c_spmat_s *a, struct c_spmat_s *b);
  struct c_spmat_s* c_eigen_spmat_s_simplicial_LDLT(struct c_spmat_s *a, struct c_spmat_s *b);
  struct c_spmat_s* c_eigen_spmat_s_conjugate_gradient(struct c_spmat_s *a, struct c_spmat_s *b);
  struct c_spmat_s* c_eigen_spmat_s_least_squares_conjugate_gradient(struct c_spmat_s *a, struct c_spmat_s *b);
  struct c_spmat_s* c_eigen_spmat_s_BiCGSTAB(struct c_spmat_s *a, struct c_spmat_s *b);


  /**************************** SparseMatrix_D ****************************/

  struct c_spmat_d {};

  struct c_spmat_d* c_eigen_spmat_d_new(INDEX size, INDEX rows, INDEX cols);
  void c_eigen_spmat_d_delete(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_eye(INDEX m);
  INDEX c_eigen_spmat_d_rows(struct c_spmat_d *m);
  INDEX c_eigen_spmat_d_cols(struct c_spmat_d *m);
  INDEX c_eigen_spmat_d_nnz(struct c_spmat_d *m);
  double c_eigen_spmat_d_get(struct c_spmat_d *m, INDEX i, INDEX j);
  void c_eigen_spmat_d_set(struct c_spmat_d *m, INDEX i, INDEX j, double x);
  void c_eigen_spmat_d_insert(struct c_spmat_d *m, INDEX i, INDEX j, double x);
  void c_eigen_spmat_d_reset(struct c_spmat_d *m);
  int c_eigen_spmat_d_is_compressed(struct c_spmat_d *m);
  void c_eigen_spmat_d_compress(struct c_spmat_d *m);
  void c_eigen_spmat_d_uncompress(struct c_spmat_d *m);
  void c_eigen_spmat_d_reshape(struct c_spmat_d *m, INDEX rows, INDEX cols);
  void c_eigen_spmat_d_prune(struct c_spmat_d *m, double ref, double eps);
  double* c_eigen_spmat_d_valueptr(struct c_spmat_d *m, INDEX *l);
  INDEX* c_eigen_spmat_d_innerindexptr(struct c_spmat_d *m);
  INDEX* c_eigen_spmat_d_outerindexptr(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_clone(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_row(struct c_spmat_d *m, INDEX i);
  struct c_spmat_d* c_eigen_spmat_d_col(struct c_spmat_d *m, INDEX i);
  struct c_spmat_d* c_eigen_spmat_d_transpose(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_adjoint(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_diagonal(struct c_spmat_d *m);
  double c_eigen_spmat_d_trace(struct c_spmat_d *m);
  int c_eigen_spmat_d_is_zero(struct c_spmat_d *m);
  int c_eigen_spmat_d_is_positive(struct c_spmat_d *m);
  int c_eigen_spmat_d_is_negative(struct c_spmat_d *m);
  int c_eigen_spmat_d_is_nonpositive(struct c_spmat_d *m);
  int c_eigen_spmat_d_is_nonnegative(struct c_spmat_d *m);
  int c_eigen_spmat_d_is_equal(struct c_spmat_d *m0, struct c_spmat_d *m1);
  int c_eigen_spmat_d_is_unequal(struct c_spmat_d *m0, struct c_spmat_d *m1);
  int c_eigen_spmat_d_is_greater(struct c_spmat_d *m0, struct c_spmat_d *m1);
  int c_eigen_spmat_d_is_smaller(struct c_spmat_d *m0, struct c_spmat_d *m1);
  int c_eigen_spmat_d_equal_or_greater(struct c_spmat_d *m0, struct c_spmat_d *m1);
  int c_eigen_spmat_d_equal_or_smaller(struct c_spmat_d *m0, struct c_spmat_d *m1);
  struct c_spmat_d* c_eigen_spmat_d_add(struct c_spmat_d *m0, struct c_spmat_d *m1);
  struct c_spmat_d* c_eigen_spmat_d_sub(struct c_spmat_d *m0, struct c_spmat_d *m1);
  struct c_spmat_d* c_eigen_spmat_d_mul(struct c_spmat_d *m0, struct c_spmat_d *m1);
  struct c_spmat_d* c_eigen_spmat_d_div(struct c_spmat_d *m0, struct c_spmat_d *m1);
  struct c_spmat_d* c_eigen_spmat_d_gemm(struct c_spmat_d *m0, struct c_spmat_d *m1);
  struct c_spmat_d* c_eigen_spmat_d_add_scalar(struct c_spmat_d *m, double a);
  struct c_spmat_d* c_eigen_spmat_d_sub_scalar(struct c_spmat_d *m, double a);
  struct c_spmat_d* c_eigen_spmat_d_mul_scalar(struct c_spmat_d *m, double a);
  struct c_spmat_d* c_eigen_spmat_d_div_scalar(struct c_spmat_d *m, double a);
  struct c_spmat_d* c_eigen_spmat_d_min2(struct c_spmat_d *m0, struct c_spmat_d *m1);
  struct c_spmat_d* c_eigen_spmat_d_max2(struct c_spmat_d *m0, struct c_spmat_d *m1);
  double c_eigen_spmat_d_sum(struct c_spmat_d *m);
  double c_eigen_spmat_d_min(struct c_spmat_d *m);
  double c_eigen_spmat_d_max(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_abs(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_neg(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_sqrt(struct c_spmat_d *m);
  void c_eigen_spmat_d_print(struct c_spmat_d *m);
  struct c_spmat_d* c_eigen_spmat_d_sparse_LU(struct c_spmat_d *a, struct c_spmat_d *b);
  struct c_spmat_d* c_eigen_spmat_d_sparse_QR(struct c_spmat_d *a, struct c_spmat_d *b);
  struct c_spmat_d* c_eigen_spmat_d_simplicial_LLT(struct c_spmat_d *a, struct c_spmat_d *b);
  struct c_spmat_d* c_eigen_spmat_d_simplicial_LDLT(struct c_spmat_d *a, struct c_spmat_d *b);
  struct c_spmat_d* c_eigen_spmat_d_conjugate_gradient(struct c_spmat_d *a, struct c_spmat_d *b);
  struct c_spmat_d* c_eigen_spmat_d_least_squares_conjugate_gradient(struct c_spmat_d *a, struct c_spmat_d *b);
  struct c_spmat_d* c_eigen_spmat_d_BiCGSTAB(struct c_spmat_d *a, struct c_spmat_d *b);


  /**************************** SparseMatrix_C ****************************/

  struct c_spmat_c {};

  struct c_spmat_c* c_eigen_spmat_c_new(INDEX size, INDEX rows, INDEX cols);
  void c_eigen_spmat_c_delete(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_eye(INDEX m);
  INDEX c_eigen_spmat_c_rows(struct c_spmat_c *m);
  INDEX c_eigen_spmat_c_cols(struct c_spmat_c *m);
  INDEX c_eigen_spmat_c_nnz(struct c_spmat_c *m);
  c_spmat_c_elt c_eigen_spmat_c_get(struct c_spmat_c *m, INDEX i, INDEX j);
  void c_eigen_spmat_c_set(struct c_spmat_c *m, INDEX i, INDEX j, c_spmat_c_elt x);
  void c_eigen_spmat_c_insert(struct c_spmat_c *m, INDEX i, INDEX j, c_spmat_c_elt x);
  void c_eigen_spmat_c_reset(struct c_spmat_c *m);
  int c_eigen_spmat_c_is_compressed(struct c_spmat_c *m);
  void c_eigen_spmat_c_compress(struct c_spmat_c *m);
  void c_eigen_spmat_c_uncompress(struct c_spmat_c *m);
  void c_eigen_spmat_c_reshape(struct c_spmat_c *m, INDEX rows, INDEX cols);
  void c_eigen_spmat_c_prune(struct c_spmat_c *m, c_spmat_c_elt ref, float eps);
  c_spmat_c_elt* c_eigen_spmat_c_valueptr(struct c_spmat_c *m, INDEX *l);
  INDEX* c_eigen_spmat_c_innerindexptr(struct c_spmat_c *m);
  INDEX* c_eigen_spmat_c_outerindexptr(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_clone(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_row(struct c_spmat_c *m, INDEX i);
  struct c_spmat_c* c_eigen_spmat_c_col(struct c_spmat_c *m, INDEX i);
  struct c_spmat_c* c_eigen_spmat_c_transpose(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_adjoint(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_diagonal(struct c_spmat_c *m);
  c_spmat_c_elt c_eigen_spmat_c_trace(struct c_spmat_c *m);
  int c_eigen_spmat_c_is_zero(struct c_spmat_c *m);
  int c_eigen_spmat_c_is_positive(struct c_spmat_c *m);
  int c_eigen_spmat_c_is_negative(struct c_spmat_c *m);
  int c_eigen_spmat_c_is_nonpositive(struct c_spmat_c *m);
  int c_eigen_spmat_c_is_nonnegative(struct c_spmat_c *m);
  int c_eigen_spmat_c_is_equal(struct c_spmat_c *m0, struct c_spmat_c *m1);
  int c_eigen_spmat_c_is_unequal(struct c_spmat_c *m0, struct c_spmat_c *m1);
  int c_eigen_spmat_c_is_greater(struct c_spmat_c *m0, struct c_spmat_c *m1);
  int c_eigen_spmat_c_is_smaller(struct c_spmat_c *m0, struct c_spmat_c *m1);
  int c_eigen_spmat_c_equal_or_greater(struct c_spmat_c *m0, struct c_spmat_c *m1);
  int c_eigen_spmat_c_equal_or_smaller(struct c_spmat_c *m0, struct c_spmat_c *m1);
  struct c_spmat_c* c_eigen_spmat_c_add(struct c_spmat_c *m0, struct c_spmat_c *m1);
  struct c_spmat_c* c_eigen_spmat_c_sub(struct c_spmat_c *m0, struct c_spmat_c *m1);
  struct c_spmat_c* c_eigen_spmat_c_mul(struct c_spmat_c *m0, struct c_spmat_c *m1);
  struct c_spmat_c* c_eigen_spmat_c_div(struct c_spmat_c *m0, struct c_spmat_c *m1);
  struct c_spmat_c* c_eigen_spmat_c_gemm(struct c_spmat_c *m0, struct c_spmat_c *m1);
  struct c_spmat_c* c_eigen_spmat_c_add_scalar(struct c_spmat_c *m, c_spmat_c_elt a);
  struct c_spmat_c* c_eigen_spmat_c_sub_scalar(struct c_spmat_c *m, c_spmat_c_elt a);
  struct c_spmat_c* c_eigen_spmat_c_mul_scalar(struct c_spmat_c *m, c_spmat_c_elt a);
  struct c_spmat_c* c_eigen_spmat_c_div_scalar(struct c_spmat_c *m, c_spmat_c_elt a);
  c_spmat_c_elt c_eigen_spmat_c_sum(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_neg(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_sqrt(struct c_spmat_c *m);
  void c_eigen_spmat_c_print(struct c_spmat_c *m);
  struct c_spmat_c* c_eigen_spmat_c_sparse_LU(struct c_spmat_c *a, struct c_spmat_c *b);
  struct c_spmat_c* c_eigen_spmat_c_sparse_QR(struct c_spmat_c *a, struct c_spmat_c *b);
  struct c_spmat_c* c_eigen_spmat_c_simplicial_LLT(struct c_spmat_c *a, struct c_spmat_c *b);
  struct c_spmat_c* c_eigen_spmat_c_simplicial_LDLT(struct c_spmat_c *a, struct c_spmat_c *b);
  struct c_spmat_c* c_eigen_spmat_c_conjugate_gradient(struct c_spmat_c *a, struct c_spmat_c *b);
  struct c_spmat_c* c_eigen_spmat_c_least_squares_conjugate_gradient(struct c_spmat_c *a, struct c_spmat_c *b);
  struct c_spmat_c* c_eigen_spmat_c_BiCGSTAB(struct c_spmat_c *a, struct c_spmat_c *b);


  /**************************** SparseMatrix_Z ****************************/

  struct c_spmat_z {};

  struct c_spmat_z* c_eigen_spmat_z_new(INDEX size, INDEX rows, INDEX cols);
  void c_eigen_spmat_z_delete(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_eye(INDEX m);
  INDEX c_eigen_spmat_z_rows(struct c_spmat_z *m);
  INDEX c_eigen_spmat_z_cols(struct c_spmat_z *m);
  INDEX c_eigen_spmat_z_nnz(struct c_spmat_z *m);
  c_spmat_z_elt c_eigen_spmat_z_get(struct c_spmat_z *m, INDEX i, INDEX j);
  void c_eigen_spmat_z_set(struct c_spmat_z *m, INDEX i, INDEX j, c_spmat_z_elt x);
  void c_eigen_spmat_z_insert(struct c_spmat_z *m, INDEX i, INDEX j, c_spmat_z_elt x);
  void c_eigen_spmat_z_reset(struct c_spmat_z *m);
  int c_eigen_spmat_z_is_compressed(struct c_spmat_z *m);
  void c_eigen_spmat_z_compress(struct c_spmat_z *m);
  void c_eigen_spmat_z_uncompress(struct c_spmat_z *m);
  void c_eigen_spmat_z_reshape(struct c_spmat_z *m, INDEX rows, INDEX cols);
  void c_eigen_spmat_z_prune(struct c_spmat_z *m, c_spmat_z_elt ref, double eps);
  c_spmat_z_elt* c_eigen_spmat_z_valueptr(struct c_spmat_z *m, INDEX *l);
  INDEX* c_eigen_spmat_z_innerindexptr(struct c_spmat_z *m);
  INDEX* c_eigen_spmat_z_outerindexptr(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_clone(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_row(struct c_spmat_z *m, INDEX i);
  struct c_spmat_z* c_eigen_spmat_z_col(struct c_spmat_z *m, INDEX i);
  struct c_spmat_z* c_eigen_spmat_z_transpose(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_adjoint(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_diagonal(struct c_spmat_z *m);
  c_spmat_z_elt c_eigen_spmat_z_trace(struct c_spmat_z *m);
  int c_eigen_spmat_z_is_zero(struct c_spmat_z *m);
  int c_eigen_spmat_z_is_positive(struct c_spmat_z *m);
  int c_eigen_spmat_z_is_negative(struct c_spmat_z *m);
  int c_eigen_spmat_z_is_nonpositive(struct c_spmat_z *m);
  int c_eigen_spmat_z_is_nonnegative(struct c_spmat_z *m);
  int c_eigen_spmat_z_is_equal(struct c_spmat_z *m0, struct c_spmat_z *m1);
  int c_eigen_spmat_z_is_unequal(struct c_spmat_z *m0, struct c_spmat_z *m1);
  int c_eigen_spmat_z_is_greater(struct c_spmat_z *m0, struct c_spmat_z *m1);
  int c_eigen_spmat_z_is_smaller(struct c_spmat_z *m0, struct c_spmat_z *m1);
  int c_eigen_spmat_z_equal_or_greater(struct c_spmat_z *m0, struct c_spmat_z *m1);
  int c_eigen_spmat_z_equal_or_smaller(struct c_spmat_z *m0, struct c_spmat_z *m1);
  struct c_spmat_z* c_eigen_spmat_z_add(struct c_spmat_z *m0, struct c_spmat_z *m1);
  struct c_spmat_z* c_eigen_spmat_z_sub(struct c_spmat_z *m0, struct c_spmat_z *m1);
  struct c_spmat_z* c_eigen_spmat_z_mul(struct c_spmat_z *m0, struct c_spmat_z *m1);
  struct c_spmat_z* c_eigen_spmat_z_div(struct c_spmat_z *m0, struct c_spmat_z *m1);
  struct c_spmat_z* c_eigen_spmat_z_gemm(struct c_spmat_z *m0, struct c_spmat_z *m1);
  struct c_spmat_z* c_eigen_spmat_z_add_scalar(struct c_spmat_z *m, c_spmat_z_elt a);
  struct c_spmat_z* c_eigen_spmat_z_sub_scalar(struct c_spmat_z *m, c_spmat_z_elt a);
  struct c_spmat_z* c_eigen_spmat_z_mul_scalar(struct c_spmat_z *m, c_spmat_z_elt a);
  struct c_spmat_z* c_eigen_spmat_z_div_scalar(struct c_spmat_z *m, c_spmat_z_elt a);
  c_spmat_z_elt c_eigen_spmat_z_sum(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_neg(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_sqrt(struct c_spmat_z *m);
  void c_eigen_spmat_z_print(struct c_spmat_z *m);
  struct c_spmat_z* c_eigen_spmat_z_sparse_LU(struct c_spmat_z *a, struct c_spmat_z *b);
  struct c_spmat_z* c_eigen_spmat_z_sparse_QR(struct c_spmat_z *a, struct c_spmat_z *b);
  struct c_spmat_z* c_eigen_spmat_z_simplicial_LLT(struct c_spmat_z *a, struct c_spmat_z *b);
  struct c_spmat_z* c_eigen_spmat_z_simplicial_LDLT(struct c_spmat_z *a, struct c_spmat_z *b);
  struct c_spmat_z* c_eigen_spmat_z_conjugate_gradient(struct c_spmat_z *a, struct c_spmat_z *b);
  struct c_spmat_z* c_eigen_spmat_z_least_squares_conjugate_gradient(struct c_spmat_z *a, struct c_spmat_z *b);
  struct c_spmat_z* c_eigen_spmat_z_BiCGSTAB(struct c_spmat_z *a, struct c_spmat_z *b);


#ifdef __cplusplus
} // end extern "C"
#endif
