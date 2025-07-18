#ifndef __MERIDIAN_KEYS_H__
#define __MERIDIAN_KEYS_H__

// Wifiアクセスポイントの設定
#define WIFI_AP_SSID "xxxxxx"      // アクセスポイントのWIFI_AP_SSID
#define WIFI_AP_PASS "xxxxxx"      // アクセスポイントのパスワード
#define WIFI_SEND_IP "192.168.3.3" // 送り先のPCのIPアドレス(PCのIPアドレスを調べておく)
#define UDP_SEND_PORT 22222        // 送り先のポート番号
#define UDP_RECV_PORT 22224        // このESP32のポート番号

// Wifi用のESP32固定IPアドレスの設定
// ※config.hの MODE_FIXED_IP を1に設定することで有効
#define FIXED_IP_ADDR "192.168.3.xx"     // ESP32のIPアドレス固定時のESPのIPアドレス
#define FIXED_IP_GATEWAY "192.168.3.xx"  // ESP32のIPアドレス固定時のルーターのゲートウェイ
#define FIXED_IP_SUBNET "255.255.255. 0" // ESP32のIPアドレス固定時のサブネットマスク

// Ethernet用のESP32固定IPアドレスの設定
// ※config.hの MODE_ETHER を1に設定に設定することで有効
#define ETHER_LOCAL_IP "192.168.77.110" // 有線LAN使用時のESP32のIPアドレス
#define ETHER_GATEWAY "192.168.77.100"  // 有線LAN使用時のPCのIPアドレス
#define ETHER_SUBNET "255.255.255.0"    // 有線LAN使用時のサブネットマスク
#define ETHER_DNS "8.8.8.8"             // 有線LAN使用時のDNSアドレス
#define ETHER_MAC "02:xx:xx:xx:xx:xx"   // 有線LAN使用時の固有MACアドレスを転記（W5500ボード等のMACアドレス）

#endif // __MERIDIAN_KEYS_H__
