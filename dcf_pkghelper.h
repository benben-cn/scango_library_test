#pragma once
#include "dcf_cmdid.h"
/****************************************************************
*文件范围 : 与服务器通讯参数描述对象
****************************************************************/
struct TLV_CMD_PKG_INFO
{
    const char* cmd_stru_script;  /* 发送给服务器的参数描述对象 */
    const char* rsp_stru_script;  /* 响应的参数描述对象，特别注意:前面有一个WORD的错误码 */
    WORD        cmd;                /* 各个模块的命令字定义 */
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bsg[] = {
    {"s16-s16-f16-s16-s16", "w-d-d-d-d-d-w-w-d", MOD_CMD_BSG_LOGIN}, //最后:s16-s16表示:版本,spc可访问IP
    {"s16-s16-f16",      "w-d-d-d-d-d-w-w-d",    MOD_CMD_BSG_LOGOUT},
    {"s16-s16-f16",      "w-d-d-d-d-d-w-w-d",    MOD_CMD_BSG_LOGIN_ERR},

};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss[] = {
    {"d-d-d-d-w-s16",  "w",                MOD_CMD_BSS_SYN_LOGDT}, //最后:s16表示:版本
    {"d-d",            "w-d-d-d-w-v",      MOD_CMD_BSS_LOGIN},   /* 2017-08-23  16:48:14 增加数据库更新序号的同步 */
    {"d",              "w-d-d",            MOD_CMD_BSS_ACTIVE},   /* 2017-08-23  16:48:42 增加数据库更新序号的同步 */
    {"d-d",            "w-d-d-d-w-v",      MOD_CMD_BSS_LOGOUT},   /* 2017-08-23  16:48:14 退出登录 */
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_in[] = {
    {"d",      "w",    MOD_CMD_BSS_IN_CMT_F},
    {"d",      "w",    MOD_CMD_BSS_IN_CMT_AF},
    {"q-q-d-d-d-s20-s20-s20-s10-s20",  "w",    MOD_CMD_BSS_IN_CMT_TASK}, //任务ID,生产订单号,商品ID(灭菌前的),商品ID(灭菌后的), 行项目号, 生产批号,生产日期,有效期至,班次,操作员
    {"q-d-w-w-d-d-s64",                "w",    MOD_CMD_BSS_IN_CMT_S}, //任务ID,商品ID,是否y码,二维码类型,随机码,商品ID(灭菌后的),二维码
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_bsdb[] = {
    {"d",			 "w-d",      MOD_CMD_BSS_DB_QUERY_BSS},
    {"d-s32-s32",    "w-d",      MOD_CMD_BSS_DB_QUERY_QR},
    {"d-s2",         "w-d",      MOD_CMD_BSS_DB_PLINE_QR}, //参数1:请求方(数量,类型i/k/p); 参数2:给出反馈
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_out[] = {
    {"d",      "w",    MOD_CMD_BSS_OUT_CMT},
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_pin[] = {
    {"d",      "w",    MOD_CMD_BSS_PIN_CMT},
    {"d",      "w",    MOD_CMD_BSS_CANCEL_IN_CMT},
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_qrget[] = {
    {"s64",  "w-s64-d-d-s32-s128-s64-s64-s32",    MOD_CMD_BSS_QRGET_GDSI},/* 响应信息:自己的二维码,商品id,批次id,任务id,任务简称,生产日期,序列号,赋码时间 */
    {"s64",  "w-s64-d-w-v",           MOD_CMD_BSS_QRGET_RELATED_S},    /* 响应信息:自己的二维码,商品信息,分组数,[商品id,数量] */
    {"s64",  "w-s64-s20-s20-s32-d-w-w-v", MOD_CMD_BSS_QRGET_RELATED_D},    /* 响应信息:自己的二维码,效期,box_number,灭菌批号,商品信息,体积,分组数,[子商品id,二维码] */
    {"s64",  "w-s64-d-w-v",           MOD_CMD_BSS_QRGET_RELATED_SFB_D},   /* 小单位查找大单位 响应信息:自己的二维码,商品信息,分组数,[商品id,二维码] */
    {"s64",  "w-s64-d-s16-d",         MOD_CMD_BSS_QRGET_3RD},
};

static TLV_CMD_PKG_INFO g_cmd_struc_trans_bss_damaged[] = {
    { "d",      "w-d",    MOD_CMD_BSS_DAMAGED},
};