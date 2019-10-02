/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-API"
 * 	found in "../xranc-sb-api/xRAN-API-IEs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#include "MeasID.h"

static asn_oer_constraints_t asn_OER_type_action_constr_4 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_action_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_addmeasid_5[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_addmeasid_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_addmeasid_specs_5 = {
	sizeof(struct MeasID__action__addmeasid),
	offsetof(struct MeasID__action__addmeasid, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_addmeasid_5 = {
	"addmeasid",
	"addmeasid",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_addmeasid_tags_5,
	sizeof(asn_DEF_addmeasid_tags_5)
		/sizeof(asn_DEF_addmeasid_tags_5[0]) - 1, /* 1 */
	asn_DEF_addmeasid_tags_5,	/* Same as above */
	sizeof(asn_DEF_addmeasid_tags_5)
		/sizeof(asn_DEF_addmeasid_tags_5[0]), /* 2 */
	{ 0, 0, SEQUENCE_OF_constraint },
	asn_MBR_addmeasid_5,
	1,	/* Single element */
	&asn_SPC_addmeasid_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_delmeasid_7[] = {
	{ ATF_POINTER, 0, 0,
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		""
		},
};
static const ber_tlv_tag_t asn_DEF_delmeasid_tags_7[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_SET_OF_specifics_t asn_SPC_delmeasid_specs_7 = {
	sizeof(struct MeasID__action__delmeasid),
	offsetof(struct MeasID__action__delmeasid, _asn_ctx),
	0,	/* XER encoding is XMLDelimitedItemList */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_delmeasid_7 = {
	"delmeasid",
	"delmeasid",
	&asn_OP_SEQUENCE_OF,
	asn_DEF_delmeasid_tags_7,
	sizeof(asn_DEF_delmeasid_tags_7)
		/sizeof(asn_DEF_delmeasid_tags_7[0]) - 1, /* 1 */
	asn_DEF_delmeasid_tags_7,	/* Same as above */
	sizeof(asn_DEF_delmeasid_tags_7)
		/sizeof(asn_DEF_delmeasid_tags_7[0]), /* 2 */
	{ 0, 0, SEQUENCE_OF_constraint },
	asn_MBR_delmeasid_7,
	1,	/* Single element */
	&asn_SPC_delmeasid_specs_7	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_action_4[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasID__action, choice.addmeasid),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_addmeasid_5,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"addmeasid"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasID__action, choice.delmeasid),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_delmeasid_7,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"delmeasid"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasID__action, choice.hototarget),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_BOOLEAN,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"hototarget"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_action_tag2el_4[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* addmeasid */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* delmeasid */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* hototarget */
};
static asn_CHOICE_specifics_t asn_SPC_action_specs_4 = {
	sizeof(struct MeasID__action),
	offsetof(struct MeasID__action, _asn_ctx),
	offsetof(struct MeasID__action, present),
	sizeof(((struct MeasID__action *)0)->present),
	asn_MAP_action_tag2el_4,
	3,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_action_4 = {
	"action",
	"action",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_action_constr_4, &asn_PER_type_action_constr_4, CHOICE_constraint },
	asn_MBR_action_4,
	3,	/* Elements count */
	&asn_SPC_action_specs_4	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_MeasID_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct MeasID, measobject_id),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"measobject-id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasID, reportconfig_id),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reportconfig-id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct MeasID, action),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_action_4,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"action"
		},
};
static const ber_tlv_tag_t asn_DEF_MeasID_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_MeasID_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* measobject-id */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* reportconfig-id */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* action */
};
asn_SEQUENCE_specifics_t asn_SPC_MeasID_specs_1 = {
	sizeof(struct MeasID),
	offsetof(struct MeasID, _asn_ctx),
	asn_MAP_MeasID_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_MeasID = {
	"MeasID",
	"MeasID",
	&asn_OP_SEQUENCE,
	asn_DEF_MeasID_tags_1,
	sizeof(asn_DEF_MeasID_tags_1)
		/sizeof(asn_DEF_MeasID_tags_1[0]), /* 1 */
	asn_DEF_MeasID_tags_1,	/* Same as above */
	sizeof(asn_DEF_MeasID_tags_1)
		/sizeof(asn_DEF_MeasID_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_MeasID_1,
	3,	/* Elements count */
	&asn_SPC_MeasID_specs_1	/* Additional specs */
};

