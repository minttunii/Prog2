#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards()
    : top_(nullptr)
{
}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data{id, nullptr};
    if(!is_empty()){
       new_card->next = top_;
    }
    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
   int order_number = 1;
   for(auto* current = top_;
       current != nullptr;
       current = current->next, ++order_number){
       s << order_number << ": " << (*current).data << std::endl;
   }
}

bool Cards::remove(int &id)
{
    if(is_empty()){
        return false;
    }

    auto* old_top = top_;
    top_ = old_top->next;
    id = old_top->data;

    delete old_top;

    return true;
}

bool Cards::bottom_to_top()
{
    if(is_empty()){
        return false;
    }

    auto* old_top = top_;

    auto* new_top = top_;
    Card_data* new_bottom = nullptr;

    for(; new_top->next != nullptr;
        new_bottom = new_top, new_top = new_top->next){
    }

    top_ = new_top;
    new_top->next = old_top;

    if(new_bottom != nullptr){
        new_bottom->next = nullptr;
    }

    return true;
}

bool Cards::top_to_bottom()
{
    if(is_empty()){
        return false;
    }

    auto* old_bottom = find_bottom();
    auto* new_bottom = top_;
    auto* new_top = top_->next;

    if(old_bottom != new_bottom){
        old_bottom->next = new_bottom;

    }
    new_bottom->next = nullptr;

    if(new_top != nullptr){
        top_ = new_top;
    }

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    recursive_print(top_, s);
}

Cards::~Cards()
{
    while(!is_empty()){
        int dummy;
        remove(dummy);
    }
}

bool Cards::is_empty() const
{
    return top_ == nullptr;
}

Card_data *Cards::find_previous_card(int id)
{
    Card_data* current = nullptr;

    for(current = top_;
        current != nullptr && current->next != nullptr && current->next->data != id;
        current = current->next){
    }
    return current;
}

Card_data *Cards::find_card(int id)
{
    Card_data* current = nullptr;

    for(current = top_;
        current != nullptr;
        current = current->next){

        if(current->data == id){
            break;
        }
    }
    return current;
}

Card_data *Cards::find_bottom()
{
    Card_data* current = nullptr;

    for(current = top_;
        current != nullptr && current->next != nullptr;
        current = current->next){

    }
    return current;
}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    if(top == nullptr){
        //kertoo alimaisen kortin
        return 1;
    }

    int running_number = recursive_print(top->next, s);
    s << running_number << ": " << top->data << std::endl;

    return running_number+1;
}
