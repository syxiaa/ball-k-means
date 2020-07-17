# ball-k-means

* Implementations of ball k-means algorithms as described in https://ieeexplore.ieee.org/document/9139397.

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

* Only need to rely on the DLL files.

# Installation (C++)

* Eigen 3: In order to use Eigen, you just need to download and extract Eigen's source code: http://eigen.tuxfamily.org/index.php?title=Main_Page#Download

* ball_k_means_noRingVersion.cpp and ball_k_means_RingVersion.cpp both can be executed directly, only need to import Eigen library.

# Using

## C++ version:

### Call 'ball_k_means' function

#### Parameters: 

* dataset: clustering data in Matrix format in the Eigen library.

* centroids: initial center point data in matrix format in the Eigen library.

* detail: bool type variable, 'true' means output detailed information (including k value, distance calculation times, time, etc.), 'false' means no detailed information is output. The default is false.

#### Output: 

* labels: labels of clustering data in matrix format in the Eigen library.

## python version:

### Step1: declare class 'ball_k_means' and initialize algorithm.

#### Parameters: 

* isRing: int type, switch the ring version and the no ring version of the algorithm. '1' means the current algorithm is a ring version ,and others mean the current algorithm is no ring version.

### Step2: call 'fit' function

#### Parameters: 

* s1: absolute path of th csv file of clustering data.

* s2: absolute path of th csv file of initial center point data.

* detail: bool type variable, 'true' means output detailed information (including k value, distance calculation times, time, etc.), 'false' means no detailed information is output. The default is false.

#### Output: 

* m: labels of clustering data in numpy matrix format.

# Doesn't work?

* Please contact Yong Zheng at zhengyongv3@163.com
