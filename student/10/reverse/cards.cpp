#include <iostream>
#include <memory>
#include "cards.hh"

Cards::Cards(): top_( nullptr ) {
}

void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;
   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int& id)
{
    if (top_.get() == nullptr )
        return false;
    else
    {
        id = top_->data;
        top_ = top_->next;
        return true;
    }
}

void Cards::add_bottom(int x)
{
    if (top_.get() == nullptr)
    {
        add(x);
    }
    else
    {
        int id;
        remove(id);
        add_bottom(x);
        add(id);
    }
}

void Cards::reverse()
{
    if (top_.get() != nullptr)
    {
        int id;
        remove(id);
        reverse();
        add_bottom(id);
    }
}
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp
