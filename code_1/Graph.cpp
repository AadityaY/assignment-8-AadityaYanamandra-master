#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Graph::addVertex(string name){
    vertex* temp = new vertex;
    temp->name=name;
    vertices.push_back(temp);
    return;
}

void Graph::addEdge(string v1, string v2){
    vertex* vertex1=nullptr;
    vertex* vertex2=nullptr;
    for (int i=0; i<vertices.size(); i++) {
        if (vertices[i]->name==v1) {
            vertex1=vertices[i];
        } else if (vertices[i]->name==v2) {
            vertex2=vertices[i];
        }
    }
    if ((vertex1==nullptr)||(vertex2==nullptr)) {
        cout << "One of these vertices does not exist!" << endl;
        return;
    }
    adjVertex vx1 = {vertex1};
    adjVertex vx2 = {vertex2};
    vertex1->adj.push_back(vx2);
    vertex2->adj.push_back(vx1);
    return;
}

void Graph::displayEdges(){
    for (int i=0; i<vertices.size(); i++) {
        cout << vertices[i]->name << " --> ";
        for (int j=0; j<vertices[i]->adj.size(); j++) {
            cout << vertices[i]->adj[j].v->name << " ";
        }
        cout << endl;
    }
}

vector<vertex*> breadthFirstTraverseHelper(string sourceVertex, vector<vertex*> vertices){
    vertex* v=nullptr;
    for (int i=0; i<vertices.size(); i++) {
        if (vertices[i]->name==sourceVertex) {
            v=vertices[i];
        }
    }
    queue<vertex*> q;
    for (int i=0; i<vertices.size(); i++) {
        vertices[i]->distance=-1;
        vertices[i]->visited=false;
    }
    vector<vertex*> trail;
    v->distance=0;
    v->visited=true;
    q.push(v);
    while (!q.empty()) {
        vertex* vert = q.front();
        trail.push_back(vert);
        vertex* vertAdj = nullptr;
        q.pop();
        for (int j=0; j<vert->adj.size(); j++) {
            vertAdj=vert->adj[j].v;
            if (vertAdj->visited==false) {
                vertAdj->visited=true;
                vertAdj->distance=vert->distance+1;
                q.push(vertAdj);
            }
        }
    }
    return trail;
}

void Graph::breadthFirstTraverse(string sourceVertex){
    vector<vertex*> trail = breadthFirstTraverseHelper(sourceVertex, vertices);
    for (int i=0; i<trail.size(); i++) {
        if (i!=0) {
            cout << trail[i]->name << "(" << trail[i]->distance << ")" << " ";
        } else {
            cout << "Starting vertex (root): " << trail[i]->name << "-> ";
        }
    }
    cout << endl << endl;
}

/*
string::source : source vertex (starting city)
int::k : distance that you can travel from source city with remaining fuel
*/
vector<string> Graph::findReachableCitiesWithinDistanceK(string source, int k){
    vector<vertex*> trail = breadthFirstTraverseHelper(source, vertices);
    vector<string> reachableCities;
    for (int i=trail.size()-1; i>=0; i--) {
        if (trail[i]->distance==k) {
            reachableCities.push_back(trail[i]->name);
        }
    }
    return reachableCities;
}
