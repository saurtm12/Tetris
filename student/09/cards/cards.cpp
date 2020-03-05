#include "cards.hh"
// TODO: Implement the methods here
Cards::Cards()
{
    top_ = nullptr;

}
void Cards::add(int id)
{
    Card_data* new_card = new Card_data;
    new_card->data = id;
    new_card->next = top_;
    this->top_ = new_card;
}
void Cards::print_from_top_to_bottom(std::ostream& s)
{
    int i = 1;
    Card_data* card = top_;
    while (card != nullptr)
    {
        s<<i++<<": "<<card->data<<std::endl;
        card = card->next;
    }

}
bool Cards::remove(int& id)
{
    if (top_ == nullptr)
        return false;
    id = top_->data;
    Card_data* card = top_;
    top_ = top_->next;
    delete card;
    return true;
}
bool Cards::bottom_to_top()
{
    if (top_ == nullptr)
        return false;
    Card_data* card = top_;
    Card_data* p_card = nullptr;
    while (card->next != nullptr)
    {
        p_card = card;
        card = card->next;
    }
    if (p_card == nullptr)
        return true;
    p_card->next = nullptr;
    card->next=top_;
    top_ = card;
    return true;
}

bool Cards::top_to_bottom()
{
    if (top_ == nullptr)
        return false;
    if (top_->next == nullptr)
        return true;


    Card_data* card = top_;

    while (card->next != nullptr)
    {

        card = card->next;
    }

    Card_data* temp = top_;
    top_ = top_->next;
    card->next = temp;
    temp->next = nullptr;
    return true;
}
void Cards::print_from_bottom_to_top(std::ostream& s){
    recursive_print(top_, s,1);
}
Cards::~Cards()
{
    Card_data* card = top_;
    while (top_!= nullptr)
    {
        card = top_;
        top_ = top_->next;
        delete card;
    }
}
int Cards::recursive_print(Card_data* top, std::ostream& s, int i)
{
    if (top == nullptr)
        return 0;
    recursive_print(top->next,s,i+1);
    s<<i<<": "<<top->data<<std::endl;
    return 0;

}

