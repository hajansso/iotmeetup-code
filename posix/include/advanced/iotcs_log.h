/*
 * Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is dual-licensed to you under the MIT License (MIT) and
 * the Universal Permissive License (UPL). See the LICENSE file in the root
 * directory for license terms. You may choose either license, or both.
 */


/**
 * @file iotcs_log.h
 * @brief The file defines the public API to control library logging system.
 * Library logging system has several channels each one for a particular
 * library module (see iotcs_log_channel type). And each channel has its
 * logging level (see iotcs_log_level type) to filter out undesirable log entries.
 * Also there is a global logging level that is applicable to every channel.
 * 
 * Any logging entry that library tries to output to particular log channel
 * also has associated log level. Initially this log level is checked
 * against global log level. Entries with log level less or equal to global
 * log level pass the check, others are dropped. Next entry's log level is
 * similarly checked against channel specific level.
 * 
 * Library does the actual output by invoking log method (see iotcs_log_method
 * type) that could be overridden by user (see iotcs_log_set_method).
 * By default libc's \a fwrite(buf,len,1,fp) is used, where \a fp is \a stderr
 * for WARNING, ERROR, CRITICAL and \a stdout otherwise.
 * 
 * Besides run-time options there are also compile-time options that could be used
 * to completely remove certain log entries from binary image thus reducing
 * image size. Those options include global define IOTCS_LOG_LEVEL. E.g. if
 * \a IOTCS_LOG_LEVEL=2 is given to preprocessor during compilation then only
 * log entries with IOTCS_LOG_LEVEL_CRITICAL and IOTCS_LOG_LEVEL_ERROR level
 * will make its way into a binary. Additionally each channel has its own define
 * \a IOTCS_LOG_LEVEL_CHANNEL_xxx. E.g. if \a IOTCS_LOG_LEVEL_CHANNEL_CORE=1 is
 * given to preprocessor during compilation then only log entries with
 * IOTCS_LOG_LEVEL_CRITICAL level of core module will make its way into a binary.
 * 
 * Optionally every log entry could include base file name and line number of
 * the place that generated the entry by giving IOTCS_LOG_USE_FILE_LINE. 
 * It is implicitly turned on by default for debug build.
 */

#ifndef IOTCS_LOG_H_
#define IOTCS_LOG_H_

