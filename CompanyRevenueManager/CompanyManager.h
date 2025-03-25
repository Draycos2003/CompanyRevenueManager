#ifndef COMPANYMANAGER_H
#define COMPANYMANAGER_H

#include <string>
#include <vector>

struct Company {
    std::string name;
    float revenue;
};

class CompanyManager {
public:
    void displayMenu();
    void createEntry();
    void displayEntries() const;
    void editEntry();
    void deleteEntry();
    void exitApp();

private:
    std::vector<Company> companies;
    void sortCompaniesByRevenue();
    void loadFromFile();
    void saveToFile() const;
    const std::string dataFile = "companies.txt";
};

#endif // COMPANYMANAGER_H