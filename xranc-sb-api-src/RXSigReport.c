/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-API"
 * 	found in "../xranc-sb-api/xRAN-API-IEs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#include "RXSigReport.h"

asn_TYPE_member_t asn_MBR_RXSigReport_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct RXSigReport, pci_arfcn),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PCI_ARFCN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pci-arfcn"
		},
	{ ATF_POINTER, 3, offsetof(struct RXSigReport, ecgi),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ECGI,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ecgi"
		},
	{ ATF_POINTER, 2, offsetof(struct RXSigReport, rsrp),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RSRP_Range,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rsrp"
		},
	{ ATF_POINTER, 1, offsetof(struct RXSigReport, rsrq),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_RSRQ_Range,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rsrq"
		},
};
static const int asn_MAP_RXSigReport_oms_1[] = { 1, 2, 3 };
static const ber_tlv_tag_t asn_DEF_RXSigReport_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_RXSigReport_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pci-arfcn */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ecgi */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* rsrp */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* rsrq */
};
asn_SEQUENCE_specifics_t asn_SPC_RXSigReport_specs_1 = {
	sizeof(struct RXSigReport),
	offsetof(struct RXSigReport, _asn_ctx),
	asn_MAP_RXSigReport_tag2el_1,
	4,	/* Count of tags in the map */
	asn_MAP_RXSigReport_oms_1,	/* Optional members */
	3, 0,	/* Root/Additions */
	4,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_RXSigReport = {
	"RXSigReport",
	"RXSigReport",
	&asn_OP_SEQUENCE,
	asn_DEF_RXSigReport_tags_1,
	sizeof(asn_DEF_RXSigReport_tags_1)
		/sizeof(asn_DEF_RXSigReport_tags_1[0]), /* 1 */
	asn_DEF_RXSigReport_tags_1,	/* Same as above */
	sizeof(asn_DEF_RXSigReport_tags_1)
		/sizeof(asn_DEF_RXSigReport_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_RXSigReport_1,
	4,	/* Elements count */
	&asn_SPC_RXSigReport_specs_1	/* Additional specs */
};

