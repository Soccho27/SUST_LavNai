const int64_t MOD=998244353,G=3;
inline int64_t modpow(int64_t a,int64_t e){
 int64_t r=1;
 while(e){if(e&1) r=r*a%MOD;
  a=a*a%MOD; e>>=1;
 }
 return r;
}
struct NTT{
 int max_base;
 vector<int64_t> root;
 vector<int> rev;
 NTT(){int tmp=MOD-1; max_base=0;
  while(!(tmp&1)) tmp>>=1,max_base++;
  root.resize(1<<max_base); root[0]=1;
  for(int len=1;len<(1<<max_base);len<<=1){
   int64_t w=modpow(G,(MOD-1)/(len*2));
   for(int i=0;i<len;i++)
    root[len+i]=(i?root[len+i-1]*w%MOD:1);
  }
 }
 void ntt(vector<int64_t>&a,bool inv){
  int n=a.size();
  if((int)rev.size()!=n){
   rev.resize(n); int k=__builtin_ctz(n)-1;
   for(int i=0;i<n;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<k);
  }
  for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
  for(int len=1;len<n;len<<=1)
   for(int i=0;i<n;i+=len*2)
    for(int j=0;j<len;j++){
     int64_t u=a[i+j],v=a[i+j+len]*root[len+j]%MOD;
     a[i+j]=(u+v<MOD?u+v:u+v-MOD);
     a[i+j+len]=(u-v>=0?u-v:u-v+MOD);
    }
  if(inv){
   reverse(a.begin()+1,a.end());
   int64_t inv_n=modpow(n,MOD-2);
   for(int64_t&x:a) x=x*inv_n%MOD;
  }
 }
 vector<int64_t> multiply(const vector<int64_t>&a,const vector<int64_t>&b){
  if(a.empty()||b.empty()) return {};
  int need=a.size()+b.size()-1,n=1;
  while(n<need) n<<=1;
  vector<int64_t> fa(a.begin(),a.end()),fb(b.begin(),b.end());
  fa.resize(n); fb.resize(n);
  ntt(fa,false); ntt(fb,false);
  for(int i=0;i<n;i++) fa[i]=fa[i]*fb[i]%MOD;
  ntt(fa,true); fa.resize(need);
  return fa;
 }
};
static NTT ntt;
vector<int> pow(vector<int>&a,int p){
 vector<int>res={1};
 while(p){
  if(p&1) res=ntt.multiply(res,a);
  a=ntt.multiply(a,a); p>>=1;
 }
 return res;
}
