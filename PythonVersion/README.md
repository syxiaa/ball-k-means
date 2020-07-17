# Python version:

* the implementation of the ball k-means algorithm is "ball_k_means_Xf.py" and "ball_k_means_Xd.py", which are code for "float" and "double" versions respectively..

* the param "isRing" is used to switch ring version and no ring version of the algorithm.

### Description of 'Xd' and 'Xf' versions：

* "Xd" means that data is stored and operated in the program in "double" type.

* "Xf" means that data is stored and operated in the program in "float" type.

* According to our experience, the "Xd" version can get more accurate results but the running time is slightly slower, and the "Xf" version can reach the fastest running time, but low accuracy will result in inaccurate results.

# Requirements

### Installation requirements (Python):

* Only need to rely on the DLL files in the "PythonVersion" file.

# Using

## python version:

### Step 1: declare class "ball_k_means" and initialize algorithm.

#### Parameters: 

* isRing: int type, switch the ring version and the no ring version of the algorithm. '1' means the current algorithm is a ring version, and others mean the current algorithm is no ring version.

### Step 2: call "fit" function

#### Parameters: 

* s1: absolute path of th csv file of clustering data.

* s2: absolute path of th csv file of initial center point data.

* detail: bool type variable, "true" means output detailed information (including k value, distance calculation times, time, etc.), "false" means no detailed information is output. The default is false.

#### Output: 

* m: labels of clustering data in numpy matrix format.
