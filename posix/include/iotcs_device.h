/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is dual-licensed to you under the MIT License (MIT) and
 * the Universal Permissive License (UPL). See the LICENSE file in the root
 * directory for license terms. You may choose either license, or both.
 */

#ifndef IOTCS_DEVICE_H
#define	IOTCS_DEVICE_H

#ifdef	__cplusplus
extern "C" {
#endif


#include <inttypes.h>
#include "iotcs.h"

    /**
     * @file iotcs_device.h
     * @brief Methods for device client
     */

    /**
     * @brief IoT DC library initialization.
     *
     * IoT DC library initialization. Initiates all subsystems.
     * This function must be called before any iotcs_* calls
     * (except \a iotcs_log_* methods).
     * @param path a path to trusted assets store.
     * @param password a password for trusted assets store.
     * @retval IOTCS_RESULT_OK if succeeds.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_init(const char* path, const char* password);

    /**
     * @brief IoT DC library finalization.
     *
     * IoT DC library finalization. Releases previously allocated 
     * temporary resources.
     */
    void iotcs_finalize(void);

    /**
     * @brief Get endpoint Id
     * @return null terminated string with endpoint id
     */
    const char* iotcs_get_endpoint_id(void);

    /**
     * @brief Activate the device
     * @param device_models array of device model URN strings. Last element must have NULL value.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if \a device_models is NULL.
     * @retval IOTCS_RESULT_OK if succeeds or device has already been activated.
     * @retval IOTCS_RESULT_CANNOT_AUTHORIZE if there are problems with authorization.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_activate(const char *device_models[]);

    /**
     * @brief Returns whether the device is activated
     * @return non-zero value is device is activated or zero otherwise
     */
    int iotcs_is_activated(void);

#ifdef IOTCS_GATEWAY

#define IOTCS_METADATA_DEVICE_CLASS "deviceClass" /**< The deviceClass metadata attribute key */
#define IOTCS_METADATA_MANUFACTURER "manufacturer" /**< The manufacturer metadata attribute key */
#define IOTCS_METADATA_MODEL_NUMBER "modelNumber" /**< The modelNumber metadata attribute key */
#define IOTCS_METADATA_PROTOCOL "protocol" /**< The protocol metadata attribute key */
#define IOTCS_METADATA_PROTOCOL_DEVICE_CLASS "protocolDeviceClass" /**< The protocolDeviceClass metadata attribute key */
#define IOTCS_METADATA_PROTOCOL_DEVICE_ID "protocolDeviceId" /**< The protocolDeviceId metadata attribute key */
#define IOTCS_METADATA_SERIAL_NUMBER "serialNumber" /**< The serialNumber metadata attribute key */
    
    /**
     * @brief Register an indirectly-connected device with the cloud service.
     * Register an indirectly-connected device with the cloud service and specifiy whether
     * the gateway device is required to have the appropriate credentials for activating
     * the indirectly-connected device.
     *
     * @param restricted indicate whether or not credentials are required for
     *             activating the indirectly connected device
     * @param hardware_id an identifier unique within the Cloud Service instance
     * @param metadata keys and values for device metadata. Last element must have NULL 'key'.
     * @param device_models array with pointers to zero or more device models that are
     *             implemented by the directly connected device. Last element must have NULL value.
     * @param endpoint_id buffer for returning endpoint id string
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if hardware_id or \a metadata or \a device_models are NULL.
     * @retval IOTCS_RESULT_CANNOT_AUTHORIZE if there are problems with authorization.
     * @retval IOTCS_RESULT_OK if succeeds.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_register_device(iotcs_bool restricted, const char *hardware_id, const iotcs_key_value metadata[],
            const char *device_models[],
            char *endpoint_id);

#endif	/* ifdef IOTCS_GATEWAY */

#ifdef	__cplusplus
}
#endif

#endif	/* IOTCS_DEVICE_H */