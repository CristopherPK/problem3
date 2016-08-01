//
//  graph.hpp
//  problem3
//
//  Created by Cristopher Freitas on 7/31/16.
//  Copyright © 2016 Cristopher Freitas. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <iostream>
#include <vector>
#include "node.hpp"

using namespace std;

class Graph {
    Node * curr;
    vector<vector<int>> distances;
    
public:
    Graph();
    vector<int> generateGenome(int start);
    vector<int> permute(vector<int> * genome);
    bool isConnect(int v1, int v2);
    int getFitness(vector<int> genome);
    int travel(int start);
};

#endif /* graph_hpp */
