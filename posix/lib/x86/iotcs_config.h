/**
 * This set of compile-time options may be used to enable
 * or disable features selectively
 */
#ifndef IOTCS_CONFIG_H
#define IOTCS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ==================================================== 
 * Base library configuration 
 * ==================================================== 
 */

/**
 * Enable tread safety for Messaging API
 */
#define IOTCS_MESSAGING_THREAD_SAFETY

/**
 * Enable async message dispatcher support
 * Requires: IOTCS_MESSAGING_THREAD_SAFETY enabled
 */
#define IOTCS_MESSAGE_DISPATCHER

/**
 * Enable Virtualization API support
 * Requires: IOTCS_MESSAGE_DISPATCHER enabled
 */
#define IOTCS_VIRTUALIZATION_SUPPORT

/**
 * Enable indirect activation support
 */
#define IOTCS_GATEWAY

/**
 * ==================================================== 
 * Shared library settings
 * ==================================================== 
 */

/**
 * Enable static heap instead on libc's malloc/free
 * Requires: IOTCS_MESSAGING_THREAD_SAFETY disabled
 */
//#define IOTCS_USE_STATIC_HEAP

/**
 * Override static heap size in bytes (by default 8192)
 * Requires: IOTCS_USE_STATIC_HEAP enabled
 */
//#define IOTCS_STATIC_HEAP_SIZE 8192

/**
 * Enable creation of draft Device Models
 */
//#define IOTCS_USE_DRAFT_DEVICE_MODELS

/**
 * Enable static usage time from server
 */
//#define IOTCS_USE_SERVER_TIME

/**
 * Specify to enable device model caching on local file system
 */
//#define IOTCS_DEVICE_MODEL_DIR ""

/**
 * Enable debug mode
 */
//#define IOTCS_DEBUG

/**
 * Disable mqtt support
 */
//#define IOTCS_DISABLE_MQTT

/**
 * Disable mqtt accepted bytes support
 * Requires: IOTCS_DISABLE_MQTT disabled
 */
//#define IOTCS_DISABLE_MQTT_ACCEPTED_BYTES

/**
 * Disable http support
 */
//#define IOTCS_DISABLE_HTTP

/**
 * Enable the long polling implementation
 */
#define IOTCS_LONG_POLLING

/**
 * Enable diagnostic capability API usage in library
 */
#define IOTCS_USE_DIAGNOSTIC_CAPABILITY

/**
 * The size of buffer for device model filename in bytes
 */
#define IOTCS_DEVICE_MODEL_FILENAME_BUFFER_SIZE 128

/**
 * The size of buffer for device model capability server response in bytes
 */
#define IOTCS_CAPABILITY_RESPONSE_BUFFER_SIZE 1024

/**
 * The polling timeout in milliseconds for internal async message dispatcher
 */
#define IOTCS_POLLING_TIMEOUT_MS 5000

/**
 * The maximum number messages to send in one request
 */
#define IOTCS_MAX_MESSAGES_FOR_SEND 5

/**
 * The size of buffer for reason of async message send failure in bytes
 */
#define IOTCS_ASYNC_FAIL_REASON_BUFFER_SIZE 256

/**
 * The size of buffer for request message in bytes
 */
#define IOTCS_REQUEST_MESSAGE_BUFFER_SIZE 512

/**
 * The number of request messages
 */
#define IOTCS_REQUEST_MESSAGE_NUMBER 4

/**
 * The maximum number of resource for registration
 */
#define IOTCS_MAX_RESOURCE_NUMBER 6

/**
 * The server host buffer length in bytes
 * The default value is 128 + 14, where 128 is got from TAM store
 * and 14 is the length of string 'server.host=' + '/n' + '/0'
 */
#define IOTCS_SERVER_HOST_BUFFER_LENGTH 142

/**
 * The client ID buffer length in bytes
 * The default value is 20 + 12, where 12 is the length of
 * string 'client.id'= + '/n' + '/0'
 */
#define IOTCS_CLIENT_ID_BUFFER_LENGTH 76

/**
 * The shared secret buffer length in bytes
 * The default value is 50 + 15, where 15 is the length
 * string 'client.secret' + '/n' + '/0'
 */
#define IOTCS_SHARED_SECRET_BUFFER_LENGTH 65

/**
 * The signature buffer length in bytes
 */
#define IOTCS_SIGNATURE_BUFFER_LENGTH 256

/**
 * The assets signature buffer length in bytes
 */
#define IOTCS_ASSETS_SIGNATURE_BUFFER_LENGTH 256

