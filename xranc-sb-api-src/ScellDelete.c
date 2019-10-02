/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-PDU"
 * 	found in "../xranc-sb-api/xRAN-API-PDUs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#include "ScellDelete.h"

static asn_TYPE_member_t asn_MBR_scells_ind_4[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_PCI_ARFCN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_scells_ind_tags_4[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_scells_ind_specs_4 = {
	sizeof(struct ScellDelete__scells_ind),
	offsetof(struct ScellDelete__scells_ind, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_scells_ind_4 = {
	"scells-ind",
	"scells-ind",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_scells_ind_tags_4,
	sizeof(asn_DEF_scells_ind_tags_4)
		/sizeof(asn_DEF_scells_ind_tags_4[0]) - 1, /* 1 */
	asn_DEF_scells_ind_tags_4,	/* Same as above */
	sizeof(asn_DEF_scells_ind_tags_4)
		/sizeof(asn_DEF_scells_ind_tags_4[0]), /* 2 */
	{ 0, 0, SEQUENCE_OF_constraint },
	asn_MBR_scells_ind_4,
	1,	/* Single element */
	&asn_SPC_scells_ind_specs_4	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_ScellDelete_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ScellDelete, crnti),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_CRNTI,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"crnti"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScellDelete, ecgi),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ECGI,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ecgi"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ScellDelete, scells_ind),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		0,
		&asn_DEF_scells_ind_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"scells-ind"
		},
};
static const ber_tlv_tag_t asn_DEF_ScellDelete_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ScellDelete_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* crnti */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ecgi */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* scells-ind */
};
asn_SEQUENCE_specifics_t asn_SPC_ScellDelete_specs_1 = {
	sizeof(struct ScellDelete),
	offsetof(struct ScellDelete, _asn_ctx),
	asn_MAP_ScellDelete_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ScellDelete = {
	"ScellDelete",
	"ScellDelete",
	&asn_OP_SEQUENCE,
	asn_DEF_ScellDelete_tags_1,
	sizeof(asn_DEF_ScellDelete_tags_1)
		/sizeof(asn_DEF_ScellDelete_tags_1[0]), /* 1 */
	asn_DEF_ScellDelete_tags_1,	/* Same as above */
	sizeof(asn_DEF_ScellDelete_tags_1)
		/sizeof(asn_DEF_ScellDelete_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ScellDelete_1,
	3,	/* Elements count */
	&asn_SPC_ScellDelete_specs_1	/* Additional specs */
};

