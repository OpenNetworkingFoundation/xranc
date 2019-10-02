/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "XRAN-API"
 * 	found in "../xranc-sb-api/xRAN-API-IEs.asn1"
 * 	`asn1c -fcompound-names -pdu=XRANCPDU`
 */

#include "L2ReportInterval.h"

asn_TYPE_member_t asn_MBR_L2ReportInterval_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct L2ReportInterval, t_radio_meas_report_per_ue),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_L2MeasReportInterval,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"t-radio-meas-report-per-ue"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct L2ReportInterval, t_radio_meas_report_per_cell),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_L2MeasReportInterval,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"t-radio-meas-report-per-cell"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct L2ReportInterval, t_radio_sched_report_per_ue),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_L2MeasReportInterval,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"t-radio-sched-report-per-ue"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct L2ReportInterval, t_radio_sched_report_per_cell),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_L2MeasReportInterval,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"t-radio-sched-report-per-cell"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct L2ReportInterval, t_pdcp_meas_report_per_ue),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_L2MeasReportInterval,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"t-pdcp-meas-report-per-ue"
		},
};
static const ber_tlv_tag_t asn_DEF_L2ReportInterval_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_L2ReportInterval_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* t-radio-meas-report-per-ue */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* t-radio-meas-report-per-cell */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* t-radio-sched-report-per-ue */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* t-radio-sched-report-per-cell */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 } /* t-pdcp-meas-report-per-ue */
};
asn_SEQUENCE_specifics_t asn_SPC_L2ReportInterval_specs_1 = {
	sizeof(struct L2ReportInterval),
	offsetof(struct L2ReportInterval, _asn_ctx),
	asn_MAP_L2ReportInterval_tag2el_1,
	5,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	5,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_L2ReportInterval = {
	"L2ReportInterval",
	"L2ReportInterval",
	&asn_OP_SEQUENCE,
	asn_DEF_L2ReportInterval_tags_1,
	sizeof(asn_DEF_L2ReportInterval_tags_1)
		/sizeof(asn_DEF_L2ReportInterval_tags_1[0]), /* 1 */
	asn_DEF_L2ReportInterval_tags_1,	/* Same as above */
	sizeof(asn_DEF_L2ReportInterval_tags_1)
		/sizeof(asn_DEF_L2ReportInterval_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_L2ReportInterval_1,
	5,	/* Elements count */
	&asn_SPC_L2ReportInterval_specs_1	/* Additional specs */
};

