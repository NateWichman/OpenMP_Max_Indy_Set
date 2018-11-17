
/*
 * Find the smallest dominating set for a graph
 *  This version is parallelized using OpenMP
 *  This is a first version that uses a parallel for
 *  and a critical section
 */



#include <iostream>
#include <omp.h>
#include <set>
using namespace std;

/* Return true if the long x encodes
   a subset that is a dominating set
*/
bool isDominatingSet(const long x,const int n, int **adjacencyMatrix) {
  long mask = 1;
  /* Calculate which vertices belong to the set
     encoded by the value x
  */
  
  std::set<int> verticesInSet;

  for(int i = 0; i < n; i++){
	if((x & mask) != 0){
		verticesInSet.insert(i);
	}
	mask = mask * 2;
  }

  for(int i : verticesInSet){
	for(int j: verticesInSet){
		if(j != i && adjacencyMatrix[i][j] == 1){
			return false;
		}
	}
  }

  return true;

 /* for(int i=0;i < n;i++) {
    if ((x & mask) != 0) {
      verticesInSet[i] = 1;
      verticesCovered[i] = 1;
    }
    else {
      verticesInSet[i] = 0;
      verticesCovered[i] = 0;
    }
    mask = mask * 2;
  }	
  
     Check for all nodes if:
     - They belong to the dominating set
     - or they are connected to a node in the dominating set
  */
  /*
  for(int i = 0;i < n;i++) {
    // Check if node i is adjacent
    // to a node in verticesInSet
    if (verticesCovered[i] == 0) { 
      for(int j = 0;j < n;j++) {
	if (i!=j && adjacencyMatrix[i][j] == 1 && verticesInSet[j] == 1) {
	  verticesCovered[i] = 1;
	  break;
	}
      }
    }
  }
  // Check if all vertices are covered
  for(int i = 0;i < n;i++) {
    if (verticesCovered[i] == 0) {
      return false;
    }
  }
  // 
  // System.out.println("Inside isDominatingSet - argument "+x);
  return true;
}
*/
}
//Return the number of bits that contain 1 in the value x
int bitsIn1( long x,int n ) {
  long mask = 1;
  int result = 0;
 /*  Calculate which vertices belong to the set
     encoded by the value x */
  
  for(int i=0;i < n;i++) {
    if ((x & mask) != 0) {
      result++;
    }
    mask = mask * 2;
  }	
  return result;
}

int main() {
  /* Read the size of the graph - number of vertices
     and then read the adjacency matrix for the graph
  */
  int n;
  cin >> n;
  int **adjacencyMatrix;
  adjacencyMatrix = new int *[n];
  for(int i = 0;i < n;i++) {
    adjacencyMatrix[i] = new int[n];
  }

  for(int i = 0;i < n;i++) {
    for(int j = 0;j < n;j++) {
      cin >> adjacencyMatrix[i][j];
    }
  }
  // Print the adjacency matrix
 
  for(int i = 0;i < n;i++) {
    for(int j = 0;j < n;j++) {
      cout << (adjacencyMatrix[i][j]) << " ";
    }
    cout << endl;
  }
  
  long twoToN = 1;
  for(int i = 0;i < n;i++) {
    twoToN = twoToN * 2;
  }

  int maxNumberBits = 0;
  int result = twoToN - 1;
  //#pragma omp parallel for schedule(dynamic)
#pragma omp parallel for 
  for(long e = 0; e < twoToN;e++) {
    
    if (isDominatingSet(e,n,adjacencyMatrix)) {
#pragma omp critical
      {
	if (bitsIn1(e,n) > maxNumberBits) {
	  maxNumberBits = bitsIn1(e,n);
	  result = e;
	}
      }
    }
  }
  cout << "Result: " << result << " with " <<  
    maxNumberBits << " elements" << endl;
}
