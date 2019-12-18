/*
 * Copyright 2019-present Open Networking Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ASN_H
#define _ASN_H

#include <XRANCPDU.h>

/*  Test PLMN ID = Test MCC (001) + Test MNC (001) */
const uint8_t TEST_PLMNID[3] = {0x00, 0x10, 0x01};

#define XRAN_HEADER(pdu, NAME) \
{ \
    pdu->hdr.ver.buf = (uint8_t *)calloc(1, sizeof(char)); \
    *(pdu->hdr.ver.buf) = '5'; \
    pdu->hdr.ver.size = sizeof(char); \
    pdu->hdr.api_id = XRANC_API_ID_ ## NAME; \
    pdu->body.present = XRANCPDUBody_PR_ ## NAME; \
}

#define XRAN_CRNTI(pdu, NAME, crnti) \
{ \
    pdu->body.choice.NAME.crnti.buf = (uint8_t *)calloc(1, sizeof(uint16_t)); \
    pdu->body.choice.NAME.crnti.size = sizeof(uint16_t); \
    *((uint16_t *)(pdu->body.choice.NAME.crnti.buf)) = htons(crnti); \
}

#define XRAN_ECGI(pdu, NAME, enb_index) \
{ \
    make_ecgi(&pdu->body.choice.NAME.ecgi, enb_index); \
}

inline void make_ecgi(ECGI_t *dest, int enb_index) {
    dest->pLMN_Identity.buf = (uint8_t *)calloc(1, sizeof(PLMN_Identity_t));
    memcpy(dest->pLMN_Identity.buf, TEST_PLMNID, 3);
    dest->pLMN_Identity.size = 3;
    dest->eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, 4);
    dest->eUTRANcellIdentifier.buf[0] = 0;
    dest->eUTRANcellIdentifier.buf[1] = 0;
    dest->eUTRANcellIdentifier.buf[2] = enb_index;
    dest->eUTRANcellIdentifier.buf[3] = 0;
    dest->eUTRANcellIdentifier.size = 4;
}

inline void copy_crnti(CRNTI_t *dest, CRNTI_t *src) {
    dest->buf = (uint8_t *)calloc(1, src->size);
    memcpy(dest->buf, src->buf, src->size);
    dest->size = src->size;
}

inline void copy_ecgi(ECGI_t *dest, ECGI_t *src) {
    dest->pLMN_Identity.buf = (uint8_t *)calloc(1, src->pLMN_Identity.size);
    memcpy(dest->pLMN_Identity.buf, src->pLMN_Identity.buf, src->pLMN_Identity.size);
    dest->pLMN_Identity.size = src->pLMN_Identity.size;
    dest->eUTRANcellIdentifier.buf = (uint8_t *)calloc(1, src->eUTRANcellIdentifier.size);
    memcpy(dest->eUTRANcellIdentifier.buf, src->eUTRANcellIdentifier.buf, src->eUTRANcellIdentifier.size);
    dest->eUTRANcellIdentifier.size = src->eUTRANcellIdentifier.size;
}

#endif
