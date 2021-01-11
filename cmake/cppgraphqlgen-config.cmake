# Copyright (c) Microsoft Corporation. All rights reserved.
# Licensed under the MIT License.

#[=======================================================================[.rst:
cppgraphqlgen
-------------

The following import targets are created

::

  cppgraphqlgen::graphqlpeg
  cppgraphqlgen::graphqlresponse
  cppgraphqlgen::graphqlservice
  cppgraphqlgen::graphqlintrospection
  cppgraphqlgen::graphqljson
  cppgraphqlgen::schemagen
#]=======================================================================]

include(CMakeFindDependencyMacro)
find_package(Threads REQUIRED)
include("${CMAKE_CURRENT_LIST_DIR}/cppgraphqlgen-targets.cmake")
