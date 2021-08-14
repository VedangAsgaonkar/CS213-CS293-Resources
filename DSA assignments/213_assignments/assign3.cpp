#include<cassert>

class Node{
    public:
        int data;
        Node* tr;
        Node* tl;
        Node* br;
        Node* bl;
        Node();
        Node(const Node& node);
        void transform(int x1, int x2, int y1, int y2, int n, int& b);
        void setData(int b);
        void disjunction(Node* node);
        void conjunction(Node* node);
        void complement();
        int getMax();
        void blurOut(int depth);
        ~Node();
};

Node::Node(){
    tr = nullptr;
    tl = nullptr;
    br = nullptr;
    bl = nullptr;
    data = 0;
}

Node::Node(const Node& node){
    this->data = node.data;
    if(node.tr != nullptr){
        this->tr = new Node(*node.tr);
    }
    else{
        this->tr = nullptr;
    }
    if(node.tl != nullptr){
        this->tl = new Node(*node.tl);
    }
    else{
        this->tl = nullptr;
    }
    if(node.br != nullptr){
        this->br = new Node(*node.br);
    }
    else{
        this->br = nullptr;
    }
    if(node.bl != nullptr){
        this->bl = new Node(*node.bl);
    }
    else{
        this->bl = nullptr;
    }
}

void Node::transform(int x1, int x2, int y1, int y2, int n, int& b){
    if(data==-1){
        if(x1==0 && x2==(1<<n)-1 && y1==0 && y2==(1<<n)-1){
            delete tl;
            delete tr;
            delete bl;
            delete br;
            data = b ;
        }
        else{
            if(x1<=(1<<(n-1))-1 && y1<=(1<<(n-1))-1){
                tl->transform(x1, ( x2 >= (1<<(n-1)) ? (1<<(n-1))-1 : x2 ) , y1, ( y2 >= (1<<(n-1)) ? (1<<(n-1))-1 : y2 ) , n-1 , b );
            }
            if(x2 > (1<<(n-1))-1 && y1<=(1<<(n-1))-1){
                tr->transform( (x1 > (1<<(n-1))-1 ? x1-(1<<(n-1)) : 0) , x2-(1<<(n-1)) , y1, ( y2 >= (1<<(n-1)) ? (1<<(n-1))-1 : y2 ) , n-1, b );
            }
            if(y2 > (1<<(n-1))-1 && x1<=(1<<(n-1))-1){
                bl->transform( x1 , ( x2 >= (1<<(n-1)) ? (1<<(n-1))-1 : x2 ), (y1 > (1<<(n-1))-1 ? y1-(1<<(n-1)) : 0), y2-(1<<(n-1)) , n-1, b );
            }
            if(x2 > (1<<(n-1))-1 && y2 > (1<<(n-1))-1 ){
                br->transform((x1 > (1<<(n-1))-1 ? x1-(1<<(n-1)) : 0) , x2-(1<<(n-1)) , (y1 > (1<<(n-1))-1 ? y1-(1<<(n-1)) : 0) ,  y2-(1<<(n-1)) , n-1, b  );
            }
        }
    }
    else{
        if(x1==0 && x2==(1<<n)-1 && y1==0 && y2==(1<<n)-1){
            data = b ;
        }
        else{
            data = -1 ;
            tr = new Node();
            tl = new Node();
            br = new Node();
            bl = new Node();
            if(x1<=(1<<(n-1))-1 && y1<=(1<<(n-1))-1){
                tl->transform(x1, ( x2 >= (1<<(n-1)) ? (1<<(n-1))-1 : x2 ) , y1, ( y2 >= (1<<(n-1)) ? (1<<(n-1))-1 : y2 ) , n-1 , b );
            }
            if(x2 > (1<<(n-1))-1 && y1<=(1<<(n-1))-1){
                tr->transform( (x1 > (1<<(n-1))-1 ? x1-(1<<(n-1)) : 0) , x2-(1<<(n-1)) , y1, ( y2 >= (1<<(n-1)) ? (1<<(n-1))-1 : y2 ) , n-1, b );
            }
            if(y2 > (1<<(n-1))-1 && x1<=(1<<(n-1))-1){
                bl->transform( x1 , ( x2 >= (1<<(n-1)) ? (1<<(n-1))-1 : x2 ), (y1 > (1<<(n-1))-1 ? y1-(1<<(n-1)) : 0), y2-(1<<(n-1)) , n-1, b );
            }
            if(x2 > (1<<(n-1))-1 && y2 > (1<<(n-1))-1 ){
                br->transform((x1 > (1<<(n-1))-1 ? x1-(1<<(n-1)) : 0) , x2-(1<<(n-1)) , (y1 > (1<<(n-1))-1 ? y1-(1<<(n-1)) : 0) ,  y2-(1<<(n-1)) , n-1, b  );
            }
        }
    }
}

