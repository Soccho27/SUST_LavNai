int n,p1=137,p2=277;
int currPow1[sz+5], currPow2[sz + 5];
int pref1[sz+5], pref2[sz+5];
vector<int> fnArr;
// hash with it's own some space
void pre(){
    currPow1[0]=1;
    currPow2[0]=1;
    fr(i,1,sz+4){
        currPow1[i]=(currPow1[i-1]*p1)%mod1;
        currPow2[i]=(currPow2[i-1]*p2)%mod2;
    }
}
void genHash(){
    pref1[0] = 0;
    pref2[0] = 0;
    fr(i,0,n){
        // pref[i+1]=(pref[i]*p1+(s[i]-'a'+1))%mod1;
        pref1[i + 1] = (pref1[i] + (fnArr[i] * currPow1[fnArr[i]]) % mod1) % mod1;
        pref2[i + 1] = (pref2[i] + (fnArr[i] * currPow2[fnArr[i]]) % mod2) % mod2;
    }
}
int getHash1(int l,int r){
    return (pref1[r] - pref1[l - 1] + mod1) % mod1;;
}
int getHash2(int l,int r){
    return (pref2[r] - pref2[l - 1] + mod2) % mod2;
}
// hash with some prime pow, unique for all elements
void pre(){
    currPow1[0]=1;
    currPow2[0]=1;
    fr(i,1,sz+4){
        currPow1[i]=(currPow1[i-1]*p1)%mod1;
        currPow2[i]=(currPow2[i-1]*p2)%mod2;
    }
}
void genHash(){
    pref1[0] = 0;
    pref2[0] = 0;
    fr(i,0,n){
        // pref[i+1]=(pref[i]*p1+(s[i]-'a'+1))%mod1;
        pref1[i + 1] = (pref1[i] + (currPow1[fnArr[i]]) % mod1) % mod1;
        pref2[i + 1] = (pref2[i] + (currPow2[fnArr[i]]) % mod2) % mod2;
    }
}
int getHash1(int l,int r){
    return (pref1[r] - pref1[l - 1] + mod1) % mod1;;
}
int getHash2(int l,int r){
    return (pref2[r] - pref2[l - 1] + mod2) % mod2;
}
// randomize unique for all elements
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    } 
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
}rng;
map<int, int> uniqueVal1, uniqueVal2;
void pre(){
    fr(i,1,sz+4){
        uniqueVal1[i] = rng(i) % mod1;
        uniqueVal2[i] = rng(i) % mod2;
    }
}
void genHash(){
    pref1[0] = 0;
    pref2[0] = 0;
    fr(i,0,n){
        // pref[i+1]=(pref[i]*p1+(s[i]-'a'+1))%mod1;
        pref1[i + 1] = (pref1[i] + (uniqueVal1[fnArr[i]]) % mod1) % mod1;
        pref2[i + 1] = (pref2[i] + (uniqueVal2[fnArr[i]]) % mod2) % mod2;
    }
}
int getHash1(int l,int r){
    return (pref1[r] - pref1[l - 1] + mod1) % mod1;;
}
int getHash2(int l,int r){
    return (pref2[r] - pref2[l - 1] + mod2) % mod2;
}