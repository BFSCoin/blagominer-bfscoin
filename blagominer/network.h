#pragma once
#include "logger.h"
#include "error.h"
#include "accounts.h"


#define RAPIDJSON_NO_SIZETYPEDEFINE

namespace rapidjson { typedef size_t SizeType; }
using namespace rapidjson;

//config items
extern size_t send_interval;					// ����� �������� ����� ����������
extern size_t update_interval;					// ����� �������� ����� ���������								
extern bool enable_proxy;						// enable client/server functionality
extern bool show_winner;						// true: show winner information after each round

#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/error/en.h"

#pragma comment(lib,"Ws2_32.lib")

#include "picohttpparser.h"

extern std::map <u_long, unsigned long long> satellite_size; // ��������� � �������� ������ ����������

extern char str_signature[65];


extern int network_quality;
extern std::thread showWinner;

extern std::string nodeaddr;	// ����� ����
extern std::string nodeport;		// ���� ����

extern std::string updateraddr;// ����� ����
extern std::string updaterport;		// ���� ����

extern std::string infoaddr;	// ����� ����
extern std::string infoport;		// ���� ����

extern std::string proxyport;		// ���� ����



char* GetJSON(char const *const req);

void ShowWinner(unsigned long long const num_block);
void pollLocal(void);

void hostname_to_ip(char const *const  in_addr, char* out_addr);
void updater_i(void);
void proxy_i(void);
void send_i(void);
size_t xstr2strr(char *buf, size_t const bufsize, const char *const in);
void VchConfusion(std::vector<char>& vch_data);
bool Aes256_Encrypt(std::string str_key, std::string str_plain_text, std::string& str_encrypted_text);
std::string ToHex(const std::string& data);
