#ifndef HALFEDGE_2021_10_19
#define HALFEDGE_2021_10_19

#include <iostream>
#include <vector>
#include <algorithm>
#include "Eigen/Core"
#include "Mesh.hpp"
/*
 三角形メッシュ限定の空間効率の良いハーフエッジデータ構造
*/
namespace mds{
  class Halfedge{
    using veci = std::vector<int>;
    using vec3i = Eigen::Vector3i;

  public:
    Halfedge(){}
    Halfedge(Mesh mesh){
      halfedge_struct(mesh);
    }
    void halfedge_struct(Mesh mesh);//データ構築
    int tgt_vertex(int h_idx);//半辺の添字から終点の添字を返す
    int src_vertex(int h_idx);//半辺の添字から支点の添字を返す
  /* void edge_to_face();
    void next_edge();
    void prev_edge();
    void src_vertex();
    void face_to_edge();
    void ccw_edge();
    void cw_edge();*/
    bool boundary_or_not(int h_idx); //入力：半辺の添字
    void boundary_set(veci &boundary, int start_idx); //入力：境界頂点の添字を収納するvector<int>、 半辺の添字
  private:
    veci opp_halfedges;
    veci out_halfedges;
  };

////////////////////////////////////////////////////

  //ハーフエッジの添字の割り当て
  Eigen::Vector3i assain(int a, int b, int c){
    if(a < b) return Eigen::Vector3i(a, b, c);
    else return Eigen::Vector3i(b, a, c);
  }

  //データ構築
  void Halfedge::halfedge_struct(Mesh m){
    mesh = m;
    std::cout << mesh.f_number() <<"\n";
  //out_halfedgeを初期化
    std::vector<vec3i> e_tmp;
    int f_num = mesh.f_number();
    int v_num = mesh.v_number();
    out_halfedges.resize(v_num);
    out_halfedges.assign(v_num, -1);
    for(int i=0; i<f_num; i++){
      vec3i a = mesh.f(i);
      for(int j=0; j<3; j++){
        vec3i e = assain(a[j], a[(j+1)%3], 3*i+((j+2)%3));
        e_tmp.push_back(e);
        if(out_halfedges[a[j]] == -1) out_halfedges[a[j]] = 3*i+((j+2)%3);
      }
    }

    std::sort(e_tmp.begin(), e_tmp.end(),
        [](const vec3i& x, const vec3i& y){
        if(x[0] == y[0]) return x[1] < y[1];
        else return x[0] < y[0];});

  //opp_halfedgeの初期化
    opp_halfedges.resize(f_num*3);
    opp_halfedges.assign(f_num*3, -1); 
    int ii=0;
    while(ii < f_num*3){
      if(e_tmp[ii].x() == e_tmp[ii+1].x() && e_tmp[ii].y() == e_tmp[ii+1].y()){
        opp_halfedges[e_tmp[ii].z()] = e_tmp[ii+1].z();
        opp_halfedges[e_tmp[ii+1].z()] = e_tmp[ii].z();
        ii+=2;
      }else ii++;
    }
  }

  //ハーフエッジの終点の添字を返すメンバ関数
  int Halfedge::tgt_vertex(int h_idx){
    vec3i f = mesh.f(h_idx/3);
    int i = (h_idx + 2) % 3;
    if(i == 0) return f.x();
    else if(i == 1) return f.y();
    else return f.z();
    return 0;
  }

  //ハーフエッジの支点の添字を返すメンバ関数
  int Halfedge::src_vertex(int h_idx){
    vec3i f = mesh.f(h_idx/3);
    int i = (h_idx + 1) % 3;
    if(i == 0) return f.x();
    else if(i == 1) return f.y();
    else return f.z();
    return 0;
  }

  //境界辺かどうか判定するメンバ関数
  bool Halfedge::boundary_or_not(int h_idx){
    if(opp_halfedges[h_idx] == -1) return true;
    return false;
  }


  //境界辺を引数のvector<int>(=veci)に代入するメンバ関数
  void Halfedge::boundary_set(veci &boundary, int start_idx){
    //境界辺じゃなかったとき
    if(!boundary_or_not(start_idx)) return;
    //境界辺のとき
    int idx = src_vertex(start_idx);
    int end_idx = idx;
    do{
      int h_idx = out_halfedges[idx];
      while(!boundary_or_not(h_idx)){
        int opp_idx = opp_halfedges[h_idx];
        if(opp_idx%3 != 2) h_idx = opp_idx+1;
        else h_idx = opp_idx-2;
        //cout << h <<"\n";
      }
      boundary.push_back(idx);
      idx = tgt_vertex(h_idx);
    }while(idx != end_idx);
    return;
  }
}
#endif


