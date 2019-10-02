/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-API"
 * 	found in "../xranc-sb-api/xRAN-API-IEs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#include "MeasObject.h"

static asn_TYPE_member_t asn_MBR_meas_cells_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasObject__meas_cells, pci),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PhysCellId,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pci"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasObject__meas_cells, cellIndividualOffset),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Q_OffsetRange,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"cellIndividualOffset"
		},
};
static const int asn_MAP_meas_cells_oms_3[] = { 1 };
static const ber_tlv_tag_t asn_DEF_meas_cells_tags_3[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_meas_cells_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pci */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* cellIndividualOffset */
};
static asn_SEQUENCE_specifics_t asn_SPC_meas_cells_specs_3 = {
	sizeof(struct MeasObject__meas_cells),
	offsetof(struct MeasObject__meas_cells, _asn_ctx),
	asn_MAP_meas_cells_tag2el_3,
	2,	/* Count of tags in the map */
	asn_MAP_meas_cells_oms_3,	/* Optional members */
	1, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_meas_cells_3 = {
	"meas-cells",
	"meas-cells",
	&asn_OP_SEQUENCE,
	asn_DEF_meas_cells_tags_3,
	sizeof(asn_DEF_meas_cells_tags_3)
		/sizeof(asn_DEF_meas_cells_tags_3[0]) - 1, /* 1 */
	asn_DEF_meas_cells_tags_3,	/* Same as above */
	sizeof(asn_DEF_meas_cells_tags_3)
		/sizeof(asn_DEF_meas_cells_tags_3[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_meas_cells_3,
	2,	/* Elements count */
	&asn_SPC_meas_cells_specs_3	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_MeasObject_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasObject, dl_freq),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ARFCN_Value,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"dl-freq"
		},
	{ ATF_POINTER, 1, offsetof(struct MeasObject, meas_cells),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_meas_cells_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"meas-cells"
		},
};
static const int asn_MAP_MeasObject_oms_1[] = { 1 };
static const ber_tlv_tag_t asn_DEF_MeasObject_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MeasObject_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* dl-freq */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* meas-cells */
};
asn_SEQUENCE_specifics_t asn_SPC_MeasObject_specs_1 = {
	sizeof(struct MeasObject),
	offsetof(struct MeasObject, _asn_ctx),
	asn_MAP_MeasObject_tag2el_1,
	2,	/* Count of tags in the map */
	asn_MAP_MeasObject_oms_1,	/* Optional members */
	1, 0,	/* Root/Additions */
	2,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MeasObject = {
	"MeasObject",
	"MeasObject",
	&asn_OP_SEQUENCE,
	asn_DEF_MeasObject_tags_1,
	sizeof(asn_DEF_MeasObject_tags_1)
		/sizeof(asn_DEF_MeasObject_tags_1[0]), /* 1 */
	asn_DEF_MeasObject_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasObject_tags_1)
		/sizeof(asn_DEF_MeasObject_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MeasObject_1,
	2,	/* Elements count */
	&asn_SPC_MeasObject_specs_1	/* Additional specs */
};

