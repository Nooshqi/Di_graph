/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  bkinuthi @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"
#include <vector>
#include <algorithm>


//The struct edge holds the two graoh node indices and the weigh between them
struct edge{
    int i;
    int j;
    double weight;
};
//this function works as sort function for the edge struct placing first priority to lowest weight 
bool SortHS( const edge& edge1, const edge& edge2 )
{
	return edge1.weight < edge2.weight;
}

class Weighted_graph {
	private:
		static const double INF;

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );
		int graph_size;
		int *degree_count;
		int edge_counter;
		Data_structures::Disjoint_sets *indie;		

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();
		double **matrix;

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph( int n ) {
	//Creates an adjacency matrix of size n by n 
	//it also initializes them to infinity 
	//it creastes an object of class Disjoint sets with n disjoint sets for the 
	//vertices in the graph
	degree_count = new int[n];
	indie = new Data_structures::Disjoint_sets( n );
	graph_size = n;
	edge_counter = 0;
	matrix = new double * [n];
	for ( int i = 0; i < n; ++i ) {
		degree_count[i] = 0;
		matrix[i] = new double[n];
		for (int j = i ; j < n; j++){
			matrix[i][j] = INF;

			//matrix[j][i] = INF;
		}
	}



}

Weighted_graph::~Weighted_graph() {
	//The destructor frees up memory from matrix degree_count and indie declared
	//in the constructor

	for ( int i = 0; i < graph_size; ++i ) {
	delete [] matrix[i] ;
	}

	delete [] matrix;
	delete [] degree_count; 
	delete indie;


}


int Weighted_graph::degree( int i ) const{
	//Returns the total degrees of the vertex node i.
	
	return degree_count[i];

}

int Weighted_graph::edge_count() const{
	//Returns the number of edges in the graph.

	return edge_counter;


}



std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {

	//these counters are for the edge checked, edges added and the weight
	int minspan_edges = 0;
	int test_edges  = 0;
	double minspan_weight = 0.0;


	//create a vector and push everything into the vector from the matrix
	std::vector<edge> minspan;
	for ( int i = 0; i < graph_size; ++i ) {
		for (int j = i+1 ; j < graph_size; j++){
			edge temp;
			temp.i = i;
			temp.j = j;
			temp.weight = matrix[i][j];
			minspan.push_back(temp);
			
		}
	}

	//sort vector by weight using the defined function sortSH
	std::sort(minspan.begin(), minspan.end(), SortHS);


	//used to print out items in my vector minspan
	/*****************************************************************************************************
	//std::cout << minspan.at(1).i << std::endl;-->minspan.at(i).i 
	// for(int i = 0; i < minspan.size(); i++)
	// {
	// 	std::cout << minspan.at(i).i << " " << minspan.at(i).j << " " << minspan.at(i).weight << std::endl;
	// }
	******************************************************************************************************/

	

	//This is the main highlight for getting the minimum spanning set, iterates through the vector adding up
	//the edges that exist from the smallest to the largest as long as they dont make a cycle, done using the 
	//disjoint set class that joins unites any two vertice sets that have their edge added to the minimum spanning
	//set successfully
	for ( int i = 0; i < minspan.size(); ++i ) {
		//ensure no INF is added to the weight counters 
		if (minspan.at(i).weight != INF){
			if(indie->find(minspan.at(i).i) != indie->find(minspan.at(i).j))
			{

				indie->set_union(minspan.at(i).i, minspan.at(i).j );

				minspan_edges ++;
				minspan_weight += minspan.at(i).weight;

				//used to help debug the function
				//std::cout << " minspan_edges(n-1): " << minspan_edges << std::endl;

			}
			test_edges++;


			//used to help debug the function
			//std::cout << minspan.at(i).i << " " << minspan.at(i).j << " " << minspan.at(i).weight << std::endl;			

			if(minspan_edges == graph_size-1){
				break;
			}
		} 
			
			
	}

	//used to help debug the function
	//std::cout << " minspan_edges(n-1): " << minspan_edges << "  tested-edges: " << test_edges << std::endl;

	//Used to clear all the vertices that were joined to form new sets so to accomodate for updates to the graph
	indie->clear();

	return std::pair<double, int>( minspan_weight, test_edges );

}



//This inserts an edge to the matrix and returns true else returns false if trying to make an edge to itself
//throws illegal argument if out of graph bounds
bool Weighted_graph::insert_edge( int i, int j, double d ) {

	if(i < 0 || i > graph_size-1 || j < 0 || j > graph_size-1 || d <= 0){
		throw illegal_argument();
	}
	if (i == j){
		return false;
	}
	if (i < j){
		matrix[i][j] = d;
		degree_count[i] += 1;
		degree_count[j] += 1;
		edge_counter += 1;
		return true;

	}
	else{
		matrix[j][i] = d;
		degree_count[i] += 1;
		degree_count[j] += 1;
		edge_counter += 1;
		return true;
	} 
		
}


//This erases an edge to the matrix and returns true if i and j is the same node or if the edge exists
//and was removed(set to INF). Returns false if there was no edge between the two nodes 
//throws illegal argument if out of graph bounds
bool Weighted_graph::erase_edge( int i, int j){
	if(i < 0 || i > graph_size-1 || j < 0 || j > graph_size-1 ){
		throw illegal_argument();
	}
	if (i == j){
		return true;
	}
	if (i < j){
		if(matrix[i][j] == INF){
			return false;
		}
		else{
			matrix[i][j] = INF;
			degree_count[i] -= 1;
			degree_count[j] -= 1;
			edge_counter -= 1;
			return true;
		}
		
	}
	else{
		if(matrix[j][i] == INF){
			return false;
		}
		else{
			matrix[j][i] = INF;
			degree_count[i] -= 1;
			degree_count[j] -= 1;
			edge_counter -= 1;
			return true;
		}
	} 


}


//Clears everything in the matrix also the degree and edge counter is set to 0
void Weighted_graph::clear_edges(){
	edge_counter = 0;
	for ( int i = 0; i < graph_size; ++i ) {
		degree_count[i] = 0;
		for (int j = i ; j < graph_size; j++){
			matrix[i][j] = INF;
			//matrix[j][i] = INF;
		}
	}


}


//Outputs the matrix as it currently is 
std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	for ( int i = 0; i < graph.graph_size; ++i ) {

		out << std::endl << i << std::endl;

		for (int j = i ; j < graph.graph_size; j++){

			out << graph.matrix[i][j] << ' ';
		}
	}


	return out;
}

#endif
