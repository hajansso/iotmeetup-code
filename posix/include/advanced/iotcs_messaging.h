/*
 * Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
 *
 * This software is dual-licensed to you under the MIT License (MIT) and
 * the Universal Permissive License (UPL). See the LICENSE file in the root
 * directory for license terms. You may choose either license, or both.
 */

/**
 * @file  iotcs_messaging.h
 * @brief The file contains API for IOT CS Message and Request Dispatchers
 */

#ifndef IOTCS_MESSAGE_DISPATCHER_H_
#define	IOTCS_MESSAGE_DISPATCHER_H_

#include "iotcs_message.h"

#ifdef	__cplusplus
extern "C" {
#endif

    /*
     * IOT CS Message Dispatcher part
     */
#if defined IOTCS_MESSAGE_DISPATCHER || defined IOTCS_DOXYGEN

    /**
     * @typedef iotcs_message_dispatcher_delivery_callback
     * @brief typedef for message dispatcher send callback.
     * @note The implementation of callback should not call
     * #iotcs_message_dispatcher_queue procedure to avoid a possible deadlock
     * on waiting for the message sending status from the calling thread.
     * @param message pointer to #iotcs_message
     */
    typedef void(*iotcs_message_dispatcher_delivery_callback)(iotcs_message *message);

    /**
     * @typedef iotcs_message_dispatcher_error_callback
     * @brief typedef for message dispatcher receive callback.
     * @note The implementation of callback should not call
     * #iotcs_message_dispatcher_queue procedure to avoid a possible deadlock
     * on waiting for the message sending status from the calling thread.
     * @param message pointer to #iotcs_message
     * @param result #iotcs_result
     * @param fail_reason string with fail reason
     */
    typedef void(*iotcs_message_dispatcher_error_callback)(iotcs_message *message, iotcs_result result,
            const char *fail_reason);

    /**
     * @brief set delivery callback for IoT CS message dispatcher
     * @param delivery_cb delivery callback
     */
    void iotcs_message_dispatcher_set_delivery_callback(iotcs_message_dispatcher_delivery_callback delivery_cb);

    /**
     * @brief set error callback for IoT CS message dispatcher
     * @param error_cb error callback
     */
    void iotcs_message_dispatcher_set_error_callback(iotcs_message_dispatcher_error_callback error_cb);

    /**
     * @brief IoT CS message dispatcher send method.
     * @param message pointer to #iotcs_message
     * @note This procedure should not be called from the callback 
     * implementation due to the possible deadlock on waiting for the message
     * sending status from the current thread.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if message is NULL.
     * @retval IOTCS_RESULT_OK if succeeds.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_message_dispatcher_queue(iotcs_message* message);

#endif

#if !defined IOTCS_MESSAGE_DISPATCHER || defined IOTCS_DOXYGEN

    /**
     * @brief Send a number of messages to IOT server. This method blocks until all messages are sent.
     * All incoming request messages are put into library-maintained request queue and can be retrieved from it by calling receive method.
     * @param messages Array of {@link iotcs_message} to be sent.
     * @param len Number of messages in array to be sent.
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if some of messages are NULL or len is negative or zero.
     * @retval IOTCS_RESULT_CANNOT_AUTHORIZE if there are problems with authorization.
     * @retval IOTCS_RESULT_OK if succeeds.
     * @retval IOTCS_RESULT_FAIL otherwise.
     */
    iotcs_result iotcs_send(iotcs_message messages[], size_t len);

    /**
     * @brief Receive a \a iotcs_request_message from the server, if any. This call may
     * block if the implementation sends a message to the server to poll
     * for requests. This call may return null.
     * @param timeout maximum time, in milliseconds, to wait for a response from
     *                the server
     * @retval #iotcs_request_message pointer to request message.
     * @retval NULL if empty or no request from the server received during the timeout.
     */
    iotcs_request_message* iotcs_receive(int32_t timeout);

    /**
     * @brief Destroy request message when it is no longer needed.
     * @param message
     */
    void iotcs_request_message_free(iotcs_request_message* message);

#endif /* #else #ifdef IOTCS_MESSAGE_DISPATCHER */

    /*
     * IOT CS Request Dispatcher part
     */

    /**
     * @brief resource handler callback function
     * After handler invocation request id and url is copied from 'request' and 'request'
     * is freed.
     * @param request request received from server
     * @param arg optional argument given during registration (iotcs_register_request_handler call)
     * @param response address of request to be filled
     */
    typedef void (*iotcs_resource_handler)(iotcs_request_message *request, void *arg, iotcs_message *response);

#if !defined IOTCS_MESSAGE_DISPATCHER || defined IOTCS_DOXYGEN

    /**
     * @brief Initializes a request dispatcher
     * @retval IOTCS_RESULT_OK if success
     * @retval IOTCS_RESULT_FAIL otherwise
     */
    iotcs_result iotcs_request_dispatcher_init(void);

    /**
     * @brief Finalizes a request dispatcher
     */
    void iotcs_request_dispatcher_finalize(void);

    /**
     * @brief Match the request to a handler and invoke the handler.
     * The function looks up for a request handler based on \a endpoint_id and \a url.
     * If no user callback is found then default handler (does nothing if not overridden)
     * will be invoked.
     * 
     * Before the handler invocation the given \a response_message is filled with zeros,
     * status code is set to \a 404 and \a response_message->base is initialized with
     * a pointer to default constant values (type = \a IOTCS_MESSAGE_RESPONSE, priority
     *  = \a IOTCS_MESSAGE_PRIORITY_HIGH, reliability = \a IOTCS_MESSAGE_RELIABILITY_BEST_EFFORT).
     * 
     * Next the handler is invoked. A handler is responsible for filling in \a response_message
     * with required data. If the handler performs no actions, server will get \a 404
     * code.
     * 
     * After handler invocation \a request_message is linked to \a response_message by
     * setting field \a response_message->u.response.request. This is required so when
     * \a response_message is sent, \a iotcs_request_message_free will be automatically
     * called in order to deallocate \a request_message resources. For operation without
     * asynchronous message dispatcher it means that if no \a iotcs_send was called then
     * user must explicitely release request by calling \a iotcs_request_message_free
     * with \a request_message as an argument. In asynchronous mode with message dispatcher everything
     * is sent and released automatically.
     * @param request_message The request message to be dispatched
     * @param response_message The response message to be filled by handler
     */
    void iotcs_request_dispatcher_dispatch(iotcs_request_message* request_message, iotcs_message* response_message);

#endif /* #ifndef IOTCS_MESSAGE_DISPATCHER */

    /**
     * @brief Register a handler for the given endpoint and path.
     * If endpoint is null, empty, or a wildcard ("*"), then the handler is 
     * registered as being used for all endpoints. If path is null, empty, or 
     * a wildcard ("*") then the handler is registered as the handler for any 
     * requests that do not have a more specific handler.
     * @param endpoint_id the endpoint id that has the given the resource path, 
     * or a wildcard ("*") for any endpoint.
     * @param path the resource path, or a wildcard ("*") for any resource.
     * @param handler the handler to invoke for requests to this endpoint and path
     * @param arg argument to be passed to handler
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if handler is NULL
     * @retval IOTCS_RESULT_OUT_OF_MEMORY if no additional memory can be allocated for use
     * @retval IOTCS_RESULT_OK if success
     */
    iotcs_result iotcs_register_request_handler(const char* endpoint_id, const char* path, iotcs_resource_handler handler, void* arg);

    /**
     * @brief Un-register the given handler for all endpoints and paths for which the handler may be registered.
     * @param handler the handler to un-register  
     * @retval IOTCS_RESULT_INVALID_ARGUMENT if handler is NULL
     * @retval IOTCS_RESULT_OK if the handler was unregistered successfully or
     * wasn't found in registered handlers
     * @retval IOTCS_RESULT_FAIL otherwise
     */
    iotcs_result iotcs_unregister_request_handler_all(iotcs_resource_handler handler);

    /**
     * @brief Un-register the handler for the given endpoint and path.
     * Either or both of the parameters may be a wildcard ("*"). Null or empty 
     * parameters are interpreted as a wildcard.
     * @param endpoint_id the endpoint id that has the given the resource path.
     * @param path the resource path.
     * @retval IOTCS_RESULT_OK if the handler was unregistered successfully or
     * wasn't found in registered handlers
     * @retval IOTCS_RESULT_FAIL otherwise
     */
    iotcs_result iotcs_unregister_request_handler(const char* endpoint_id, const char* path);

    /**
     * @brief Lookup a iotcs_resource_handler for the given endpoint_id and path.
     * The lookup will return the most specific handler for the endpoint_id and 
     * path. If there is not a specific match for endpoint_id, the lookup will 
     * try to match ("*", path). Failing that, the lookup will return a handler 
     * for ("*", "*"), or the default handler if no handler for ("*","*") has 
     * been registered. 
     * Null or empty parameters are interpreted as a wildcard.
     * @param endpoint_id the endpoint id that has the given the resource path, 
     * or a wildcard ("*").
     * @param path the resource path, or a wildcard ("*").
     * @retval iotcs_resource_handler if success
     * @retval NULL otherwise
     */
    iotcs_resource_handler iotcs_get_request_handler(const char* endpoint_id, const char* path);

#ifdef	__cplusplus
}
#endif

#endif	/* IOTCS_MESSAGE_DISPATCHER_H_ */