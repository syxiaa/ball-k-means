# Python version:

* the implementation of the ball k-means algorithm is "ball_k_means_Xf.py" and "ball_k_means_Xd.py", which are code for "float" and "double" versions respectively..

* the param "isRing" is used to switch ring version and no ring version of the algorithm.

* According to our experience, the "Xd" version can get more accurate results but the running time is slightly slower, and the "Xf" version can reach the fastest running time, but low accuracy will result in inaccurate results.

# Requirements

### Installation requirements (Python):

* Only need to rely on the DLL files in the "PythonVersion" file.

# Using

## python version:

### Step 1: declare class "ball_k_means" and initialize algorithm.

#### Parameters: 

* isRing: bool type, switch the ring version and the no ring version of the algorithm. "true" means the current algorithm is a ring version, and others mean the current algorithm is no ring version.

* detail: bool type, "true" means output detailed information (including k value, distance calculation times, time, etc.), "false" means no detailed information is output. The default is false.

### Step 2: call "fit" function

#### Parameters: 

* dataset: absolute path of th csv file of clustering data.

* centroids: absolute path of th csv file of initial center point data.

#### Output: 

* labels: labels of clustering data in numpy matrix format.
