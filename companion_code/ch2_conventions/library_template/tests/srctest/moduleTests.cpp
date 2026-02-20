/**
 * @file moduleTests.cpp
 * @brief Unit tests for the Module — follows UT-09 CppUTest Template.
 *
 * Conventions demonstrated:
 *   UT-04 (Test Independence)
 *   UT-05 (Arrange, Act, Assert)
 *   UT-06 (Test Naming: Function_Condition_ExpectedResult)
 *   UT-07 (Living Documentation / usage_example)
 *   UT-09 (CppUTest Template)
 */

#include "CppUTest/TestHarness.h"

extern "C" {
    #include "module.h"
}

/* Optional module-specific helpers (see UT-08)
 * #include "helpers/ModuleTestHelper.h"
 */

/* ------------------------------------------------------------------
 * TEST_GROUP: Module_Usage
 * Happy-path tests that read like a usage guide (UT-07).
 * ------------------------------------------------------------------ */
TEST_GROUP(Module_Usage)
{
    module_t mod;
    hModule_t self = &mod;

    void setup() override
    {
        /* Each test starts clean (UT-04) */
        memset(&mod, 0, sizeof(mod));
    }

    void teardown() override
    {
        module_deinit(self);
    }
};

/* UT-07: This test demonstrates the intended call sequence. */
TEST(Module_Usage, usage_example)
{
    /* 1. Configure */
    module_config_t cfg = {};
    cfg.id = 42;

    /* 2. Initialize */
    CHECK_EQUAL(MODULE_STATUS_OK, module_init(self, &cfg));

    /* 3. Use */
    CHECK_TRUE(module_isActive(self));

    /* 4. Periodic work */
    module_task(self);

    /* 5. Cleanup (handled in teardown) */
}

/* ------------------------------------------------------------------
 * TEST_GROUP: Module_Errors
 * Edge cases and error handling (UT-06 naming).
 * ------------------------------------------------------------------ */
TEST_GROUP(Module_Errors)
{
    module_t mod;
    hModule_t self = &mod;

    void setup() override
    {
        memset(&mod, 0, sizeof(mod));
    }

    void teardown() override
    {
        /* Nothing to tear down for error cases */
    }
};

/* UT-05: Arrange / Act / Assert pattern */
TEST(Module_Errors, Init_NullSelf_ReturnsInvalidArg)              /* UT-06 */
{
    /* Arrange */
    module_config_t cfg = {};
    cfg.id = 1;
    module_status_t status;

    /* Act */
    status = module_init(NULL, &cfg);

    /* Assert */
    CHECK_EQUAL(MODULE_STATUS_INVALID_ARG, status);
}

TEST(Module_Errors, Init_NullConfig_ReturnsInvalidArg)
{
    module_status_t status = module_init(self, NULL);

    CHECK_EQUAL(MODULE_STATUS_INVALID_ARG, status);
}