void Node::setData(int b){
    assert(b>=0);
    data = b ;
    delete tr;
    delete tl;
    delete br;
    delete bl;
}

void Node::disjunction(Node* node){
    if(data==-1 && node->data==-1){
        tl->disjunction(node->tl);
        tr->disjunction(node->tr);
        bl->disjunction(node->bl);
        br->disjunction(node->br);
    }
    else if(data==1 || node->data==1){
        setData(1);
    }
    else if(data==0 && node->data==-1){
        data = -1;
        tl = new Node();
        tr = new Node();
        bl = new Node();
        br = new Node();
        tl->disjunction(node->tl);
        tr->disjunction(node->tr);
        bl->disjunction(node->bl);
        br->disjunction(node->br);
    }
    else if(node->data==-1 && data==0){
        ;
    }
    else{
        setData(0);
    }
}

void Node::conjunction(Node* node){
    if(data==-1 && node->data==-1){
        tl->conjunction(node->tl);
        tr->conjunction(node->tr);
        bl->conjunction(node->bl);
        br->conjunction(node->br);
    }
    else if(data==0 || node->data==0){
        setData(0);
    }
    else if(data==1 && node->data==-1){
        data = -1;
        tl = new Node();
        tr = new Node();
        bl = new Node();
        br = new Node();
        tl->disjunction(node->tl);
        tr->disjunction(node->tr);
        bl->disjunction(node->bl);
        br->disjunction(node->br);
    }
    else if(node->data==-1 && data==1){
        ;
    }
    else{
        setData(1);
    }
}

void Node::complement(){
    if(data>=0){
        data = 1-data;
    }
    else{
        tl->complement();
        tr->complement();
        bl->complement();
        br->complement();
    }
}

int Node::getMax(){
    if(data>=0){
        return data;
    }
    else{
        int x = tl->getMax() + tr->getMax() + bl->getMax() + br->getMax();
        if(x>=2){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void Node::blurOut(int depth){
    if(depth==0){
        setData(getMax());
    }
    else{
        if(data==-1){
            tl->blurOut(depth-1);
            tr->blurOut(depth-1);
            bl->blurOut(depth-1);
            br->blurOut(depth-1);
        }
    }
}

Node::~Node(){
    if(tr != nullptr){
        delete tr;
    }
    if(tl != nullptr){
        delete tl;
    }
    if(br != nullptr){
        delete br;
    }
    if(bl != nullptr){
        delete bl;
    }
}

class QuadTree{
    private:
        int n;
    public:
        Node* root;
        QuadTree(int n);
        QuadTree(const QuadTree& q);
        void set(int x1, int y1, int x2, int y2, int b);
        int get(int x1, int y1);
        int size() const;
        void overlap(QuadTree const &Q);
        void intersect(QuadTree const &Q);
        void complement();
        void resize(int m);
        void extract(int x1, int y1, int m);
        ~QuadTree();
};

QuadTree::QuadTree(int n){
    this->n = n;
    root = new Node();
}

QuadTree::QuadTree(const QuadTree& q){
    root = new Node(*q.root);
}

QuadTree::~QuadTree(){
    delete root;
}

void QuadTree::set(int x1, int y1, int x2, int y2, int b){

    root->transform(x1,x2,y1,y2,b,n);
}

int QuadTree::get(int x1, int y1){
    Node* ptr = root ;
    int num = n ;
    int x = x1;
    int y = y1;
    while(ptr->data <0 ){
        if(x < (1<<(n-1)) && y < (1<<(n-1))){
            n = n-1;
            ptr = ptr->tl ;
        }
        else if(x < (1<<(n-1)) && y >= (1<<(n-1))){
            y = y - (1<<(n-1)) ;
            n = n-1;
            ptr = ptr->tr;
        }
        else if(y < (1<<(n-1)) && x >= (1<<(n-1))){
            x = x - (1<<(n-1)) ;
            n = n-1;
            ptr = ptr->bl;
        }
        else{
            y = y - (1<<(n-1)) ; 
            x = x - (1<<(n-1)) ;
            n = n-1;
            ptr = ptr->br;
        }
    }
    return ptr->data;
}

int QuadTree::size() const{
    return n;
}

void QuadTree::overlap(QuadTree const &Q){
    root->disjunction(Q.root);
}

void QuadTree::intersect(QuadTree const &Q){
    root->conjunction(Q.root);
}

void QuadTree::complement(){
    root->complement();
}

void QuadTree::resize(int m){
    if(m>=n){
        n = m;
    }
    else{
        root->blurOut(n-m);
    }
}

void QuadTree::extract(int x1, int y1, int m){
    
}