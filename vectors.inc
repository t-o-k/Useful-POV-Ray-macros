// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
/*

https://github.com/t-o-k/Useful-POV-Ray-macros
Copyright (c) 2021 Tor Olav Kristensen, http://subcube.com
Use of this source code is governed by the GNU Lesser General Public License version 3,
which can be found in the LICENSE file.

Relevant Wikipedia articles:
https://en.wikipedia.org/wiki/Euclidean_vector
https://en.wikipedia.org/wiki/Multiplication_of_vectors
https://en.wikipedia.org/wiki/Scalar_projection
https://en.wikipedia.org/wiki/Vector_projection
https://en.wikipedia.org/wiki/Triple_product
https://en.wikipedia.org/wiki/Rotation_matrix
https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula
https://en.wikipedia.org/wiki/Euler%E2%80%93Rodrigues_formula

*/
// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#version 3.7;

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10

#macro ScalarTripleProduct(vA, vB, vC)

    vdot(vA, vcross(vB, vC))

#end // macro ScalarTripleProduct


#macro VectorTripleProduct(vA, vB, vC)

    vcross(vA, vcross(vB, vC))

#end // macro VectorTripleProduct


/*
// The version above is faster

#macro VectorTripleProduct(vA, vB, vC)

    (vdot(vA, vC)*vB - vdot(vA, vB)*vC)

#end // macro VectorTripleProduct
*/


#macro VectorCos(vA, vB)

    #local Dot = vdot(vnormalize(vA), vnormalize(vB));

    min(max(-1, Dot), +1)

#end // macro VectorCos


#macro VectorSin(vA, vB)

    #local vCross = vcross(vnormalize(vA), vnormalize(vB));

    min(vlength(vCross), +1)

#end // macro VectorSin


#macro AngleBetweenVectors(vA, vB)

    #local Dot = vdot(vnormalize(vA), vnormalize(vB));

    acos(min(max(-1, Dot ), +1))

#end // macro AngleBetweenVectors


// Use this version if the vectors may be almost parallel or antiparallel
// The version above is faster

#macro AccurateAngleBetweenVectors(v1, v2)

     #local v1n = vnormalize(v1);
     #local v2n = vnormalize(v2);

     (2*atan2(vlength(v1n - v2n), vlength(v1n + v2n)))

#end // macro AccurateAngleBetweenVectors


#macro ScalarProject(vA, vB)

    vdot(vA, vnormalize(vB))

#end // macro ScalarProject


#macro VectorProject(vA, vB)

    (vdot(vA, vB)/vdot(vB, vB)*vB)

#end // macro VectorProject


#macro ScalarReject(vA, vB)

    #local vP = vcross(vB, vcross(vA, vB));

    vdot(vA, vnormalize(vP))

#end // macro ScalarReject


#macro VectorReject(vA, vB)

    (vA - vdot(vA, vB)/vdot(vB, vB)*vB)

#end // macro VectorReject


#macro OrthogonalVector(v0)

   #if (vlength(v0) = 0)
      #local vN = <0, 0, 0>;
   #else
      #local Dm = min(abs(v0.x), abs(v0.y), abs(v0.z));
      #if (abs(v0.z) = Dm)
         #local vN = vnormalize(vcross(v0, z));
      #else
         #if (abs(v0.y) = Dm)
            #local vN = vnormalize(vcross(v0, y));
         #else
            #local vN = vnormalize(vcross(v0, x));
         #end // if
      #end // if
   #end // if

   vN

#end // macro OrthogonalVector


// Alternative to the version abvoe

#macro AltOrthogonalVector(v0)

    #switch (min(abs(v0.x), abs(v0.y), abs(v0.z)))
        #case (abs(v0.x))
            #local vE = x;
            #break
        #case (abs(v0.y))
            #local vE = y;
            #break
        #case (abs(v0.z))
            #local vE = z;
            #break
        #else
            #local vE = <0, 0, 0>;
    #end // switch
    #local vP = vdot(v0, v0)*vE - vdot(vE, v0)*v0;
    #if (vlength(vP) = 0)
        #local vN = <0, 0, 0>;
    #else
        #local vN = vnormalize(vP);
    #end // if

    vN

#end // macro AltOrthogonalVector


// Use built in vaxis_rotate() instead

#macro VectorAxisRotate(v0, vAxis, Angle)

    #local Phi = radians(Angle);
    #local vA = vnormalize(vAxis);
    #local v1 = vcross(v0, vA);
    #local v2 = vcross(v1, vA);

    (v0 - sin(Phi)*v1 + (1 - cos(Phi))*v2)

#end // macro VectorAxisRotate


#macro VectorReorient(v0, vFrom, vTo)

    #local vF = vnormalize(vFrom);
    #local vT = vnormalize(vTo);
    #local vAxis = vcross(vF, vT);
    #local Cos = vdot(vF, vT);
    #local Sin = vlength(vAxis);
    #if (Sin = 0)
        #local vR = (Cos < 0 ? -v0 : +v0);
    #else
        #local vA = vAxis/Sin;
        #local v1 = vcross(v0, vA);
        #local v2 = vcross(v1, vA);
        #local vR = v0 - Sin*v1 + (1 - Cos)*v2;
    #end // if

    vR

#end // macro VectorReorient


#macro FunctionValue(Fn, v0)

    Fn(v0.x, v0.y, v0.z)

#end // macro FunctionValue


#macro VectorTransform(v0, Transform)

    FunctionValue(function { transform { Transform } }, v0)

#end // macro VectorTransform


#macro VectorInverseTransform(v0, Transform)

    FunctionValue(function { transform { Transform inverse } }, v0)

#end // macro VectorInverseTransform


#macro MatrixTransform(vX, vY, vZ, pT)

    transform {
        matrix <
            vX.x, vX.y, vX.z,
            vY.x, vY.y, vY.z,
            vZ.x, vZ.y, vZ.z,
            pT.x, pT.y, pT.z
        >
    }

#end // macro MatrixTransform


#macro AxisRotateTransform(vAxis, Angle)

    MatrixTransform(
        vaxis_rotate(x, vAxis, Angle),
        vaxis_rotate(y, vAxis, Angle),
        vaxis_rotate(z, vAxis, Angle),
        <0, 0, 0>
    )

#end // macro AxisRotateTransform


#macro ReorientTransform(vFrom, vTo)

    #local vF = vnormalize(vFrom);
    #local vT = vnormalize(vTo);
    #local vAxis = vcross(vF, vT);
    #local Dot = min(max(-1, vdot(vF, vT)), +1);
    #local Angle = degrees(acos(Dot));

    MatrixTransform(
        vaxis_rotate(x, vAxis, Angle),
        vaxis_rotate(y, vAxis, Angle),
        vaxis_rotate(z, vAxis, Angle),
        <0, 0, 0>
    )

#end // macro ReorientTransform

// ===== 1 ======= 2 ======= 3 ======= 4 ======= 5 ======= 6 ======= 7 ======= 8 ======= 9 ======= 10
