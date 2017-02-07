macro(add_gtest_dependencies test)
  target_link_libraries(${test} gtest)
  if (${UNIX})
    target_link_libraries(${test} rt)
    target_link_libraries(${test} pthread)
    if (BUILD_SHARED_LIBS)
      target_link_libraries(${test} dl)
    endif()
  endif()
endmacro(add_gtest_dependencies)