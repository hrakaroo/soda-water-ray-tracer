#include <stdio.h>
#include <iostream.h>
#include <math.h>
#include <ANN/ANN.h>

void printPt(ANNpoint pt)
{
  cout << "x = " << pt[0] << " y = " << pt[1] << " z = " << pt[2] << endl;
}
  
void main()
{
  ANNpointArray   points;
  ANNkd_tree    * theTree;
  ANNidxArray     nn_idx;
  ANNdistArray    dists;

  points = annAllocPts(4, 3);

  nn_idx = new ANNidx[5];
  dists  = new ANNdist[5];
  
  points[0][0] = 1.0;
  points[0][1] = 1.0;
  points[0][2] = 1.0;

  points[1][0] = 5.0;
  points[1][1] = 5.0;
  points[1][2] = 5.0;

  points[2][0] = 6.0;
  points[2][1] = 6.0;
  points[2][2] = 6.0;

  points[3][0] = 1.0;
  points[3][1] = 2.0;
  points[3][2] = 3.0;

  theTree = new ANNkd_tree( points, 4, 3 );

  ANNpoint query = annAllocPt(3);

  query[0] = 4.0;
  query[1] = 4.0;
  query[2] = 4.0;
  
  theTree->annkSearch(query, 5, nn_idx, dists, 0.0);

  cout << "query: ";
  printPt(query);

  for( int i = 0; i < 5 ; i ++ )
    {
      cout << "point: " << nn_idx[i] << " dist: " << dists[i] << endl;
      printPt(points[nn_idx[i]]);
    }
}


  
