#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {

  start_x *= 0.01f;
  start_y *= 0.01f;
  end_x *= 0.01f;
  end_y *= 0.01f;

  start_node = &m_Model.FindClosestNode(start_x,start_y);
  end_node = &m_Model.FindClosestNode(end_x,end_y);




}

// 안 되는 코드다.. 왜지?? segmentation failed 가 떴어..
std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node * current_node){

  std::vector<RouteModel::Node> path_found = {};
  RouteModel::Node* parent_node = (*current_node).parent;
  distance = 0.0f;

  while(parent_node!=nullptr){
    path_found.push_back(*current_node);
    distance += (*parent_node).distance(*current_node);

    current_node = parent_node;
    parent_node = (*current_node).parent;
  }

  path_found.push_back(*parent_node);
  distance += (*parent_node).distance(*current_node);
  distance *=m_Model.MetricScale();

  return path_found;

}
// 돌아가는 코드
// std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node * current_node){
//
//   std::vector<RouteModel::Node> path_found;
//   distance = 0.0f;
//   RouteModel::Node parent;
//
//   while(current_node->parent !=nullptr){
//     path_found.push_back(*current_node);
//     parent = (*current_node->parent);
//     distance += current_node->distance(parent);
//
//     current_node = current_node->parent;
//   }
//
//   path_found.push_back(*current_node);
//   distance *=m_Model.MetricScale();
//
//   return path_found;
// }



void RoutePlanner::AStarSearch(){
  start_node->visited = true;
  open_list.push_back(start_node);
  RouteModel::Node *current_node = nullptr;

  while(open_list.size()>0){
    current_node = NextNode();
    if(current_node->distance(*end_node)==0){
      m_Model.path = ConstructFinalPath(current_node);
      return;
    }
    else{
      //어차피 return이 위에 있어서 else는 해줄 필요가 없다.
      AddNeighbors(current_node);
    }
  }
  // end_node->parent = start_node;
  // m_Model.path = ConstructFinalPath(end_node);
}

float RoutePlanner::CalculateHValue(const RouteModel::Node *passed_node){
  return end_node->distance(*passed_node);
}

bool compare(const RouteModel::Node *a, const RouteModel::Node *b){
  return (a->g_value+a->h_value) < (b->g_value+g->h_value);
}

RouteModel::Node *RoutePlanner::NextNode(){
  std::sort(open_list.begin(),open_list.end(),compare);

  // std::sort(open_list.begin(),open_list.end(),[](const auto &_1st, const auto &_2st){
  //   return _lst->h_value+_1st->g_value _2nd->h_value+_2st->g_value;
  // });

  //using front for copy. 만약 begin으로 생성한다면, erase 할 때, lowest_node도 문제가 생기나??
  RouteModel::Node *lowest_node = open_list.front();
  open_list.erase(open_list.begin());

  return lowest_node;
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node){
  current_node->FindNeighbors();

  for(RouteModel::Node *neighbor : current_node->neighbors){
    neighbor->parent = current_node;
    neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
    neighbor->h_value = CalculateHValue(neighbor);

    open_list.push_back(neighbor);
    neighbor->visited = true;
  }
}
