(*
 * Eigen - an OCaml interface to C++ Eigen library
 * Copyright (c) 2016-2020 Liang Wang <liang.wang@cl.cam.ac.uk>
 *)

open Ctypes
open Eigen_types.SPMAT_Z

let create ?(reserve=0.01) m n =
  let s = max 1024 (float_of_int (m * n) *. reserve |> int_of_float) in
  let x = ml_eigen_new (Int64.of_int s) (Int64.of_int m) (Int64.of_int n) in
  Gc.finalise ml_eigen_delete x;
  x

let delete x = ml_eigen_delete x

let eye m = ml_eigen_eye (Int64.of_int m)

let rows x = ml_eigen_rows x |> Int64.to_int

let cols x = ml_eigen_cols x |> Int64.to_int

let nnz x = ml_eigen_nnz x |> Int64.to_int

let get x i j = ml_eigen_get x (Int64.of_int i) (Int64.of_int j)

let set x i j a = ml_eigen_set x (Int64.of_int i) (Int64.of_int j) a

let insert x i j a = ml_eigen_insert x (Int64.of_int i) (Int64.of_int j) a

let reset x = ml_eigen_reset x

let is_compressed x = ml_eigen_is_compressed x = 1

let compress x = ml_eigen_compress x

let uncompress x = ml_eigen_uncompress x

let reshape x m n = ml_eigen_reshape x (Int64.of_int m) (Int64.of_int n)

let prune x r e = ml_eigen_prune x r e

let valueptr x =
  let l = allocate int64_t (Signed.Int64.of_int 0) in
  let raw = ml_eigen_valueptr x l in
  let l = Signed.Int64.to_int !@l in
  bigarray_of_ptr array1 l Bigarray.complex64 raw

let innerindexptr x =
  let raw = ml_eigen_innerindexptr x in
  bigarray_of_ptr array1 (nnz x) Bigarray.int64 raw

let outerindexptr x =
  let raw = ml_eigen_outerindexptr x in
  bigarray_of_ptr array1 (rows x + 1) Bigarray.int64 raw

let clone x = ml_eigen_clone x

let row x i = ml_eigen_row x (Int64.of_int i)

let col x i = ml_eigen_col x (Int64.of_int i)

let transpose x = ml_eigen_transpose x

let adjoint x = ml_eigen_adjoint x

let diagonal x = ml_eigen_diagonal x

let trace x = ml_eigen_trace x

let is_zero x = ml_eigen_is_zero x = 1

let is_positive x = ml_eigen_is_positive x = 1

let is_negative x = ml_eigen_is_negative x = 1

let is_nonpositive x = ml_eigen_is_nonpositive x = 1

let is_nonnegative x = ml_eigen_is_nonnegative x = 1

let is_equal x y = ml_eigen_is_equal x y = 1

let is_unequal x y = ml_eigen_is_unequal x y = 1

let is_greater x y = ml_eigen_is_greater x y = 1

let is_smaller x y = ml_eigen_is_smaller x y = 1

let equal_or_greater x y = ml_eigen_equal_or_greater x y = 1

let equal_or_smaller x y = ml_eigen_equal_or_smaller x y = 1

let add x y = ml_eigen_add x y

let sub x y = ml_eigen_sub x y

let mul x y = ml_eigen_mul x y

let div x y = ml_eigen_div x y

let gemm x y = ml_eigen_gemm x y

let add_scalar x a = ml_eigen_add_scalar x a

let sub_scalar x a = ml_eigen_sub_scalar x a

let mul_scalar x a = ml_eigen_mul_scalar x a

let div_scalar x a = ml_eigen_div_scalar x a

let sum x = ml_eigen_sum x

let neg x = ml_eigen_neg x

let sqrt x = ml_eigen_sqrt x

let print x = ml_eigen_print x

let sparse_LU a b = ml_eigen_sparse_LU a b

let sparse_QR a b = ml_eigen_sparse_QR a b

let simplicial_LLT a b = ml_eigen_simplicial_LLT a b

let simplicial_LDLT a b = ml_eigen_simplicial_LDLT a b

let conjugate_gradient a b = ml_eigen_conjugate_gradient a b

let least_squares_conjugate_gradient a b = ml_eigen_least_squares_conjugate_gradient a b

let biCGSTAB a b = ml_eigen_BiCGSTAB a b
