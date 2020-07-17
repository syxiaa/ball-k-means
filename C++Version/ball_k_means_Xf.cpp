//This version is completed by Yong Zheng(413511280@qq.com), Shuyin Xia（380835019@qq.com）, Xingxin Chen, Junkuan Wang.  2020.5.1

#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <algorithm>
#include  <Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;

typedef float OurType;

typedef VectorXf VectorOur;

typedef MatrixXf MatrixOur;

typedef vector <vector<OurType>> ClusterDistVector;

typedef vector <vector<unsigned int>> ClusterIndexVector;

typedef Array<bool, 1, Dynamic> VectorXb;

typedef struct Neighbor
//Define the "neighbor" structure
{
    OurType distance;
    int index;
};

typedef vector <Neighbor> sortedNeighbors;

MatrixOur load_data(const char* filename);

inline MatrixOur
update_centroids(MatrixOur& dataset, ClusterIndexVector& cluster_point_index, unsigned int k, unsigned int n,
    VectorXb& flag,
    unsigned int iteration_counter, MatrixOur& old_centroids);


inline void update_radius(MatrixOur& dataset, ClusterIndexVector& cluster_point_index, MatrixOur& new_centroids,
    ClusterDistVector& temp_dis,
    VectorOur& the_rs, VectorXb& flag, unsigned int iteration_counter, unsigned int& cal_dist_num,
    unsigned int the_rs_size);

inline sortedNeighbors
get_sorted_neighbors_Ring(VectorOur& the_Rs, MatrixOur& centers_dis, unsigned int now_ball, unsigned int k,
    vector<unsigned int>& now_center_index);

inline sortedNeighbors get_sorted_neighbors_noRing(VectorOur& the_rs, MatrixOur& centers_dist, unsigned int now_ball, unsigned int k, vector<unsigned int>& now_center_index);


inline void
cal_centers_dist(MatrixOur& new_centroids, unsigned int iteration_counter, unsigned int k, VectorOur& the_rs,
    VectorOur& delta, MatrixOur& centers_dis);

inline MatrixOur cal_dist(MatrixOur& dataset, MatrixOur& centroids);

inline MatrixOur
cal_ring_dist_Ring(unsigned j, unsigned int data_num, unsigned int dataset_cols, MatrixOur& dataset, MatrixOur& now_centers,
    ClusterIndexVector& now_data_index);

inline MatrixOur cal_ring_dist_noRing(unsigned int data_num, unsigned int dataset_cols, MatrixOur& dataset, MatrixOur& now_centers, vector<unsigned int>& now_data_index);


void initialize(MatrixOur& dataset, MatrixOur& centroids, VectorXi& labels, ClusterIndexVector& cluster_point_index,
    ClusterIndexVector& clusters_neighbors_index,
    ClusterDistVector& temp_dis);


