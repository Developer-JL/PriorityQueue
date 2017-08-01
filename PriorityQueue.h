#ifndef _PR_QUEUE_H
#define _PR_QUEUE_H

#include <vector>
#include <list>
#include <utility>
#include <iostream>

using std::vector;
using std::pair;

/*
 * This class implements a priority queue ADT
 * with priorities specified in ints.
 * Lower priority values precede higher values in
 * the ordering.
 * The template type E is the element type.
 * See the tests for examples.
 */
template <typename E>
class PriorityQueue {

private:

   vector<pair<int,E> > priorityQueue; // Holds the result as a min-heap data structure.
   
public:

  /*
   * An empty constructor.
   */
  PriorityQueue() {}

  /*
   * Recursively compare the priority of a element with its' parent, if parent's priority is lower(the number is bigger), swap them. 
   */
  void bubbleUp(int position){
  
		if(position == 0) return;
		
		int parentPosition = (position - 1) / 2;
		
		if(priorityQueue[parentPosition].first > priorityQueue[position].first){
		
			pair<int,E> temp = priorityQueue[parentPosition];
			priorityQueue[parentPosition] = priorityQueue[position];
			priorityQueue[position] = temp;
			bubbleUp(parentPosition);	
			
		}
  
  }

  /*
   * Recursively compare the priority of a element with its' children, if children's priority is higher(the number is smaller), swap them.
   */
  void sinkDown(int position){
  
		int size = priorityQueue.size();
		int leftChildPosition = position * 2 + 1;
		int rightChildPosition = position * 2 + 2;
		
		if(leftChildPosition >= size || rightChildPosition >= size) return;  // This means the position is a leaf which donn't have children. 
  	   
  	   int minPosition =  position;
  	   
  	   if(priorityQueue[position].first > priorityQueue[leftChildPosition].first){
  	   
			minPosition = leftChildPosition;  	   
  	   	
  	   }
  	   
  	   if(priorityQueue[minPosition].first > priorityQueue[rightChildPosition].first){
  	   
			minPosition = rightChildPosition;  	   
  	   	
  	   }
  	   
  	   if(minPosition != position) {  // Means this position has lower priority than its' child which has lower priority, so needed to be swap.
  	   	
			pair<int,E> temp = priorityQueue[position];
			priorityQueue[position] = priorityQueue[minPosition];
			priorityQueue[minPosition] = temp;
			sinkDown(minPosition); 	   
  	   	
  	   }
  	   
  }
  
  /*
   * Make the whole priorityQueue to apply min-heap data structure.
   */
  void makeItHeap(){
  				
		for(int i = priorityQueue.size()- 1; i > 0; i--){
			
			sinkDown(i);		
			
		}  
  	
  } 
   
  
  /*
   * This function adds a new element "element" to the queue
   * with priorioty "priority".
   */
  void insert(int priority, E element) {

		if(priority < 0)	return;	// Bad priority, won't insert it.
		
		pair<int,E> newPair;
		newPair.first = priority; // Creat a new pair with the given priority and element.
		newPair.second = element;
		
		priorityQueue.push_back(newPair);  // Add it to the queue. 
		bubbleUp(priorityQueue.size() - 1);  // Bubble it up to the right position. 

  }

  /*
   * Similar to insert, but takes a whole vector of new things to
   * add.
   */
  void insert_all(std::vector<std::pair<int,E> > new_elements) {
		
		if(new_elements.size() == 0) return; 			
		
		for(int i = 0; i < new_elements.size(); i++){
			
			insert(new_elements[i].first, new_elements[i].second);				
			
		}		
		
  }

  /*
   * Takes the lowest priority value element off the queue, 
   * and returns it.
   */
  E remove_front() {
	 
	 int size = priorityQueue.size();
	 
	 if(size == 0){
	 
		return E();
	 	
	 }
	 
	 E element = priorityQueue[0].second;  // Stores the first element which has the lowest priority to a variable.
	 
	 priorityQueue[0] = priorityQueue[size - 1];  // Replaces the first pair with the last pair.
	 priorityQueue.pop_back();  // Delete the last pair.
	 sinkDown(0);    // Sorts the queue from the root.
	 
    return element;

  }

  /*
   * Returns the lowest priority value element in the queue, but leaves
   * it in the queue.
   */
  E peek() {
    
    return priorityQueue[0].second;

  }

  /*
   * Returns a vector containing all the elements in the queue.
   */
  std::vector<E> get_all_elements() {

	 vector<E> elements;
	 
	 for(int i = 0; i < priorityQueue.size(); i++){
			
		elements.push_back(priorityQueue[i].second);				
			
	 }
	 
    return elements;
    
  }

  /*
   * Returns true if the queue contains element "element", false
   * otherwise.
   */
  bool contains(E element){

	 for(int i = 0; i < priorityQueue.size(); i++){
			
		if(priorityQueue[i].second == element)
		 
		 return true;				
			
	 }
	 
	 return false;

  }

  /*
   * Returns the priority of the element that matches
   * "element". If there is more than one, return it returns
   * the lowest priority value.
   * If no element matches, return -1.
   */
  int get_priority(E element){

	 for(int i = 0; i < priorityQueue.size(); i++){
			
		if(priorityQueue[i].second == element)
		 
		 return priorityQueue[i].first;				
			
	 }
	 
    return -1;

  }

  /*
   * Returns a vector containing all the priorities.
   * The ordering of the vector should match that of the
   * return from get_all_elements().
   * That is, the priority of the element
   * get_all_elements()[i] should be get_all_prriorities()[i].
   */
  std::vector<int> get_all_priorities(){

	 vector<int> priorities;
	 
	 for(int i = 0; i < priorityQueue.size(); i++){
			
		priorities.push_back(priorityQueue[i].first);				
			
	 }
	 
    return priorities;

  }

  /*
   * Finds the first (in priority order) element that matches
   * "element", and changes its priority to "new_priority".
   */
  void change_priority(E element, int new_priority) {

	 for(int i = 0; i < priorityQueue.size(); i++){
			
		if(priorityQueue[i].second == element)
		 
		 priorityQueue[i].first = new_priority;
		  				
			
	 }
	 
	 makeItHeap();	 // Sorts the queue after change the priority.
	 
  }

  /*
   * Returns the number of elements in the queue.
   */
  int size() {

    return priorityQueue.size();

  }

  /*
   * Returns true if the queue has no elements, false otherwise.
   * Do a testing about git
   */
  bool empty() {

    return priorityQueue.size() == 0;
    
  }

};

#endif
