#include <iostream>
#include <map>
#include <string>
#include "scango_dll.h"
#include "dcf_cmdid.h"
#include "dcf_i_rcc_dth.h"

#include <vector>
#include <algorithm>
#include <fstream>

#ifdef _MSC_VER
#include <WinSock2.h>
#include <tcpmib.h>
#include <IPHlpApi.h>
#else
#include <sys/socket.h>
#include <ifaddrs.h>
#include <net/if_dl.h>
#endif

using namespace std;

#ifdef _MSC_VER
#pragma comment(lib, "WS2_32.lib")
#pragma comment(lib, "IPHlpApi.lib")

#define PORT_DOWN 49152
#define PORT_UP 65535
#endif

//获取udp所有的空闲端口
std::vector<WORD> GetAllUdpConnectionsPort()
{
    std::vector<WORD> ret;
    ULONG size = 0;
    GetUdpTable(NULL, &size, TRUE);
    std::unique_ptr<char[]> buffer(new char[size]);

    PMIB_UDPTABLE udpTable = reinterpret_cast<PMIB_UDPTABLE>(buffer.get());
    if (GetUdpTable(udpTable, &size, FALSE) == NO_ERROR)
        for (size_t i = 0; i < udpTable->dwNumEntries; i++)
            ret.push_back(ntohs((WORD)udpTable->table[i].dwLocalPort));
    std::sort(std::begin(ret), std::end(ret));
    return ret;
}

//获取一个udp空闲端口
WORD FindAvailableUdpPort(WORD begin = PORT_DOWN, WORD end = PORT_UP)
{
    auto vec = GetAllUdpConnectionsPort();
    for (WORD port = begin; port != end; ++port)
        if (!std::binary_search(std::begin(vec), std::end(vec), port))
            return port;
    return 0;
}

//获取MAC地址
bool GetMacByGetAdaptersInfo(std::string& macOUT) {
    #ifdef _MSC_VER
        bool ret = false;
        ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
        PIP_ADAPTER_INFO pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
        if (pAdapterInfo == NULL)
            return false;

        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
            free(pAdapterInfo);
            pAdapterInfo = (IP_ADAPTER_INFO*)malloc(ulOutBufLen);
            if (pAdapterInfo == NULL)
                return false;
        }

        if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == NO_ERROR) {
            for (PIP_ADAPTER_INFO pAdapter = pAdapterInfo; pAdapter != NULL; pAdapter = pAdapter->Next) {
                if (pAdapter->Type != MIB_IF_TYPE_ETHERNET)
                    continue;
                if (pAdapter->AddressLength != 6)
                    continue;

                char acMAC[32];
                sprintf_s(acMAC, sizeof(acMAC), "%02X%02X%02X%02X%02X%02X",
                    int(pAdapter->Address[0]),
                    int(pAdapter->Address[1]),
                    int(pAdapter->Address[2]),
                    int(pAdapter->Address[3]),
                    int(pAdapter->Address[4]),
                    int(pAdapter->Address[5]));
                macOUT = acMAC;
                ret = true;
                break;
            }
        }
        free(pAdapterInfo);
        return ret;
    #else
        struct ifaddrs *ifaddr, *ifa;

        if (getifaddrs(&ifaddr) == -1) {
            perror("getifaddrs");
            return false;
        }

        for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
            if (ifa->ifa_addr == nullptr || ifa->ifa_addr->sa_family != AF_LINK)
                continue;

            struct sockaddr_dl* sdl = (struct sockaddr_dl*)ifa->ifa_addr;
            unsigned char* mac = (unsigned char*)LLADDR(sdl);

            char buffer[18];
            snprintf(buffer, sizeof(buffer), "%02X:%02X:%02X:%02X:%02X:%02X",
                    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
            macOUT = buffer;
            break;
        }

        freeifaddrs(ifaddr);
        return true;
    #endif
}

