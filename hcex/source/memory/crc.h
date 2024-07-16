#pragma once

/* ---------- prototypes/CRC.C */

void crc_new(uint32_t *crc_reference);
void crc_checksum_buffer(uint32_t *crc_reference, const void *buffer, size_t buffer_size);

