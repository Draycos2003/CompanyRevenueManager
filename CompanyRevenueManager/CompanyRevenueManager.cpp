#include "CompanyManager.h"
#include "utilities.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <sstream>



void CompanyManager::displayMenu() {
    loadFromFile();
    int choice;

    do {
        std::cout << "\n==== Company Manager ====\n";
        std::cout << "1. Create Entry\n";
        std::cout << "2. Display Entries\n";
        std::cout << "3. Edit Entry\n";
        std::cout << "4. Delete Entry\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an option: ";
        std::cin >> choice;

        switch (choice) {
        case 1: createEntry(); break;
        case 2: displayEntries(); break;
        case 3: editEntry(); break;
        case 4: deleteEntry(); break;
        case 5: exitApp(); break;
        default: std::cout << "Invalid option. Try again.\n"; break;
        }
    } while (choice != 5);
}

void CompanyManager::createEntry() {
    system("cls");
    Company company;
    std::cout << "Enter company name: ";
    std::cin.ignore(); // Clear newline from previous input
    std::getline(std::cin, company.name);
    std::cout << "Enter annual net revenue: ";
    std::cin >> company.revenue;
    companies.push_back(company);
    sortCompaniesByRevenue();
    std::cout << "Entry added.\n";
    system("pause");
    system("cls");
    saveToFile();

}

void CompanyManager::displayEntries() const {
    system("cls");
    if (companies.empty()) {
        std::cout << "No entries available.\n";
        system("pause");
        system("cls");
        return;
    }

    std::cout << "\nCompany List (sorted by revenue):\n";
    for (size_t i = 0; i < companies.size(); ++i) {
        std::cout << i + 1 << ". " << companies[i].name
            << " - $" << formatWithCommas(companies[i].revenue) << "\n";
    }
    system("pause");
    system("cls");
}

void CompanyManager::editEntry() {
    system("cls");
    if (companies.empty()) {
        std::cout << "No entries to edit.\n";
        system("pause");
        system("cls");
        return;
    }
    if (companies.empty()) {
        std::cout << "No entries available.\n";
        system("pause");
        system("cls");
        return;
    }

    std::cout << "\nCompany List (sorted by revenue):\n";
    for (size_t i = 0; i < companies.size(); ++i) {
        std::cout << i + 1 << ". " << companies[i].name
            << " - $" << formatWithCommas(companies[i].revenue) << "\n";
    }
    std::cout << "Enter the number of the company to edit: ";
    size_t index;
    std::cin >> index;

    if (index == 0 || index > companies.size()) {
        std::cout << "Invalid index.\n";
        system("pause");
        system("cls");
        return;
    }
    std::cout << "Enter new annual net revenue for "
        << companies[index - 1].name << ": ";
    std::cin >> companies[index - 1].revenue;
    sortCompaniesByRevenue();
    system("cls");
    std::cout << "Entry updated.\n";
    system("pause");
    system("cls");
    saveToFile();
}

void CompanyManager::deleteEntry() {
    system("cls");
    if (companies.empty()) {
        std::cout << "No entries to delete.\n";
        system("pause");
        system("cls");
        return;
    }
    if (companies.empty()) {
        std::cout << "No entries available.\n";
        system("pause");
        system("cls");
        return;
    }

    std::cout << "\nCompany List (sorted by revenue):\n";
    for (size_t i = 0; i < companies.size(); ++i) {
        std::cout << i + 1 << ". " << companies[i].name
            << " - $" << formatWithCommas(companies[i].revenue) << "\n";
    }
    std::cout << "Enter the number of the company to delete: ";
    size_t index;
    std::cin >> index;

    if (index == 0 || index > companies.size()) {
        std::cout << "Invalid index.\n";
        system("pause");
        system("cls");
        return;
    }
    system("cls");
    companies.erase(companies.begin() + index - 1);
    std::cout << "Entry deleted.\n";
    system("pause");
    system("cls");
    saveToFile();
}

void CompanyManager::exitApp()
{
    system("cls");
    std::cout << "Session Terminated!" << std::endl;
    system("pause");
    system("cls");
}

void CompanyManager::sortCompaniesByRevenue() {
    std::sort(companies.begin(), companies.end(),
        [](const Company& a, const Company& b) {
            return a.revenue > b.revenue;
        });
}

void CompanyManager::saveToFile() const {

    std::ofstream outFile(dataFile);
    if (!outFile) {
        std::cerr << "Error saving file.\n";
        return;
    }

    for (const auto& company : companies) {
        outFile << company.name << "|" << company.revenue << "\n";
    }
}

void CompanyManager::loadFromFile() {
    companies.clear();  // Ensure we start fresh

    std::ifstream inFile(dataFile);
    if (!inFile) {
        // No file? First run maybe, just return
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        Company company;
        std::string revenueStr;

        if (std::getline(iss, company.name, '|') &&
            std::getline(iss, revenueStr)) {
            company.revenue = std::stod(revenueStr);
            companies.push_back(company);
        }
    }

    sortCompaniesByRevenue();
}