//登入入口
void login() {
    string Ip = "192.168.5.128"; //服务器IP地址
    #ifdef _MSC_VER
    WORD recv_port = FindAvailableUdpPort(); //空闲udp端口
    #else
    WORD recv_port = 50000; //空闲udp端口
    #endif
    string recv_addr = "0.0.0.0:" + to_string(recv_port);
    string gateway_addr = Ip + ":4021";
    cout << gateway_addr << "," << recv_addr << endl;
    string dev_name = "sml002"; //账号名称
    string dev_cirtify;
    GetMacByGetAdaptersInfo(dev_cirtify); //MAC地址
    const char* key_pub_com_bsg = "zhw_pubkey";
    const char* key_pub_com_bss = "zhw_pubkey";
    string key_self_com_bs = "sml002"; //账号密码
    const char* version = "1.0.0"; //软件版本号
    smartdog_scango_dcframe_BSClient_init(recv_addr.c_str(), gateway_addr.c_str(), dev_name.c_str(), dev_cirtify.c_str(), 0, 0, 0, 0, key_pub_com_bsg, key_pub_com_bss, key_self_com_bs.c_str(), "", "", version, Ip.c_str());
}

//退出登入
void outlogin() {
    smartdog_scango_dcframe_BSClient_quit();
    cout << "退出登入" << endl;
}

//获取和服务端的状态
void getServerState() {
    DWORD state = smartdog_scango_dcframe_BSClient_getServerState();
    /* 和服务端的状态 0:初始化，等待和网关通讯正常 1:正在登陆 2:通讯正常*/
    switch (state)
    {
    case 0:
        cout << "初始化，等待和网关通讯正常" << endl;
        break;
    case 1:
        cout << "正在登陆" << endl;
        break;
    case 2:
        cout << "通讯正常" << endl;
        break;
    default:
        break;
    }
}

//上传文件
void sendRAWmessage() {
    WORD modId_I = 7777; //自定义模块id
    //信息帧类型
    //WORD infoType_I = INFO_TYPE_BSS_DAMAGED; //盘点业务
    //WORD infoType_I = INFO_TYPE_BSS_INSTORE; //赋码业务
    //WORD infoType_I = INFO_TYPE_BSS_PINSTORE; //收货业务
    WORD infoType_I = INFO_TYPE_BSS_OUTSTORE; //发货业务
    //各个模块的命令字定义
    //WORD cmd_I = MOD_CMD_BSS_DAMAGED; //盘点业务
    //WORD cmd_I = MOD_CMD_BSS_IN_CMT_F; //赋码业务
    //WORD cmd_I = MOD_CMD_BSS_PIN_CMT; //收货业务
    WORD cmd_I = MOD_CMD_BSS_OUT_CMT; //发货业务
    //const char* srcPath = "C:/Users/zhedao/Desktop/xxx.db"; //要发送文件的路径
    const char* srcPath = "C:/Users/zhedao/Desktop/bs_gds_out_opt_1787240384.db"; //发货在途库存


    std::ifstream inFile;
    inFile.open(srcPath, std::ios::in);
    if (!inFile.is_open()) {
        std::cout << "Open file " << srcPath << " fail!" << std::endl;
        return;
    }
    inFile.seekg(0, std::ios_base::end);
    std::streampos fileSize = inFile.tellg(); //文件大小
    inFile.seekg(0, std::ios_base::beg);
    inFile.close();

    smartdog_scango_dcframe_BSClient_sendRawMessage(modId_I, infoType_I, cmd_I, srcPath, fileSize);

}

