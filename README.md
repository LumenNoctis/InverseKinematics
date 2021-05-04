# InverseKinematics

This IK solver is my own aproach and take on inverse kinematics.

--------------------
Given an array of vectors (the "IK chain"), a starting point (or root of the chain) R and a target point T , the pocedure is as follows:

1 Iterate through and add up all the vectors in the chain to the starting point to get the position of the last point in the chain. Set the current position P to this point, and keep this point somewhere, it shall be the endpoint E.

2 Starting from the last point in the chain, iterate backwards.

3 Substract the current vector from P and set this as the current position.

4 To find the next position of the end point, we need to find the angle by which to rotate the current vector such that the endpoint is as close as possible to T. To do this we make a vector from P to T and from P to E. The angle between them is the angle by which we must rotate our vector.

5 We update E to the rotated position and go back to step 3 until we reach the beginning of the chain

6 This completes one iteration of the algorithm. One may continue until E gets abirtrarily close to T or until a certain number of iterations is reached

----

<img align="top" src="Ressources/IK.gif" />
