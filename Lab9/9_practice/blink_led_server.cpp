/*
 * You can write copyrights rules here. These rules will be copied into the outputs.
 */

/*
 * Generated by erpcgen 1.9.0 on Sun Apr 17 23:11:45 2022.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#include "blink_led_server.h"
#if ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_DYNAMIC
#include <new>
#include "erpc_port.h"
#endif
#include "erpc_manually_constructed.h"

#if 10900 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

using namespace erpc;
using namespace std;

#if ERPC_NESTED_CALLS_DETECTION
extern bool nestingDetection;
#endif

ERPC_MANUALLY_CONSTRUCTED_STATIC(LEDBlinkService_service, s_LEDBlinkService_service);



// Call the correct server shim based on method unique ID.
erpc_status_t LEDBlinkService_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory)
{
    erpc_status_t erpcStatus;
    switch (methodId)
    {
        case kLEDBlinkService_led3_change_id:
        {
            erpcStatus = led3_change_shim(codec, messageFactory, sequence);
            break;
        }

        default:
        {
            erpcStatus = kErpcStatus_InvalidArgument;
            break;
        }
    }

    return erpcStatus;
}

// Server shim for led3_change of LEDBlinkService interface.
erpc_status_t LEDBlinkService_service::led3_change_shim(Codec * codec, MessageBufferFactory *messageFactory, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;


    // startReadMessage() was already called before this shim was invoked.

    err = codec->getStatus();
    if (err == kErpcStatus_Success)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        led3_change();
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBuffer());
    }

    if (err == kErpcStatus_Success)
    {
        // preparing codec for serializing data
        codec->reset();

        // Build response message.
        codec->startWriteMessage(kReplyMessage, kLEDBlinkService_service_id, kLEDBlinkService_led3_change_id, sequence);

        err = codec->getStatus();
    }

    return err;
}

#if ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_DYNAMIC
erpc_service_t create_LEDBlinkService_service()
{
    return new (nothrow) LEDBlinkService_service();
}

void destroy_LEDBlinkService_service(erpc_service_t *service)
{
    if (*service)
    {
        delete service;
    }
}
#elif ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_STATIC
erpc_service_t create_LEDBlinkService_service()
{
    s_LEDBlinkService_service.construct();
    return s_LEDBlinkService_service.get();
}

void destroy_LEDBlinkService_service()
{
    s_LEDBlinkService_service.destroy();
}
#else
#warning "Unknown eRPC allocation policy!"
#endif
