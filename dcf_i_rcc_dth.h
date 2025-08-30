
/* 信息帧类型 为了防止和别的应用混淆，信息帧从0x8000开始编排*/
/* 当前版本为了简化，添加类型之后，还需要在 dcf_sv_info_provider_register() 中注册，而且还需要调用该函数注册，否则不生效 */
const WORD INFO_TYPE_BSS_INSTORE = 0x8205;        /* 生产企业商品入库服务 */
const WORD INFO_TYPE_BSS_BSDB = 0x8206;               /* 企业基本信息查询 */
const WORD INFO_TYPE_BSS_OUTSTORE = 0x8207;     /* 企业商品出库服务 */
const WORD INFO_TYPE_BSS_PINSTORE = 0x8208;      /* 企业采购入库服务 */
const WORD INFO_TYPE_BSS_QRGET = 0x820a;            /* 命令查询QR信息 */
const WORD INFO_TYPE_BSS_DAMAGED = 0x820d;        /* 盘点业务 */

