//
//  graph.cpp
//  problem3
//
//  Created by Cristopher Freitas on 7/31/16.
//  Copyright © 2016 Cristopher Freitas. All rights reserved.
//

#include "graph.hpp"

Graph::Graph(){
    // initializing the distance cost matrix.
    this->distances.push_back({0,30,84,56,-1,-1,-1,-1,75,-1,80});
    this->distances.push_back({30,0,65,-1,-1,-1,70,-1,-1,40});
    this->distances.push_back({84,65,0,74,52,55,-1,60,143,48});
    this->distances.push_back({56,-1,74,0,135,-1,-1,20,-1,-1});
    this->distances.push_back({-1,-1,52,135,0,70,-1,122,98,80});
    this->distances.push_back({70,-1,55,-1,70,0,63,-1,82,35});
    this->distances.push_back({-1,70,-1,-1,-1,63,0,-1,120,57});
    this->distances.push_back({75,-1,135,20,122,-1,-1,0,-1,-1});
    this->distances.push_back({-1,-1,143,-1,98,82,120,-1,0,-1});
    this->distances.push_back({80,40,48,-1,80,35,57,-1,-1,0});
}


// creating genome based on cities.
vector<int> Graph::generateGenome(int start){
    vector<int> genome;
    // pushing start point.
    genome.push_back(start);
    for(int i=0; i < distances.size(); i++){
        if(i!=start){
            genome.push_back(i);
        }
    }
    // pushing end point.
    genome.push_back(start);
    return genome;
}

// verifying if nodes are connected.
bool Graph::isConnect(int v1, int v2){
    bool flag = false;
    
    if(this->distances[v1][v2] > 0){
        flag = true;
    }
    
    return flag;
}

int Graph::f(vector<int> genome){
    int score = 0;
    for(int i = 1; i < genome.size(); i++){
        if(distances[genome[i-1]][genome[i]] == -1){
            score += 1000000;
        } else {
            score += distances[genome[i-1]][genome[i]];
        }
    }
    return score;
}

// permuting genes to create the fittest.
vector<int> Graph::permute(vector<int> * genome){
    // initializing random seed.
    srand (time(NULL));
    for(int i=1; i < genome->size()-1; i++){
        if(!isConnect((*genome)[i-1], (*genome)[i])){
            int j = rand() % 9 + 1;
            int aux = (*genome)[i];
            (*genome)[i] = (*genome)[j];
            (*genome)[j] = aux;
        }
    }
    return *genome;
}

vector<int> Graph::doMutation(vector<int> * genome){
    srand (time(NULL));
    for(int k = 0; k < mutProb; k++){
        int i = rand() % 9 + 1;
        int j = rand() % 9 + 1;
        int aux = (*genome)[i];
        (*genome)[i] = (*genome)[j];
        (*genome)[j] = aux;
    }
    return *genome;
}

// generating the gene pool
vector<vector<int>> Graph::getGenePool(vector<int> genome){
    vector<vector<int>> pool;
    for(int i=0; i < 50; i++){
        pool.push_back(genome);
    }
    return pool;
}

// getting the fitness score.
int Graph::getFitness(vector<int> genome){
    int score = 0;
    for(int i=1;i<genome.size(); i++){
        if(isConnect(genome[i-1], genome[i])){
            score++;
        } else {
            break;
        }
    }
    return score;
}

vector<int> Graph::getFittest(vector<vector<int>> pool){
    vector<int> fittest = pool.front();
    for(int i = 1; i < pool.size(); i++){
        if(getFitness(fittest) < getFitness(pool[i])){
            if(getFitness(fittest) == 10 && getFitness(pool[i]) == 10){
                if(f(pool[i]) < f(fittest)){
                    fittest = pool[i];
                }
            } else {
                fittest = pool[i];
            }
        }
    }
    return fittest;
}

float Graph::evaluate(int score1, int score2){
    return float(score1)/float(score2);
}

int Graph::travel(int start){
    // creating start node
    start = start - 1;
    curr = new Node(start);
    curr->setPrev(NULL);
    
    vector<vector<int>> elite;
    
    // creating 'zero' generation
    int numGen = 0;
    vector<int> genome = generateGenome(start);
    mutProb = int(genome.size());
    vector<int> fittest = genome;
    
    while(true) {
        numGen++;
        vector<vector<int>> pool = getGenePool(genome);
        for(int i = 0; i < pool.size(); i++){
            doMutation(&pool[i]);
            permute(&pool[i]);
        }
        
        fittest = getFittest(pool);
        
        if(getFitness(fittest) > getFitness(genome)){
            mutProb--;
        } else {
            mutProb++;
        }
        
        genome = fittest;
        
        if(getFitness(genome) == 10 && elite.size() < 100){
            elite.push_back(genome);
        } else if(elite.size() == 100){
            break;
        }
    }
    
    cout << "n of generations: " << numGen << endl;
    
    vector<vector<int>>::iterator itg = elite.begin();
    while(itg != elite.end()){
        if(f(*itg) < f(fittest)){
            fittest = *itg;
        }
        
        cout << "fitness: " << getFitness(*itg);
        cout << ", score: " << f(*itg) << endl;
        
        itg++;
    }
    
    vector<int>::iterator itf = fittest.begin();
    while(itf != fittest.end()){
        cout << "," << *itf + 1;
        itf++;
    }
    cout << endl;
    cout << "fitness: " << getFitness(fittest);
    cout << ", score: " << f(fittest) << endl;
    
    return 0;
}
