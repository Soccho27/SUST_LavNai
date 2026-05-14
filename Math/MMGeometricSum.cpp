vector <int> multi (vector <int> &a, vector<int> &b)
{
    vector <int> ans = {1, 0, 0, 1};
    ans[0] = a[0] * b[0] + a[1] * b[2];
    ans[1] = a[0] * b[1] + a[1] * b[3];
    ans[2] = a[2] * b[0] + a[3] * b[2];
    ans[3] = a[2] * b[1] + a[3] * b[3];
    for (auto &it : ans) it %= mod;
    return ans;
}
vector <int> mat1;
mat1 = {a, 1, 0, 1};
// mat1[0] = a ^ n
// mat1[1] = a^0 + a^1 + ... + a^(n - 1)
void binPowMatrix (int b)
{vector <int> ans = {1, 0, 0, 1};
while (b){if (b & 1){ans = multi(ans, mat1);}
mat1 = multi(mat1, mat1);b >>= 1;}mat1 = ans;}
