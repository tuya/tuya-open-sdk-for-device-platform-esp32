/**
 * @file tkl_thread.c
 * @brief this file was auto-generated by tuyaos v&v tools, developer can add implements between BEGIN and END
 * 
 * @warning: changes between user 'BEGIN' and 'END' will be keeped when run tuyaos v&v tools
 *           changes in other place will be overwrited and lost
 *
 * @copyright Copyright 2020-2021 Tuya Inc. All Rights Reserved.
 * 
 */

// --- BEGIN: user defines and implements ---
#include "tkl_thread.h"
#include "tuya_error_code.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// --- END: user defines and implements ---

/**
* @brief Create thread
*
* @param[out] thread: thread handle
* @param[in] name: thread name
* @param[in] stack_size: stack size of thread
* @param[in] priority: priority of thread,please ref to tkl thread priority define in tuya_cloud_types.h
* @param[in] func: the main thread process function
* @param[in] arg: the args of the func, can be null
*
* @note This API is used for creating thread.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_create(TKL_THREAD_HANDLE* thread,
                              const char* name,
                              uint32_t stack_size,
                              uint32_t priority,
                              const THREAD_FUNC_T func,
                              void* const arg)
{
    // --- BEGIN: user implements ---
    if (!thread) {
        return OPRT_INVALID_PARM;
    }
    
    BaseType_t ret = 0;
    #if CONFIG_IDF_TARGET_ESP32
    #elif CONFIG_IDF_TARGET_ESP32S3
        stack_size += 1024;
    #else

    #endif
    ret = xTaskCreate(func, name, stack_size / sizeof(portSTACK_TYPE), (void *const)arg, priority, (TaskHandle_t * const)thread);
    if (ret != pdPASS) {
        return OPRT_OS_ADAPTER_THRD_CREAT_FAILED;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Terminal thread and release thread resources
*
* @param[in] thread: thread handle
*
* @note This API is used to terminal thread and release thread resources.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_release(const TKL_THREAD_HANDLE thread)
{
    // --- BEGIN: user implements ---
    if (!thread) {
        return OPRT_INVALID_PARM;
    }
    
    vTaskDelete((TaskHandle_t)thread);
    
    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Get the thread stack's watermark
*
* @param[in] thread: thread handle
* @param[out] watermark: watermark in Bytes
*
* @note This API is used to get the thread stack's watermark.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_get_watermark(const TKL_THREAD_HANDLE thread, uint32_t* watermark)
{
    // --- BEGIN: user implements ---
    if (NULL == thread || NULL == watermark) {
        return OPRT_INVALID_PARM;
    }
    *watermark = uxTaskGetStackHighWaterMark(thread) * sizeof( StackType_t );
    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Get the thread thread handle
*
* @param[out] thread: thread handle
*
* @note This API is used to get the thread handle.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_get_id(TKL_THREAD_HANDLE *thread)
{
    // --- BEGIN: user implements ---
    *thread = (TKL_THREAD_HANDLE)xTaskGetCurrentTaskHandle();
    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Set name of self thread
*
* @param[in] name: thread name
*
* @note This API is used to set name of self thread.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_set_self_name(const char* name)
{
    // --- BEGIN: user implements ---
    if (!name) {
        return OPRT_INVALID_PARM;
    }

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Check thread is self thread
*
* @param[in] thread: thread handle
* @param[out] is_self: is self thread or not
*
* @note This API is used to check thread is self thread.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_is_self(TKL_THREAD_HANDLE thread, BOOL_T* is_self)
{
    // --- BEGIN: user implements ---
    if (NULL == thread || NULL == is_self) {
        return OPRT_INVALID_PARM;
    }

    TKL_THREAD_HANDLE self_handle = (TKL_THREAD_HANDLE)xTaskGetCurrentTaskHandle();
    if (NULL == self_handle) {
        return OPRT_OS_ADAPTER_THRD_JUDGE_SELF_FAILED;
    }

    *is_self = (thread == self_handle);
	
    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Get thread priority
*
* @param[in] thread: thread handle, If NULL indicates the current thread
* @param[in] priority: thread priority
*
* @note This API is used to get thread priority.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_get_priority(TKL_THREAD_HANDLE thread, int *priority)
{
    // --- BEGIN: user implements ---
    if (NULL == thread || NULL == priority) {
        return OPRT_INVALID_PARM;
    }

    *priority = (uint32_t)uxTaskPriorityGet((TaskHandle_t)thread);

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Set thread priority
*
* @param[in] thread: thread handle, If NULL indicates the current thread
* @param[in] priority: thread priority
*
* @note This API is used to Set thread priority.
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_set_priority(TKL_THREAD_HANDLE thread, int priority)
{
    // --- BEGIN: user implements ---
    if (NULL == thread) {
        return OPRT_INVALID_PARM;
    }

    vTaskPrioritySet((TaskHandle_t)thread, priority);

    return OPRT_OK;
    // --- END: user implements ---
}

/**
* @brief Diagnose the thread(dump task stack, etc.)
*
* @param[in] thread: thread handle
*
* @return OPRT_OK on success. Others on error, please refer to tuya_error_code.h
*/
OPERATE_RET tkl_thread_diagnose(TKL_THREAD_HANDLE thread)
{
    // --- BEGIN: user implements ---    
    return OPRT_OK;
    // --- END: user implements ---
}

