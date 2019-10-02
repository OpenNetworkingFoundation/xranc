/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-API"
 * 	found in "../xranc-sb-api/xRAN-API-IEs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#ifndef	_PRBUsage_H_
#define	_PRBUsage_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* PRBUsage */
typedef struct PRBUsage {
	struct PRBUsage__prb_usage_dl {
		A_SEQUENCE_OF(long) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} prb_usage_dl;
	struct PRBUsage__prb_usage_ul {
		A_SEQUENCE_OF(long) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} prb_usage_ul;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} PRBUsage_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_PRBUsage;
extern asn_SEQUENCE_specifics_t asn_SPC_PRBUsage_specs_1;
extern asn_TYPE_member_t asn_MBR_PRBUsage_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _PRBUsage_H_ */
#include <asn_internal.h>
