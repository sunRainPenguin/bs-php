#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <algorithm> 
#include <set>
#include <queue>
#include <utility>
using std::string;
using std::vector;
using std::set;
using std::queue;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::ofstream;

// ��ö��������Ҫ��SFCConvertor��ʹ��
enum SFCEleType {
	tpSFCAction,
	tpSFCInVar,
	tpSFCTransition,
	tpSFCActionBlock,
	tpSFCJumpStep,
	tpSFCSimutaneousCv,
	tpSFCSimutaneousDv 
};