#include "cseries/cseries.h"
#include "bungie_net/common/message_header.h"

typedef unsigned short message_header;

unsigned short *create_message(unsigned char type, void *data, unsigned short data_size, void *buffer, unsigned short buffer_size);
void *initialize_message_buffer(void *buffer, int32_t buffer_size, int32_t *maximum_content_size);
unsigned short *prepare_buffer_to_send(unsigned char type, void *buffer, unsigned short content_size);
void build_message_header(unsigned short *msg, unsigned short length, unsigned char type, unsigned char flags);
void byte_swap_message_header(unsigned short *header, int32_t desired_order);
