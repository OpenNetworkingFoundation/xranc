/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-PDU"
 * 	found in "../xranc-sb-api/xRAN-API-PDUs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#ifndef	_BearerAdmissionRequest_H_
#define	_BearerAdmissionRequest_H_


#include <asn_application.h>

/* Including external dependencies */
#include "CRNTI.h"
#include "ECGI.h"
#include "UEAMBR.h"
#include <NativeInteger.h>
#include "ERABParams.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* BearerAdmissionRequest */
typedef struct BearerAdmissionRequest {
	CRNTI_t	 crnti;
	ECGI_t	 ecgi;
	UEAMBR_t	 ue_ambr;
	long	 num_erabs;
	ERABParams_t	 erab_params;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BearerAdmissionRequest_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BearerAdmissionRequest;
extern asn_SEQUENCE_specifics_t asn_SPC_BearerAdmissionRequest_specs_1;
extern asn_TYPE_member_t asn_MBR_BearerAdmissionRequest_1[5];

#ifdef __cplusplus
}
#endif

#endif	/* _BearerAdmissionRequest_H_ */
#include <asn_internal.h>