//发送信息
void sendCMD() {
    WORD modId_I = 6666;//自定义模块id

    WORD infoType_I = INFO_TYPE_BSS_BSDB;//打标业务

    WORD cmd_I = MOD_CMD_BSS_DB_PLINE_QR;//打标业务

    DWORD req_num = 100; //请求码的数量

    char codetype[2] = { 'i' }; //请求码的类型

    //json格式参考dcf_pkghelper.h头文件，通过cmd_I找到相应的请求格式
    //{"d-s2", "w-d", MOD_CMD_BSS_DB_PLINE_QR}, //参数1:请求方(数量,类型i/k/p); 参数2:给出反馈
    //字符参数对应的数据类型
    //b-w-q-d-s13-s17-f8-v
    //{
    //    \"byte\":255, b代表字节
    //    \"word\":100, w代表字
    //    \"uint64\":\"9121900021748049114\", q代表uint64，该类型最大值超出json的整形上限需要用字符串表示
    //    \"dword\":\"4294967295\", d代表双字，该类型最大值超出json的整形上限需要用字符串表示
    //    \"s13\":\"aaaaaaaaaaaa\", s13代表长度为13的字符串
    //    \"s17\":\"aaaaaaaabbbbbbbb\",  s17代表长度为17的字符串
    //    \"f8\":\"12345678\", f8代表长度为8的字节数组
    //    \"v\":{ 字节数组的另一种表示
    //        \"word\": 3, 字节数组长度
    //        \"BYTE*\" : \"abc\" 字节数组的值
    //    }
    //}
    //                          d                     s2
    const char* json_str = "{\"req_num\":\"0x64\", \"codetype\":\"i\"}"; //json类型存储的信息

    DWORD dwRet = smartdog_scango_dcframe_BSClient_sendCMD(modId_I, infoType_I, cmd_I, json_str);
    if(dwRet) cout << "错误代码：" << dwRet << endl;
}

//回调函数----------------------------------------------------------------------------------------
//退出登入
void myonLogout() {
    cout << "被服务器踢出登入" << endl;
}

//登入成功后实时同步主数据
void myonDatabaseIdxRecv(DWORD baseDbIdx, DWORD psDbIdx) {
    cout << baseDbIdx << "......" << psDbIdx << endl;
    cout << "SPC login is success!" << endl;
    //获取功能权限, 返回值：权限代码容器
    vector<WORD> v_fun = smartdog_scango_dcframe_BSClient_getFuncList();
    for (vector<WORD>::iterator iter = v_fun.begin(); iter != v_fun.end(); iter++) {
        cout << *iter << ",";
    }
    cout << endl;
}

//错误报错 modId_I：自定义模块id，errmsg：错误信息
void myonError(WORD modId, char* errmsg) {
    cout << "模块id：" << modId << "错误信息：" << errmsg << endl;
}

//登入失败报错 code：错误代码
void myonLoginError(WORD code) {
    cout << "登入错误：" << code << endl;
}

//上传文件进度条 modId_I：自定义模块id，curBegin：当前进度，totalFrame：总进度
void myonProgress(WORD modId, WORD curBegin, WORD totalFrame) {
    cout << "模块id：" << modId << " 进度条：" << curBegin << "/" << totalFrame << endl;
}

//接收信息 cjson：json类型存储的服务器返回信息
void myonCRMRecv(char* cjson) {
        cout << cjson << endl;
}

//通过模块id获取文件保存路径 返回值：文件保存的路径，modId：自定义模块id
char* mynewTempFile(WORD modid) {
    char* tempdfile = (char*)malloc(256 * sizeof(char));
    sprintf_s(tempdfile, 256, "c:/users/zhedao/desktop/%d/index.db", modid);
    return tempdfile;
}

//文件保存后返回模块id以及文件完整路径 modId：自定义模块id，dstFile：文件完整路径
void myonFileRecv(WORD modId, char* dstFile) {
    cout << "模块id：" << modId << " 文件接收地址：" << dstFile << endl;
    free(dstFile);
    dstFile = NULL;
}

int main() {
    //注册回调函数
    SetonLogout(myonLogout);

    SetonDatabaseIdxRecv(myonDatabaseIdxRecv);

    SetonError(myonError);

    SetonLoginError(myonLoginError);

    SetonProgress(myonProgress);

    SetonCRMRecv(myonCRMRecv);

    SetnewTempFile(mynewTempFile);

    SetonFileRecv(myonFileRecv);

    while (1) {
        int a;
        scanf_s("%d", &a, sizeof(a));
        switch (a)
        {
        case 1:
            login(); //登入
            break;
        case 2:
            outlogin(); //退出登入
            break;
        case 3:
            getServerState(); //查看登入状态
            break;
        case 4:
            sendRAWmessage(); //上传文件
            break;
        case 5:
            sendCMD(); //请求码文件
            break;
        default:
            break;
        }
    }

    system("pause");
    return 0;
}
