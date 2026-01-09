#include "ray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Canvas{
  int h,w;
  Vec3** contents;
};

void canvas_to_ppm(const Canvas &canvas, const char * path){
  std::ofstream outf(path);
  // write header
  outf << "P3\n"
            << canvas.w << ' ' << canvas.h << "\n255\n";
  // write body
  for (int i = 0; i < canvas.h; ++i){
    for (int j = 0; j < canvas.w; ++j)
      for (int k = 0; k < 3; ++k)
        outf << (int)canvas.contents[i][j][k] << ' ';
    outf << '\n';
  }
  outf.close();
}

bool is_empty_token(char c){
  if(c==' ' || c=='\t' || c=='\n')
    return true;
  return false;
}

std::vector<std::string> split(const std::string &s, char sep){
    std::vector<std::string> sl;
    int last_idx = 0;
    std::string temp;
    for(auto ch:s){
        if (ch!=sep &&  !is_empty_token(ch)) temp.push_back(ch);
        else {
          sl.push_back(temp);
          temp.clear();
        }
    }
    if (temp.size())
      sl.push_back(temp);
    return sl;
}

std::string trim(const std::string &s){
  int start = 0, end = s.size();
  while(start<s.size() && is_empty_token(s[start])) ++start;
  while(end>=start && is_empty_token(s[start])) --end;
  return s.substr(start,std::max(0,end-start+1));
}

Canvas ppm_to_canvas(const char *ppm_path){
  std::ifstream f;
  f.open(ppm_path);
  

  std::string line;
  bool header = false, init = false, high = false ;
  Canvas cnv;
  int row_count = 0, col_count = 0;
  const int MOD = 3;

  while(std::getline(f,line)){
    if (!header){

      std::string trimmed = trim(line);
      if (trimmed=="P3") header = true;
      continue; 
    }

    if (!init){
      std::string trimmed = trim(line);
      if(trimmed!=""){
        int start = 0;
        while (start<trimmed.size() && !is_empty_token(trimmed[start])) ++start;
        
        cnv.h = std::stoi(trimmed.substr(0,start));
        
        while(start<trimmed.size() && trimmed[start]==' ') ++start;
        
        cnv.w = std::stoi(trimmed.substr(start, trimmed.size()-start+1));
        cnv.contents = (Vec3**)calloc(cnv.h, sizeof(Vec3*));
        for(int i=0; i<cnv.h; ++i) cnv.contents[i] = (Vec3*)calloc(cnv.w, sizeof(Vec3)); 
        
        init = true;
      }        
      continue;
    } 
    
    if(!high){
        std::string trimmed_high = trim(line) ;
        if (trimmed_high!="")
            high=true;
        continue;
    }


    std::string trimmed_line = trim(line);
    Vec3 buffer = {0};int count;
    std::vector<std::string> sl = split(trimmed_line, ' ');
    for(auto it:sl){
      try{
        if (col_count>=cnv.w||row_count>=cnv.h) break;   
        if(!(col_count % MOD)) cnv.contents[row_count][col_count] = buffer;
        buffer[col_count%MOD] = std::stoi(it);
        col_count = col_count % cnv.w;
        ++col_count;  
        if(!(col_count % cnv.w)) ++row_count;
      }
      catch (...){
        std::cout<<"Error char: "<<it<<'\n';
      }
    }                  
  }
  f.close();
  return cnv;
}