#include "iotcs.h"

    /**
     * @enum iotcs_log_level
     * @brief Log level
     */
    typedef enum {
        IOTCS_LOG_LEVEL_NONE = 0, ///< No log
        IOTCS_LOG_LEVEL_CRITICAL = 1, ///< Critical log entry: unrecoverable internal error - library can't work properly anymore
        IOTCS_LOG_LEVEL_ERROR = 2,  ///< Error log entry: recoverable error, user action is required
        IOTCS_LOG_LEVEL_WARNING = 3, ///< Warning log entry: recoverable error, no user action is required
        IOTCS_LOG_LEVEL_INFO = 4, ///< Information log entry: not an error
        IOTCS_LOG_LEVEL_DEBUG = 5,  ///< Debug log entry
        IOTCS_LOG_LEVEL_ALL = IOTCS_LOG_LEVEL_DEBUG,
    } iotcs_log_level;

    /**
     * @enum iotcs_log_channel
     * @brief Log channel
     */
    typedef enum {
        IOTCS_LOG_CHANNEL_DM = 0, ///< Device model channel
        IOTCS_LOG_CHANNEL_EXT, ///< External module channel
        IOTCS_LOG_CHANNEL_CORE, ///< Iotcs module channel
        IOTCS_LOG_CHANNEL_JSON, ///< Json module channel
        IOTCS_LOG_CHANNEL_MSG, ///< Messaging module channel
        IOTCS_LOG_CHANNEL_PROTO, ///< Protocol module channel
        IOTCS_LOG_CHANNEL_TAM, ///< TAM module channel
        IOTCS_LOG_CHANNEL_UTIL, ///< Util module channel
        IOTCS_LOG_CHANNEL_LOG, ///< Logging module channel
        IOTCS_LOG_CHANNEL_TEST, ///< Tests channel
        IOTCS_LOG_CHANNEL_PORT_QUEUE, ///< Port blocking queue module channel
        IOTCS_LOG_CHANNEL_PORT_CRYPTO, ///< Port crypto module channel
        IOTCS_LOG_CHANNEL_PORT_TAM, ///< Port TAM module channel
        IOTCS_LOG_CHANNEL_PORT_DIAG, ///< Port diagnostic module channel
        IOTCS_LOG_CHANNEL_PORT_MEM, ///< Port memory module channel
        IOTCS_LOG_CHANNEL_PORT_MUTEX, ///< Port mutex module channel
        IOTCS_LOG_CHANNEL_PORT_SSL, ///< Port SSL module channel
        IOTCS_LOG_CHANNEL_PORT_SYSTEM, ///< Port system module channel
        IOTCS_LOG_CHANNEL_PORT_THREAD, ///< Port thread module channel
        IOTCS_LOG_CHANNEL_PORT_MQTT, ///< Port mqtt module channel
        IOTCS_LOG_CHANNEL_NUM, ///< Total number of logging levels
    } iotcs_log_channel;

    /**
     * @typedef iotcs_log_method
     * @brief typedef for log callback.
     * By default libc's \a fwrite(buf,len,1,stdout) is used.
     * @param level log level
     * @param channel log channel
     * @param buf formatted buffer for writing to log
     * @param len buffer size
     */
    typedef void (*iotcs_log_method)(iotcs_log_level level, iotcs_log_channel channel,
            const char *buf, size_t len);
    
    /**
     * @brief Get logging method
     * By default libc's \a fwrite(buf,len,1,fp) is used, where \a fp is
     * \a stderr for WARN, ERR, CRIT and \a stdout otherwise.
     * @retval current logging method or NULL is case of default method
     */
    iotcs_log_method iotcs_log_get_method(void);
    
    /**
     * @brief Set logging method
     * The method MUST be called before \a iotcs_init invocation.
     * By default libc's \a fwrite(buf,len,1,stdout) is used.
     * @param logging method or NULL to set default logging method
     */
    void iotcs_log_set_method(iotcs_log_method method);

    /**
     * @brief Get global logging level
     * @retval global logging level
     */
    iotcs_log_level iotcs_log_get_global_level(void);
    
    /**
     * @brief Set global logging level
     * @param level global logging level
     */
    void iotcs_log_set_global_level(iotcs_log_level level);

    /**
     * @brief Get logging levels for all channels
     * Returns pointer to internal array with log level for all channels.
     * The array size is IOTCS_LOG_CHANNEL_NUM. Enum iotcs_log_channel values can be
     * used as an index to the array.
     * @retval pointer to array with log level for all channels
     */
    const iotcs_log_level* iotcs_log_get_levels(void);
    
    /**
     * @brief Set logging levels for all channels
     * Accepts pointer to internal array with log level for all channels.
     * The array size must be IOTCS_LOG_CHANNEL_NUM. Enum iotcs_log_channel
     * values will be used as an index to the array.
     * The method MUST be called before \a iotcs_init invocation.
     * @param levels pointer to array with log level for all channels
     */
    void iotcs_log_set_levels(const iotcs_log_level *levels);

    
    /**
     * @brief Get logging level for specified channel
     * @param channel channel
     * @retval current logging level for given channel
     */
    iotcs_log_level iotcs_log_get_level(iotcs_log_channel channel);
    
    /**
     * @brief Set logging level for specified channel
     * @param channel channel
     * @param level new logging level for given channel
     */
    void iotcs_log_set_level(iotcs_log_channel channel, iotcs_log_level level);
    
    /**
     * @brief Set logging levels for all channels to specified value
     * @param level logging level
     */
    void iotcs_log_set_level_all(iotcs_log_level level);

#endif /* IOTCS_LOG_H_ */
