#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

class Reference {
public:
    Reference(std::string& author, std::string& title, std::string& year, std::string& page) :
        Author(author), Title(title), Year(year), Page(page) {}
    std::string Author;
    std::string Title;
    std::string Year;
    std::string Page;

    void Print() {
        std::cout << Author << ", " << Title << ", " << Year << ", " << Page << std::endl;
    }
};

bool cmp(const Reference& a, const Reference& b) {
    auto isRussian = [](const std::string& s) {
        return (s[0] >= 0 && s[0] <= 127);
    };
    if (isRussian(a.Title) && !isRussian(b.Title)) {
        return false;
    }
    else if (!isRussian(a.Title) && isRussian(b.Title)) {
        return true;
    }
    else {
        return (a.Title < b.Title);
    }
}

void printReferences(const std::vector<Reference>& references, bool withNumbers) {
    int i = 1;
    for (auto ref : references) {
        if (withNumbers) {
            std::cout << i << ". ";
        }
        ref.Print();
        i++;
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    std::vector<Reference> references;
    std::ifstream fl("lol.txt");
    if (!fl.is_open()) {
        std::cout << "Error opening file!!!" << std::endl;
    }
    else {
        std::string line;
        while (getline(fl, line)) {
            std::string author, title, year, page;
            std::istringstream iss(line);
            getline(iss, author, ',');
            getline(iss, year, ',');
            getline(iss, title, ',');
            iss >> page;
            Reference ref = { author, title, year, page };
            references.push_back(ref);
        }
    }
    std::sort(references.begin(), references.end(), cmp);

    printReferences(references, true);
    std::cout << std::endl;

    std::cout << "<==================================================================================>" << std::endl;
    printReferences(references, false);
    std::cout << std::endl;

    fl.close();
    return 0;
}
