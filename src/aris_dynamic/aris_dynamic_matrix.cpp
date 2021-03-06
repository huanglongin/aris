﻿#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <limits>
#include <sstream>
#include <cstddef>
#include <array>
#include <list>

#include "aris_dynamic_matrix.h"

namespace aris
{
	namespace dynamic
	{
		auto dlmread(const char *FileName, double *pMatrix)->void
		{
			std::ifstream file;

			file.open(FileName);

			if (!file) throw std::logic_error("file not exist");


			Size i = 0;
			while (!file.eof())
			{
				file >> *(pMatrix + i);
				++i;
			}
		}
	}
}
