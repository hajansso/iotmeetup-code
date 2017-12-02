/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is dual-licensed to you under the MIT License (MIT) and
 * the Universal Permissive License (UPL). See the LICENSE file in the root
 * directory for license terms. You may choose either license, or both.
 */


/**
 * @file iotcs.h
 * @brief The file contains common public types
 */

#ifndef IOTCS_H
#define IOTCS_H

#include <stddef.h>
#include <stdint.h>

#include "iotcs_config.h"

/**
 * @enum iotcs_result
 * @brief Return codes for iotcs_* client library functions.
 */
typedef enum {
    IOTCS_RESULT_OK = 0x0,                     /**< Operation succeded.*/
    IOTCS_RESULT_FAIL = 0x1,                   /**< Operation failed.*/
    IOTCS_RESULT_OUT_OF_MEMORY = 0x2,          /**< Out Of Memory error.*/
    IOTCS_RESULT_INVALID_ARGUMENT = 0x4,       /**< Invalid argument provided.*/
    IOTCS_RESULT_CANNOT_AUTHORIZE = 0x8        /**< Authorization problems.*/
} iotcs_result;

/**
 * @enum iotcs_value_type
 * @brief Device Model Attribute type
 */
typedef enum {
    IOTCS_VALUE_TYPE_INT = 0,
    IOTCS_VALUE_TYPE_NUMBER = 1,
    IOTCS_VALUE_TYPE_BOOLEAN = 2,
    IOTCS_VALUE_TYPE_STRING = 3,
    IOTCS_VALUE_TYPE_DATE_TIME = 4,
    IOTCS_VALUE_TYPE_NONE = 5,
} iotcs_value_type;

/**
 * @typedef iotcs_date_time
 * @brief number of milliseconds that have elapsed since January 1, 1970 (midnight UTC/GMT)
 */
typedef int64_t iotcs_date_time;

#define IOTCS_TRUE  ((iotcs_bool)1) /**< True boolean value*/
#define IOTCS_FALSE ((iotcs_bool)0) /**< False boolean value*/

/**
 * @typedef iotcs_bool
 * @brief boolean type
 */
typedef int iotcs_bool;

/**
 * @union iotcs_value
 * @brief value type
 */
typedef union {
    int int_value;                     /**< integer value */
    float number_value;                /**< floating-point value */
    const char* string_value;          /**< address of null-terminated string */
    iotcs_bool bool_value;             /**< boolean value */
    iotcs_date_time date_time_value;   /**< 64-bit epoch */
} iotcs_value;

/**
 * @struct iotcs_typed_value
 * @brief value together with its type
 */
typedef struct {
    iotcs_value_type type;  /**< #value type */
    iotcs_value value;  /**< value union */
} iotcs_typed_value;

/**
 * @brief Simple string key-value pair.
 * @struct iotcs_key_value
 */
typedef struct {
    const char* key;           /**< Key */
    const char* value;         /**< Value */
} iotcs_key_value;

#endif /* IOTCS_H */
