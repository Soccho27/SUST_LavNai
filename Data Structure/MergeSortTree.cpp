const int N=1e5+5;
int n,q,a[N];
vector<int> seg[4*N+5];
//build merge sort tree
void build(int node,int l,int r){
    //if range length is 1 there's only one element to add and no children
    if (l==r){
        seg[node].push_back(a[l]);
        return;
    }int mid=(l+r)/2;
    build(node*2,l,mid);
    build(node*2+1,mid+1,r);
    int i=0,j=0;
    // use two pointers to merge the two vectors in O(r-l+1)
    while (i<seg[node*2].size() && j<seg[node*2+1].size()){
        if (seg[node*2][i]<seg[node*2+1][j]) seg[node].push_back(seg[node*2][i++]);
        else seg[node].push_back(seg[node*2+1][j++]);
    }
    while (i<seg[node*2].size()) seg[node].push_back(seg[node*2][i++]);
    while (j<seg[node*2+1].size()) seg[node].push_back(seg[node*2+1][j++]);
    return;
}
//query
int query(int node,int l,int r,int lx,int rx,int x){
    //if outside -> 0
    if (l>rx || r<lx) return 0;
    //if inside do binary search
    if (l>=lx && r<=rx){
        int L=0,R=seg[node].size()-1,mid,ans=0;
        while (L<=R){
            mid=(L+R)/2;
            if (seg[node][mid]>x){
                ans = seg[node].size() - mid;
                R = mid - 1;
            }else L = mid + 1;
        }
        return ans;
    }
    int mid=(l+r)/2;
    return query(node*2,l,mid,lx,rx,x)+query(node*2+1,mid+1,r,lx,rx,x);
}