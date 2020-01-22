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

#ifndef __UE_H
#define __UE_H

#include <XRANCPDU.h>
#include "client.h"

void ue_admission_request(XRANCPDU *pdu, client_t *client);
void ue_admission_status(XRANCPDU *pdu, client_t *client);
void ue_context_update(XRANCPDU *pdu, client_t *client);
#endif
