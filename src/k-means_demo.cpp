#include <stdio.h>
#include <stdlib.h>
#include "k-means.h"
using namespace alg;

int main()
{
    double data[] = {
        0.0, 0.2, 0.4,
        0.3, 0.2, 0.4,
        0.4, 0.2, 0.4,
        0.5, 0.2, 0.4,
        5.0, 5.2, 8.4,
        6.0, 5.2, 7.4,
        4.0, 5.2, 4.4,
        10.3, 10.4, 10.5,
        10.1, 10.6, 10.7,
        11.3, 10.2, 10.9
    };

    const int size = 10; //Number of samples
    const int dim = 3;   //Dimension of feature
    const int cluster_num = 4; //Cluster number

    KMeans* kmeans = new KMeans(dim,cluster_num);
    int* labels = new int[size];
    kmeans->SetInitMode(KMeans::InitUniform);
	kmeans->Cluster(data,size,labels);

	for(int i = 0; i < size; ++i)
	{
	    printf("%f, %f, %f belongs to %d cluster\n", data[i*dim+0], data[i*dim+1], data[i*dim+2], labels[i]);
	}

	delete []labels;
	delete kmeans;

    return 0;
}