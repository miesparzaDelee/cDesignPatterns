/**
 * @file module.h
 * @brief Public API for the Module.
 *
 * Skeleton header following conventions:
 *   CS-03 (Self-Contained Header)
 *   CS-04 (Header Organization: Guard → Includes → Defines → Types → Prototypes)
 *   CS-05 (Configuration Structs)
 *   NC-01 (Module-Prefixed Names)
 *   NC-03 (Typedef _t Suffix)
 *   NC-04 (Handle Prefix h)
 *   NC-05 (Macro UPPER_CASE)
 *   DO-01 (Doxygen Public Documentation)
 */

/* ============================================================
 * 1. INCLUDE GUARD                                   [CS-03]
 * ============================================================ */
#ifndef MODULE_H
#define MODULE_H

/* ============================================================
 * 2. INCLUDES — only what this header needs          [CS-03]
 * ============================================================ */
#include <stdint.h>
#include <stdbool.h>

/* ============================================================
 * 3. DEFINES — public constants and macros           [NC-05]
 * ============================================================ */
#define MODULE_MAX_ITEMS   16
#define MODULE_VERSION     1

/* ============================================================
 * 4. TYPES — enums, structs, typedefs                [NC-01, NC-03]
 * ============================================================ */

/** @brief Possible return statuses for module operations. */
typedef enum {
    MODULE_STATUS_OK,
    MODULE_STATUS_ERROR,
    MODULE_STATUS_INVALID_ARG
} module_status_t;

/** @brief Runtime state of the module instance. */
typedef struct {
    uint32_t id;
    bool     active;
    /* Add module-specific fields here */
} module_t;

/** @brief Configuration passed to module_init().        [CS-05] */
typedef struct {
    uint32_t id;
    /* Add configuration parameters here */
} module_config_t;

/** @brief Handle for passing module instances by reference. [NC-04] */
typedef module_t* hModule_t;

/* ============================================================
 * 5. PROTOTYPES — lifecycle first, then others       [CS-04, NC-02]
 * ============================================================ */

/**
 * @brief  Initializes a module instance.                [DO-01]
 * @param  self   Handle to the module instance.
 * @param  config Pointer to the configuration struct.
 * @return MODULE_STATUS_OK on success.
 */
module_status_t module_init(hModule_t self, module_config_t* config);

/**
 * @brief  De-initializes a module instance.
 * @param  self Handle to the module instance.
 */
void module_deinit(hModule_t self);

/**
 * @brief  Periodic task to be called from the main loop or scheduler.
 * @param  self Handle to the module instance.
 */
void module_task(hModule_t self);

/**
 * @brief  Queries whether the module is currently active.
 * @param  self Handle to the module instance.
 * @return true if the module is active, false otherwise.
 */
bool module_isActive(hModule_t self);

#endif /* MODULE_H */
