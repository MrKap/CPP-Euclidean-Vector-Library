/*

  ---- Explanation and rationale of testing ----
*/

/*
 * The order the tests were written in was:
    - Constructor Tests
    - Operation tests
    - Member Function tests
    - Friends Tests
    - Utility function tests

  All the tests constructed are based on assumption that all previous functions that
  have been tested prior, are 'correct' and will not be further checked at each level.
  One exception to this was before constructor tests, where the subscript operator was created first
  in order to aid the testing process. All methods are tested in chronological order of the spec for
  correctness.


 ---Brittleness---  All of my tests are not brittle, as they only access the public methods and
specific implementations of the Euclidean Vector class, and should the implementation of the
eucldiean vector methods be changed, would not need to be changed. Further, the size of the eucidean
vector is only accessed through the public function of dimensions() and getSize() (and not directly
accessed).

---Clarity:--- All my tests are grouped into different files depending on what part of the spec they
cover (e.g. constructor tests in 1 file, operator tests in another file etc...), which makes it
extremely clear to see which part failed (should it fail). Further, within each grouped file, the
tests were labelled and split into different sections well.

--Coverage---- I believe my tests are very thorough and have covered almost all possibilities as I
tested all exceptions and many edge cases, and vectors of diffeerent sizes, vectors constructed in
different ways etc.. They helped me find many many bugs within my program, which can be evident
through git history. THe only tests not written are testing the cache for euclidean normal as that
was not implemented.

 */