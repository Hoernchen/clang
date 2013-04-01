// RUN: %clang_cc1 -triple x86_64-unknown-unknown -emit-llvm -o - %s | FileCheck %s

// CHECK: @test1
int test1(int *a) {
// CHECK: %0 = load i32** %a.addr, align 8
// CHECK: %cmp = icmp ne i32* %0, null
// CHECK: call void @llvm.invariant(i1 %cmp)
  __builtin_assume(a != 0);
  return a[0];
}

