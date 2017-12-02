/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is dual-licensed to you under the MIT License (MIT) and
 * the Universal Permissive License (UPL). See the LICENSE file in the root
 * directory for license terms. You may choose either license, or both.
 */


/**
 * @file iotcs_message.h
 * @brief The file defines the public API for building IoT Messages.
 */
#ifndef IOTCS_MESSAGE_H_
#define IOTCS_MESSAGE_H_

#include "iotcs.h"

/**
 * @enum iotcs_message_type
 * @brief IoT CS Message type.
 */
typedef enum {
    IOTCS_MESSAGE_DATA = 0,
    IOTCS_MESSAGE_ALERT = 1,
    IOTCS_MESSAGE_REQUEST = 2,
    IOTCS_MESSAGE_RESPONSE = 3,
    IOTCS_MESSAGE_RESOURCE = 4,
} iotcs_message_type;

/**
 * @enum iotcs_message_priority
 * @brief IoT CS Message priority values.
 */
typedef enum {
    IOTCS_MESSAGE_PRIORITY_LOWEST = 0,
    IOTCS_MESSAGE_PRIORITY_LOW = 1,
    IOTCS_MESSAGE_PRIORITY_MEDIUM = 2,
    IOTCS_MESSAGE_PRIORITY_HIGH = 3,
    IOTCS_MESSAGE_PRIORITY_HIGHEST = 4,
    IOTCS_MESSAGE_PRIORITY_DEFAULT = IOTCS_MESSAGE_PRIORITY_LOW
} iotcs_message_priority;

/**
 * @enum iotcs_message_reliability
 * @brief IoT CS Message reliability values.
 */
typedef enum {
    IOTCS_MESSAGE_RELIABILITY_NO_GUARANTEE = 0,
    IOTCS_MESSAGE_RELIABILITY_BEST_EFFORT = 1, /**< Default relability */
    IOTCS_MESSAGE_RELIABILITY_GUARANTED_DELIVERY = 2,
    IOTCS_MESSAGE_RELIABILITY_DEFAULT = IOTCS_MESSAGE_RELIABILITY_BEST_EFFORT
} iotcs_message_reliability;

/**
 * @enum iotcs_message_severity
 * @brief Alert Message severity level.
 */
typedef enum {
    IOTCS_MESSAGE_SEVERITY_CRITICAL = 0,
    IOTCS_MESSAGE_SEVERITY_SIGNIFICANT = 1,
    IOTCS_MESSAGE_SEVERITY_NORMAL = 2,
    IOTCS_MESSAGE_SEVERITY_LOW = 3,
    IOTCS_MESSAGE_SEVERITY_DEFAULT = IOTCS_MESSAGE_SEVERITY_SIGNIFICANT
} iotcs_message_severity;

/**
 * @enum iotcs_resource_message_type
 * @brief IoT CS Resource Message type.
 */
typedef enum {
    IOTCS_RESOURCE_MESSAGE_UPDATE = 0,
    IOTCS_RESOURCE_MESSAGE_DELETE = 1,
    IOTCS_RESOURCE_MESSAGE_RECONCILIATION = 2
} iotcs_resource_message_type;

/**
 * @struct iotcs_data_item_desc
 * @brief IoT CS data item description structure.
 */
typedef struct {
    iotcs_value_type type;   /**< Data item value type.*/  
    const char* key;         /**< Data item value key.*/
} iotcs_data_item_desc;

/**
 * @struct iotcs_data_item
 * @brief IoT CS data item structure.
 */
typedef struct {
    iotcs_data_item_desc *base;  /**< Pointer to data item base structure.*/
    iotcs_value value;           /**< Data item value.*/
} iotcs_data_item;

/**
 * @struct iotcs_message_diagnostic
 * @brief IoT CS message diagnostic item
 */
typedef struct {
    const char* key; /**< diagnostic key */
    iotcs_value value; /**< diagnostic value */
    iotcs_value_type type; /**< diagnostic value type */
} iotcs_message_diagnostic;

/**
 * @struct iotcs_message_property
 * @brief IoT CS message property
 */
typedef struct {
    const char* key; /**< property key*/
    const char* const* values; /**< address of null terminated array with 'values' assosiated with the 'key' */
} iotcs_message_property;

/**
 * @struct iotcs_message_base
 * @brief IoT CS message base structure.
 */
typedef struct {
    iotcs_message_type type;               /**< Message type.*/
    const char* source;                    /**< Source name.*/
    const char* sender;                    /**< Sender name.*/
    const char* destination;               /**< Destination.*/
    iotcs_message_priority priority;       /**< Message priority.*/
    iotcs_message_reliability reliability; /**< Message reliability.*/
} iotcs_message_base;

/**
 * @struct iotcs_data_message_base
 * @brief IoT CS data message base structure.
 */
