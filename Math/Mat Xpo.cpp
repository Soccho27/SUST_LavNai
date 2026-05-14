struct Mat{
 int n,m;
 vector<vector<int>> a;
 Mat(){}
 Mat(int _n,int _m){n=_n;m=_m;a.assign(n,vector<int>(m,0));}
 Mat(vector<vector<int>> v){n=v.size();m=n?v[0].size():0;a=v;}
 inline void make_unit(){assert(n==m);for(int i=0;i<n;i++)for(int j=0;j<n;j++)a[i][j]=(i==j);}
 inline Mat operator+(const Mat&b){
  assert(n==b.n&&m==b.m);Mat r(n,m);
  for(int i=0;i<n;i++)for(int j=0;j<m;j++)r.a[i][j]=(a[i][j]+b.a[i][j])%mod;
  return r;
 }
 inline Mat operator-(const Mat&b){
  assert(n==b.n&&m==b.m);Mat r(n,m);
  for(int i=0;i<n;i++)for(int j=0;j<m;j++)r.a[i][j]=(a[i][j]-b.a[i][j]+mod)%mod;
  return r;
 }
 inline Mat operator*(const Mat&b){
  assert(m==b.n);Mat r(n,b.m);
  for(int i=0;i<n;i++)for(int j=0;j<b.m;j++)for(int k=0;k<m;k++)
   r.a[i][j]=(r.a[i][j]+1LL*a[i][k]*b.a[k][j]%mod)%mod;
  return r;
 }
 inline Mat fow(int64_t k){
  assert(n==m);Mat r(n,m),b=*this;r.make_unit();
  while(k){if(k&1)r=r*b;b=b*b;k>>=1LL;}
  return r;
 }
 inline Mat& operator+=(const Mat&b){return *this=(*this)+b;}
 inline Mat& operator-=(const Mat&b){return *this=(*this)-b;}
 inline Mat& operator*=(const Mat&b){return *this=(*this)*b;}
 inline bool operator==(const Mat&b){return a==b.a;}
 inline bool operator!=(const Mat&b){return a!=b.a;}
};
