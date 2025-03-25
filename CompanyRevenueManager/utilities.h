#pragma once
#include <sstream>
#include <iomanip>
#include "CompanyManager.h"

std::string formatWithCommas(double value) {
    std::ostringstream oss;
    oss.imbue(std::locale(""));  // Use the user's locale to insert commas
    oss << std::fixed << std::setprecision(2) << value;
    return oss.str();
}