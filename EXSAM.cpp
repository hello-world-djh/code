const int N = 1e6 + 3;//字符串数量
const int SZ = 2e6 + 5;//字符串长度（两倍空间）
const int ALP = 26 + 5;//字符集大小

struct Trie {
    int tree[N][ALP], c[N], fa[N];//字典树，以及它的颜色（权值），和在树上的父亲
    int tot;

    Trie() {tot = 1;}

    void ins(char s[]) {
        int p = 1;
        for (int i = 1; s[i]; i++) {
            int a = s[i] - 'a';
            if (!tree[p][a]) tree[p][a] = ++tot, fa[tot] = p, c[tot] = a;
            p = tree[p][a]; 
        }
        return;
    }//trie 插入模板（主程序就从这里插入）
} trie;

struct SAM {
    int tree[SZ][ALP], fail[SZ], len[SZ]; int tot;//普通SAM，但没有last
    
    SAM() {tot = 1;}

    int ins(int x, int last) {
        int u = ++tot, p = last;
        len[u] = len[last] + 1;
        while (p && !tree[p][x]) tree[p][x] = u, p = fail[p];
        if (!p) fail[u] = 1;
        else {
            int q = tree[p][x];
            if (len[q] == len[p] + 1) fail[u] = q;
            else {
                int cq = ++tot;
                len[cq] = len[p] + 1; fail[cq] = fail[q];
                memcpy(tree[cq], tree[q], sizeof tree[q]); fail[u] = fail[q] = cq;
                while (p && tree[p][x] == q) tree[p][x] = cq, p = fail[p];
            }
        }
        return u;
    }

    int pos[SZ]; std::queue<int> q;

    void build() {
        for (int i = 0; i < 26; i++) if (trie.tree[1][i]) q.push(trie.tree[1][i]);
        pos[1] = 1;
        while (!q.empty()) {
            int x = q.front(); q.pop(); pos[x] = ins(trie.c[x], pos[trie.fa[x]]);
            for (int i = 0; i < 26; i++) if (trie.tree[x][i]) q.push(trie.tree[1][x]);
        }
        return;
    }
} sam;

//将每个字符串先插入进 trie 中，再调用一遍 build 建好广义SAM。
//记得建树！！记得建树！！记得建树！！
