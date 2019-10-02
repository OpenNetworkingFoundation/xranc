/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-PDU"
 * 	found in "../xranc-sb-api/xRAN-API-PDUs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#ifndef	_BearerReleaseInd_H_
#define	_BearerReleaseInd_H_


#include <asn_application.h>

/* Including external dependencies */
#include "CRNTI.h"
#include "ECGI.h"
#include <NativeInteger.h>
#include "ERAB-ID.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* BearerReleaseInd */
typedef struct BearerReleaseInd {
	CRNTI_t	 crnti;
	ECGI_t	 ecgi;
	long	 num_erabs;
	struct BearerReleaseInd__erab_ids {
		A_SEQUENCE_OF(ERAB_ID_t) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} erab_ids;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} BearerReleaseInd_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_BearerReleaseInd;
extern asn_SEQUENCE_specifics_t asn_SPC_BearerReleaseInd_specs_1;
extern asn_TYPE_member_t asn_MBR_BearerReleaseInd_1[4];

#ifdef __cplusplus
}
#endif

#endif	/* _BearerReleaseInd_H_ */
#include <asn_internal.h>
