#include<bits/stdc++.h>
#include "../models/RubiksCube.h"

#ifndef RUBIKS_CUBE_SOLVER_BFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_BFSSOLVER_H

template<typename T, typename H>
class BFSolver{
  private:
        vector<RubiksCube::MOVE> moves;

        unordered_map<T,bool,H> visited;
        unordered_map<T,RubiksCube::MOVE,H> move_done;
        unordered_map<T,T,H> parent;

        T bfs(){
          queue<T> q;
          q.push(rubiksCube);
          visited[rubiksCube]=true;

          while(!q.empty()){
            T node=q.front();
            q.pop();

            if(node.isSolved()){
              return node;
            }

            for(int i=0;i<18;i++){
              node.move(RubiksCube::MOVE(i));

              if(visited.find(node)==visited.end()){
                visited[node]=true;
                parent[node]=q.front();
                move_done[node]=RubiksCube::MOVE(i);
                q.push(node);
              }

              node.invert(RubiksCube::MOVE(i));
            }
          }
          return rubiksCube;
        }

  public:
        T rubiksCube;

        BFSolver(T _rubiksCube){
          rubiksCube=_rubiksCube;
        }

        vector<RubiksCube::MOVE> solve(){
          moves.clear();

          T cube=bfs();
          assert(cube.isSolved());

          T curr=cube;
          while(curr!=rubiksCube){
            RubiksCube::MOVE currmove=move_done[curr];
            moves.push_back(currmove);
            curr=parent[curr];
          }

          reverse(moves.begin(),moves.end());
          return moves;
        }
};

#endif