/**
 * The public key buffer length in bytes
 * The default value is 350. It's enough for public key with length 2048 bits
 */
#define IOTCS_PUBLIC_KEY_BUFFER_LENGTH 350

/**
 * The server port length in bytes
 * The default value is 19, where 12 is the length of 'server.port=' + 5
 * is max port value '65535' + 1('/n') + 1('/0') = 19
 */
#define IOTCS_SERVER_PORT_LENGTH 19

/**
 * The payload buffer size in bytes. It is used for storing messages payload.
 * The less then IOTCS_MIN_PAYLOAD_BUFFER_SIZE value is not acceptable 
 * for IOTCS_PAYLOAD_BUFFER_SIZE and compile time error is generated in this case. 
 * Also could be reused for other operation (e.g. reading of the trusted assets store).
 */
#define IOTCS_PAYLOAD_BUFFER_SIZE 4700

/**
 * Buffer is used for MQTT frames.
 * NOTE: Publish frames doesn't contain a payload, the payload is written to socket from payload buffer directly.
 */
#define IOTCS_MQTT_SEND_BUFFER_SIZE 700

/**
 * The mqtt topic name buffer size
 */
#define IOTCS_MQTT_SUB_TOPIC_BUFFER_SIZE (32 + IOTCS_CLIENT_ID_BUFFER_LENGTH)

/**
 * The timeout for waiting of the response for mqtt request
 */
#define IOTCS_MQTT_CMD_TIMEOUT_MS 10000

/**
 * Represents how much time the library will provide to user to set the resource handlers.
 * NOTE: Requests without user handler could be processed later during this time.
 */
#define IOTCS_SETTLE_TIME_MS 5000

/**
 * The size for default buffer used for logging
 */
#define IOTCS_LOG_MSG_BUFFER_SIZE 180

/**
 * Represents how much jsmntok_t instances should be allocated for jsmn json parser.
 */
#define IOTCS_JSON_TOKEN_NUM 512

/**
 * ==================================================== 
 * Logging settings
 * ==================================================== 
 */

/**
 * Supported log levels:
 * 0 = none|no       - No log
 * 1 = critical|crit - Critical log entry: unrecoverable internal error - library can't work properly anymore
 * 2 = error|err     - Error log entry: recoverable error, user action is required
 * 3 = warning|warn  - Warning log entry: recoverable error, no user action is required
 * 4 = info          - Information log entry: not an error
 * 5 = debug|dbg     - Debug log entry
 * 5 = all
 */

/**
 * The global library log level
 */
#define IOTCS_LOG_LEVEL 4

/**
 * Enable include base file name and line number in the log entry
 * It is implicitly turned on by default for debug mode
 */
//#define IOTCS_LOG_USE_FILE_LINE 

/**
 * The iotcs module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_CORE IOTCS_LOG_LEVEL

/**
 * The device model channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_DM IOTCS_LOG_LEVEL

/**
 * The external module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_EXT IOTCS_LOG_LEVEL

/**
 * The json module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_JSON IOTCS_LOG_LEVEL

/**
 * The messaging module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_MSG IOTCS_LOG_LEVEL

/**
 * The protocol module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PROTO IOTCS_LOG_LEVEL

/**
 * The TAM module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_TAM IOTCS_LOG_LEVEL

/**
 * The util module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_UTIL IOTCS_LOG_LEVEL

/**
 * The logging module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_LOG IOTCS_LOG_LEVEL

/**
 * The port blocking queue module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_QUEUE IOTCS_LOG_LEVEL

/**
 * The port crypto module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_CRYPTO IOTCS_LOG_LEVEL

/**
 * The port TAM module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_TAM IOTCS_LOG_LEVEL

/**
 * The port diagnostic module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_DIAG IOTCS_LOG_LEVEL

/**
 * The port memory module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_MEM IOTCS_LOG_LEVEL

/**
 * The port mutex module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_MUTEX IOTCS_LOG_LEVEL

/**
 * The port SSL module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_SSL IOTCS_LOG_LEVEL

/**
 * The port system module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_SYSTEM IOTCS_LOG_LEVEL

/**
 * The port thread module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_THREAD IOTCS_LOG_LEVEL

/**
 * The port MQTT module channel log level
 */
#define IOTCS_LOG_LEVEL_CHANNEL_PORT_MQTT IOTCS_LOG_LEVEL

/**
 * ====================================================
 * Library posix specific port layer settings
 * ==================================================== 
 */


#ifdef __cplusplus
}
#endif

#endif /* IOTCS_CONFIG_H */
