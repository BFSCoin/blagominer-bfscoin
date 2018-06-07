#pragma once

#define RAPIDJSON_NO_SIZETYPEDEFINE

namespace rapidjson { typedef size_t SizeType; }
using namespace rapidjson;

#include "rapidjson/document.h"		// rapidjson's DOM-style API
#include "rapidjson/error/en.h"

#include <ws2tcpip.h>

//includes
#include "curses.h" //include pdcurses
#include <windows.h> //windows API
#include <thread> //threadding
#include <vector> //vectors
#include <sstream>
#include "InstructionSet.h"
#include <map>
#include "sph_shabal.h"
#include "mshabal.h"
#include "mshabal256.h"


//#include <stdio.h>
//#include <tchar.h>

//#include <string.h>
//#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <vector>
//

#pragma comment(lib,"Ws2_32.lib")
//#include <mswsock.h> // Need for SO_UPDATE_CONNECT_CONTEXT


#include "picohttpparser.h"

HANDLE hHeap;

CRITICAL_SECTION sessionsLock;	
CRITICAL_SECTION bestsLock;		
CRITICAL_SECTION sharesLock;	

bool exit_flag = false;
char *p_minerPath = nullptr;		// Path
char *pass = nullptr;							// ������
unsigned long long baseTarget = 0;
char signature[33];
char str_signature[65];
char oldSignature[33];
unsigned long long total_size = 0;	// ����� ����� ������
std::map <u_long, unsigned long long> satellite_size; // ��������� � �������� ������ ����������
unsigned long long targetDeadlineInfo = 0;			// ������������ ������� ����
unsigned long long height = 0;
volatile int stopThreads = 0;
int network_quality = 100;
unsigned long long deadline = 0;
unsigned int scoop = 0;

WINDOW * win_main;
#ifdef __AVX2__
char const *const version = "v1.170911_AVX2_POC2";
#else
#ifdef __AVX__
char const *const version = "v1.170911_AVX_POC2";
#else
char const *const version = "v1.170911_POC2";
#endif
#endif 
//config

std::string nodeaddr = "localhost";	// ����� ����
std::string nodeport = "8125";		// ���� ����

std::string updateraddr = "localhost";// ����� ����
std::string updaterport = "8125";		// ���� ����

std::string infoaddr = "localhost";	// ����� ����
std::string infoport = "8125";		// ���� ����

std::string proxyport = "8125";		// ���� ����

unsigned long long my_target_deadline = MAXDWORD;	// 4294967295;
SYSTEMTIME cur_time;				// ������� �����

size_t miner_mode = 0;				// ����� �������. 0=����, 1=���
size_t cache_size = 100000;			// ������ ���� ������ ������
size_t cache_size2 = 100000;		// ������ ���� ������ ������ POC2
std::vector<std::string> paths_dir; // ����
									//bool show_msg = false;				// �������� ������� � �������� � ����������
									//bool show_updates = false;			// �������� ������� � �������� � ���������
FILE * fp_Log = nullptr;			// ��������� �� ���-����
size_t send_interval = 100;			// ����� �������� ����� ����������
size_t update_interval = 1000;		// ����� �������� ����� ���������
short win_size_x = 80;
short win_size_y = 60;
//bool use_fast_rcv = false;
bool use_debug = false;
bool enable_proxy = false;
//bool send_best_only = true;
bool use_wakeup = false;
bool use_log = true;				// ����� ���
bool use_boost = false;				// ������������ ���������� ��������� ��� �������
bool show_winner = false;			// ���������� ����������
									//short can_generate = 0;				// 0 - disable; 1 - can start generate; 2 - already run generator
									//POC2: HF Block where POC2 gets active
unsigned long long POC2StartBlock = 502000;
//indicates if POC2 is active
bool POC2 = false;

std::vector<std::thread> worker;

struct t_worker_progress {
	size_t Number;
	unsigned long long Reads_bytes;
	bool isAlive;
};

std::vector<t_worker_progress> worker_progress;

struct t_shares {
	std::string file_name;
	unsigned long long account_id;// = 0;
	unsigned long long best;// = 0;
	unsigned long long nonce;// = 0;
};

std::vector<t_shares> shares;

struct t_best {
	unsigned long long account_id;// = 0;
	unsigned long long best;// = 0;
	unsigned long long nonce;// = 0;
	unsigned long long DL;// = 0;
	unsigned long long targetDeadline;// = 0;
};

std::vector<t_best> bests;

struct t_session {
	SOCKET Socket;
	unsigned long long deadline;
	t_shares body;
};

std::vector<t_session> sessions;

struct t_files {
	std::string Path;
	std::string Name;
	unsigned long long Size;
	unsigned long long Key;
	unsigned long long StartNonce;
	unsigned long long Nonces;
	unsigned long long Stagger;
	bool P2;
};

//headers
int load_config(char const *const filename);
void Log(char const *const strLog);
void GetCPUInfo(void);
void ShowMemErrorExit(void);
void GetPass(char const *const p_strFolderPath);
void hostname_to_ip(char const *const  in_addr, char* out_addr);
size_t GetFiles(const std::string &str, std::vector <t_files> *p_files);
void Log_llu(unsigned long long const llu_num);
void Log_u(size_t const u_num);
void updater_i(void);
void proxy_i(void);
void Log_init(void);
void send_i(void);
void work_i(const size_t local_num);
void GetBlockInfo(unsigned const num_block);
size_t Get_index_acc(unsigned long long const key);
void pollLocal(void);
int xdigit(char const digit);
size_t xstr2strr(char *buf, size_t const bufsize, const char *const in);
void th_hash(t_files const * const iter, double * const sum_time_proc, const size_t &local_num, unsigned long long const bytes, size_t const cache_size_local, unsigned long long const i, unsigned long long const nonce, unsigned long long const n, char const * const cache, size_t const acc);
void th_read(HANDLE ifile, unsigned long long const start, unsigned long long const MirrorStart, bool * const cont, unsigned long long * const bytes, t_files const * const iter, bool * const flip, bool p2, unsigned long long const i, unsigned long long const stagger, size_t * const cache_size_local, char * const cache, char * const MirrorCache);
void procscoop_sph(const unsigned long long nonce, const unsigned long long n, char const *const data, const size_t acc, const std::string &file_name);
char* GetJSON(char const *const req);
void procscoop_m256_8(unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name);
void procscoop_m_4(unsigned long long const nonce, unsigned long long const n, char const *const data, size_t const acc, const std::string &file_name);

