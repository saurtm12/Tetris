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
#include <set>


//declare constant.
const double out_of_stock = -1;
const int SUCCESS = 0, FAIL = 1;
const double MAX_DOUBLE = 1.79769e+308;

//declare a stuct that contains information about product :
struct Product
{
    std::string product_name;
    double price;
    //This function initialize the struct.
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
 * RETURN a vector includes all the separated words.
*/
std::vector< std::string > split(const std::string& s,
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
                 std::vector<std::string > strings);
/*This function is aim to compare the order of two product based on their
 * names. This function is used in sort algorithm when sorting a vector that
 * has Product elements and we want to sort them by their name.
 * Parameter : two Products that we want to compare.
 * RETURN false when the order of product_name of product 1
 *  is before product 2. And true when it happens in the opposite way.
 * we compare the correspoding char of two string (two product name)
 * then by order, we return the result compare them, if they are the same
 * , continue to compare the next couple chars. Then if a string
 * is a substring of the other, the substring is the one need to has the
 * order before.
*/

bool Compare_two_Product( Product product1,Product product2 )
{
    int min_size;
    std::string name1 = product1.product_name, name2 = product2.product_name;

    //determine which string has shorter length.
    if ( name1.size() > name2.size() )
        min_size = name2.size();
    else
        min_size = name1.size();

    for ( int i =0; i<= min_size; i++ )
    {
        if ( name1[i] < name2[i] )
            return true;
        if ( name1[i] > name2[i] )
            return false;
    }
    //if it is the end of the shorter string, the one who has the shorter
    //length is before.
    return name1.size()<name2.size();
}

/*  This function proceed command, compares command with the used one,
 * then call them.
 * Parameter : a string is the whole line command.
 *             Chains : our database.
 * RETURN FAIL when the command is unknown
 *        SUCCESS when command is proceeded successfully.
*/
bool proceed_command( std::string command_line,
                      std::map<std::string,
                      std::map<std::string, std::vector<Product> > > Chains);


/*Those functions do the command that user require.
 * The first part of name of the function expresses what is the
 * corresponding command.
 * Parameter : vector strings command includes the the seperated words in
 * commandline
 *             Chains : the Data structure;
 * Return FAIL if the command is not recognised.
 *        SUCCESS if the command is conducted well.
*/
bool chain_command( std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool store_command( std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool selection_command( std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool cheapest_command( std::vector < std::string > strings_command,
    std::map < std::string,
               std::map < std::string , std::vector < Product > > > Chains);
bool products_command( std::vector < std::string > strings_command,
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
    getline( std::cin, ifile_name );
    std::ifstream input_file( ifile_name );
    if ( !input_file)
    {
        std::cout<<"Error: the input file cannot be opened";
        return EXIT_FAILURE;
    }

   //if reading file success, then store them in the chosen container.
    std::string line ="";
    while ( getline( input_file,line ) )
    {
        std::vector< std::string> strings = split(line, ';', true);
        bool current_status = add_product( Chains,strings );
        if ( current_status == FAIL )
        {
            std::cout<<"Error: the input file has an erroneous line";
            return EXIT_FAILURE;
        }
    }
    input_file.close();

    //proceeding user's command
    //if command = "quit", return EXIT_SUCCESS.
    while (true)
    {
        std::cout<<"> ";
        std::string command;
        getline( std::cin, command );
        if ( command == "quit" )
        {
            return EXIT_SUCCESS;
        }
        proceed_command( command,Chains );
    }


    return EXIT_SUCCESS;
}


//This function is plainly copied from the previous exercise.
//Split a line to words.
//RETURN a vector contains all of them.
std::vector<std::string> split( const std::string& s,
                                const char delimiter,
                                bool ignore_empty )
{
    std::vector<std::string> result;
    std::string tmp = s;

    while( tmp.find(delimiter) != std::string::npos )
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

/* This function add information from the file to the data structre.
 * Parameter : a vector  contains strings and should have size of 4:
 * Inlcuding all information of a  specific product.
 *             Chains : our data structure (use reference because we
 * want to change it)
 * RETURN FAIL if the file is not appropriate.
 *        SUCCESS if the file is read successfully.
*/
//we have to check if the chain/store is in already in the data structure.
//if not, insert them.

bool add_product( std::map < std::string,
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
    if ( strings[3] == "out-of-stock" )
        {
        Product_price = out_of_stock;
        }
    else
    {

        Product_price = std::stod( strings.at(3) );
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
    if ( Chains.find( Chain_name) == Chains.end() )
    {
        Chains.insert( { Chain_name, {} } );
    }
    //this iterator points to the current chain.
    std::map < std::string,
          std::map < std::string ,
            std::vector < Product > > > :: iterator
            Chain_iter = Chains.find(Chain_name);
    //find if the store has been added to the chain,
    //if not, insert a new store.
    if ( Chain_iter->second.find(Store_name) == Chain_iter->second.end() )
    {
        Chain_iter->second.insert( { Store_name, {} } );
    }
    //this iterator point to the current store.
    std::map < std::string
            , std::vector < Product > > :: iterator
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
        if ( product_iterator-> product_name == Product_name )
        {
            product_iterator->price = Product_price;
            has_been_added = true;
        }
    }
    if ( has_been_added == false )
    {
        Product product( Product_name,Product_price );
        Store_iter->second.push_back( product );
    }
    return SUCCESS;
}

/* Proceed command.
 * find the command then call it.
*/
bool proceed_command( std::string command_line,
    std::map < std::string,
                std::map < std::string , std::vector < Product > > > Chains )
{
    std::vector < std::string > strings_command = split(command_line,' ',true);
    if ( command_line.size() == 0 )
    {
        std::cout<<"Error: unknown command: \n";
        return FAIL;
    }
    std::string command = strings_command.at(0);
    if ( command == "chains" )
    {
        chain_command(strings_command, Chains);
        return SUCCESS;
    }
    if ( command == "stores" )
    {
        store_command(strings_command, Chains);
        return SUCCESS;
    }
    if ( command == "selection" )
    {
        selection_command(strings_command, Chains);
        return SUCCESS;
    }
    if ( command == "cheapest" )
    {
        cheapest_command(strings_command, Chains);
        return SUCCESS;
    }
    if ( command == "products" )
    {
        products_command( strings_command, Chains );
        return SUCCESS;
    }

    //if the command is not listed above, it is unknown command:
    std::cout << "Error: unknown command: "<<command_line<<"\n";
    return FAIL;
}

/* Chain command is plainly list all the chains store in the keys of the map.
*/
bool chain_command( std::vector < std::string > strings_command,
         std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains )
{
    if ( strings_command.size() == 1 )
    {
        for ( auto chain : Chains )
        {
        std::cout<<chain.first<<"\n";
        }
        return SUCCESS;
    }
    else std::cout<< "Error: error in command chains\n";
    return FAIL;
}

/* store command plainly lists all the stores that in a chain.
 * They are the keys of the value correspoding to the key is chain name.
*/
bool store_command( std::vector < std::string > strings_command,
         std::map < std::string,
                    std::map < std::string , std::vector < Product > > > Chains )
{
    if ( strings_command.size() == 2 )
    {
        std::string Chain_name = strings_command.at(1);
        if ( Chains.find(Chain_name) == Chains.end() )
        {
            std::cout<<"Error: unknown chain name\n";
            return FAIL;
        }
        else
        {
            for ( auto store : Chains.at(Chain_name) )
            {
                std::cout<<store.first<<"\n";
            }
            return SUCCESS;
        }
    }else
    {
        std::cout<< "Error: error in command stores\n";
        return FAIL;
    }

}
/* Plainly listing the Products of a stores.
*/
bool selection_command( std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains )
{


    if ( strings_command.size() != 3 )
    {
       std::cout<<"Error: error in command selection \n";
       return FAIL;
    }
     else
    {
        std::string Chain_name = strings_command[1],
                    Store_name = strings_command[2];
        if ( Chains.find(Chain_name) == Chains.end() )
        {
            std::cout<<"Error: unknown chain name\n";
            return FAIL;
        }

        if ( Chains.at(Chain_name).find(Store_name)
                == Chains.at(Chain_name).end() )
        {
            std::cout<<"Error: unknown store\n";
            return FAIL;
        }
        //if all the conditions satisfy, then prin the list.
        std::vector <Product> ::iterator
                iter_begin = Chains.at(Chain_name).at(Store_name).begin(),
                iter_end = Chains.at(Chain_name).at(Store_name).end();
        //Because our STL container contains Products is a vector, we have
        //to sort them by name, and by the function implemented :
        // Compare_two_product.
        std::sort( iter_begin,iter_end,Compare_two_Product );
        for ( std::vector <Product> ::iterator iter
               = Chains.at(Chain_name).at(Store_name).begin();
               iter != iter_end; iter++)
        {
            if ( iter->price != out_of_stock )
            {
                std::cout<<iter->product_name<<" ";
                 printf("%.2f",iter->price);
                 std::cout<<"\n";
            }
            else
                std::cout<<iter->product_name<<" out of stock\n";

        }

    }

    return SUCCESS;
}


/* This function find the Cheapest stores that sell this product.
 * First  we assume that the price is infinity.
 * If we find a store that sell this product, then
 * variable :exist_product is true.
 * and if it is not out of stock,and its price is smaller
 * than temporay cheapest, so we clear the set that contains the
 * temporary set, then insert this new one.
 * When continuing to browse other stores, if the product is found
 * with the same price, then insert it but the cheapest value is
 * not changed.
*/
bool cheapest_command( std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains )
{
    if ( strings_command.size() != 2 )
    {
        std::cout<<"Error: error in command cheapest\n";
        return FAIL;
    }
    else
    {
        std::string find_product = strings_command.at(1);
        //locations is a set include all the stores that have the lowest price.
        std::set < std::string>  locations;
        double cheapest = MAX_DOUBLE;
        bool exist_product =false;
        for ( auto chain :Chains )
            for ( auto store : chain.second )
                for ( auto product : store.second )
                {
                    if ( product.product_name == find_product )
                    {
                        exist_product = true;

                        if ( product.price == cheapest )
                        {
                            locations.insert( chain.first+" "+ store.first );
                        }
                        else if ( product.price < cheapest
                                  && product.price != out_of_stock )
                        {
                            cheapest = product.price;
                            locations.clear();
                            locations.insert( chain.first+" "+ store.first );
                        }
                    }
                }

        //If there no stores sell this  product, notify
        if ( !exist_product )
        {
            std::cout<<"The product is not part of product selection\n";
            return FAIL;
        }
        // if all of the store is all out of stock, notify
        else if ( exist_product && cheapest == MAX_DOUBLE )
        {
            std::cout<<"The product is temporarily out of stock everywhere\n";
            return SUCCESS;
        }else
           //if not, print the final results are fromo the set
        {
            printf( "%.2f",cheapest );
            std::cout << " euros"<<"\n";

            for ( auto location : locations )
            {
            std::cout<< location<<"\n";
            }
        }
    }
    return SUCCESS;
}

//Browsing all the stores, insert them in a set, then print all of them.
bool products_command(std::vector < std::string > strings_command,
        std::map < std::string,
                   std::map < std::string , std::vector < Product > > > Chains)
{
    if ( strings_command.size() != 1 )
    {
        std::cout<<"Error: error in command products\n";
        return FAIL;
    }
    std::set < std::string > products;
    for ( auto chain :Chains )
        for ( auto store : chain.second )
            for ( auto product : store.second )
            {
                if ( products.find( product.product_name ) == products.end() )
                {
                    products.insert( product.product_name );
                }
            }
    for ( auto product : products )
        std::cout<<product<<"\n";
    return SUCCESS;
}

