const int SZ=int(1e6)+9;
const int B1=151,mod1=127657753;
const int B2=239,mod2=987654319;
vector<int> P1(SZ,1),P2(SZ,1);
void pow_cal(){
   for(int i=1;i<SZ;i++){
      P1[i]=(P1[i-1]*B1)%mod1;
      P2[i]=(P2[i-1]*B2)%mod2;
   }
}
class segHash{
public:
   int n;
   vector<int> T1,T2;
   segHash(const string& s){
      n=s.size();
      T1.assign(n*4+1,0);
      T2.assign(n*4+1,0);
      build(s,1,0,n-1);
   }

   void build(const string& s, int v, int tl, int tr){
      if(tl==tr){
         T1[v]=(s[tl]-'a'+1)%mod1;
         T2[v]=(s[tl]-'a'+1)%mod2;
         return;
      }
      int mid=(tl+tr)/2;
      build(s,v*2,tl,mid);
      build(s,v*2+1,mid+1,tr);
      T1[v]=(((T1[v*2]*P1[tr-mid])%mod1)+T1[v*2+1])%mod1;
      T2[v]=(((T2[v*2]*P2[tr-mid])%mod2)+T2[v*2+1])%mod2;
   }

   void update(int v, int tl, int tr, int pos, char c){
      if(tl==tr){
         T1[v]=(c-'a'+1)%mod1;
         T2[v]=(c-'a'+1)%mod2;
         return;
      }
      int mid=(tl+tr)/2;
      if(pos<=mid){
         update(v*2,tl,mid,pos,c);
      }else{
         update(v*2+1,mid+1,tr,pos,c);
      }
      T1[v]=(((T1[v*2]*P1[tr-mid])%mod1)+T1[v*2+1])%mod1;
      T2[v]=(((T2[v*2]*P2[tr-mid])%mod2)+T2[v*2+1])%mod2;
   }

   pair<int,int> query(int v, int tl, int tr, int l, int r){
      if(tl>r || tr<l){
         return {0,0};
      }
      if(l<=tl && tr<=r){
         return {T1[v],T2[v]};
      }
      int mid=(tl+tr)/2;
      auto left=query(v*2,tl,mid,l,min(mid,r));
      auto right=query(v*2+1,mid+1,tr,max(l,mid+1),r);
      int len=max(int(0),r-max(l,mid+1)+1);
      int H1=(((left.first*P1[len])%mod1)+right.first)%mod1;
      int H2=(((left.second*P2[len])%mod2)+right.second)%mod2;
      return {H1,H2};
   }
   void update(int pos, char c){
      return update(1,0,n-1,pos-1,c);
   }
   pair<int,int> geth(int l,int r){
      return query(1,0,n-1,l-1,r-1);
   }
};
