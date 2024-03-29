/*
 * Generated by erpcgen 1.9.0 on Tue May 17 21:35:50 2022.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#if !defined(_bbcar_control_server_h_)
#define _bbcar_control_server_h_

#ifdef __cplusplus
#include "erpc_server.h"
#include "erpc_codec.h"
extern "C"
{
#include "bbcar_control.h"
#include <stdint.h>
#include <stdbool.h>
}

#if 10900 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif


/*!
 * @brief Service subclass for BBCarService.
 */
class BBCarService_service : public erpc::Service
{
public:
    BBCarService_service() : Service(kBBCarService_service_id) {}

    /*! @brief Call the correct server shim based on method unique ID. */
    virtual erpc_status_t handleInvocation(uint32_t methodId, uint32_t sequence, erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory);

private:
    /*! @brief Server shim for stop of BBCarService interface. */
    erpc_status_t stop_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for goStraight of BBCarService interface. */
    erpc_status_t goStraight_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);

    /*! @brief Server shim for turn of BBCarService interface. */
    erpc_status_t turn_shim(erpc::Codec * codec, erpc::MessageBufferFactory *messageFactory, uint32_t sequence);
};

extern "C" {
#else
#include "bbcar_control.h"
#endif // __cplusplus

typedef void * erpc_service_t;

erpc_service_t create_BBCarService_service(void);

#if ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_DYNAMIC
void destroy_BBCarService_service(erpc_service_t *service);
#elif ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_STATIC
void destroy_BBCarService_service(void);
#else
#warning "Unknown eRPC allocation policy!"
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _bbcar_control_server_h_
