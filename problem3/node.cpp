//
//  node.cpp
//  problem3
//
//  Created by Cristopher Freitas on 7/31/16.
//  Copyright © 2016 Cristopher Freitas. All rights reserved.
//

#include "node.hpp"

Node::Node(int state){
    this->state = state;
}

void Node::setPrev(Node * prev){
    this->prev = prev;
}