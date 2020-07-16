# ball-k-means

* Implementations of ball k-means algorithms as described in xxxxxxx.

* the implementation of the ball k-means algorithm of the C++ version can be found in the 'C++Version' file.

* the implementation of the ball k-means algorithm of the Python version can be found in the 'PythonVersion' file.

### C++ version:

* the implementation of the ball k-means algorithm with dividing ring is 'ball_k_means_RingVersion_Xd.cpp' and 'ball_k_means_RingVersion_Xf.cpp'.

* the implementation of the ball k-means algorithm with dividing ring is 'ball_k_means_noRingVersion_Xd.cpp' and 'ball_k_means_noRingVersion_Xf.cpp'.

### Python version:

* the implementation of the ball k-means algorithm is 'ball_k_means_Xf.py' and 'ball_k_means_Xd.py'.


### Description of 'Xd' and 'Xf' versions：

* 'Xd' means that data is stored and operated in the program in double type.

* 'Xf' means that data is stored and operated in the program in float type.

* According to our experience, the 'Xd' version can get more accurate results but the running time is slightly slower, and the 'Xf' version can reach the fastest running time, but low accuracy will result in inaccurate results.

# Requirements

### Minimal installation requirements (C++):

* C++ compiler supporting C++11
  
* Linux operating system or Windows operating system

* Eigen 3 template library

### Optional but recommended (C++):

* BLAS implementation, we recommend this one: http://www.openblas.net/
  
* Intel MKL implementation, we recommend this one: https://software.intel.com/en-us/mkl


### Installation requirements (Python):

* Only need to rely on the dll files.

# Installation (C++)

* Eigen 3: In order to use Eigen, you just need to download and extract Eigen's source code: http://eigen.tuxfamily.org/index.php?title=Main_Page#Download

* ball_k_means_noRingVersion.cpp and ball_k_means_RingVersion.cpp both can be executed directly, only need to import Eigen library.

# Using

* C++: In 'main' function, modify the location of the dataset and the centroids, loaded by the 'load_data' function.

* python: modify the location of the data and center point. In function 'ball_k_means', you can change the param 'isRing' ('0' represents the algorithm with ring area and others represent the algorithm with no ring area) to choose the different version of the algorithm.

# Doesn't work?

* Please contact Yong Zheng at zhengyongv3@163.com
