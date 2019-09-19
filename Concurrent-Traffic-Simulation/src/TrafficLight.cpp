#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */


template <typename T>
T MessageQueue<T>::receive()
{
  std::unique_lock<std::mutex> uLock(_mutex);
  _condition.wait(uLock,[this] {return !(_queue.empty());});
  T msg = std::move(_queue.back());
  // _queue.pop_back();

  // std::cout<<"Msg ID # "<<std::this_thread::get_id()<<" receive new message value of "<<msg<<std::endl;

  // is_block = true;
  
  return msg;
  
  
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
  std::lock_guard<std::mutex> Lock(_mutex);
  _queue.push_back(std::move(msg));
  // is_block = false;
  // std::cout<<"Msg ID # "<<std::this_thread::get_id()<<" notify new message"<<std::endl;
  _condition.notify_one();
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
}


/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = red;
}

void TrafficLight::waitForGreen()
{
  while(true){
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));

    if(_light_messages.receive() == green)
    {
      return;
    }
  }
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
  
  threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhase,this));
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhase()
{
  // std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::hash<std::thread::id> hasher;
  srand((unsigned int)hasher(std::this_thread::get_id()));
  // srand(time(NULL));
  double cycle_duration = (rand()%2000 + 4000);
  // _light_messages.is_block = false;
  //init stop watch
  std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  lastUpdate = std::chrono::system_clock::now();
  
  while(true){

    

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    long timeSinceLastUpdate = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastUpdate).count();
    
    if (timeSinceLastUpdate >= cycle_duration){
      std::lock_guard<std::mutex> Lock(_mutex);

      if (_currentPhase == green){
        _currentPhase = red;
      }
      else{
        _currentPhase = green;
      }
    //  std::cout<<std::this_thread::get_id()<<"'s is : "<<_currentPhase<<std::endl;
      _light_messages.send(std::move(_currentPhase));
      
      lastUpdate = std::chrono::system_clock::now();  
    }
  }
    
                                
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles. 
}