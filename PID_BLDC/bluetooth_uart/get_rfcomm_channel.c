#include "main.h"

int get_rfcomm_channel(bdaddr_t mac_address)
    {
        int channel = -1;
        sdp_session_t *sdp_sesh = sdp_connect(BDADDR_ANY, &mac_address, SDP_RETRY_IF_BUSY);//connect to sdp server
        if(sdp_sesh == NULL)
            {
                perror("sdp_connect");
                return channel;
            }
        uuid_t uuid;
        sdp_uuid16_create(&uuid, SERIAL_PORT_SVCLASS_ID);//create uuid for cereal protocol SPP
        sdp_list_t *search_list = NULL;
        search_list = sdp_list_append(search_list, &uuid);//add uuid/service into search list

        uint32_t attr = SDP_ATTR_PROTO_DESC_LIST;//describes what attr u want from a particular service
        sdp_list_t *search_attr = NULL;
        search_attr = sdp_list_append(search_attr, &attr);//adds  attribute to search list
        
        sdp_list_t *response = NULL;
        int req = sdp_service_search_attr_req(sdp_sesh, search_list, SDP_ATTR_REQ_INDIVIDUAL, search_attr, &response);
        if (req < 0)
            {
                printf("SPP service request failed\n");
                goto sdp_serv_req;
            }

        if (!response)
            {
                printf("SPP service not found\n");
                goto sdp_serv_req;
            }
        
        sdp_list_t *protocol = NULL;
        int proto_ret = sdp_get_access_protos((sdp_record_t*)response->data, &protocol);
        if (proto_ret < 0 || !protocol)
            {
                printf("Failed to obtain SPP protocol information\n");
                goto sdp_proto_req;;
            }
        channel = sdp_get_proto_port(protocol, RFCOMM_UUID);

        sdp_list_free(protocol, 0);
        sdp_proto_req:
        sdp_list_free(response, (sdp_free_func_t)sdp_record_free);
        sdp_serv_req:
        sdp_list_free(search_list, 0);
        sdp_list_free(search_attr, 0);
        sdp_close(sdp_sesh);

        if(channel <= 0)
            printf("no rfcomm\n");
        else
            printf("SPP found, RFCOMM channel = %d\n", channel);
        return channel;
    }