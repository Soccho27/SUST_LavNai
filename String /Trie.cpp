struct TrieNode{
   int32_t nxt[26];
   int32_t freq, pref;
   TrieNode() {
      memset(nxt, -1, sizeof(nxt));
      freq = pref = 0;
   }
};
struct Trie {
   vector<TrieNode> t;
   int64_t totalWords;
   Trie() { clear(); }
   void clear() {
      t.clear();
      t.emplace_back();
      totalWords = 0;
   }
   void insert(const string& s){
      int32_t v = 0;
      t[v].pref++;
      for (char c : s) {
         int32_t x = c - 'a';
         if (t[v].nxt[x] == -1) {
            t[v].nxt[x] = (int32_t)t.size();
            t.emplace_back();
         }
         v = t[v].nxt[x];
         t[v].pref++;
      }
      t[v].freq++;
      totalWords++;
   }
   bool search(const string& s) const{
      int32_t v = 0;
      for (char c : s) {
         int32_t x = c - 'a';
         if (t[v].nxt[x] == -1) return false;
         v = t[v].nxt[x];
      }
      return t[v].freq > 0;
   }
   bool startsWith(const string& s) const{
      int32_t v = 0;
      for (char c : s) {
         int32_t x = c - 'a';
         if (t[v].nxt[x] == -1) return false;
         v = t[v].nxt[x];
      }
      return true;
   }
   int32_t countPrefix(const string& s) const{
      int32_t v = 0;
      for (char c : s) {
         int32_t x = c - 'a';
         if (t[v].nxt[x] == -1) return 0;
         v = t[v].nxt[x];
      }
      return t[v].pref;
   }
   void remove(const string& s){
      if (!search(s)) return;
      int32_t v = 0;
      t[v].pref--;
      for (char c : s) {
         int32_t x = c - 'a';
         v = t[v].nxt[x];
         t[v].pref--;
      }
      t[v].freq--;
      totalWords--;
   }
   int32_t getNode(const string& s) const{
      int32_t v = 0;
      for (char c : s) {
         int32_t x = c - 'a';
         if (t[v].nxt[x] == -1) return -1;
         v = t[v].nxt[x];
      }
      return v;
   }
   vector<int32_t> nextCharCounts(const string& prefix) const{
      vector<int32_t> cnt(26, 0);
      int32_t v = getNode(prefix);
      if (v == -1) return cnt;
      for (int32_t i = 0; i < 26; i++) {
         int32_t u = t[v].nxt[i];
         if (u != -1) cnt[i] = t[u].pref;
      }
      return cnt;
   }
   int32_t nodeCount() const{ return (int32_t)t.size(); }
   int64_t wordCount() const{ return totalWords; }
};
