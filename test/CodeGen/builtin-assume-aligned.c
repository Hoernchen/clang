// RUN: %clang_cc1 -triple x86_64-unknown-unknown -emit-llvm -o - %s | FileCheck %s

// CHECK: @test1
int test1(int *a) {
// CHECK: %ptrint = ptrtoint
// CHECK: %offsetptr = sub i64 %ptrint, 0
// CHECK: %maskedptr = and i64 %offsetptr, 31
// CHECK: %maskcond = icmp eq i64 %maskedptr, 0
// CHECK: call void @llvm.invariant(i1 %maskcond)
  a = __builtin_assume_aligned(a, 32, 0ull);
  return a[0];
}

// CHECK: @test2
int test2(int *a) {
// CHECK: %ptrint = ptrtoint
// CHECK: %offsetptr = sub i64 %ptrint, 0
// CHECK: %maskedptr = and i64 %offsetptr, 31
// CHECK: %maskcond = icmp eq i64 %maskedptr, 0
// CHECK: call void @llvm.invariant(i1 %maskcond)
  a = __builtin_assume_aligned(a, 32, 0);
  return a[0];
}

// CHECK: @test3
int test3(int *a) {
// CHECK: %ptrint = ptrtoint
// CHECK: %maskedptr = and i64 %ptrint, 31
// CHECK: %maskcond = icmp eq i64 %maskedptr, 0
// CHECK: call void @llvm.invariant(i1 %maskcond)
  a = __builtin_assume_aligned(a, 32);
  return a[0];
}

// CHECK: @test4
int test4(int *a, int b) {
// CHECK: %ptrint = ptrtoint
// CHECK: %offsetcast = sext i32
// CHECK: %offsetptr = sub i64 %ptrint, %offsetcast
// CHECK: %maskedptr = and i64 %offsetptr, 31
// CHECK: %maskcond = icmp eq i64 %maskedptr, 0
// CHECK: call void @llvm.invariant(i1 %maskcond)
  a = __builtin_assume_aligned(a, 32, b);
  return a[0];
}

