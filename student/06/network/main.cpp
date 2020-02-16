#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
int insert_relation(std::string id1, std::string id2,
                    std::map < std::string, std::vector <std::string> > & tree)
{
    std::map < std::string, std::vector <std::string> > ::iterator iter;
    iter = tree.find(id1);
    if (tree.find(id2)== tree.end())
    {
        tree.insert({id2,{}});
    }
    tree.insert({id2,{}});
    if (iter == tree.end())
    {
        tree.insert({id1,{id2}});

    }
    else {
        iter->second.push_back(id2);
    }
    return 0;

}
int P_command(std::string id, std::map < std::string, std::vector <std::string> > tree, std::set <std::string> &checked,int depth =0)
{

    checked.insert(id);
    for (int k =0; k<depth;k++)
    {
        std::cout<<"..";
    }
    std::cout<< id << std::endl;
    for (auto id_ : tree.at(id))
    {
        if (checked.find(id_) == checked.end())
            P_command(id_, tree, checked,depth+1);
    }
    return 0;
}

int C_command(std::string id, std::map < std::string, std::vector <std::string> > tree, std::set <std::string> &checked)
{
    checked.insert(id);
    if (tree.at(id).size() == 0)
        return 1;
    int S =0;
    for (auto id_ : tree.at(id))
    {

        if (checked.find(id_) == checked.end())
            S+= C_command(id_, tree, checked);
    }
    return S+1;
}


int D_command(std::string id, std::map < std::string, std::vector <std::string> > tree, std::set <std::string> &checked)
{
    checked.insert(id);
    if (tree.at(id).size() == 0)
        return 1;
    int S =0;
    for (auto id_ : tree.at(id))
    {

        if (checked.find(id_) == checked.end())
        {
                int K= D_command(id_, tree, checked);
                if (K > S )
                    S=K;
        }
    }
    return S+1;
}


int main()
{
    // TODO: Implement the datastructure here
    std::map < std::string, std::vector <std::string> > tree;



    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            insert_relation(id1,id2,tree);
        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;

            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::set <std::string> checked;
            P_command(id,tree,checked);
        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);
            std::set <std::string> checked;
            std::cout<< C_command(id,tree,checked) - 1<<std::endl;
            // TODO: Implement the command here!

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::set <std::string> checked;
            std::cout<< D_command(id,tree,checked) <<std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
