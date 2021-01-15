// By Dominykas, 2021
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <fstream>
#include <regex>
#include <map>
#include <iomanip>
using std::string;
using std::cout;
using std::set;
using std::endl;

std::list<string> list_from_string(string str)
{
    std::list<string> pseudo_word_list;
    string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            pseudo_word_list.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    pseudo_word_list.push_back(word);
    return pseudo_word_list;
}

int main() {
    string file_name = "C:\\Users\\minyk\\CLionProjects\\untitled1\\tekstas.txt";
    std::ifstream MyReadFile(file_name);
    if (!MyReadFile) {
        cout << "\nNepavyko pasiekti failo, pasitkrinkite ar jis tikrai tokiu pavadinimu.\n";
        exit(1);
    }
    cout << "Pavyko atidaryti faila... \n";
    std::multimap< string, int> my_map;
    set<string> web_set;
    // regex expression for words
    std::regex regexp("[A-z|ž|ū|ų|š|į|ė|ę|č|ą|Ą|Č|Ę|Ė|Į|Š|Ų|Ū|Ž]+");

    // flag type for determining the matching behavior (in this case on string objects)
    std::smatch m;

    std::regex reg_for_web("w{3}\\.[A-z|0-9]+\\.(?:...|..)");
    std::smatch w;
    int line_number = 1;

    while (!MyReadFile.eof()) {
        string line;
        getline(MyReadFile, line);
        std::list<string> word_list = list_from_string(line);
        for(auto str : word_list){
            regex_search(str, m, regexp);
            regex_search(str, w, reg_for_web);
            for (auto x : m)
              my_map.insert(std::make_pair(x, line_number));
            for (auto x : w)
                web_set.insert(x);
        }

        line_number = line_number + 1;

    }
    MyReadFile.close();


    std::map< string, std::list<int>> map_with_list;
    for (auto it = my_map.begin(); it != my_map.end(); ++it){
        std::list<int> line_list;
        for (auto it_inner = my_map.begin(); it_inner != my_map.end(); ++it_inner){
            if (it->first == it_inner->first){
                line_list.push_back(it_inner->second);
            }
        }
        map_with_list.insert(std::make_pair(it->first,line_list));
        //my_map.erase(it->first);

    }

    file_name = "C:\\Users\\minyk\\CLionProjects\\untitled1\\rezultatas.txt";
    std::ofstream MyOutputFile;
    MyOutputFile.open(file_name);
    MyOutputFile << '\t' << std::left << std::setw(20) << "Zodis" << std::setw(10) << "Kiekis" << '\t' << "Eilutes kur pasikartojo" << std::endl;
    MyOutputFile << "--------------------------------------------------------------------------------------------------" << std::endl;
    for (auto it = map_with_list.begin(); it != map_with_list.end(); ++it){
        if (it->second.size() > 1){
            MyOutputFile  << '\t' << std::left << std::setw(20) << it->first  << std::left << std::setw(10)  << it->second.size() << '\t';
            for (auto x : it->second)
                MyOutputFile<< x << " ";
            MyOutputFile << '\n';
        }
    }
    MyOutputFile.close();

    file_name = "C:\\Users\\minyk\\CLionProjects\\untitled1\\url.txt";
    std::ofstream URL_file;
    URL_file.open(file_name);
    for (auto x : web_set){
        URL_file << x << std::endl;
    }

    return 0;
}
