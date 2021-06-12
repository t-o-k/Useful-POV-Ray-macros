# Useful POV-Ray macros

The include file vectors.inc for POV-Ray v3.7 contains these macros related to 3D vectors, transforms and transform functions:

## ScalarTripleProduct(vA, vB, vC)

Calculates the scalar triple product of the vectors vA, vB and vC.
It is equal to the determinand of the matrix represented by the row (or column) vectors vA, vB and vC.

https://en.wikipedia.org/wiki/Triple_product#Scalar_triple_product

## VectorTripleProduct(vA, vB, vC)

Calculates the vector triple product of the vectors vA, vB and vC.

https://en.wikipedia.org/wiki/Triple_product#Vector_triple_product

## VectorCos(vA, vB)

Calculates the cosine of the smallest angle between the vectors vA and vB.

The result is between -1 and +1, including the limits.

https://en.wikipedia.org/wiki/Multiplication_of_vectors

https://en.wikipedia.org/wiki/Dot_product#Geometric_definition

## VectorSin(vA, vB)

Calculates the sine of the smallest angle between the vectors vA and vB.

The result is between 0 and +1, including the limits.

https://en.wikipedia.org/wiki/Multiplication_of_vectors

https://en.wikipedia.org/wiki/Cross_product#Geometric_meaning

## AngleBetweenVectors(vA, vB)

Calculates the smallest angle between the vectors vA and vB.

The result is in radians between 0 and +pi, including the limits.

https://en.wikipedia.org/wiki/Dot_product#Geometric_definition

## AccurateAngleBetweenVectors(vA, vB)

Calculates the smallest angle between the vectors vA and vB.

The result is in radians between 0 and +pi, including the limits.

It is more accurate than the AngleBetweenVectors if the vectors are almost parallel or almost antiparallel.

## ScalarProject(vA, vB)

Calculates the scalar projection of the vector vA on the vector vB.

https://en.wikipedia.org/wiki/Vector_projection#Scalar_projection

https://en.wikipedia.org/wiki/Scalar_projection

## VectorProject(vA, vB)

Calculates the projection of the vector vA on the vector vB.

https://en.wikipedia.org/wiki/Vector_projection#Vector_projection

## ScalarReject(vA, vB)

Calculates the scalar rejection of the vector vA from the vector vB.

https://en.wikipedia.org/wiki/Vector_projection#Scalar_rejection

## VectorReject(vA, vB)

Calculates the vector rejection of the vector vA from the vector vB.

https://en.wikipedia.org/wiki/Vector_projection#Vector_rejection

## OrthogonalVector(v0)

Calculates, if possible, a normalized vector that is orthogonal to vector v0.

If v0 is the zero vector then the resulting vector is also the zero vector.

If the same vector is passed to both the OrthogonalVector() macro and the AltOrthogonalVector() macro, the returned vectors are orthogonal to each other in addition to being orthogonal to the vector passed to the macros.

## AltOrthogonalVector(v0)

Calculates, if possible, a normalized vector that is orthogonal to vector v0.

If v0 is the zero vector then the resulting vector is also the zero vector.

If the same vector is passed to both the AltOrthogonalVector() macro and the OrthogonalVector() macro, the returned vectors are orthogonal to each other in addition to being orthogonal to the vector passed to the macros.

## VectorAxisRotate(v0, vAxis, Angle)

Calculates the rotation of the vector v0 around the vector vAxis by the angle Angle in degrees.

Note that direction of rotation in POV-Ray's left handed coordinate system is opposite of rotations in right handed coordinate systems.

(The sign of the sine part in the macro is therefore negative.)

https://en.wikipedia.org/wiki/Rodrigues%27_rotation_formula

Note that POV-Ray has a built in vector operator; vaxis_rotate() that should be used instead.

## VectorReorient(v0, vFrom, vTo)

Calculates the result of the reorientation transformation from the vector vFrom to the vector vTo applied to the vector v0.

## FunctionValue(Fn, v0)

Evaluates the function Fn() at the coordinates in the v0 vector.

It works with both regular trivariate functions, transform functions and pattern functions.

## VectorTransform(v0, Transform)

Calculates result of the transformation Transform applied to the vector v0.

## VectorInverseTransform(v0, Transform)

Calculates result of the inverse of the transformation Transform applied to the vector v0.

## TransformFromVectors(vX, vY, vZ, pT)

Creates a tranformation given by a 4x3 matrix consiting of the row vectors vX, vY, vZ and pT.

The 3x3 matrix represented by the row vectors vX, vY and vZ must not be singular.

## TransformFromTransformFunction(TransformFn)

Creates a transformation from the transformation inherent in the transform function TransformFn().

## TransformFunctionFromTransform(Transform)

Creates a transform function from the transformation Transform.

## TransformFunctionFromVectors(vX, vY, vZ, pT)

Creates a tranform function from the transformation given by a 4x3 matrix consiting of the row vectors vX, vY, vZ and pT.

The 3x3 matrix represented by the row vectors vX, vY and vZ must not be singular. 

## VectorsFromTransformFunction(TransformFn, vX, vY, vZ, pT)

Extracts the row vectors vX, vY, vZ and pT from the 4x3 matrix inherent in the transform function TransformFn().

Vectors that are passed as arguments are set to new values. Variables for these vectors can be declared with either #local or #declare before calling the macro.

Example:

    #declare ReorientTransformFn = function { ReorientTransform(x - z, y) };
    #declare v_X = 0*x;
    #declare v_Y = 0*y;
    #declare v_Z = 0*z;
    #declare p_T = 0*x + 0*y + 0*z;
    VectorsFromTransformFunction(ReorientTransformFn, v_X, v_Y, v_Z, p_T)
    // The vectors v_X, v_Y, v_Z and p_T have now been set to the calculated vectors

## VectorsFromTransform(Transform, vX, vY, vZ, pT)

Extracts the row vectors vX, vY, vZ and pT from the 4x3 matrix inherent in the transform Transform.

The vectors that are passed as arguments are set to new values. Variables for these vectors can be declared with either #local (local scope) or #declare (global scope) before calling the macro.

Example:

    #local CompoundTransform =
        transform {
            scale <+3, -1, +2>
            AxisRotateTransform(<+1, +1, +1>, 30)
            translate <-2, +4, -2>
        }
    #local v_X = < 0,  0,  0>;
    #local v_Y = < 0,  0,  0>;
    #local v_Z = < 0,  0,  0>;
    #local p_T = < 0,  0,  0>;
    VectorsFromTransform(CompoundTransform, v_X, v_Y, v_Z, p_T)
    // The vectors v_X, v_Y, v_Z and p_T have now been set to the calculated vectors

## AxisRotateTransform(vAxis, Angle)

Creates a transformation that is a rotation around the vector vAxis by the angle Angle in degrees.

Note that direction of rotations in POV-Ray's left handed coordinate system is opposite of the direction of rotations in right handed coordinate systems.

## ReorientTransform(vFrom, vTo)

Creates a transformation that is a reorientation from the vector vFrom to the vector vTo.

The vectors vFrom and vTo must not be antiparallel.
