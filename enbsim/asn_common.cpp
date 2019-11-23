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

#include "asn_common.h"

void make_ecgi(ECGI_t *dest, int enb_index) {
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
