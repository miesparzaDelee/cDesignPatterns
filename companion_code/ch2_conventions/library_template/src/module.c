/**
 * @file module.c
 * @brief Implementation of the Module.
 *
 * Skeleton source following conventions:
 *   CS-08 (Include Order: Main → Sub-modules → System → Project)
 *   CS-09 (Source Organization)
 *   NC-06 (Private Naming: priv_ prefix for static vars)
 *   DO-02 (Internal Documentation: "why", not "what")
 */

/* ============================================================
 * 1. INCLUDES                                        [CS-08]
 * ============================================================ */

/* 1a. Main Module Header */
#include "module.h"

/* 1b. Sub-module Headers (if any, alphabetical)
 * #include "module/module_sub.h"
 */

/* 1c. System Headers (alphabetical) */
#include <string.h>

/* 1d. Project Headers (alphabetical)
 * #include "other_library.h"
 */

/* ============================================================
 * 2. LOCAL DEFINES                                   [CS-09]
 * ============================================================ */
#define INTERNAL_BUFFER_SIZE  64

/* ============================================================
 * 3. LOCAL TYPES                                     [CS-09]
 * ============================================================ */

/* (Add file-private typedefs, enums, or structs here) */

/* ============================================================
 * 4. STATIC FUNCTION PROTOTYPES                      [CS-09]
 * ============================================================ */
static void reset_state(hModule_t self);

/* ============================================================
 * 5. STATIC (LOCAL) VARIABLES                        [CS-09, NC-06]
 * ============================================================ */

/* Use priv_ prefix for file-scoped static variables [NC-06] */
static uint32_t priv_instanceCount = 0;

/* ============================================================
 * 6. PUBLIC FUNCTION IMPLEMENTATIONS                 [CS-09]
 * ============================================================ */

module_status_t module_init(hModule_t self, module_config_t* config)
{
    if (self == NULL || config == NULL) {
        return MODULE_STATUS_INVALID_ARG;
    }

    reset_state(self);

    self->id     = config->id;
    self->active = true;
    priv_instanceCount++;

    return MODULE_STATUS_OK;
}

void module_deinit(hModule_t self)
{
    if (self == NULL) { return; }

    self->active = false;

    if (priv_instanceCount > 0) {
        priv_instanceCount--;
    }
}

void module_task(hModule_t self)
{
    if (self == NULL || !self->active) { return; }

    /* Periodic work goes here */
}

bool module_isActive(hModule_t self)
{
    if (self == NULL) { return false; }
    return self->active;
}

/* ============================================================
 * 7. STATIC FUNCTION IMPLEMENTATIONS                [CS-09]
 * ============================================================ */

// No prefix needed on static functions — 'static' keyword
// already signals file scope.  [NC-06]
static void reset_state(hModule_t self)
{
    memset(self, 0, sizeof(module_t));
}
