#include <iostream>
#include "Weighted_graph.h"

using namespace std;

int main() {
	// Weighted_graph graph(4);

	// graph.insert_edge( 0, 1, 7.2 ); 
	// graph.insert_edge( 0, 2, 7.5 ); 
	// graph.insert_edge( 0, 3, 7.3 );
	// graph.insert_edge( 1, 2, 7.6 );
	// graph.insert_edge( 1, 3, 7.4 );
	// graph.insert_edge( 2, 3, 7.7 );
	// //cout << minspan.at(1).i << std::endl;
	// cout << graph.minimum_spanning_tree().first << endl;   // returns the minimum spanning tree weight: 22
	// cout << graph.minimum_spanning_tree().second << endl;  // returns the number of nodes inspected: 4
	// graph.insert_edge( 0, 2, 7.5 );   // returns true
	// graph.insert_edge( 0, 2, 7.8 );   // returns true
	// cout << graph.minimum_spanning_tree().first << endl;   // returns the minimum spanning tree weight: 22.1
	// cout << graph.minimum_spanning_tree().second << endl;  // returns the number of nodes inspected: 4

	Weighted_graph *graph = new Weighted_graph(5);



	// graph->insert_edge( 0, 1, 7.2 ); 
	// graph->insert_edge( 0, 2, 7.5 ); 
	// graph->insert_edge( 0, 3, 7.3 );
	// graph->insert_edge( 1, 2, 7.6 );
	// graph->insert_edge( 1, 3, 7.4 );
	// graph->insert_edge( 2, 3, 7.7 );

	graph->insert_edge(0, 1, 0.1);
	graph->insert_edge(1, 2, 0.1);
	graph->insert_edge(2, 3, 0.1);
	graph->insert_edge(0, 4, 3.1);
	graph->insert_edge(1, 4, 2.1);
	graph->insert_edge(2, 4, 1.1);
	graph->insert_edge(3, 4, 0.9);
	graph->insert_edge(0, 2, 0.4);
	graph->insert_edge(0, 3, 0.5);
	graph->insert_edge(1, 3, 0.6);

	graph->minimum_spanning_tree();

	graph->insert_edge(0, 4, 0.45);
	cout << " after update ----- " << endl << endl;

	graph->minimum_spanning_tree();

	cout << " after update ----- " << endl << endl;

	graph->erase_edge(0, 4);

	graph->minimum_spanning_tree();
	return 0;
}