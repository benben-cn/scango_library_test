#pragma once
#include "dcf_cmdid.h"
/****************************************************************
*�ļ���Χ : �������ͨѶ������������
****************************************************************/
struct TLV_CMD_PKG_INFO
{
    const char* cmd_stru_script;  /* ���͸��������Ĳ����������� */
    const char* rsp_stru_script;  /* ��Ӧ�Ĳ������������ر�ע��:ǰ����һ��WORD�Ĵ����� */
    WORD        cmd;                /* ����ģ��������ֶ��� */
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bsg[] = {
    {"s16-s16-f16-s16-s16", "w-d-d-d-d-d-w-w-d", MOD_CMD_BSG_LOGIN}, //���:s16-s16��ʾ:�汾,spc�ɷ���IP
    {"s16-s16-f16",      "w-d-d-d-d-d-w-w-d",    MOD_CMD_BSG_LOGOUT},
    {"s16-s16-f16",      "w-d-d-d-d-d-w-w-d",    MOD_CMD_BSG_LOGIN_ERR},

};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss[] = {
    {"d-d-d-d-w-s16",  "w",                MOD_CMD_BSS_SYN_LOGDT}, //���:s16��ʾ:�汾
    {"d-d",            "w-d-d-d-w-v",      MOD_CMD_BSS_LOGIN},   /* 2017-08-23  16:48:14 �������ݿ������ŵ�ͬ�� */
    {"d",              "w-d-d",            MOD_CMD_BSS_ACTIVE},   /* 2017-08-23  16:48:42 �������ݿ������ŵ�ͬ�� */
    {"d-d",            "w-d-d-d-w-v",      MOD_CMD_BSS_LOGOUT},   /* 2017-08-23  16:48:14 �˳���¼ */
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_in[] = {
    {"d",      "w",    MOD_CMD_BSS_IN_CMT_F},
    {"d",      "w",    MOD_CMD_BSS_IN_CMT_AF},
    {"q-q-d-d-d-s20-s20-s20-s10-s20",  "w",    MOD_CMD_BSS_IN_CMT_TASK}, //����ID,����������,��ƷID(���ǰ��),��ƷID(������), ����Ŀ��, ��������,��������,��Ч����,���,����Ա
    {"q-d-w-w-d-d-s64",                "w",    MOD_CMD_BSS_IN_CMT_S}, //����ID,��ƷID,�Ƿ�y��,��ά������,�����,��ƷID(������),��ά��
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_bsdb[] = {
    {"d",			 "w-d",      MOD_CMD_BSS_DB_QUERY_BSS},
    {"d-s32-s32",    "w-d",      MOD_CMD_BSS_DB_QUERY_QR},
    {"d-s2",         "w-d",      MOD_CMD_BSS_DB_PLINE_QR}, //����1:����(����,����i/k/p); ����2:��������
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_out[] = {
    {"d",      "w",    MOD_CMD_BSS_OUT_CMT},
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_pin[] = {
    {"d",      "w",    MOD_CMD_BSS_PIN_CMT},
    {"d",      "w",    MOD_CMD_BSS_CANCEL_IN_CMT},
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_qrget[] = {
    {"s64",  "w-s64-d-d-s32-s128-s64-s64-s32",    MOD_CMD_BSS_QRGET_GDSI},/* ��Ӧ��Ϣ:�Լ��Ķ�ά��,��Ʒid,����id,����id,������,��������,���к�,����ʱ�� */
    {"s64",  "w-s64-d-w-v",           MOD_CMD_BSS_QRGET_RELATED_S},    /* ��Ӧ��Ϣ:�Լ��Ķ�ά��,��Ʒ��Ϣ,������,[��Ʒid,����] */
    {"s64",  "w-s64-s20-s20-s32-d-w-w-v", MOD_CMD_BSS_QRGET_RELATED_D},    /* ��Ӧ��Ϣ:�Լ��Ķ�ά��,Ч��,box_number,�������,��Ʒ��Ϣ,���,������,[����Ʒid,��ά��] */
    {"s64",  "w-s64-d-w-v",           MOD_CMD_BSS_QRGET_RELATED_SFB_D},   /* С��λ���Ҵ�λ ��Ӧ��Ϣ:�Լ��Ķ�ά��,��Ʒ��Ϣ,������,[��Ʒid,��ά��] */
    {"s64",  "w-s64-d-s16-d",         MOD_CMD_BSS_QRGET_3RD},
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_damaged[] = {
    { "d",      "w-d",    MOD_CMD_BSS_DAMAGED},
};