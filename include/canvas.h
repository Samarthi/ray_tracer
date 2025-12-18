#include "ray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

void canvas_to_ppm(const Canvas &canvas){
  FILE *newstreamptr;
  freopen_s(&newstreamptr, "scene.ppm", "w", stdout);
  // write header
  std::cout << "P3\n"
            << canvas.w << ' ' << canvas.h << "\n255\n";
  // write body
  for (int i = 0; i < canvas.h; ++i){
    for (int j = 0; j < canvas.w; ++j)
      for (int k = 0; k < 3; ++k)
        std::cout << (int)canvas.contents[i][j][k] << ' ';
    std::cout << '\n';
  }
}

bool is_empty_token(char c){
  if(c==' ' || c=='\t' || c=='\n')
    return true;
  return false;
}

struct StringNode{
    std::string s;
    StringNode* next;
};

struct StringList{
    StringNode * head;
    int n;
};

StringList split(const std::string &s, char sep){
    StringList sl; sl.head = nullptr;
    int last_idx = 0;
    StringNode *last_node_ptr = nullptr;

    for(int i=0;i<s.size();++i){
        if (s[i]==sep || i==s.size()-1){
            StringNode *node = (StringNode*) malloc(sizeof(StringNode));
            node->s =  s.substr(last_idx, i-last_idx+1);
            node->next = nullptr;
            if(last_node_ptr)
                last_node_ptr->next = node;
            last_idx = i+1;
            last_node_ptr = node;
            if(sl.head) sl.head = node;
        }
    }
    return sl;
}

std::string trim(const std::string &s){
  int start = 0, end = s.size();
  while(start<s.size() && is_empty_token(s[start])) ++start;
  while(end>=0 && is_empty_token(s[start])) --end;
  return s.substr(start,end-start+1);
}

Canvas ppm_to_canvas(const char *ppm_path){
  auto f = freopen(ppm_path, "r", stdin);
  std::string line;
  bool header = false, init = false, high = false ;
  Canvas cnv;
  int row_count = 0, col_count = 0;
  const int MOD = 3;

  while(std::getline(f,line)){
    if (!header){
      if (trim(line)=="P3") header = true;
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
        continue;
      }
    }
    
    if(!high){
        std::string trimmed_high = trim(line) ;
        if (trimmed_high=="")
            continue;
        high = true;
    }

    std::string trimmed_line = trim(line);
    Vec3 buffer;int count;
    StringList sl = split(trimmed_line, ' ');
    for(auto it = sl.head; it!=nullptr; it = it->next, ++col_count){
        if(!col_count % MOD) cnv.contents[row_count][col_count] = buffer;
        if(!col_count % cnv.w) ++row_count;
        buffer[col_count%MOD] = (float)std::stoi(it->s);
        col_count = col_count % cnv.w;
    }    
  }
  return cnv;
}
