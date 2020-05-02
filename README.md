# ball-k-means

* Implementations of ball k-means algorithms as described in xxxxxxx.

* ball_k_means_noRingVersion.cpp is the implementation of the ball k-means algorithm without dividing the ring area.

* ball_k_means_RingVersion.cpp is the implementation of the ball k-means algorithm with dividing the ring area.

# Requirements

### Minimal installation requirements:

* C++ compiler supporting C++11
  
* Linux operating system or Windows operating system

* Eigen 3 template library

### Optional but recommended:

* BLAS implementation, we recommend this one : http://www.openblas.net/
  
* Intel MKL implementation, we recommend this one :https://software.intel.com/en-us/mkl

# Installation

* Eigen 3: In order to use Eigen, you just need to download and extract Eigen's source code :http://eigen.tuxfamily.org/index.php?title=Main_Page#Download

* ball_k_means_noRingVersion.cpp and ball_k_means_RingVersion.cpp both can be executed directly, only need to import Eigen library.

# Using

* In 'main' function, modify the location of the dataset and the centroids, loaded by the 'load_data' function.

* Then, run program.

# Doesn't work?

* Please contact Yong Zheng at zhengyongv3@163.com
