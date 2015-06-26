#include "stdafx.h"
#include <iostream>
#include <string>
#include <iterator>
using namespace std;
class WriteTxt{
public:
	template <typename T> static bool writeInfo(string fileName,int cellId,T infos);
};