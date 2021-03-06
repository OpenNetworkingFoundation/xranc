/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-PDU"
 * 	found in "../xranc-sb-api/xRAN-API-PDUs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#include "XRANCPDUHdr.h"

asn_TYPE_member_t asn_MBR_XRANCPDUHdr_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct XRANCPDUHdr, ver),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_UTF8String,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ver"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct XRANCPDUHdr, api_id),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_XRANC_API_ID,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"api-id"
		},
};
static const ber_tlv_tag_t asn_DEF_XRANCPDUHdr_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_XRANCPDUHdr_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ver */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* api-id */
};
asn_SEQUENCE_specifics_t asn_SPC_XRANCPDUHdr_specs_1 = {
	sizeof(struct XRANCPDUHdr),
	offsetof(struct XRANCPDUHdr, _asn_ctx),
	asn_MAP_XRANCPDUHdr_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_XRANCPDUHdr = {
	"XRANCPDUHdr",
	"XRANCPDUHdr",
	&asn_OP_SEQUENCE,
	asn_DEF_XRANCPDUHdr_tags_1,
	sizeof(asn_DEF_XRANCPDUHdr_tags_1)
		/sizeof(asn_DEF_XRANCPDUHdr_tags_1[0]), /* 1 */
	asn_DEF_XRANCPDUHdr_tags_1,	/* Same as above */
	sizeof(asn_DEF_XRANCPDUHdr_tags_1)
		/sizeof(asn_DEF_XRANCPDUHdr_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_XRANCPDUHdr_1,
	2,	/* Elements count */
	&asn_SPC_XRANCPDUHdr_specs_1	/* Additional specs */
};

