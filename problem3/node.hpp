//
//  node.hpp
//  problem3
//
//  Created by Cristopher Freitas on 7/31/16.
//  Copyright © 2016 Cristopher Freitas. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <stdio.h>

class Node {
    int state;
    bool visited;
    Node * prev;
    
public:
    Node(int state);
    void setPrev(Node * prev);
};
#endif /* node_hpp */
