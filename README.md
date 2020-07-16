# ball-k-means

* Implementations of ball k-means algorithms as described in xxxxxxx.

* ball_k_means_noRingVersion.cpp is the implementation of the ball k-means algorithm without dividing the ring area.

* ball_k_means_RingVersion.cpp is the implementation of the ball k-means algorithm with dividing the ring area.

* ball_kmean.rar is the Python version of the ball k-means algorithm.

# Requirements

### Minimal installation requirements (C++):

* C++ compiler supporting C++11
  
* Linux operating system or Windows operating system

* Eigen 3 template library

### Optional but recommended (C++):

* BLAS implementation, we recommend this one : http://www.openblas.net/
  
* Intel MKL implementation, we recommend this one :https://software.intel.com/en-us/mkl

# Installation (C++)

* Eigen 3: In order to use Eigen, you just need to download and extract Eigen's source code :http://eigen.tuxfamily.org/index.php?title=Main_Page#Download

* ball_k_means_noRingVersion.cpp and ball_k_means_RingVersion.cpp both can be executed directly, only need to import Eigen library.

# Using

* C++: In 'main' function, modify the location of the dataset and the centroids, loaded by the 'load_data' function.

* python: Unzip, then modify the location of the data and center point. In function 'ball_k_means', you can change the param 'isRing' ('0' represents the algorithm with ring area and others represents the algorithm with no ring area) to choose different version of the algorithm.

# Doesn't work?

* Please contact Yong Zheng at zhengyongv3@163.com
