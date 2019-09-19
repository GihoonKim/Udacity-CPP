#include "route_model.h"
#include <iostream>

//RouteModel constructor를 실행하면 Model constructor를 부른다. Model constructor 안에는 loaddata()등의 함수들이 들어가 있다.
//constructor를 실행하면 Model::Node()가 만들어지는데, 우리가 원하는건 RouteModel::Node()가 만들어 지는 것

// : Model(xml)을 쓴 이유는 알겠는데, 형태가 왜 저렇게 되는가? 상속받는다는 것을 나타냄
//그냥 RouteModel(xml)을 쓰면 안 되는 이유는? Model 안의 method를 쓸 수 없음
RouteModel::RouteModel(const std::vector<std::byte> &xml) : Model(xml) {

  int counter = 0;
  //아래 쓰임새는 범위 기반 for문으로 this->Nodes()안의 각 node에 대해서 반복한다.
  // 쓰는 방법은 int A = {1,2,3,4} 일 때, for(int number : A){cout<<number} 이런식으로
  for (Model::Node node : this->Nodes()){
    //Nodes()라는 것을 실행시키면 Model::m_Nodes를 reference로 반환해준다.
    //그런데 Nodes()라는 것은 vector<Node>를 반환하기 때문에 Model::Node를 type으로 받는다.

    //this 가 가리키는 것은 Model(xml) class이다.
    m_Nodes.push_back(Node(counter,this,node)); //node를 통해 Model::node의 정보를 상속 받으면서 새롭게 counter와 parent_model을 추가한다.
    counter++;


  }
  CreateNodeToRoadHashmap();
}

void RouteModel::CreateNodeToRoadHashmap(){
  for(const Model::Road &road : Model::Roads()){  //Model::Roads()로 하거나 Roads()로 하거나 상관이 없다. why?
    if(road.type !=Model::Road::Type::Footway){
      for(int node_idx : Model::Ways()[road.way].nodes){

        if(node_to_road.find(node_idx)==node_to_road.end()){
          node_to_road[node_idx]=std::vector<const Model::Road*>();
        }

        node_to_road[node_idx].push_back(&road)
      }
    }
  }
}
//그럼 밖 코드에서 RouteModel(xml)이라고 하면 SNodes() 함수를 실행시키면 m_Nodes가 나온다.

//얘는 node class 안에 있는 아이라서 this를 하면 RouteModel::Node를 가리키고, SNodes는 RouteModel에 정의되어 있기 때문에
//parent_model을 통해서 RouteModel로 간 후에 거기서 SNodes를 찾아야 한다.
RouteModel::Node* RouteModel::Node::FindNeighbor(std:: vector<int> node_indices){
  RouteModel::Node* closest_node = nullptr;
  RouteModel::Node node;

  for(int node_index : node_indices){
    node = parent_model->SNodes()[node_index];

    if((this->distance(node)!=0.0)&&(!node.visited)){

      if ((closest_node==nullptr) || (this->distance(node) < this->distance(*closest_node))){
        closest_node = &parent_model->SNodes()[node_index];  //&node로 해도 상관 없지 않나?
      }
    }
  }

  return closest_node;
}

void RouteModel::Node::FindNeighbors(){

  RouteModel::Node* neighbor_point = nullptr; //초반에 굳이 선언 안 해도 됨
  for (const Model::Road* &road : parent_model->node_to_road[this->index]){
    //RouteModel::Node * neighbor_point = FindeNeigh~~ 로 하면 됨. FindNeighbor 함수는 cpp 안에 있어서 굳이 Model:: 안 붙여도 됨.
    neighbor_point = FindNeighbor(parent_model->Ways()[road->way].nodes)

    if (neighbor_point !=nullptr){ //if neighbor_point 라고 하면 된다. 없으면 false를 반납하는듯.
      this->neighbors.push_back(neighbor_point); //push_back 대신 emplace_back을 썼는데 효율적이라고 함.
    }
  }
}

RouteModel::Node &RouteModel::FindClosestNode(float x, float y){

  RouteModel::Node node;
  node.x = x; node.y = y;

  float min_dist = std::numeric_limits<float>::max();
  int closest_idx;
  float dist_temp;

  for(const Model::Road &road : Roads()){
    if(road.type !=Model::Road::Footway){
      for(int node_idx : Ways()[road.way].nodes){
        dist_temp = SNodes()[node_idx].distance(node);  //이거는 반대로 해도 됨 node.distance(SNodes()[node_idx])이런식으

        if (dist_temp<min_dist){
          min_dist = dist_temp;
          closest_idx = node_idx;
        }
      }
    }
  }

  return SNodes()[closest_idx];
}
