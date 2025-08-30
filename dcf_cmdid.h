#ifndef Dcf_cmdid_h
#define Dcf_cmdid_h
/****************************************************************
*文件范围 : 各个模块的命令字定义，便于收发方对照解析
                   命令字是否需要统一编排?基于技术角度，无需编排，但基于维护的角度，一个系统有唯一的命令字，会方便很多，通过命令字就可以搜索消息发送和处理的地方
*设计说明 : NA
*注意事项 : NA
*作   者 :     zjb
*创建日期 : 2017-05-19  14:54:9
****************************************************************/
//#include "dcf_def.h"

/* 新增命令的区段之后，一定要在dcf_pkghelper.cpp中的区段中增加相关信息 */

// 按照下面区段的样式进行统一分配

/* 网关支持的相关命令 */
const WORD MOD_CMD_BSG_BEGIN = 0x200;
const WORD MOD_CMD_BSG_LOGIN = MOD_CMD_BSG_BEGIN + 1;/* 登录网关命令 */
const WORD MOD_CMD_BSG_LOGOUT = MOD_CMD_BSG_BEGIN + 2;/* 退出登录网关命令 */
const WORD MOD_CMD_BSG_LOGIN_ERR = MOD_CMD_BSG_BEGIN + 3;/* 登录错误命令 */
const WORD MOD_CMD_BSG_END = 0x210;

/* 服务端支持的相关命令 */
const WORD MOD_CMD_BSS_BEGIN = 0x210;
const WORD MOD_CMD_BSS_SYN_LOGDT = MOD_CMD_BSS_BEGIN + 1;   /* 同步客户端登录数据命令 */
const WORD MOD_CMD_BSS_LOGIN = MOD_CMD_BSS_BEGIN + 2;   /* 登录服务进程命令 */
const WORD MOD_CMD_BSS_ACTIVE = MOD_CMD_BSS_BEGIN + 3;   /* 企业设备和服务端保活命令 */
const WORD MOD_CMD_BSS_LOGOUT = MOD_CMD_BSS_BEGIN + 4;   /* 退出登录服务进程命令 */
const WORD MOD_CMD_BSS_END = 0x220;

/* 服务端支持的业务相关命令 */
/* 生产企业提交入库 */
const WORD MOD_CMD_BSS_IN_BEGIN = 0x220;
const WORD MOD_CMD_BSS_IN_CMT_F = MOD_CMD_BSS_IN_BEGIN + 1;   /* 生产企业批量提交入库数据 */
const WORD MOD_CMD_BSS_IN_CMT_AF = MOD_CMD_BSS_IN_BEGIN + 2;   /* 生产企业批量自动提交入库数据 */
const WORD MOD_CMD_BSS_IN_CMT_TASK = MOD_CMD_BSS_IN_BEGIN + 3;    /* PDA 提交单品码 */
const WORD MOD_CMD_BSS_IN_CMT_S = MOD_CMD_BSS_IN_BEGIN + 4;    /* PDA 提交单品码 */
const WORD MOD_CMD_BSS_IN_END = 0x230;

/* 企业服务器基本信息管理 */
const WORD MOD_CMD_BSS_DB_BEGIN = 0x230;
const WORD MOD_CMD_BSS_DB_QUERY_BSS = MOD_CMD_BSS_DB_BEGIN + 1; /* 获取基本信息 */
const WORD MOD_CMD_BSS_DB_QUERY_QR = MOD_CMD_BSS_DB_BEGIN + 2; /* 获取QR所有信息 */
const WORD MOD_CMD_BSS_DB_PLINE_QR = MOD_CMD_BSS_DB_BEGIN + 3;  /* 获取产线白码 */
const WORD MOD_CMD_BSS_DB_END = 0x235;

/* 喆道处理企业出库操作 */
const WORD MOD_CMD_BSS_OUT_BEGIN = 0x235;
const WORD MOD_CMD_BSS_OUT_CMT = MOD_CMD_BSS_OUT_BEGIN + 1;         /* 出库 */
const WORD MOD_CMD_BSS_OUT_END = 0x240;

/* 喆道处理经销商采购入库 */
const WORD MOD_CMD_BSS_PIN_BEGIN = 0x240;
const WORD MOD_CMD_BSS_PIN_CMT = MOD_CMD_BSS_PIN_BEGIN + 1;         /* 采购入库 */
const WORD MOD_CMD_BSS_CANCEL_IN_CMT = MOD_CMD_BSS_PIN_BEGIN + 2;   /* 退货调拨入库 */
const WORD MOD_CMD_BSS_PIN_END = 0x245;

/* 实时查询二维码信息 */
const WORD MOD_CMD_BSS_QRGET_BEGIN = 0x24a;
const WORD MOD_CMD_BSS_QRGET_GDSI = MOD_CMD_BSS_QRGET_BEGIN + 1;           /* 查询二维码对应的商品信息，生产任务信息，可以返回商品id */
const WORD MOD_CMD_BSS_QRGET_RELATED_S = MOD_CMD_BSS_QRGET_BEGIN + 2;      /* 查询其关联的二维码精简信息(二维码商品id和对应数量) */
const WORD MOD_CMD_BSS_QRGET_RELATED_D = MOD_CMD_BSS_QRGET_BEGIN + 3;      /* 查询其关联的二维码详细信息(二维码、商品id) */
const WORD MOD_CMD_BSS_QRGET_RELATED_SFB_D = MOD_CMD_BSS_QRGET_BEGIN + 4;  /* 查询其关联的二维码详细信息(二维码、商品id),从小单位到大单位（由单品码找箱码） */
const WORD MOD_CMD_BSS_QRGET_3RD = MOD_CMD_BSS_QRGET_BEGIN + 5;            /* 查询第三方码(非喆道QR码)信息 */
const WORD MOD_CMD_BSS_QRGET_END = 0x250;

/* 盘点业务 */
const WORD MOD_CMD_BSS_DAMAGED_BEGIN = 0x25a;
const WORD MOD_CMD_BSS_DAMAGED = MOD_CMD_BSS_DAMAGED_BEGIN + 1;    /* 盘点业务 */
const WORD MOD_CMD_BSS_DAMAGED_END = 0x260;

#endif
