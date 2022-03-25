#ifndef MESH_2022_03_3
#define MESH_2022_03_3

#include <iostream>
#include <vector>
#include <string>
#include "Eigen/Core"
#include "input.h"

namespace mds{
  class Mesh{
    using vec3i = Eigen::Vector3i;
    using vec2i = Eigen::Vector2i;
    using vec3d = Eigen::Vector3d;

  public:
    std::vector<vec3d> V;
    std::vector<vec2i> E;
    std::vector<vec3i> F;

    int Vsize, Esize, Fsize;

    Mesh(){};
    Mesh(std::string file_name, std::string suffix){
      mesh_reading(file_name, suffix);
      Vsize = (int)v.size();
      Esize = (int)E.size();
      Fsize = (int)F.size();
    }

    vec3d v(int idx){ return V[idx]; }
    vec2i e(int idx){ return E[idx]; }
    vec3i f(int idx){ return F[idx]; }

    int v_size(){ return Vsize; }
    int e_size(){ return Esize; }
    int f_size(){ return Fsize; }

    void mesh_reading(std::string file_name, std::string suffix);//メッシュの読み込み
  };

  void Mesh::mesh_reading(const std::string file_name, const std::string suffix){
    switch(suffix)
    {
      case off:{
        resdOFF(file_name, v, e, f);
        break;
      }
      case obj:{
        readOBJ(file_name, v, e, f);
        break;
      }
    }
  }
}
#endif

