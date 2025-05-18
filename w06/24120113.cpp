#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

struct Company {
	string name;
	string profit_tax;
	string address;
};
struct HashTable {
	vector<vector<Company>> listCompany;
};
Company createName(string line) {
	stringstream ss(line);
	Company company;

	getline(ss, company.name, '|');
	getline(ss, company.profit_tax, '|');
	getline(ss, company.address);

	return company;
}
vector<Company> readCompanyList(string file_name) {
	ifstream ifs(file_name);
	string line;
	vector<Company> list_company;
	if (!ifs.is_open()) {
		cout << "Can not open the input file." << endl;
		return list_company;
	}
	getline(ifs, line);
	while (getline(ifs, line)) {
		list_company.push_back(createName(line));
	}
	ifs.close();
	return list_company;
}
long long hashString(string company_name) {
	if (company_name.size() > 20) {
		company_name = company_name.substr(company_name.length() - 20);
	}
	int p = 31;
	int m = 2000;
	long long power = 1;
	long long hash_value = 0;
	for (int i = 0; i < company_name.size(); i++) {
		hash_value = (hash_value + (company_name[i] * power) % m) % m;
		power = (power *p) % m;
	}
	return (hash_value + m) % m;
}
HashTable* createHashTable(vector<Company> list_company) {
	HashTable* hashTable = new HashTable;
	hashTable->listCompany.resize(2000);
	for (auto &x: list_company) {
		hashTable->listCompany[hashString(x.name)].push_back(x);
	}
	return hashTable;
}
void insert(HashTable* hash_table, Company company) {
	hash_table->listCompany[hashString(company.name)].push_back(company);
}
Company* search(HashTable* hash_table, string company_name) {
	vector<Company> &bucket = hash_table->listCompany[hashString(company_name)];
	for (auto &x : bucket) {
		if (x.name == company_name) {
			return &x;
		}
	}
	return NULL;
}
void saveCompany(Company* company, ofstream &ofs) {
	ofs << company->name << "|" << company->profit_tax << "|" << company->address << endl;
}
int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Usage: ./main <MST.txt> <input.txt> <output.txt>" << endl;
		return 1;
	}
	string mstFile = argv[1];
	string inputFile = argv[2];
	string outputFile = argv[3];
	HashTable* hashTable = createHashTable(readCompanyList(mstFile));
	ifstream ifs(inputFile);
	ofstream ofs(outputFile, ios:: app);
	if (!ifs.is_open() || !ofs.is_open()) {
		cout << "Error opening input/ output file." << endl;
		return 1;
	}
	string companyName;
	while (getline(ifs, companyName)) {
		Company* company = search(hashTable, companyName);
		if (company != NULL) {
			saveCompany(company, ofs);
		}
	}
	ifs.close();
	ofs.close();
	delete hashTable;
}