VectorXi ball_k_means_Ring(MatrixOur& dataset, MatrixOur& centroids, bool detail = false)
{

    double start_time, end_time;


    bool judge = true;

    const unsigned int dataset_rows = dataset.rows();
    const unsigned int dataset_cols = dataset.cols();
    const unsigned int k = centroids.rows();

    ClusterIndexVector temp_cluster_point_index;
    ClusterIndexVector cluster_point_index;
    ClusterIndexVector clusters_neighbors_index;
    ClusterIndexVector now_data_index;
    ClusterDistVector temp_dis;

    MatrixOur new_centroids(k, dataset_cols);
    MatrixOur old_centroids = centroids;
    MatrixOur centers_dis(k, k);

    VectorXb flag(k);
    VectorXb old_flag(k);

    VectorXi labels(dataset_rows);
    VectorOur delta(k);

    vector<unsigned int> old_now_index;
    vector <OurType> distance_arr;

    VectorOur the_rs(k);

    unsigned int now_centers_rows;
    unsigned int iteration_counter;
    unsigned int num_of_neighbour;
    unsigned int neighbour_num;
    unsigned int cal_dist_num;
    unsigned int data_num;

    MatrixOur::Index minCol;
    new_centroids.setZero();
    iteration_counter = 0;
    num_of_neighbour = 0;
    cal_dist_num = 0;
    flag.setZero();

    //initialize cluster_point_index and temp_dis
    initialize(dataset, centroids, labels, cluster_point_index, clusters_neighbors_index, temp_dis);

    temp_cluster_point_index.assign(cluster_point_index.begin(), cluster_point_index.end());

    start_time = clock();

    while (true) {
        old_flag = flag;
        //record cluster_point_index from the previous round
        cluster_point_index.assign(temp_cluster_point_index.begin(), temp_cluster_point_index.end());
        iteration_counter += 1;


        //update the matrix of centroids
        new_centroids = update_centroids(dataset, cluster_point_index, k, dataset_cols, flag, iteration_counter,
            old_centroids);

        if (new_centroids != old_centroids) {
            //delta: distance between each center and the previous center
            delta = (((new_centroids - old_centroids).rowwise().squaredNorm())).array().sqrt();

            old_centroids = new_centroids;

            //get the radius of each centroids
            update_radius(dataset, cluster_point_index, new_centroids, temp_dis, the_rs, flag, iteration_counter, cal_dist_num,
                k);
            //Calculate distance between centers

            cal_centers_dist(new_centroids, iteration_counter, k, the_rs, delta, centers_dis);

            flag.setZero();

            //returns the set of neighbors

            //nowball;
            unsigned int now_num = 0;
            for (unsigned int now_ball = 0; now_ball < k; now_ball++) {
                sortedNeighbors neighbors = get_sorted_neighbors_Ring(the_rs, centers_dis, now_ball, k,
                    clusters_neighbors_index[now_ball]);


                now_num = temp_dis[now_ball].size();
                if (the_rs(now_ball) == 0) continue;

                //Get the coordinates of the neighbors and neighbors of the current ball
                old_now_index.clear();
                old_now_index.assign(clusters_neighbors_index[now_ball].begin(), clusters_neighbors_index[now_ball].end());
                clusters_neighbors_index[now_ball].clear();
                neighbour_num = neighbors.size();
                MatrixOur now_centers(neighbour_num, dataset_cols);

                for (unsigned int i = 0; i < neighbour_num; i++) {
                    clusters_neighbors_index[now_ball].push_back(neighbors[i].index);
                    now_centers.row(i) = new_centroids.row(neighbors[i].index);

                }
                num_of_neighbour += neighbour_num;

                now_centers_rows = now_centers.rows();

                judge = true;

                if (clusters_neighbors_index[now_ball] != old_now_index)
                    judge = false;
                else {
                    for (int i = 0; i < clusters_neighbors_index[now_ball].size(); i++) {
                        if (old_flag(clusters_neighbors_index[now_ball][i]) != false) {
                            judge = false;
                            break;
                        }
                    }
                }

                if (judge) {
                    continue;
                }

                now_data_index.clear();
                distance_arr.clear();

                for (unsigned int j = 1; j < neighbour_num; j++) {
                    distance_arr.push_back(centers_dis(clusters_neighbors_index[now_ball][j], now_ball) / 2);
                    now_data_index.push_back(vector<unsigned int>());
                }

                for (unsigned int i = 0; i < now_num; i++) {
                    for (unsigned int j = 1; j < neighbour_num; j++) {
                        if (j == now_centers_rows - 1 && temp_dis[now_ball][i] > distance_arr[j - 1]) {
                            now_data_index[j - 1].push_back(cluster_point_index[now_ball][i]);
                            break;
                        }
                        if (j != now_centers_rows - 1 && temp_dis[now_ball][i] > distance_arr[j - 1] &&
                            temp_dis[now_ball][i] <= distance_arr[j]) {
                            now_data_index[j - 1].push_back(cluster_point_index[now_ball][i]);
                            break;
                        }
                    }
                }

                judge = false;
                int lenth = old_now_index.size();
                //Divide area
                for (unsigned int j = 1; j < neighbour_num; j++) {


                    data_num = now_data_index[j - 1].size();

                    if (data_num == 0)
                        continue;

                    MatrixOur temp_distance = cal_ring_dist_Ring(j, data_num, dataset_cols, dataset, now_centers,
                        now_data_index);
                    cal_dist_num += data_num * j;

                    unsigned int new_label;
                    for (unsigned int i = 0; i < data_num; i++) {
                        temp_distance.row(i).minCoeff(&minCol);
                        new_label = clusters_neighbors_index[now_ball][minCol];
                        if (labels[now_data_index[j - 1][i]] != new_label) {
                            flag(now_ball) = true;
                            flag(new_label) = true;

                            //Update localand global labels
                            vector<unsigned int>::iterator it = (temp_cluster_point_index[labels[now_data_index[j -
                                1][i]]]).begin();
                            while ((it) != (temp_cluster_point_index[labels[now_data_index[j - 1][i]]]).end()) {
                                if (*it == now_data_index[j - 1][i]) {
                                    it = (temp_cluster_point_index[labels[now_data_index[j - 1][i]]]).erase(it);
                                    break;
                                }
                                else
                                    ++it;
                            }
                            temp_cluster_point_index[new_label].push_back(now_data_index[j - 1][i]);
                            labels[now_data_index[j - 1][i]] = new_label;
                        }
                    }
                }
            }
        }
        else
            break;
    }
    end_time = clock();

    if (detail == true)
    {
        cout << "ball-k-means with dividing ring:" << endl;
        cout << "k                :                  ||" << k << endl;
        cout << "iterations       :                  ||" << iteration_counter << endl;
        cout << "The number of calculating distance: ||" << cal_dist_num << endl;
        cout << "The number of neighbors:            ||" << num_of_neighbour << endl;
        cout << "Time per round：                    ||" << (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000 / iteration_counter << endl;

    }
    return labels;
}

VectorXi ball_k_means_noRing(MatrixOur& dataset, MatrixOur& centroids, bool detail = false)
{

    double start_time, end_time;

    bool judge = true;

    const unsigned int dataset_rows = dataset.rows();
    const unsigned int dataset_cols = dataset.cols();
    const unsigned int k = centroids.rows();

    OurType stable_field_dist = 0;

    ClusterIndexVector temp_clusters_point_index;
    ClusterIndexVector clusters_point_index;
    ClusterIndexVector clusters_neighbors_index;

    ClusterDistVector point_center_dist;

    MatrixOur new_centroids(k, dataset_cols);
    MatrixOur old_centroids = centroids;
    MatrixOur centers_dist(k, k);

    VectorXb flag(k);
    VectorXb old_flag(k);

    VectorXi labels(dataset_rows);
    VectorOur delta(k);

    vector<unsigned int> now_data_index;
    vector<unsigned int> old_now_index;

    VectorOur the_rs(k);

    unsigned int now_centers_rows;
    unsigned int iteration_counter;
    unsigned int num_of_neighbour;
    unsigned int neighbour_num;
    unsigned int cal_dist_num;
    unsigned int data_num;

    //bool key = true;

    MatrixOur::Index  minCol;
    new_centroids.setZero();
    iteration_counter = 0;
    num_of_neighbour = 0;
    cal_dist_num = 0;
    flag.setZero();

    //initialize clusters_point_index and point_center_dist
    initialize(dataset, centroids, labels, clusters_point_index, clusters_neighbors_index, point_center_dist);

    temp_clusters_point_index.assign(clusters_point_index.begin(), clusters_point_index.end());

    start_time = clock();

    while (true)
    {
        old_flag = flag;
        //record clusters_point_index from the previous round
        clusters_point_index.assign(temp_clusters_point_index.begin(), temp_clusters_point_index.end());
        iteration_counter += 1;


        //update the matrix of centroids
        new_centroids = update_centroids(dataset, clusters_point_index, k, dataset_cols, flag, iteration_counter, old_centroids);

        if (new_centroids != old_centroids)
        {
            //delta: distance between each center and the previous center
            delta = (((new_centroids - old_centroids).rowwise().squaredNorm())).array().sqrt();

            old_centroids = new_centroids;

            //get the radius of each centroids
            update_radius(dataset, clusters_point_index, new_centroids, point_center_dist, the_rs, flag, iteration_counter, cal_dist_num, k);
            //Calculate distance between centers

            cal_centers_dist(new_centroids, iteration_counter, k, the_rs, delta, centers_dist);

            flag.setZero();

            //returns the set of neighbors

            //nowball;
            unsigned int now_num = 0;
            for (unsigned int now_ball = 0; now_ball < k; now_ball++)
            {
                sortedNeighbors neighbors = get_sorted_neighbors_noRing(the_rs, centers_dist, now_ball, k, clusters_neighbors_index[now_ball]);

                now_num = point_center_dist[now_ball].size();
                if (the_rs(now_ball) == 0) continue;

                //Get the coordinates of the neighbors and neighbors of the current ball
                old_now_index.clear();
                old_now_index.assign(clusters_neighbors_index[now_ball].begin(), clusters_neighbors_index[now_ball].end());
                clusters_neighbors_index[now_ball].clear();
                neighbour_num = neighbors.size();
                MatrixOur now_centers(neighbour_num, dataset_cols);

                for (unsigned int i = 0; i < neighbour_num; i++)
                {
                    clusters_neighbors_index[now_ball].push_back(neighbors[i].index);
                    now_centers.row(i) = new_centroids.row(neighbors[i].index);

                }

                num_of_neighbour += neighbour_num;

                now_centers_rows = now_centers.rows();

                judge = true;

                if (clusters_neighbors_index[now_ball] != old_now_index)
                    judge = false;
                else
                {
                    for (int i = 0; i < clusters_neighbors_index[now_ball].size(); i++)
                    {
                        if (old_flag(clusters_neighbors_index[now_ball][i]) != false)
                        {
                            judge = false;
                            break;
                        }
                    }
                }

                if (judge)
                {
                    continue;
                }

                now_data_index.clear();

                stable_field_dist = the_rs(now_ball);

                for (unsigned int j = 1; j < neighbour_num; j++)
                {
                    stable_field_dist = min(stable_field_dist, centers_dist(clusters_neighbors_index[now_ball][j], now_ball) / 2);
                }

                for (unsigned int i = 0; i < now_num; i++)
                {

                    if (point_center_dist[now_ball][i] > stable_field_dist)
                    {
                        now_data_index.push_back(clusters_point_index[now_ball][i]);
                    }

                }


                data_num = now_data_index.size();

                if (data_num == 0)
                {
                    continue;
                }

                MatrixOur temp_distance = cal_ring_dist_noRing(data_num, dataset_cols, dataset, now_centers, now_data_index);

                cal_dist_num += data_num * now_centers.rows();


                unsigned int new_label;
                for (unsigned int i = 0; i < data_num; i++)
                {
                    temp_distance.row(i).minCoeff(&minCol);  //clusters_neighbors_index(minCol)

                    new_label = clusters_neighbors_index[now_ball][minCol];
                    if (labels[now_data_index[i]] != new_label)
                    {
                        flag(now_ball) = true;
                        flag(new_label) = true;

                        //Update localand global labels
                        vector<unsigned int>::iterator it = (temp_clusters_point_index[labels[now_data_index[i]]]).begin();
                        while ((it) != (temp_clusters_point_index[labels[now_data_index[i]]]).end())
                        {
                            if (*it == now_data_index[i])
                            {
                                it = (temp_clusters_point_index[labels[now_data_index[i]]]).erase(it);
                                break;
                            }
                            else
                            {
                                ++it;
                            }
                        }
                        temp_clusters_point_index[new_label].push_back(now_data_index[i]);
                        labels[now_data_index[i]] = new_label;
                    }
                }

            }

        }
        else
        {
            break;
        }
    }
    end_time = clock();

    if (detail == true)
    {
        cout << "ball-k-means without dividing ring:" << endl;
        cout << "k                :                  ||" << k << endl;
        cout << "iterations       :                  ||" << iteration_counter << endl;
        cout << "The number of calculating distance: ||" << cal_dist_num << endl;
        cout << "The number of neighbors:            ||" << num_of_neighbour << endl;
        cout << "Time per round：                    ||" << (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000 / iteration_counter << endl;

    }
    return labels;


}

MatrixOur load_data(const char* filename)
{
    /*

    *Summary: Read data through file path

    *Parameters:

    *     filename: file path.*    

    *Return : Dataset in eigen matrix format.

    */

    int x = 0, y = 0;  // x: rows  ，  y/x: cols
    ifstream inFile(filename, ios::in);
    string lineStr;
    while (getline(inFile, lineStr)) {
        stringstream ss(lineStr);
        string str;
        while (getline(ss, str, ','))
            y++;
        x++;
    }
    MatrixOur data(x, y / x);
    ifstream inFile2(filename, ios::in);
    string lineStr2;
    int i = 0;
    while (getline(inFile2, lineStr2)) {
        stringstream ss2(lineStr2);
        string str2;
        int j = 0;
        while (getline(ss2, str2, ',')) {
            data(i, j) = atof(const_cast<const char*>(str2.c_str()));
            j++;
        }
        i++;
    }
    return data;
}

inline MatrixOur
update_centroids(MatrixOur& dataset, ClusterIndexVector& cluster_point_index, unsigned int k, unsigned int n,
    VectorXb& flag, unsigned int iteration_counter, MatrixOur& old_centroids) {
    /*

    *Summary: Update the center point of each cluster

    *Parameters:

    *     dataset: dataset in eigen matrix format.*   

    *     clusters_point_index: global position of each point in the cluster.* 

    *     k: number of center points.*  

    *     dataset_cols: data set dimensions*  

    *     flag: judgment label for whether each cluster has changed.*  

    *     iteration_counter: number of iterations.*  

    *     old_centroids: center matrix of previous round.*  

    *Return : updated center matrix.

    */

    unsigned int cluster_point_index_size = 0;
    unsigned int temp_num = 0;
    MatrixOur new_c(k, n);
    VectorOur temp_array(n);
    for (unsigned int i = 0; i < k; i++) {
        temp_num = 0;
        temp_array.setZero();
        cluster_point_index_size = cluster_point_index[i].size();
        if (flag(i) != 0 || iteration_counter == 1) {
            for (unsigned int j = 0; j < cluster_point_index_size; j++) {
                temp_array += dataset.row(cluster_point_index[i][j]);
                temp_num++;
            }
            new_c.row(i) = temp_array / temp_num;
        }
        else new_c.row(i) = old_centroids.row(i);
    }
    return new_c;
}

inline void update_radius(MatrixOur& dataset, ClusterIndexVector& cluster_point_index, MatrixOur& new_centroids,
    ClusterDistVector& temp_dis, VectorOur& the_rs, VectorXb& flag, unsigned int iteration_counter,
    unsigned int& cal_dist_num, unsigned int the_rs_size) {

    /*

    *Summary: Update the radius of each cluster

    *Parameters:

    *     dataset: dataset in eigen matrix format.*   

    *     clusters_point_index: global position of each point in the cluster.* 

    *     new_centroids: updated center matrix.*  

    *     point_center_dist: distance from point in cluster to center*  

    *     the_rs: The radius of each cluster.*  

    *     flag: judgment label for whether each cluster has changed.*  

    *     iteration_counter: number of iterations.*  

    *     cal_dist_num: distance calculation times.* 

    *     the_rs_size: number of clusters.* 

    */

    OurType temp = 0;
    unsigned int cluster_point_index_size = 0;
    for (unsigned int i = 0; i < the_rs_size; i++) {
        cluster_point_index_size = cluster_point_index[i].size();
        if (flag(i) != 0 || iteration_counter == 1) {
            the_rs(i) = 0;
            temp_dis[i].clear();
            for (unsigned int j = 0; j < cluster_point_index_size; j++) {
                cal_dist_num++;
                temp = sqrt((new_centroids.row(i) - dataset.row(cluster_point_index[i][j])).squaredNorm());
                temp_dis[i].push_back(temp);
                if (the_rs(i) < temp) the_rs(i) = temp;
            }
        }
    }
};

bool LessSort(Neighbor a, Neighbor b) {
    return (a.distance < b.distance);
}
//todo
inline sortedNeighbors
get_sorted_neighbors_Ring(VectorOur& the_Rs, MatrixOur& centers_dis, unsigned int now_ball, unsigned int k,
    vector<unsigned int>& now_center_index) {

    /*

    *Summary: Get the sorted neighbors

    *Parameters:

    *     the_rs: the radius of each cluster.*   

    *     centers_dist: distance matrix between centers.* 

    *     now_ball: current ball label.*  

    *     k: number of center points*  

    *     now_center_index: nearest neighbor label of the current ball.*  

    */

    VectorXi flag = VectorXi::Zero(k);
    sortedNeighbors neighbors;

    Neighbor temp;
    temp.distance = 0;
    temp.index = now_ball;
    neighbors.push_back(temp);
    flag(now_ball) = 1;


    for (unsigned int j = 1; j < now_center_index.size(); j++) {
        if (centers_dis(now_ball, now_center_index[j]) == 0 ||
            2 * the_Rs(now_ball) - centers_dis(now_ball, now_center_index[j]) < 0) {
            flag(now_center_index[j]) = 1;
        }
        else {
            flag(now_center_index[j]) = 1;
            temp.distance = centers_dis(now_ball, now_center_index[j]);
            temp.index = now_center_index[j];
            neighbors.push_back(temp);
        }
    }


    for (unsigned int j = 0; j < k; j++) {
        if (flag(j) == 1) {
            continue;
        }
        if (centers_dis(now_ball, j) != 0 && 2 * the_Rs(now_ball) - centers_dis(now_ball, j) >= 0) {
            temp.distance = centers_dis(now_ball, j);
            temp.index = j;
            neighbors.push_back(temp);
        }

    }

    sort(neighbors.begin(), neighbors.end(), LessSort);
    return neighbors;
}

inline sortedNeighbors get_sorted_neighbors_noRing(VectorOur& the_rs, MatrixOur& centers_dist, unsigned int now_ball, unsigned int k, vector<unsigned int>& now_center_index)
{
    /*

    *Summary: Get the sorted neighbors

    *Parameters:

    *     the_rs: the radius of each cluster.*   

    *     centers_dist: distance matrix between centers.* 

    *     now_ball: current ball label.*  

    *     k: number of center points*  

    *     now_center_index: nearest neighbor label of the current ball.*  

    */

    VectorXi flag = VectorXi::Zero(k);
    sortedNeighbors neighbors;

    Neighbor temp;
    temp.distance = 0;
    temp.index = now_ball;
    neighbors.push_back(temp);
    flag(now_ball) = 1;


    for (unsigned int j = 1; j < now_center_index.size(); j++)
    {
        if (centers_dist(now_ball, now_center_index[j]) == 0 || 2 * the_rs(now_ball) - centers_dist(now_ball, now_center_index[j]) < 0)
        {
            flag(now_center_index[j]) = 1;
        }
        else {
            flag(now_center_index[j]) = 1;
            temp.distance = centers_dist(now_ball, now_center_index[j]);
            temp.index = now_center_index[j];
            neighbors.push_back(temp);
        }
    }


    for (unsigned int j = 0; j < k; j++)
    {
        if (flag(j) == 1)
        {
            continue;
        }
        if (centers_dist(now_ball, j) != 0 && 2 * the_rs(now_ball) - centers_dist(now_ball, j) >= 0)
        {
            temp.distance = centers_dist(now_ball, j);
            temp.index = j;
            neighbors.push_back(temp);
        }

    }


    return neighbors;
}

inline void
cal_centers_dist(MatrixOur& new_centroids, unsigned int iteration_counter, unsigned int k, VectorOur& the_rs,
    VectorOur& delta, MatrixOur& centers_dis) {

    /*

    *Summary: Calculate the distance matrix between center points

    *Parameters:

    *     new_centroids: current center matrix.*   

    *     iteration_counter: number of iterations.* 

    *     k: number of center points.*  

    *     the_rs: the radius of each cluster*  

    *     delta: distance between each center and the previous center.*  

    *     centers_dist: distance matrix between centers.*  

    */

    if (iteration_counter == 1) centers_dis = cal_dist(new_centroids, new_centroids).array().sqrt();
    else {
        for (unsigned int i = 0; i < k; i++) {
            for (unsigned int j = 0; j < k; j++) {
                if (centers_dis(i, j) >= 2 * the_rs(i) + delta(i) + delta(j))
                    centers_dis(i, j) = centers_dis(i, j) - delta(i) - delta(j);
                else {
                    centers_dis(i, j) = sqrt((new_centroids.row(i) - new_centroids.row(j)).squaredNorm());
                }
            }
        }
    }
}

inline MatrixOur cal_dist(MatrixOur& dataset, MatrixOur& centroids) {

    /*

    *Summary: Calculate distance matrix between dataset and center point

    *Parameters:

    *     dataset: dataset matrix.*   

    *     centroids: centroids matrix.* 

    *Return : distance matrix between dataset and center point.

    */

    return (((-2 * dataset * (centroids.transpose())).colwise() + dataset.rowwise().squaredNorm()).rowwise() +
        (centroids.rowwise().squaredNorm()).transpose());
}

inline MatrixOur
cal_ring_dist_Ring(unsigned j, unsigned int data_num, unsigned int dataset_cols, MatrixOur& dataset, MatrixOur& now_centers,
    ClusterIndexVector& now_data_index) {

    /*

    *Summary: Calculate the distance matrix from the point in the ring area to the corresponding nearest neighbor

    *Parameters:

    *     j: the label of the current ring.* 

    *     data_num: number of points in the ring area.*   

    *     dataset_cols: data set dimensions.* 

    *     dataset: dataset in eigen matrix format.* 

    *     now_centers: nearest ball center matrix corresponding to the current ball.* 

    *     now_data_index: labels for points in each ring.* 

    *Return : distance matrix from the point in the ring area to the corresponding nearest neighbor.

    */

    MatrixOur data_in_area(data_num, dataset_cols);

    for (unsigned int i = 0; i < data_num; i++) {
        data_in_area.row(i) = dataset.row(now_data_index[j - 1][i]);
    }

    Ref <MatrixOur> centers_to_cal(now_centers.topRows(j + 1));

    return (((-2 * data_in_area * (centers_to_cal.transpose())).colwise() +
        data_in_area.rowwise().squaredNorm()).rowwise() + (centers_to_cal.rowwise().squaredNorm()).transpose());
}

inline MatrixOur cal_ring_dist_noRing(unsigned int data_num, unsigned int dataset_cols, MatrixOur& dataset, MatrixOur& now_centers, vector<unsigned int>& now_data_index)
{
    /*

    *Summary: Calculate the distance matrix from the point in the ring area to the corresponding nearest neighbor

    *Parameters:

    *     data_num: number of points in the ring area.*   

    *     dataset_cols: data set dimensions.* 

    *     dataset: dataset in eigen matrix format.* 

    *     now_centers: nearest ball center matrix corresponding to the current ball.* 

    *     now_data_index: labels for points in the ring.* 

    *Return : distance matrix from the point in the ring area to the corresponding nearest neighbor.

    */

    MatrixOur data_in_area(data_num, dataset_cols);

    for (unsigned int i = 0; i < data_num; i++)
    {
        data_in_area.row(i) = dataset.row(now_data_index[i]);
    }

    return (((-2 * data_in_area * (now_centers.transpose())).colwise() + data_in_area.rowwise().squaredNorm()).rowwise() + (now_centers.rowwise().squaredNorm()).transpose());
}

void initialize(MatrixOur& dataset, MatrixOur& centroids, VectorXi& labels, ClusterIndexVector& cluster_point_index,
    ClusterIndexVector& clusters_neighbors_index, ClusterDistVector& temp_dis) {

    /*

    *Summary: Initialize related variables

    *Parameters:

    *     dataset: dataset in eigen matrix format.*   

    *     centroids: dcentroids matrix.* 

    *     labels: the label of the cluster where each data is located.* 

    *     clusters_point_index: two-dimensional vector of data point labels within each cluster.* 

    *     clusters_neighbors_index: two-dimensional vector of neighbor cluster labels for each cluster.* 

    *     point_center_dist: distance from point in cluster to center.* 

    */

    MatrixOur::Index minCol;
    for (int i = 0; i < centroids.rows(); i++) {
        cluster_point_index.push_back(vector<unsigned int>());
        clusters_neighbors_index.push_back(vector<unsigned int>());
        temp_dis.push_back(vector<OurType>());
    }
    MatrixOur M = cal_dist(dataset, centroids);
    for (int i = 0; i < dataset.rows(); i++) {
        M.row(i).minCoeff(&minCol);
        labels(i) = minCol;
        cluster_point_index[minCol].push_back(i);
    }
}


VectorXi ball_k_means(MatrixOur& dataset, MatrixOur& centroids, int isRing = 0, bool detail = false) {
    if (isRing == 1) {
        VectorXi labels = ball_k_means_Ring(dataset, centroids, detail);
        return labels;
    }
    else {
        VectorXi labels = ball_k_means_noRing(dataset, centroids, detail);
        return labels;
    }
    
}

int main(int argc, char* argv[])
{
    MatrixOur dataset = load_data("c:/users/yog/source/repos/test20/test20/data+centers/dataset/birchdata.csv");
    MatrixOur centroids = load_data("c:/users/yog/source/repos/test20/test20/data+centers/centroids/birch4.csv");
    VectorXi labels = ball_k_means(dataset, centroids, 0, true);

}
