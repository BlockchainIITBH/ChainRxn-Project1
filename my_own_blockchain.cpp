#include <bits/stdc++.h>
using namespace std;

void create_hash(const string &input,string &output){
    unsigned long hash =0;
    for (char c:input){
        hash=(hash*131)+static_cast <unsigned char>(c);
    }
    ostringstream oss;
    oss<<hex<<hash;
    output=oss.str();
}

struct Block{
    int index;
    string timestamp;
    string data;
    string prev_hash;
    string hash;
    Block* next;
};

void get_timestamp(string &buffer){
    time_t now=time(nullptr);
    tm*tm_ptr =localtime(&now);
    ostringstream oss;
    oss << put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");
    buffer = oss.str();
}

Block* create_block(int index, string &data, string prev_hash){
    Block* newBlock=new Block();
    newBlock->index=index;
    newBlock->data =data;
    get_timestamp(newBlock->timestamp);
    newBlock->prev_hash=prev_hash;

    ostringstream ss;
    ss << newBlock->index << newBlock->timestamp << newBlock->data << newBlock->prev_hash;
    create_hash(ss.str(),newBlock->hash);

    newBlock->next= nullptr;
    return newBlock;
}

void add_block(Block *&head, string data){
    if(!head){
        head = create_block(0,data, "0");
        return;
    }
    auto curr=head;
    while(curr->next){
        curr=curr->next;
    }
    int newIndex=curr->index+1;
    string prevhash=curr->hash;
    curr->next=create_block(newIndex,data,prevhash);
}

void print_chain(Block* head){
    auto curr =head;
    while(curr){
        cout<<"Block "<<curr->index<<"\n"
            <<"  Timestamp:    "<<curr->timestamp<<"\n"
            <<"  Data:         "<<curr->data<<"\n"
            <<"  PreviousHash: "<<curr->prev_hash<<"\n"
            <<"  Hash:         "<<curr->hash<<"\n\n";
        curr=curr->next;
    }
}

int main(){
    Block* blockchain =nullptr;
    add_block(blockchain,"Genesis Block");
    add_block(blockchain,"transaction");
    add_block(blockchain, "2nd transaction");
    
    print_chain(blockchain);
    return 0;
}