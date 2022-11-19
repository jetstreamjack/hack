#include <iostream>
#include <string_view>
#include<string>
#include "general.h"
#include "subscriber.h"
#include "nlohmann/json.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Files required for transport initialization. */
#include <coresrv/nk/transport-kos.h>
#include <coresrv/sl/sl_api.h>

/* Description of the server interface used by the `client` entity. */
#include <mqtt_subscriber/Ping.idl.h>

#include <assert.h>



using namespace std::literals;
using json = nlohmann::json;
constexpr auto Topic = "my/awesome/topic"sv;

Subscriber::Subscriber(const char *id, const char *host, int port)
    : mosquittopp(id)
{
    std::cout << app::AppTag << "Connecting to MQTT Broker with address "
              << host << " and port " << port << std::endl;

    const int keepAlive = 60;

    connect(host, port, keepAlive);
}

void Subscriber::on_connect(int rc)
{
    std::cout << app::AppTag << "Subscriber connected with code "
              << rc << std::endl;

    if (rc == 0)
    {
        subscribe(NULL, Topic.data());
    }
}

void Subscriber::on_message(const struct mosquitto_message *message)
{
    if (Topic == message->topic)
    {
        const std::string payload{reinterpret_cast<char*>(message->payload),
                                       static_cast<size_t>(message->payloadlen)};
        std::cout << app::AppTag << "Got message with topic: " << message->topic
                  << ", payload: " << payload << std::endl;


        NkKosTransport transport;
    struct mqtt_subscriber_Ping_proxy proxy;
    int i;

    fprintf(stderr, "Hello I'm client\n");

    /**
     * Get the client IPC handle of the connection named
     * "server_connection".
     */
    Handle handle = ServiceLocatorConnect("server_connection");
    assert(handle != INVALID_HANDLE);

    /* Initialize IPC transport for interaction with the server entity. */
    NkKosTransport_Init(&transport, handle, NK_NULL, 0);

    /**
     * Get Runtime Interface ID (RIID) for interface mqtt_subscriber.Ping.ping.
     * Here ping is the name of the mqtt_subscriber.Ping component instance,
     * mqtt_subscriber.Ping.ping is the name of the Ping interface implementation.
     */
    nk_iid_t riid = ServiceLocatorGetRiid(handle, "mqtt_subscriber.Ping.ping");
    assert(riid != INVALID_RIID);

    /**
     * Initialize proxy object by specifying transport (&transport)
     * and server interface identifier (riid). Each method of the
     * proxy object will be implemented by s NkKosTransport transport;
    struct mqtt_subscriber_Ping_proxy proxy;
    int i;

    fprintf(stderr, "Hello I'm client\n");

    /**
     * Get the client IPC handle of the connection named
     * "server_connection".
     */
     handle = ServiceLocatorConnect("server_connection");
    assert(handle != INVALID_HANDLE);

    /* Initialize IPC transport for interaction with the server entity. */
    NkKosTransport_Init(&transport, handle, NK_NULL, 0);

    /**
     * Get Runtime Interface ID (RIID) for interface mqtt_subscriber.Ping.ping.
     * Here ping is the name of the mqtt_subscriber.Ping component instance,
     * mqtt_subscriber.Ping.ping is the name of the Pinending a request to the server.
     */
    mqtt_subscriber_Ping_proxy_init(&proxy, &transport.base, riid);

    /* Request and response structures */
    mqtt_subscriber_Ping_Ping_req req;
    mqtt_subscriber_Ping_Ping_res res;

    /* Test loop. */
    req.value = std::stoi(payload);
    req.result=std::stoi(payload)+1;
    //for (i = 0; i < 10; ++i)
    {
        /**
         * Call Ping interface method.
         * Server will be sent a request for calling Ping interface method
         * ping_comp.ping_impl with the value argument. Calling thread is locked
         * until a response is received from the server.
         */
        if (mqtt_subscriber_Ping_Ping(&proxy.base, &req, NULL, &res, NULL) == rcOk) 

        {
        
            /**
             * Print result value from response
             * (result is the output argument of the Ping method).
             */
            //fprintf(stderr, "result = %d\n", (int) res.result);
            /**
             * Include received result value into value argument
             * to resend to server in next iteration.
             */
            //req.value = res.result+1;

        }
        else
            fprintf(stderr, "Failed to call mqtt_subscriber.Ping.Ping()\n");
    }




    }

}

void Subscriber::on_subscribe(__rtl_unused int        mid,
                              __rtl_unused int        qos_count,
                              __rtl_unused const int *granted_qos)
{
    std::cout << app::AppTag << "Subscription succeeded." << std::endl;
}
