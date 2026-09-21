#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std
class Solution {
  public:
    int spanningTree(int V, vector<vector<int>>& edges) {
       vector<vector<pair<int,int>>>adj(V);
       for(auto it:edges){
          adj[it[0]].push_back({it[1],it[2]});
          adj[it[1]].push_back({it[0],it[2]});
          
       }
       priority_queue<
       pair<int,pair<int,int>>,
       vector<<int,pair<int,int>>>,
       greater<<int,pair<int,int>>>pq;
       
       pq.push({0,{0,-1}});
       int total_dis=0;
       vector<pair<int,int>>mst;
       vector<int>vis(V,0);
       while(!pq.empty()){
           auto it:pq.top();
           int d =it.first;
           int node=it.second.first;
           int parent=it.second.second;
           pq.pop();
           for(auto i){}

           
       }
       
    }
};