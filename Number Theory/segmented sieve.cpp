// Generate all primes up to limit using sieve of eratosthenes
vector<int> sieve(int limit){
 vector<bool> isp(limit+1,true);
 isp[0]=isp[1]=false;
 for(int p=2;p*p<=limit;p++) if(isp[p])
  for(int i=p*p;i<=limit;i+=p) isp[i]=false;
 vector<int> pr;
 for(int p=2;p<=limit;p++) if(isp[p]) pr.push_back(p);
 return pr;
} // Generate all primes from l to r using segmented sieve in O((r - l) log (r) + sqrt(r))
vector<ll> segmented_sieve(ll l,ll r){
 if(l==1) l++;
 int limit=sqrtl(r);
 while(1LL*limit*limit<=r)limit++;
 while(1LL*limit*limit>r)limit--;
 auto pr=sieve(limit);
 vector<bool> isp(r-l+1,true);
 for(ll p:pr){
  ll st=max(p*p,(l+p-1)/p*p);
  for(ll j=st;j<=r;j+=p) isp[j-l]=false;
 }
 vector<ll> v;
 for(ll i=l;i<=r;i++) if(isp[i-l]) v.push_back(i);
 return v;
}
