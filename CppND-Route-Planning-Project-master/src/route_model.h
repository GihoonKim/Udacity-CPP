#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H

#include <limits>
#include <cmath>
#include <unordered_map>
#include "model.h"
#include <iostream>
#include <unordered_map>


class RouteModel : public Model {

  public:
    class Node : public Model::Node {
      public:
        // Add public Node variables and methods here.

        Node * parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<Node *> neighbors;

        float distance(Node node)const{
          return std::sqrt(std::pow((x-node.x),2)+std::pow((y-node.y),2));
        };

        Node(){}

      //Constructor
        Node(int idx, RouteModel * search_model, Model::Node node) : Model::Node(node), parent_model(search_model), index(idx) {}

        void FindNeighbors();


      private:
        Node* FindNeighbor(vector<int> node_indices);

        // Add private Node variables and methods here.
        int index;
        RouteModel * parent_model = nullptr;  //상위의 model 안 data에 접근할 수 있게 해 준다.(model.cpp 껄 활용하기 위함인듯)

    };

    // Add public RouteModel variables and methods here.


    //set과 get은 암묵적인 약속

    //set은 값을 넣을 때, get은 값을 빼올 때 사용
    Node &FindClosestNode(float x, float y);
    auto &SNodes() {return m_Nodes;}

    //routemodel constructor
    RouteModel(const std::vector<std::byte> &xml);
    auto &GetNodeToRoadMap() {return node_to_road};
    std::vector<Node> path; // This variable will eventually store the path that is found by the A* search.

  private:
    std::unordered_map<int, std::vector<const Model::Road*>> node_to_road;
    void CreateNodeToRoadHashmap();
    // Add private RouteModel variables and methods here.
	std::vector<Node> m_Nodes;
};

#endif
