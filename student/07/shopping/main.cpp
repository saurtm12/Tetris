/*
 * Desc:
 * This  program aim to store all the information about the product of
 * different stores of different chain.
 * The program is able to read the input products given in files and
 * store them in containers, which product has information about its
 * price  or OUT OF STOCK.
 * Some main functions that program may do are listing all the chains,
 * listing all the stores of a chain, print status/price of a specific
 * product of a store, listing all the product and find the cheapest
 * place which sells a product.
 *
 *
 * Program author
 * Name: Nghia Duc Hong
 * Student number: 292119
 * UserID: vsduho
 * E-Mail: duc.hong@tuni.fi
 *
 *
 *
 * */



#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <bits/stdc++.h>

//declare constant.
const double out_of_stock = -1;
const int SUCCESS = 0, FAIL = 1;

//declare a stuct that contains information about product :
struct Product
{
    std::string product_name;
    double price;
    Product(std::string _product_name,double _price)
    {
        this->product_name = _product_name;
        this->price = _price;
    }

};

/*This function is copied from exercise 6.2, which is similar to
 * the exercise 4.3.2. This function has functionality that
 * devide an original line into different strings that
 * are seperated by a delimiter.
 * Parameter s : the original string
 * Parameter delimiter : the delimiter that separates strings
 * in line
 * Parameter ignore_empty : determine that if we want to skip
 * or keep the empty word between two consecutive delimiter.
*/
std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false);

/* This function add product information into the chains.
 * parameter Chains:  reference for Chains, because we would like to
 * add information to STL Chains.
 * parameter strings: a vector that will have 4 element if the input file
 * works properly, contain the following element in order :
 * 1. Chain's name.
 * 2. Store's name.
 * 3. Product's name.
 * 4. Corresponding price.
*/
bool add_product(std::map < std::string,
                 std::map < std::string , std::vector < Product > > > & Chains,
                 std::vector<std::string> strings);


bool proceed_command(std::string command_line,
                     std::map<std::string,
                     std::map<std::string, std::vector<Product> > > Chains);
bool chain_command(std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool store_command(std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool selection_command(std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool cheapest_command(std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool products_command(std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
int main()
{
    /*Declare container.
    //Our container is a map that have the chain's name as a key,
    that map to another map.
    This latter map contains keys as different stores of this chain,
    then every key (store) has an vector which stores every element
    is the struct: Product that this store contains.
    */
    std::map < std::string,
            std::map < std::string , std::vector < Product > > > Chains;


    //Read the file.
    std::string ifile_name;
    std::cout<<"Input file: ";
    getline(std::cin, ifile_name);
    std::ifstream input_file(ifile_name);
    if (!input_file)
    {
        std::cout<<"Error: the input file cannot be opened";
        return EXIT_FAILURE;
    }

   //if reading file success, then store them in the chosen container.
    std::string line ="";
    while (getline(input_file,line))
    {
        std::vector<std::string> strings = split(line, ';', true);
        bool current_status = add_product(Chains,strings);
        if (current_status == FAIL)
        {
            std::cout<<"Error: the input file has an erroneous line";
            return EXIT_FAILURE;
        }
    }
    //proceeding user's command



/*
    for (auto chain :Chains)
        for (auto store : chain.second)
            for (auto product : store.second)
                std::cout<<chain.first<<" "<<store.first<< " " <<product.product_name<<" " <<product.price<<"\n";
*/
    while (true)
    {
        std::cout<<"> ";
        std::string command;
        getline(std::cin, command);
        if (command == "quit")
        {
            return EXIT_SUCCESS;
        }
        proceed_command(command,Chains);
    }


    return EXIT_SUCCESS;
}




std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(! (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if( ! (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


bool add_product(std::map < std::string,
                 std::map < std::string , std::vector < Product > > > & Chains,
                 std::vector<std::string> strings)
{
    //check if the vector contains 4 elements. If not, return FAIL value in
    //processing add_product.
    if ( strings.size() != 4 )
    {
        return FAIL;
    }


    double Product_price ;
    if (strings[3] == "out-of-stock")
        {
        Product_price = out_of_stock;
        }
    else
    {

        Product_price =std::stod(strings.at(3));
        //check if the price of a product must be a positive double. If not,
        //return FAIL value in processing add_product.
        if ( Product_price <= 0  )
        {
        return FAIL;
        }
    }
    //if notthing happen, then proceed adding information.
    std::string Chain_name = strings[0],
                Store_name = strings[1],
                Product_name = strings[2];
    //find if the chain has been stored, if not, insert the new chain.
    if ( Chains.find(Chain_name) == Chains.end() )
    {
        Chains.insert( { Chain_name, {} } );
    }
    //this iterator points to the current chain.
    std::map < std::string,
          std::map < std::string ,
            std::vector < Product > > >::iterator
            Chain_iter = Chains.find(Chain_name);
    //find if the store has been added to the chain,
    //if not, insert a new store.
    if ( Chain_iter->second.find(Store_name) == Chain_iter->second.end() )
    {
        Chain_iter->second.insert( { Store_name, {} } );
    }
    //this iterator point to the current store.
    std::map < std::string
            , std::vector < Product > >::iterator
            Store_iter = Chain_iter->second.find(Store_name);

    //add this product to the vector of the store.
    /* now, if the product has been added to this store
     * before, we only have to change only the price.
     * If not, add a new product.
    */
    bool has_been_added = false;
    std::vector < Product >::iterator product_iterator;
    for (product_iterator = Store_iter->second.begin();
         product_iterator != Store_iter->second.end();
         product_iterator++)
    {
        if (product_iterator-> product_name == Product_name)
        {
            product_iterator->price = Product_price;
            has_been_added = true;
        }
    }
    if (has_been_added == false)
    {
        Product product(Product_name,Product_price);
        Store_iter->second.push_back(product);
    }
    return SUCCESS;
}


bool proceed_command(std::string command_line,
    std::map < std::string,
                std::map < std::string , std::vector < Product > > > Chains)
{
    std::vector < std::string > strings_command = split(command_line,' ',true);
    std::string command = strings_command.at(0);
    if (command == "chains")
    {
        chain_command(strings_command, Chains);
        return SUCCESS;
    }
    if (command == "stores")
    {
        store_command(strings_command, Chains);
        return SUCCESS;
    }
    if (command == "selection")
    {
        selection_command(strings_command, Chains);
        return SUCCESS;
    }
    if (command == "cheapest")
    {
        store_command(strings_command, Chains);
        return SUCCESS;
    }
    if (command == "products")
    {
        products_command(strings_command, Chains);
        return SUCCESS;
    }

    //if the command is not listed above, it is unknown command:
    std::cout << "Error: unknown command: "<<command_line<<"\n";
    return FAIL;
}

bool chain_command(std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains)
{
    if (strings_command.size() == 1)
    {
        for (auto chain : Chains)
        {
        std::cout<<chain.first<<"\n";
        }
        return SUCCESS;
    }
    else std::cout<< "Error: error in command chains";
    return FAIL;
}
bool store_command(std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains)
{
    return SUCCESS;
}
bool selection_command(std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains)
{
    return SUCCESS;
}
bool cheapest_command(std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains)
{
    return SUCCESS;
}
bool products_command(std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains)
{
    return SUCCESS;
}

