cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_constructor_tests
   FILENAME "euclidean_vector_constructor_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_operation_tests
   FILENAME "euclidean_vector_operation_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_member_function_tests
   FILENAME "euclidean_vector_member_function_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_friends_tests
   FILENAME "euclidean_vector_friends_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)

cxx_test(
   TARGET euclidean_vector_utility_function_tests
   FILENAME "euclidean_vector_utility_function_tests.cpp"
   LINK euclidean_vector fmt::fmt-header-only
)