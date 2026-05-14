const int Log = 32;
struct BitTrie {
   int cur;
   vector<array<int,2>> nxt;
   vector<array<int,2>> cnt; 

   BitTrie(int n){
      cur = 1;
      nxt = vector<array<int,2>>((n+5)*Log, {-1,-1});
      cnt = vector<array<int,2>>((n+5)*Log, {0,0});
   }

   void insert(int x){
      int node = 0;
      for(int i = Log-1; i >= 0; i--){
         int bt = (x >> i) & 1;

         if(nxt[node][bt] == -1) nxt[node][bt] = cur++;

         cnt[node][bt]++;        
         node = nxt[node][bt];
      }
   }

   void erase(int x){
      int node = 0;
      for(int i = Log-1; i >= 0; i--){
         int bt = (x >> i) & 1;

         if(nxt[node][bt] == -1) return; 

         cnt[node][bt]--;
         if(cnt[node][bt] == 0){
            nxt[node][bt] = -1;
            return; 
         }

         node = nxt[node][bt];
      }
   }

   int maxxor(int x){
      int node = 0, res = 0;

      for(int i = Log-1; i >= 0; i--){
         int bt = ((x >> i) & 1) ^ 1;

         if(nxt[node][bt] != -1){
            res |= (1LL << i);
            node = nxt[node][bt];
         } else if(nxt[node][bt ^ 1] != -1){
            node = nxt[node][bt ^ 1];
         } else break;
      }

      return res;
   }

   int minxor(int x){
      int node = 0, res = 0;

      for(int i = Log-1; i >= 0; i--){
         int bt = (x >> i) & 1;

         if(nxt[node][bt] != -1){
            node = nxt[node][bt];
         } else if(nxt[node][bt ^ 1] != -1){
            res |= (1LL << i);
            node = nxt[node][bt ^ 1];
         } else break;
      }

      return res;
   }
};