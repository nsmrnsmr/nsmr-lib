#ifndef UNIONFIND_2021_12_14
#define UNIONFIND_2021_12_14

#include<iostream>
#include<vector>

struct unionFind{
  //根には-1*深さ、子には親の添字を保存
  std::vector<int> node;

  unionFind(int n=0){
    node.resize(n, -1);
  }
  //根の添字を返す（子ノードを根につなぎ直す）
  int find(int n){
    if( node[n] < 0 ) return n;
    else return node[n] = find(node[n]);
  }

  //デバック用
  int find(int n, int cnt){
    std::cout << n << "\n";
    cnt++;
    if(cnt > 10) throw cnt;
    if( node[n] < 0 ) return n;
    else{
      node[n] = find(node[n], cnt);
      return node[n];
    }
  }

  //二つの木を深い方に統合する（深さが同じ場合xを根とする）
  void marge(int x, int y){
    x = find(x);
    y = find(y);
    int depthX, depthY;
    depthX = -1*node[x];
    depthY = -1*node[y];
    //if(depthX < 0)std::cout << depthY <<"\n";
    //if(depthY < 0)std::cout << depthY <<"\n";
    if( depthX > depthY ) node[y] = x;
    else if( depthY > depthX ) node[x] = y;
    else if( x != y ){
      node[y] = x;
      node[x]--;
    }
    //std::cout << "error: same parent\n";
    return;
  }
};
#endif
