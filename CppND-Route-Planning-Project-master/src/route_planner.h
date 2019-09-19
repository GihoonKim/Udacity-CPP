#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route_model.h"


class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.

    //따로 Cpp에 함수를 적어주지 않을 것들은 여기서 정의해버리면 된다.
    float GetDistance() const {return distance;}

    void AStarSearch();

  private:
    // Add private variables or methods declarations here.

    float distance;

    RouteModel &m_Model;
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;
    std::vector<RouteModel::Node *> open_list;


    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
    RouteModel::Node *NextNode();
    void AddNeighbors(RouteModel::Node *current_node);

    float CalculateHValue(const RouteModel::Node *passed_node);
};
