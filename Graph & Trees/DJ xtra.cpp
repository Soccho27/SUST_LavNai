const int N =int(2e5)+3,inf=int(1e16);
vector<pair<int,int>> g[N]; // in graph weight first & neighbour second
vector<int> dis(N,inf);
void SP(int source){
   priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
   dis[source]=0;          pq.push({0,source});
   par[source]=-1;        // if parent is necessary 
   while(!pq.empty()){
      int v=pq.top().second,wt=pq.top().first;  pq.pop();
      if(dis[v]<wt)    continue; 
      for(auto &it:g[v]){ 
         int child_v=it.second,child_wt=it.first;
         if(dis[v]+child_wt<dis[child_v]){
            par[child_v]=v;    // if parent is necessary 
            dis[child_v]=dis[v]+child_wt;
            pq.push({dis[child_v],child_v});
         }
      }
   }
}
