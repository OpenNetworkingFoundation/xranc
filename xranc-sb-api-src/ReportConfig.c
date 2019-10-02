/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-API"
 * 	found in "../xranc-sb-api/xRAN-API-IEs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#include "ReportConfig.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static asn_oer_constraints_t asn_OER_type_params_constr_3 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_params_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 3,  3,  0,  6 }	/* (0..6) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_triggerQuantity_constr_13 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_triggerQuantity_constr_13 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_type_reportQuantity_constr_16 CC_NOTUSED = {
	{ 0, 0 },
	-1};
static asn_per_constraints_t asn_PER_type_reportQuantity_constr_16 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_params_3[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params__params, choice.per_param),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PerParam,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"per-param"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params__params, choice.a1param),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_A1Param,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"a1param"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params__params, choice.a2param),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_A2Param,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"a2param"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params__params, choice.a3param),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_A3Param,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"a3param"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params__params, choice.a4param),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_A4Param,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"a4param"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params__params, choice.a5param),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_A5Param,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"a5param"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params__params, choice.a6param),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_A6Param,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"a6param"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_params_tag2el_3[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* per-param */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* a1param */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* a2param */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* a3param */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* a4param */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* a5param */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 } /* a6param */
};
static asn_CHOICE_specifics_t asn_SPC_params_specs_3 = {
	sizeof(struct ReportConfig__report_params__params),
	offsetof(struct ReportConfig__report_params__params, _asn_ctx),
	offsetof(struct ReportConfig__report_params__params, present),
	sizeof(((struct ReportConfig__report_params__params *)0)->present),
	asn_MAP_params_tag2el_3,
	7,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_params_3 = {
	"params",
	"params",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ &asn_OER_type_params_constr_3, &asn_PER_type_params_constr_3, CHOICE_constraint },
	asn_MBR_params_3,
	7,	/* Elements count */
	&asn_SPC_params_specs_3	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_report_params_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params, params),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		+1,	/* EXPLICIT tag at current level */
		&asn_DEF_params_3,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"params"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params, hysteresis),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Hysteresis,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"hysteresis"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig__report_params, timetotrigger),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeToTrigger,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"timetotrigger"
		},
};
static const ber_tlv_tag_t asn_DEF_report_params_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_report_params_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* params */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* hysteresis */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* timetotrigger */
};
static asn_SEQUENCE_specifics_t asn_SPC_report_params_specs_2 = {
	sizeof(struct ReportConfig__report_params),
	offsetof(struct ReportConfig__report_params, _asn_ctx),
	asn_MAP_report_params_tag2el_2,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_report_params_2 = {
	"report-params",
	"report-params",
	&asn_OP_SEQUENCE,
	asn_DEF_report_params_tags_2,
	sizeof(asn_DEF_report_params_tags_2)
		/sizeof(asn_DEF_report_params_tags_2[0]) - 1, /* 1 */
	asn_DEF_report_params_tags_2,	/* Same as above */
	sizeof(asn_DEF_report_params_tags_2)
		/sizeof(asn_DEF_report_params_tags_2[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_report_params_2,
	3,	/* Elements count */
	&asn_SPC_report_params_specs_2	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_triggerQuantity_value2enum_13[] = {
	{ 0,	4,	"rsrp" },
	{ 1,	4,	"rsrq" }
};
static const unsigned int asn_MAP_triggerQuantity_enum2value_13[] = {
	0,	/* rsrp(0) */
	1	/* rsrq(1) */
};
static const asn_INTEGER_specifics_t asn_SPC_triggerQuantity_specs_13 = {
	asn_MAP_triggerQuantity_value2enum_13,	/* "tag" => N; sorted by tag */
	asn_MAP_triggerQuantity_enum2value_13,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_triggerQuantity_tags_13[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_triggerQuantity_13 = {
	"triggerQuantity",
	"triggerQuantity",
	&asn_OP_NativeEnumerated,
	asn_DEF_triggerQuantity_tags_13,
	sizeof(asn_DEF_triggerQuantity_tags_13)
		/sizeof(asn_DEF_triggerQuantity_tags_13[0]) - 1, /* 1 */
	asn_DEF_triggerQuantity_tags_13,	/* Same as above */
	sizeof(asn_DEF_triggerQuantity_tags_13)
		/sizeof(asn_DEF_triggerQuantity_tags_13[0]), /* 2 */
	{ &asn_OER_type_triggerQuantity_constr_13, &asn_PER_type_triggerQuantity_constr_13, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_triggerQuantity_specs_13	/* Additional specs */
};

static const asn_INTEGER_enum_map_t asn_MAP_reportQuantity_value2enum_16[] = {
	{ 0,	21,	"sameAsTriggerQuantity" },
	{ 1,	4,	"both" }
};
static const unsigned int asn_MAP_reportQuantity_enum2value_16[] = {
	1,	/* both(1) */
	0	/* sameAsTriggerQuantity(0) */
};
static const asn_INTEGER_specifics_t asn_SPC_reportQuantity_specs_16 = {
	asn_MAP_reportQuantity_value2enum_16,	/* "tag" => N; sorted by tag */
	asn_MAP_reportQuantity_enum2value_16,	/* N => "tag"; sorted by N */
	2,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_reportQuantity_tags_16[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_reportQuantity_16 = {
	"reportQuantity",
	"reportQuantity",
	&asn_OP_NativeEnumerated,
	asn_DEF_reportQuantity_tags_16,
	sizeof(asn_DEF_reportQuantity_tags_16)
		/sizeof(asn_DEF_reportQuantity_tags_16[0]) - 1, /* 1 */
	asn_DEF_reportQuantity_tags_16,	/* Same as above */
	sizeof(asn_DEF_reportQuantity_tags_16)
		/sizeof(asn_DEF_reportQuantity_tags_16[0]), /* 2 */
	{ &asn_OER_type_reportQuantity_constr_16, &asn_PER_type_reportQuantity_constr_16, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_reportQuantity_specs_16	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_ReportConfig_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig, report_params),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_report_params_2,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"report-params"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig, triggerQuantity),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_triggerQuantity_13,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"triggerQuantity"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ReportConfig, reportQuantity),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_reportQuantity_16,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"reportQuantity"
		},
};
static const ber_tlv_tag_t asn_DEF_ReportConfig_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ReportConfig_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* report-params */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* triggerQuantity */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* reportQuantity */
};
asn_SEQUENCE_specifics_t asn_SPC_ReportConfig_specs_1 = {
	sizeof(struct ReportConfig),
	offsetof(struct ReportConfig, _asn_ctx),
	asn_MAP_ReportConfig_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	3,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_ReportConfig = {
	"ReportConfig",
	"ReportConfig",
	&asn_OP_SEQUENCE,
	asn_DEF_ReportConfig_tags_1,
	sizeof(asn_DEF_ReportConfig_tags_1)
		/sizeof(asn_DEF_ReportConfig_tags_1[0]), /* 1 */
	asn_DEF_ReportConfig_tags_1,	/* Same as above */
	sizeof(asn_DEF_ReportConfig_tags_1)
		/sizeof(asn_DEF_ReportConfig_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ReportConfig_1,
	3,	/* Elements count */
	&asn_SPC_ReportConfig_specs_1	/* Additional specs */
};

