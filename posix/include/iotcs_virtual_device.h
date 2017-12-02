/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is dual-licensed to you under the MIT License (MIT) and
 * the Universal Permissive License (UPL). See the LICENSE file in the root
 * directory for license terms. You may choose either license, or both.
 */

/**
 * @file iotcs_virtual_device.h
 * @brief The file defines the iot cs device model APIs.
 */

#ifndef IOTCS_DEVICE_VIRTUAL_H
#define	IOTCS_DEVICE_VIRTUAL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "iotcs.h"

    /**
     * @typedef iotcs_virtual_device_handle
     * @brief Device Handle
     */
    typedef struct iotcs_virtual_device_handle_t* iotcs_virtual_device_handle;

    /**
     * @struct iotcs_named_value_t
     * @brief Change event
     */
    typedef struct iotcs_named_value_t {
        const char *name; /**< The attribute for which the value was changed */
        iotcs_typed_value typed_value; /**< The value of the attribute with its type after the change */
        struct iotcs_named_value_t *next; /**< Pointer to next event in a chain. If next = NULL then this event the last event in a chain */
    } iotcs_named_value;
    /**< Typedef for #iotcs_named_value_t structure */

    /**
     * @struct iotcs_virtual_device_change_event_t
     * @brief Change event
     */
    typedef struct iotcs_virtual_device_change_event_t {
        iotcs_named_value named_value; /**< Named value */
        iotcs_virtual_device_handle virtual_device_handle; /**< The device generated this event */
    } iotcs_virtual_device_change_event;
    /**< Typedef for #iotcs_virtual_device_change_event_t structure */

    /**
     * @struct iotcs_virtual_device_error_event_t
     * @brief Change event
     */
    typedef struct iotcs_virtual_device_error_event_t {
        iotcs_named_value named_value; /**< Named value */
        iotcs_virtual_device_handle virtual_device_handle; /**< The device generated this event */
        const char *message; /**< Message */
    } iotcs_virtual_device_error_event;
    /**< Typedef for #iotcs_virtual_device_error_event_t structure */

    /**
     * Callback invoked in case of attribute value change
     * @param event describes attribute together with old and new values
     */
    typedef void (*iotcs_virtual_device_changed_callback)(iotcs_virtual_device_change_event *event);

    /**
     * Callback invoked in case of action request
     * @param virtual_device_handle The device for which this action has been invoked
     * @param argument argument value together with its type
     */
    typedef void (*iotcs_action_callback)(iotcs_virtual_device_handle virtual_device_handle,
            iotcs_typed_value argument);

    /**
     * Callback invoked in case of network error in attribute update process
     * @note The implementation of callback should not call
     * #iotcs_alert_raise, #iotcs_data_submit and #iotcs_virtual_device_setXXX
     * procedures to avoid a possible deadlock on outgoing message queue.
     * @param event describes attribute together with old and new values
     */
    typedef void (*iotcs_virtual_device_error_callback)(iotcs_virtual_device_error_event *event);

    /**
     * @typedef iotcs_device_model_handle
     * @brief Device Model Handle
     */
    typedef struct iotcs_device_model_handle_t* iotcs_device_model_handle;

    /**
     * @typedef iotcs_alert_handle
     * @brief Pointer to Device Alert Handle
     */
    typedef struct iotcs_alert_handle_t* iotcs_alert_handle;

    /**
     * @typedef iotcs_data_handle
     * @brief Pointer to Device Data Handle
     */
    typedef struct iotcs_data_handle_t* iotcs_data_handle;

    /**
     * @brief Get device model handle for a given name
     * @param device_model device model URN
     * @param device_model_handle address of Device Model Handle
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if device model urn is NULL.
     * @retval IOTCS_RESULT_FAIL if there are no device models with current urn on the server or returned device model is incorrect.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_get_device_model_handle(const char *device_model, iotcs_device_model_handle *device_model_handle);

    /**
     * @brief Release Device Handle.
     * @param device_model_handle Device Handle to release
     */
    void iotcs_free_device_model_handle(iotcs_device_model_handle device_model_handle);

    /**
     * @brief Get Device Handle.
     * @param endpoint_id endpoint id
     * @param device_model_handle Device model handle
     * @param virtual_device_handle address of Device handle
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if endpoint_id or device_model_handle are NULL.
     * @retval IOTCS_RESULT_OUT_OF_MEMORY if no additional memory can be allocated for use.
     * @retval IOTCS_RESULT_OK if succeeds.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_get_virtual_device_handle(const char *endpoint_id, iotcs_device_model_handle device_model_handle, iotcs_virtual_device_handle *virtual_device_handle);

    /**
     * @brief Release Device Handle.
     * @param virtual_device_handle Device Handle to release
     */
    void iotcs_free_virtual_device_handle(iotcs_virtual_device_handle virtual_device_handle);

    /**
     * @brief Set value of Device Attribute
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value pointer array of values of 'length' bytes. The particular type is determined based on
     *        attribute type and could be: const char*, int, float, iotcs_bool or iotcs_date_time.
     * @param length length of 'value' array in bytes
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_set(iotcs_virtual_device_handle virtual_device_handle, const char* attribute_name, const void* value, size_t length);

    /**
     * @brief Get STRING value of Device Attribute
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value address of pointer to null-terminated string. The string will be allocated by the library and use must release it by calling free(ptr)
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_FAIL if an attribute value wasn't set before and there is no default value.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_get_string(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, const char **value);

    /**
     * @brief Set STRING value of Device Attribute
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value pointer to null-terminated string
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found or attribute type is different.
     * Operation could be retried at a later time.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_set_string(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, const char *value);

    /**
     * @brief Get INTEGER  value of Device Attribute
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value address of value to return
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_FAIL if an attribute value wasn't set before and there is no default value.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_get_integer(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, int *value);

    /**
     * @brief Set INTEGER  value of Device Attribute
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found or attribute type is different.
     * Operation could be retried at a later time.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_set_integer(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, int value);

    /**
     * @brief Get NUMBER value of Device Attribute
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value address of value to return
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_FAIL if an attribute value wasn't set before and there is no default value.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_get_float(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, float *value);

    /**
     * @brief Set NUMBER value of Device Attribute
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found or attribute type is different.
     * Operation could be retried at a later time.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_set_float(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, float value);

    /**
     * @brief Get BOOLEAN value of Device Attribute
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value address of value to return
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_FAIL if an attribute value wasn't set before and there is no default value.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_get_boolean(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, iotcs_bool *value);

    /**
     * @brief Set BOOLEAN value of Device Attribute
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found or attribute type is different.
     * Operation could be retried at a later time.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_set_boolean(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, iotcs_bool value);

    /**
     * @brief Get DATETIME value of Device Attribute
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value address of value to return
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_FAIL if an attribute value wasn't set before and there is no default value.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_get_date_time(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, iotcs_date_time *value);

    /**
     * @brief Set DATETIME value of Device Attribute
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found or attribute type is different.
     * Operation could be retried at a later time.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_set_date_time(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, iotcs_date_time value);

    /**
     * @brief Set callback for every external change of Device Attributes
     * @param virtual_device_handle Device Handle
     * @param callback callback to call
     */
    void iotcs_virtual_device_set_on_change(iotcs_virtual_device_handle virtual_device_handle, iotcs_virtual_device_changed_callback callback);

    /**
     * @brief Set callback for every external change of particular Device Attribute
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param callback callback to call
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_attribute_set_on_change(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, iotcs_virtual_device_changed_callback callback);

    /**
     * @brief Set callback for network failure of Device Attribute change notification
     * @param virtual_device_handle Device Handle
     * @param callback callback to call
     */
    void iotcs_virtual_device_set_on_error(iotcs_virtual_device_handle virtual_device_handle, iotcs_virtual_device_error_callback callback);

    /**
     * @brief Set callback for network failure of particular Device Attribute change notification
     * @param virtual_device_handle Device Handle
     * @param attribute_name Name of the attribute
     * @param callback callback to call
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or attribute_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given attribute_name wasn't found.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_attribute_set_on_error(iotcs_virtual_device_handle virtual_device_handle, const char *attribute_name, iotcs_virtual_device_error_callback callback);

    /**
     * @brief Set callback for given action
     * @param virtual_device_handle Device Handle
     * @param action_name Name of the action
     * @param callback callback to call
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or action_name are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT given action_name wasn't found.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_virtual_device_set_callback(iotcs_virtual_device_handle virtual_device_handle, const char *action_name, iotcs_action_callback callback);

    /**
     * @brief Suspend background network notifications of changed attribute values
     * @param virtual_device_handle Device Handle
     */
    void iotcs_virtual_device_start_update(iotcs_virtual_device_handle virtual_device_handle);

    /**
     * @brief Resume background network notifications of changed attribute values
     * @param virtual_device_handle Device Handle
     */
    void iotcs_virtual_device_finish_update(iotcs_virtual_device_handle virtual_device_handle);

    /**
     * @brief Get Device Alert Handle
     * @param virtual_device_handle Device Handle
     * @param alert_name Name of the alert
     * @param halert address of Device Alert Handle
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or alert_name are NULL.
     * @retval IOTCS_RESULT_OUT_OF_MEMORY if no additional memory can be allocated for use.
     * @retval IOTCS_RESULT_OK if succeeds.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_virtual_device_get_alert_handle(iotcs_virtual_device_handle virtual_device_handle, const char *alert_name, iotcs_alert_handle *halert);

    /**
     * @brief Release Device Alert Handle
     * @param halert Device Alert Handle to release
     */
    void iotcs_virtual_device_free_alert_handle(iotcs_alert_handle halert);

    /**
     * @brief Send Alert asynchronously
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param halert Alert handle
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a halert is NULL.
     * @retval IOTCS_RESULT_OUT_OF_MEMORY if no additional memory can be allocated for use..
     * @retval IOTCS_RESULT_OK if succeeds.
     * Operation could be retried at a later time.
     * @retval IOTCS_RESULT_FAIL no new values or not all non-optional values were set
     *                           since the last #iotcs_alert_raise invocation.
     */
    iotcs_result iotcs_alert_raise(iotcs_alert_handle halert);

    /**
     * @brief Set the value of a field \a field in the \a halert
     * @param halert Alert handle
     * @param field Name of the field
     * @param value pointer array of values of 'length' bytes. The particular type is determined based on
     *        attribute type and could be: const char*, int, float, iotcs_bool or iotcs_date_time.
     * @param length length of 'value' array in bytes
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a halert or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_alert_set(iotcs_alert_handle halert, const char* field, const void* value, size_t length);

    /**
     * @brief Set STRING value of a field \a field in the \a halert
     * @param halert Alert handle
     * @param field Name of the field
     * @param value pointer to null-terminated string
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a halert or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_alert_set_string(iotcs_alert_handle halert, const char *field, const char *value);

    /**
     * @brief Set INTEGER value of a field \a field in the \a halert
     * @param halert Alert handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a halert or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_alert_set_integer(iotcs_alert_handle halert, const char *field, int value);

    /**
     * @brief Set NUMBER value of a field \a field in the \a halert
     * @param halert Alert handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a halert or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_alert_set_float(iotcs_alert_handle halert, const char *field, float value);

    /**
     * @brief Set BOOLEAN value of a field \a field in the \a halert
     * @param halert Alert handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a halert or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_alert_set_boolean(iotcs_alert_handle halert, const char *field, iotcs_bool value);

    /**
     * @brief Set DATETIME value of a field \a field in the \a halert
     * @param halert Alert handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a halert or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_alert_set_date_time(iotcs_alert_handle halert, const char *field, iotcs_date_time value);

    /**
     * @brief Get Device Data Handle
     * @param virtual_device_handle Device Handle
     * @param data_name Name of the custom data
     * @param hdata address of Device Data Handle
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if virtual_device_handle or alert_name are NULL.
     * @retval IOTCS_RESULT_OUT_OF_MEMORY if no additional memory can be allocated for use.
     * @retval IOTCS_RESULT_OK if succeeds.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_virtual_device_get_data_handle(iotcs_virtual_device_handle hdev, const char *data_name, iotcs_data_handle *hdata);

    /**
     * @brief Release Device Data Handle
     * @param halert Device Data Handle to release
     */
    void iotcs_virtual_device_free_data_handle(iotcs_data_handle hdata);

    /**
     * @brief Send Custom Data asynchronously
     * @note This procedure should not be called from #iotcs_virtual_device_error_callback
     * implementation due to the possible deadlock on outgoing message queue.
     * @param halert Data handle
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a hdata is NULL.
     * @retval IOTCS_RESULT_OUT_OF_MEMORY if no additional memory can be allocated for use..
     * @retval IOTCS_RESULT_OK if succeeds.
     * Operation could be retried at a later time.
     * @retval IOTCS_RESULT_FAIL no new values or not all non-optional values were set
     *                           since the last #iotcs_data_submit invocation.
     */
    iotcs_result iotcs_data_submit(iotcs_data_handle hdata);

    /**
     * @brief Set the value of a field \a field in the \a hdata
     * @param hdata Data handle
     * @param field Name of the field
     * @param value pointer array of values of 'length' bytes. The particular type is determined based on
     *        attribute type and could be: const char*, int, float, iotcs_bool or iotcs_date_time.
     * @param length length of 'value' array in bytes
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a hdata or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_data_set(iotcs_data_handle hdata, const char* field, const void* value, size_t length);

    /**
     * @brief Set STRING value of a field \a field in the \a hdata
     * @param hdata Data handle
     * @param field Name of the field
     * @param value pointer to null-terminated string
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a hdata or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_data_set_string(iotcs_data_handle hdata, const char *field, const char *value);

    /**
     * @brief Set INTEGER value of a field \a field in the \a hdata
     * @param hdata Data handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a hdata or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_data_set_integer(iotcs_data_handle hdata, const char *field, int value);

    /**
     * @brief Set NUMBER value of a field \a field in the \a hdata
     * @param hdata Data handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a hdata or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_data_set_float(iotcs_data_handle hdata, const char *field, float value);

    /**
     * @brief Set BOOLEAN value of a field \a field in the \a hdata
     * @param hdata Data handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a hdata or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_data_set_boolean(iotcs_data_handle hdata, const char *field, iotcs_bool value);

    /**
     * @brief Set DATETIME value of a field \a field in the \a hdata
     * @param hdata Data handle
     * @param field Name of the field
     * @param value value to set
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a hdata or \a field are NULL.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if given field wasn't found or attribute type is different.
     * @retval IOTCS_RESULT_OK if succeeds.
     */
    iotcs_result iotcs_data_set_date_time(iotcs_data_handle hdata, const char *field, iotcs_date_time value);

#ifdef	__cplusplus
}
#endif

#endif	/* IOTCS_DEVICE_VIRTUAL_H */

