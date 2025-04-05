Note the order of multiplication in the VertexIO shader.
Since the lm library uses column-major ordering we must
multiply vector into matrix for the product.

Let M be (n x n) matrix and v an n-vector.
Mv = b is typical but for the column order we use:
vM = b'

Be sure to set the glUniformMatrix4fv GL_ARB_transpose_matrix
argument to GL_FALSE.