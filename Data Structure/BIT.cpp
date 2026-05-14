struct BIT{ // 1-base query
   int sz;     vector<int> bit;
   BIT(int n){ sz=n;    bit.resize(sz+1,0);  }
   void update(int pos, int v){
      while(pos<=sz){
         bit[pos]+=v;
         pos=pos+(pos&(-pos));
      }
   }
   int sum(int pos){    int s=0;
      while(pos>0){
         s+=bit[pos];
         pos=pos-(pos&(-pos));
      }     
      return s;
   }
   int query(int l, int r)    return sum(r)-sum(l-1);
};
