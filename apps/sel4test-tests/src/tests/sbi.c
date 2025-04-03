/*
 * Copyright 2017, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <autoconf.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sel4/sel4.h>
#include <sel4utils/arch/util.h>

#include <vka/object.h>
#include <vka/capops.h>

#include "../test.h"
#include "../helpers.h"
#include "sel4/simple_types.h"

#ifdef CONFIG_ALLOW_SBI_CALLS

static int test_sbi_calls(env_t env)
{
    seL4_RISCV_SBIContext sbi_args;
    seL4_RISCV_SBIRet sbi_ret;
    int error;

    seL4_CPtr sbi_cap = env->sbi;
    // seL4_CPtr badged_sbi_cap = get_free_slot(env);

    // error = cnode_mint(env, sbi_cap, badged_sbi_cap, seL4_AllRights, 0);
    test_error_eq(error, seL4_NoError);

    /* Set function and arguments */
    sbi_args.a0 = 0;
    sbi_args.a1 = 0;
    sbi_args.a2 = 0;
    sbi_args.a3 = 0;
    sbi_args.a4 = 0;
    sbi_args.a5 = 0;
    sbi_args.a6 = 0;
    sbi_args.a7 = 0x10;

    /* This should succeed */
    error = seL4_RISCV_SBI_Call(sbi_cap, &sbi_args, &sbi_ret);
    test_error_eq(error, seL4_NoError);

    printf("finished SBI call to get SBI spec version\n");
    printf("        error: %d\n", sbi_ret.error);
    printf("        value: %d\n", sbi_ret.value);

    return sel4test_get_result();
}
DEFINE_TEST(SBI0001, "Test SBI calls", test_sbi_calls, true)
#endif
