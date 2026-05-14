int blk = 1;
bool cmp(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2){
    if((p1.first.first / blk) != (p2.first.first / blk))return p1.first.first < p2.first.first;
    return p1.first.second < p2.first.second;   // ekhane '<=' dile runtime error khai
}
void solve()
{
    int n;
    blk = sqrt(n);
    vector<pair<pair<int, int>, int> > qry;
    for(int i = 0; i < q; i++){
        int l,r;cin>>l>>r;
        qry.push_back({{l, r}, i});
    }
    sort(all(qry), cmp);
    int lf = 1, rg = 1;
    for(int i = 0; i < q; i++){
        int l = qry[i].first.first, r = qry[i].first.second, ind = qry[i].second;
        while(rg <= r){
            rg++;
        }
        while(rg > r + 1){
            rg--;
        }
        while(lf < l){
            lf++;
        }
        while(lf >= l + 1){
            lf--;
        }
        ansVec[ind] = ans...;
    }
    for(auto it: ansVec){
        cout<< it << nl;
    }
}