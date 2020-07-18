# ball-k-means

* Ball k-means algorithms is described in detail in https://ieeexplore.ieee.org/document/9139397.

* the implementation of the ball k-means algorithm of the C++ version can be found in the "C++Version" file.

* the implementation of the ball k-means algorithm of the Python version can be found in the "PythonVersion" file.

* All data used in the paper is in the compressed file "data+centers(1).zip".

### C++/Python version (C++/python 版本):

* the implementations of the ball k-means algorithm are "ball_k_means_Xf.cpp"/"ball_k_means_Xf.py" and "ball_k_means_Xd.cpp"/"ball_k_means_Xd.py", which are code for "float" and "double" versions respectively.

* the param "isRing" is used to switch the ring version and the no ring version of the algorithm.

* According to our experience, the "Xd" version can get more accurate results but the running time is slightly slower than "Xf"; the "Xf" version can reach the fastest running time, but low accuracy may result in many decimal places of data .

# Requirements (环境要求)

### Minimal installation requirements (C++) (最低需要安装要求):

* C++ compiler supporting C++11
  
* Linux operating system or Windows operating system

* Eigen 3 template library

### Optional but recommended (C++) (可选安装要求但建议):

* BLAS implementation, we recommend this one: http://www.openblas.net/
  
* Intel MKL implementation, we recommend this one: https://software.intel.com/en-us/mkl


### Installation requirements (Python) (安装要求):

* Only need to rely on the DLL files in the "PythonVersion" file.

# Installation (C++) (安装)

* Eigen 3: In order to use Eigen, you just need to download and extract Eigen's source code: http://eigen.tuxfamily.org/index.php?title=Main_Page#Download

* ball_k_means_noRingVersion.cpp and ball_k_means_RingVersion.cpp both can be executed directly, only need to import Eigen library.

# Using (用法)

### C++ version (C++ 版本):

##### Step 1: call "ball_k_means" function

###### Parameters: 

* dataset: clustering data in Matrix format in the Eigen library.

* centroids: initial center point data in matrix format in the Eigen library.

* isRing: bool type, switch the ring version and the no ring version of the algorithm. "true" means the current algorithm is a ring version, and "false" means the current algorithm is no ring version. The default is false.

* detail: bool type, "true" means output detailed information (including k value, distance calculation times, time, etc.), "false" means no detailed information is output. The default is false.

###### Output: 

* labels: labels of clustering data in matrix format in the Eigen library.

### python version:

##### Step 1: declare class "ball_k_means" and initialize algorithm.

###### Parameters: 

* isRing: bool type, switch the ring version and the no ring version of the algorithm. "true" means the current algorithm is a ring version, and "false" means the current algorithm is no ring version. The default is false.

* detail: bool type, "true" means output detailed information (including k value, distance calculation times, time, etc.), "false" means no detailed information is output. The default is false.

##### Step 2: call "fit" function

###### Parameters: 

* dataset: absolute path of th csv file of clustering data.

* centroids: absolute path of th csv file of initial center point data.

###### Output: 

* labels: labels of clustering data in numpy matrix format.

# Doesn't work?

* Please contact Yong Zheng at zhengyongv3@163.com
