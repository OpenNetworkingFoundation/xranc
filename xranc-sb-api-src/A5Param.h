/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-API"
 * 	found in "../xranc-sb-api/xRAN-API-IEs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#ifndef	_A5Param_H_
#define	_A5Param_H_


#include <asn_application.h>

/* Including external dependencies */
#include "ThresholdEUTRA.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A5Param */
typedef struct A5Param {
	ThresholdEUTRA_t	 a5_Threshold1;
	ThresholdEUTRA_t	 a5_Threshold2;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} A5Param_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_A5Param;
extern asn_SEQUENCE_specifics_t asn_SPC_A5Param_specs_1;
extern asn_TYPE_member_t asn_MBR_A5Param_1[2];

#ifdef __cplusplus
}
#endif

#endif	/* _A5Param_H_ */
#include <asn_internal.h>