typedef struct {
    const char *format;           /**< Format of the data message.*/
} iotcs_data_message_base;

/**
 * @struct iotcs_data_message
 * @brief IoT CS data message structure.
 */
typedef struct {
    const iotcs_data_message_base *base;       /**< Pointer to the #iotcs_data_message_base structure.*/
    const iotcs_data_item_desc *items_desc;     /**< Pointer to the #iotcs_data_item_desc structure.*/
    iotcs_value *items_value;                   /**< Array of the #iotcs_value.*/
} iotcs_data_message;

/**
 * @struct iotcs_alert_message_base
 * @brief IoT CS alert message base structure.
 */
typedef struct {
    const char *format;                     /**< Alert format name.*/
    const char* description;                /**< Alert description.*/
    iotcs_message_severity severity_level;  /**< Severity level.*/
} iotcs_alert_message_base;

/**
 * @struct iotcs_alert_message
 * @brief IoT CS alert message structure.
 */
typedef struct {
    const iotcs_alert_message_base *base;    /**< Pointer to the #iotcs_alert_message_base structure.*/
    const iotcs_data_item_desc *items_desc;   /**< Pointer to the #iotcs_data_item_desc structure.*/
    iotcs_value *items_value;                 /**< Array of the #iotcs_value.*/
} iotcs_alert_message;

/**
 * @enum iotcs_request_method
 * @brief Contains values of the request methods.
 */
typedef enum {
    IOTCS_REQUEST_METHOD_DELETE = 1, /**< DELETE method*/
    IOTCS_REQUEST_METHOD_GET = 2, /**< GET method*/
    IOTCS_REQUEST_METHOD_POST = 8, /**< POST method*/
    IOTCS_REQUEST_METHOD_PUT = 16 /**< PUT method*/
} iotcs_request_method;

/**
 * @struct iotcs_resource_message_base
 * @brief Resource description structure
 */
typedef struct {
    const char* name;                        /**< Resource name. */
    const char* path;                        /**< Path to resource */
    const char* description;                 /**< Description. */
    iotcs_request_method methods;            /**< ORed bit mask. */
} iotcs_resource_message_base;

/**
 * @struct iotcs_resource_message
 * @brief IoT CS resource message structure.
 */
typedef struct {
    const iotcs_resource_message_base* base;   /**< Pointer to the array of #iotcs_resource_message_base structures with length #resource_len*/
    int resource_len;                          /**< #base array length.*/
    iotcs_resource_message_type report_type;   /**< Resource message type.*/
    const char* endpointName;                  /**< Endpoint name.*/
} iotcs_resource_message;

/**
 * @struct iotcs_request_message
 * @brief IoT CS request message structure.
 */
typedef struct {
    char* id;                         /**< Request message id.*/
    char* source;                     /**< Request message source.*/
    char* destination;                /**< Request message destination.*/
    iotcs_key_value *headers;         /**< Headers array of #iotcs_key_value.*/
    int headers_len;                  /**< Headers array length.*/
    iotcs_key_value *params;          /**< Params array of #iotcs_key_value.*/
    int params_len;                   /**< Params array length.*/
    iotcs_request_method method;      /**< Request method #iotcs_request_method.*/
    char* url;                        /**< Request url.*/
    char* body;                       /**< Request body.*/
} iotcs_request_message;

/**
 * @struct iotcs_response_message
 * @brief IoT CS response message structure.
 */
typedef struct {
    int status_code;                 /**< Response status code.*/
    const char* body;                /**< Response body.*/
    iotcs_request_message* request;  /**< Related request with valid \a id and \a url */
    iotcs_key_value *headers;        /**< Headers array of #iotcs_key_value.*/
    int headers_len;                 /**< Headers array length.*/
} iotcs_response_message;

/**
 * @struct iotcs_message
 * @brief IoT CS message structure.
 */
typedef struct {
    const iotcs_message_base *base;       /**< Pointer to #iotcs_message_base.*/
    const char* id;                       /**< Message id.*/
    uint64_t event_time;                  /**< Message event time.*/
    void *user_data;                      /**< Arbitrary user data ignored by library.*/
    const iotcs_message_diagnostic *diagnostics;  /**< array with optional diagnostics
                                                   * for a message. Last element must have null 'key' */
    const iotcs_message_property *properties; /**< array with optional properties
                                               *  for a message. Last element must have null 'key' */

    union {
        iotcs_data_message data;           /**< #iotcs_data_message.*/
        iotcs_alert_message alert;         /**< #iotcs_alert_message.*/
        iotcs_response_message response;   /**< #iotcs_response_message.*/
        iotcs_resource_message resource;   /**< #iotcs_resource_message.*/
    } u; /**< union type is identified by #base->type */
} iotcs_message;

#endif /* IOTCS_MESSAGE_H_ */
